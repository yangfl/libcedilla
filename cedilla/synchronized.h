#ifndef CEDILLA_SYNCHRONIZED_H
#define CEDILLA_SYNCHRONIZED_H

#include <pthread.h>
#include <threads.h>

/**
 * @file
 * @brief #synchronized() and #try_synchronized() statements.
 */


/// @cond GARABGE
#define __synchronized_concat_impl(x, y) x ## y
#define __synchronized_concat(x, y) __synchronized_concat_impl(x, y)
#define __synchronized_generate(counter, expr, end) \
  void __synchronized_concat(__synchronized_func_, counter) (void *) { end; }; \
  if (__builtin_expect(expr, 1)) switch (1) \
    for (__attribute__((unused, cleanup(__synchronized_concat(__synchronized_func_, counter)))) \
         char __synchronized_concat(__synchronized_var_, counter); 0;) case 1: \
/// @endcond

/**
 * @brief Run a block of code after acquiring a lock, and release it when
 *  leaving the block.
 *
 * @code{.c}
  pthread_synchronized (mtx)
    puts("Lock acquired!");
 * @endcode
 *
 * @param lock The lock to acquire.
 */
#define pthread_synchronized(lock) __synchronized_generate( \
  __COUNTER__, pthread_mutex_lock(lock) == 0, pthread_mutex_unlock(lock))
/**
 * @brief Run a block of code after acquiring a lock, and release it when
 *  leaving the block.
 *
 * @code{.c}
  pthread_try_synchronized (mtx)
    puts("Lock acquired!");
  else
    puts("Lock not acquired!");
 * @endcode
 *
 * @param lock The lock to acquire.
 */
#define pthread_try_synchronized(lock) __synchronized_generate( \
  __COUNTER__, pthread_mutex_trylock(lock) == 0, pthread_mutex_unlock(lock))
/**
 * @brief Run a block of code after acquiring a lock, and release it when
 *  leaving the block.
 *
 * @code{.c}
  pthread_timed_synchronized (mtx, time)
    puts("Lock acquired!");
  else
    puts("Lock not acquired!");
 * @endcode
 *
 * @param lock The lock to acquire.
 * @param time Timeout specification.
 */
#define pthread_timed_synchronized(lock, time) __synchronized_generate( \
  __COUNTER__, pthread_mutex_timedlock(lock, time) == 0, pthread_mutex_unlock(lock))

/**
 * @brief Run a block of code after acquiring a lock, and release it when
 *  leaving the block.
 *
 * @code{.c}
  threads_synchronized (mtx)
    puts("Lock acquired!");
 * @endcode
 *
 * @param lock The lock to acquire.
 */
#define threads_synchronized(lock) __synchronized_generate( \
  __COUNTER__, mtx_lock(lock) == thrd_success, mtx_unlock(lock))
/**
 * @brief Run a block of code after acquiring a lock, and release it when
 *  leaving the block.
 *
 * @code{.c}
  threads_try_synchronized (mtx)
    puts("Lock acquired!");
  else
    puts("Lock not acquired!");
 * @endcode
 *
 * @param lock The lock to acquire.
 */
#define threads_try_synchronized(lock) __synchronized_generate( \
  __COUNTER__, mtx_trylock(lock) == thrd_success, mtx_unlock(lock))
/**
 * @brief Run a block of code after acquiring a lock, and release it when
 *  leaving the block.
 *
 * @code{.c}
  threads_timed_synchronized (mtx, time)
    puts("Lock acquired!");
  else
    puts("Lock not acquired!");
 * @endcode
 *
 * @param lock The lock to acquire.
 * @param time Timeout specification.
 */
#define threads_timed_synchronized(lock, time) __synchronized_generate( \
  __COUNTER__, mtx_timedock(lock, time) == thrd_success, mtx_unlock(lock))

#ifdef CEDILLA_SYNCHRONIZED_USE_PTHREAD
  #define synchronized pthread_synchronized
  #define try_synchronized pthread_try_synchronized
  #define timed_synchronized pthread_timed_synchronized
#else
  #define synchronized threads_synchronized
  #define try_synchronized threads_try_synchronized
  #define timed_synchronized threads_timed_synchronized
#endif

#endif /* CEDILLA_SYNCHRONIZED_H */
