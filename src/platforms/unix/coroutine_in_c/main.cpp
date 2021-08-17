// dllmain.cpp : Defines the entry point for the DLL application.
// ref : http://www.vishalchovatiya.com/coroutine-in-c-language/
#include "stdafx.h"
#include <ucontext.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "coroutine.hpp"

int hello(coro_t* coro) {
  printf("Hello, ");
  coro_yield(coro, 1);
  printf("SeungRye");
  return 2;
}

int world(coro_t* coro) {
  printf("World ");
  coro_yield(coro, 3);
  puts("!");
  return 4;
}

int main(int argc, char *argv[]) {
  coro_t *coro1 = coro_new(hello);
  coro_t *coro2 = coro_new(world);
  assert(coro_resume(coro1) == 1);
  assert(coro_resume(coro2) == 3);
  assert(coro_resume(coro1) == 2);
  assert(coro_resume(coro2) == 4);
  coro_free(coro1);
  coro_free(coro2);
  return 0;
}