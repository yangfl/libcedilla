#ifndef CEDILLA_TWOVALUE_H
#define CEDILLA_TWOVALUE_H

#include <complex.h>

/**
 * @file
 * @brief Return two values from one function.
 */

#if __SIZEOF_SHORT__ == __SIZEOF_SIZE_T__
typedef short _Complex twovalue_t;
#elif __SIZEOF_INT__ == __SIZEOF_SIZE_T__
typedef int _Complex twovalue_t;
#elif __SIZEOF_LONG__ == __SIZEOF_SIZE_T__
typedef long _Complex twovalue_t;
#elif __SIZEOF_LONG_LONG__ == __SIZEOF_SIZE_T__
typedef long long _Complex twovalue_t;
#else
# error "Can't find a type matching __SIZEOF_SIZE_T__"
#endif

#define TWOVALUE(x, y) (x + y * _Complex_I)

#define twovalue_bind(expr, y) __extension__ ({ \
  twovalue_t __twovalue_bind_tmp = (expr); \
  *(y) = __imag__ __twovalue_bind_tmp; \
  __real__ __twovalue_bind_tmp; \
})

#define twovalue_use(expr) (__real__ (expr))

#endif /* CEDILLA_TWOVALUE_H */
