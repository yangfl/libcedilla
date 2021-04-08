#ifndef CEDILLA_VALUABLE_H
#define CEDILLA_VALUABLE_H

/**
 * @file
 * @brief Macros that give a value.
 */

#ifndef likely
/**
 * @brief Hint the compiler that the expression is likely to evaluate to
 *  @c true.
 *
 * The compiler may use this information for optimizations.
 *
 * @code{.c}
  if likely (random() != 1)
    puts("not one");
 * @endcode
 *
 * @param x A numeric value.
 * @return The value of @p x.
 */
# define likely(x) (__builtin_expect(!!(x), 1))
#endif
#ifndef unlikely
/**
 * @brief Hint the compiler that the expression is likely to evaluate to
 *  @c false.
 *
 * The compiler may use this information for optimizations.
 *
 * @code{.c}
  if unlikely (random() == 1)
    puts("a random one");
 * @endcode
 *
 * @param x A numeric value.
 * @return The value of @p x.
 */
# define unlikely(x) (__builtin_expect(!!(x), 0))
#endif

#ifndef max
/**
 * @brief Calculate the maximum of @p a and @p b.
 *
 * @param a A numeric value.
 * @param b A numeric value.
 * @return The maximum.
 */
# define max(a,b) ((a) > (b) ? (a) : (b))
#endif
#ifndef min
/**
 * @brief Calculate the minimum of @p a and @p b.
 *
 * @param a A numeric value.
 * @param b A numeric value.
 * @return The minimum.
 */
# define min(a,b) ((a) < (b) ? (a) : (b))
#endif
#ifndef cmp
/**
 * @brief Compare @p a with @p b.
 *
 * @param a A numeric value.
 * @param b A numeric value.
 * @return If `a < b`, return -1; if `a > b`, return 1; if equal, return 0.
 */
# define cmp(a,b) ((a) < (b) ? -1 : (a) > (b))
#endif

#ifndef arraysize
/**
 * @brief Tell the number of elements in an array.
 *
 * @param x An array.
 */
# define arraysize(x) (sizeof(x) / sizeof((x)[0]))
#endif
#ifndef arraylen
# define arraylen arraysize
#endif
#ifndef NITEMS
# define NITEMS arraysize
#endif
#ifndef NELEMS
# define NELEMS arraysize
#endif
#ifndef ARRAY_LEN
# define ARRAY_LEN arraysize
#endif
#ifndef ARRAY_LENGTH
# define ARRAY_LENGTH arraysize
#endif

#ifndef membersize
/**
 * @brief Tell the size of a member in a structure.
 *
 * @param type The type of the structure.
 * @param member The member of the structure.
 */
# define membersize(type, member) sizeof(((type *) 0)->member)
#endif
#ifndef member_size
# define member_size membersize
#endif
#ifndef sizeof_member
# define sizeof_member membersize
#endif
#ifndef MEMBER_SIZE
# define MEMBER_SIZE membersize
#endif


#endif /* CEDILLA_VALUABLE_H */
