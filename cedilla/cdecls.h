#ifndef CEDILLA_CDECLS_H
#define CEDILLA_CDECLS_H

/**
 * @file
 * @brief Handle C and C++ code in one header file.
 */


#ifdef __cplusplus
# define BEGIN_C_DECLS extern "C" {
# define END_C_DECLS }
# define C_INLINE(decl, body) decl;
# define C_ONLY(...) /* empty */
# define CXX_ONLY(x) x
#else
/**
 * @brief Used (along with #C_END_DECLS) to bracket header files.
 *
 * @code{.c}
  BEGIN_C_DECLS
  // C function declarations
  END_C_DECLS
 * @endcode
 *
 * If the compiler in use is a C++ compiler, adds extern "C" around the header.
 */
# define BEGIN_C_DECLS /* empty */
/**
 * @brief Used (along with #C_BEGIN_DECLS) to bracket header files.
 *
 * If the compiler in use is a C++ compiler, adds extern "C" around the header.
 */
# define END_C_DECLS /* empty */
/**
 * @brief Declare a C-style inline (not static) function.
 *
 * @code{.c}
  C_INLINE(int func(int x), {
    return x * x;
  })

  // C++ see
  int func(int x);
  // C see
  inline int func(int x) {
    return x * x;
  }
 * @endcode
 *
 * You should always use `extern inline` to produce the object of the function
 * in a source file.
 *
 * @param decl Function declaration, without the leading `inline`.
 * @param body Function body, enclosed in braces.
 */
# define C_INLINE(decl, body) inline decl body
/**
 * @brief Mark a C only code.
 *
 * @code{.c}
  C_ONLY("C see this")
  CXX_ONLY("C++ see this")
 * @endcode
 *
 * @param ... C only code.
 */
# define C_ONLY(x) x
/**
 * @brief Mark a C++ only code.
 *
 * @code{.c}
  C_ONLY("C see this")
  CXX_ONLY("C++ see this")
 * @endcode
 *
 * @param ... C++ only code.
 */
# define CXX_ONLY(...) /* empty */
#endif


#endif /* CEDILLA_CDECLS_H */
