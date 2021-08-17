#ifndef __COROUTINE_HPP__
#define __COROUTINE_HPP__
// ref : http://www.vishalchovatiya.com/coroutine-in-c-language/

#include <unistd.h>
#include <ucontext.h>

typedef struct coro_t_ coro_t;
typedef int (*coro_function_t)(coro_t *coro);

/* 
 * Coroutine handler
 */
struct coro_t_ {
    coro_function_t     function;           // Actual co-routine function
    ucontext_t          suspend_context;    // Stores context previous to coroutine jump
    ucontext_t          resume_context;     // Stores coroutine context
    int                 yield_value;        // Coroutine return/yield value
    bool                is_coro_finished;   // To indicate the current coroutine status
};

/* 
 * Coroutine APIs for users
 */
coro_t *coro_new(coro_function_t function);
int coro_resume(coro_t *coro);    
void coro_yield(coro_t *coro, int value);
void coro_free(coro_t *coro);

#endif // __COROUTINE_HPP__