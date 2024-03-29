#include <stdlib.h>
#include "coroutine.hpp"

#define MINSIGSTKSZ (16 * 1024)

static void _coro_entry_point(coro_t* coro) {
  int return_value = coro->function(coro);
  coro->is_coro_finished = true;
  coro_yield(coro, return_value);
}

void coro_yield(coro_t* coro, int value) {
  coro->yield_value = value;
  swapcontext(&(coro->resume_context),
              &(coro->suspend_context));
}

coro_t* coro_new(coro_function_t function) {
  coro_t *coro = (coro_t*)calloc(1, sizeof(*coro));
  coro->is_coro_finished = false;
  coro->function = function;
  coro->resume_context.uc_stack.ss_sp = (coro_t*)calloc(1, MINSIGSTKSZ);
  coro->resume_context.uc_stack.ss_size = MINSIGSTKSZ;
  coro->resume_context.uc_link = 0;

  getcontext(&(coro->resume_context));
  makecontext(&(coro->resume_context),
              (void (*)())_coro_entry_point,
              1,
              coro);
  return coro;
}

void coro_free(coro_t* coro) {
  free(coro->resume_context.uc_stack.ss_sp);
  free(coro);
}

int coro_resume(coro_t* coro) {
    if (coro->is_coro_finished)
      return -1;
    swapcontext(&(coro->suspend_context),
                &(coro->resume_context));
    return coro->yield_value;
}
