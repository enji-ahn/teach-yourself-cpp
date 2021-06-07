// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <algorithm>
#include <asio.hpp>
#include <cassert>
#include <cctype>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <stopwatch.hpp>
#include <string>
#include <thread>
#include <tuple>

stopwatch stop_watch;

auto save_image(const std::string URL, const std::string file_name, bool log = false) -> void {
  std::string site;
  std::string page;
  std::tie(site, page) = [](std::string url) -> std::pair<std::string, std::string> {
    auto make_lower = [](std::string s) -> std::string {
      std::transform(s.begin(), s.end(), s.begin(), ::tolower);
      return s;
    };
    auto trim = [](std::string s) -> std::string {
      auto trimmable = [](unsigned char ch) -> bool { return !std::isspace(ch); };
      s.erase(s.begin(), std::find_if(s.begin(), s.end(), trimmable));
      s.erase(std::find_if(s.rbegin(), s.rend(), trimmable).base(), s.end());
      return s;
    };

    url = make_lower(url);
    url = trim(url);
    const auto PREFIX = std::string("http://");
    assert(url.find(PREFIX) == 0);
    // auto found = url.find_last_of('/');
    auto found = url.find('/', PREFIX.length());

    auto offset = PREFIX.length();
    auto len = found - PREFIX.length();
    std::string site = url.substr(offset, len);

    offset = found;
    std::string page = url.substr(offset);

    return std::make_pair(site, page);
  }(URL);

  if (log) {
    std::cout << "site : " << site << std::endl;
    std::cout << "page : " << page << std::endl;
  }

  asio::io_service io_service;

  // Get a list of endpoints corresponding to the server name.
  asio::ip::tcp::resolver resolver(io_service);
  asio::ip::tcp::resolver::query query(site, "http");
  asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

  // Try each endpoint until we successfully establish a connection.
  asio::ip::tcp::socket socket(io_service);
  asio::connect(socket, endpoint_iterator);

  // Form the request. We specify the "Connection: close" header so that the
  // server will close the socket after transmitting the response. This will
  // allow us to treat all data up until the EOF as the content.
  asio::streambuf request;
  std::ostream request_stream(&request);
  request_stream << "GET " << page << " HTTP/1.1\r\n";
  request_stream << "Host: " << site << "\r\n";
  request_stream << "Connection: keep-alive\r\n";
  request_stream << "Pragma: no-cache\r\n";
  request_stream << "Cache-Control: no-cache\r\n";
  request_stream << "DNT: 1\r\n";
  request_stream << "Upgrade-Insecure-Requests: 1\r\n";
  request_stream << "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.77 Safari/537.36 Edg/91.0.864.41\r\n";
  request_stream << "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\n";
  request_stream << "Accept-Encoding: gzip, deflate\r\n";
  request_stream << "Accept-Language: ko,en-US;q=0.9,en;q=0.8,ca;q=0.7,da;q=0.6\r\n\r\n";

  // Send the request.
  asio::write(socket, request);

  // Read the response status line. The response streambuf will automatically
  // grow to accommodate the entire line. The growth may be limited by passing
  // a maximum size to the streambuf constructor.
  asio::streambuf response;
  asio::read_until(socket, response, "\r\n");

  // Check that response is OK.
  std::istream response_stream(&response);
  std::string http_version;
  response_stream >> http_version;
  unsigned int status_code;
  response_stream >> status_code;
  std::string status_message;
  std::getline(response_stream, status_message);
  if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
    std::cout << "ERRORED: Invalid response\n";
    return;
  }
  if (status_code != 200) {
    std::cout << "ERRORED: Response returned with status code " << status_code << "\n";
    return;
  }

  // Read the response headers, which are terminated by a blank line.
  asio::read_until(socket, response, "\r\n\r\n");

  // Process the response headers.
  std::string header;
  while (std::getline(response_stream, header) && header != "\r") {
    if (log) {
      std::cout << header << "\n";
    }
  }
  std::cout << "\n";

  std::ofstream file;
  file.open(file_name, std::ios::out | std::ios::binary);

  // Read until EOF, writing data to output as we go.
  asio::error_code error;
  while (asio::read(socket, response, asio::transfer_at_least(1), error)) {
    file << &response;
  }
  file.close();

  if (error != asio::error::eof) {
    std::cout << "ERRORED: " << error.message() << std::endl;
  }
}

auto async_fn(const std::string URL) -> std::thread {
  std::thread t([URL]() {
    save_image(URL, "image.png");
    std::cout << "async end : " << stop_watch.elapsed(false) << std::endl;
  });
  return t;
}

int main(int argc, char *argv[]) {
  stop_watch.reset();
  auto t = async_fn("http://www.korea.edu/dext5editordata/2020/12/20201210_093034568_30817.png");
  std::cout << "cur time : " << stop_watch.elapsed(false) << std::endl;
  t.join();
  std::cout << "end time : " << stop_watch.elapsed(false) << std::endl;
  return 0;
}