#ifndef CEDILLA_YIELD_H
#define CEDILLA_YIELD_H

#define __yield_generate(counter) \
  if (stack->counter = counter, 0) { case counter:; } else return
#define yield __yield_generate(__COUNTER__)

#define generate switch (__COUNTER__, stack->counter) case 0:

#endif /* CEDILLA_YIELD_H */
