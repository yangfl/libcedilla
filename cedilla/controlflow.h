#ifndef CEDILLA_CONTROLFLOW_H
#define CEDILLA_CONTROLFLOW_H

/**
 * @file
 * @brief Meaningful control flow statements.
 */


/**
 * @brief Indicate a test should success.
 *
 * If the test fails, an error should have happened.
 *
 * This keyword should always be used with #otherwise.
 *
 * @code{.c}
  should (fopen("/tmp/a", "w") != NULL) otherwise puts("Cannot open file!");
 * @endcode
 *
 * @param test The test expression.
 */
#define should(test) if likely (test) {
/**
 * @brief Tell what to do if an error happens.
 *
 * This keyword should always be used with #should.
 */
#define otherwise } else

/**
 * @brief Make a breakable code block.
 *
 * @c break statement is available in the block.
 *
 * @code{.c}
  if (write_log) do_once {
    if (log_does_not_exist) break;
    write();
  }
 * @endcode
 */
#define do_once switch (1) case 1:

/**
 * @brief Execute the former block after the latter block.
 *
 * If a @c break or @c return happens in the latter block, the former block is
 * not executed.
 *
 * This keyword should always be used with #after.
 *
 * @code{.c}
  run printf("world!\n"); after printf("Hello ");
  // Hello world!
 * @endcode
 */
#define run switch (1) while (1) if (1) {
/// Used with #run.
#define after ; break;} else case 1:

/**
 * @brief Make a goto-able code block.
 *
 * @c break statement is available in the block.
 *
 * @code{.c}
  ...
  goto fail;
  named_block(unused): {
    // never exectued
    exit(0);
  }
  named_block(fail): {
    exit(1);
  }
  ...
 * @endcode
 *
 * @param name name of the block
 */
#define named_block(name) if (0) name: switch (1) case 1

/**
 * @brief Return from a function if the test succeeds.
 *
 * @param expr The test expression.
 */
#define return_if(expr) if (expr) return
/**
 * @brief Return from a function if the test fails.
 *
 * @param expr The test expression.
 */
#define return_if_not(expr) if (!(expr)) return
/**
 * @brief Return from a function if the test should succeed but fails.
 *
 * @param expr The test expression.
 */
#define return_if_fail(expr) if unlikely (!(expr)) return
/**
 * @brief Return from a function with the given value if the value is not zero.
 *
 * @param expr The test expression.
 */
#define return_nonzero(expr) do { \
  int __res = (expr); \
  return_if_fail (__res == 0) __res; \
} while (0)

/**
 * @brief Break from a code block if the test succeeds.
 *
 * @param expr The test expression.
 */
#define break_if(expr) if (expr) break
/**
 * @brief Break from a code block if the test fails.
 *
 * @param expr The test expression.
 */
#define break_if_not(expr) if (!(expr)) break
/**
 * @brief Break from a code block if the test should succeed but fails.
 *
 * @param expr The test expression.
 */
#define break_if_fail(expr) if unlikely (!(expr)) break

/**
 * @brief Continue from a code block if the test succeeds.
 *
 * @param expr The test expression.
 */
#define continue_if(expr) if (expr) continue
/**
 * @brief Continue from a code block if the test fails.
 *
 * @param expr The test expression.
 */
#define continue_if_not(expr) if (!(expr)) continue
/**
 * @brief Continue from a code block if the test should succeed but fails.
 *
 * @param expr The test expression.
 */
#define continue_if_fail(expr) if unlikely (!(expr)) continue

/**
 * @brief @c goto a label if the test succeeds.
 *
 * @param expr The test expression.
 */
#define goto_if(expr) if (expr) goto
/**
 * @brief @c goto a label if the test fails.
 *
 * @param expr The test expression.
 */
#define goto_if_not(expr) if (!(expr)) goto
/**
 * @brief @c goto a label if the test should succeed but fails.
 *
 * @param expr The test expression.
 */
#define goto_if_fail(expr) if unlikely (!(expr)) goto
/**
 * @brief @c goto a label if the value is not zero, and save the value to
 *  @c ret.
 *
 * @param expr The test expression.
 */
#define goto_nonzero(expr) if unlikely ((ret = (expr)) != 0) goto

/**
 * @brief @c goto a label if the test should succeed but fails, and save
 *  @p errnum to @c ret.
 *
 * @param expr The test expression.
 * @param errnum The error number to save.
 */
#define test_goto(expr, errnum) should (expr) otherwise \
  if (ret = (errnum), 1) goto

/**
 * @brief Hint the compiler that the expression can not be evaluated to @c true.
 *
 * The compiler may use this information for optimizations.
 *
 * @param expr The test expression that can not be evaluated to @c true.
 */
#define promise(expr) if (!(expr)) __builtin_unreachable()

/// @cond GARABGE
#define __defer_concat_impl(x, y) x ## y
#define __defer_concat(x, y) __defer_concat_impl(x, y)
#define __defer_generate(counter) \
  auto void __defer_concat(__defer_func_, counter) (void *); \
  __attribute__((unused, cleanup(__defer_concat(__defer_func_, counter)))) \
  char __defer_concat(__defer_var_, counter); \
  void __defer_concat(__defer_func_, counter) (void *)
/// @endcond
/**
 * @brief Execute a block of code at the end of the current scope.
 *
 * @code{.c}
  FILE *f = fopen("/etc/passwd", "r");
  defer {
    puts("Closing file");
    fclose(f));
  }
 * @endcode
 */
#define defer __defer_generate(__COUNTER__)


#endif /* CEDILLA_CONTROLFLOW_H */
