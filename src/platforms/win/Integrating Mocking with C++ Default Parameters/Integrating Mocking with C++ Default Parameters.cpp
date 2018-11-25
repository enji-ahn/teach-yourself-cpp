// Integrating Mocking with C++ Default Parameters.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>

class ILogger {
public:
	virtual void log(int value) const = 0;
};

class LoggerMock : public ILogger {
public:
	void log(int value) const override { /* do nothing */ };
};

class Logger : public ILogger {
public:
	void log(int value) const override { printf("value : %d\n", value); }
};

int f(int x, int y) {
	return x * y;
}

int f1(int x, int y, const ILogger& logger) {
	logger.log(x * y);
	return x * y;
}

int f2(int x, int y, const ILogger& logger = Logger()) {
	logger.log(x * y);
	return x * y;
}

using LoggerSeam = ILogger;
int f3(int x, int y, const LoggerSeam& logger = Logger()) {
	logger.log(x * y);
	return x * y;
}

int main()
{
	f (3, 4);
	f1(3, 4, Logger());
	f2(3, 4);
	f3(3, 4);

	std::getchar();
    return 0;
}

