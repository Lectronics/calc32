#ifndef _STACK_HPP
#define _STACK_HPP

#include "viennamath/forwards.h"

enum stack_types_t {
    STACK_NO_TYPE,
    STACK_INTEGER,
    STACK_FLOAT_E,
    STACK_FLOAT_S,
    STACK_FLOAT_D,
    STACK_FLOAT,
    STACK_VARIABLE,
    STACK_EXPRESSION,
    STACK_VECTOR,
    STACK_MATRIX,
    STACK_ERROR
};

struct stack_val_t {
    stack_types_t val_type;
    union {

    } val;
};

class calc32Stack {};

#endif // _STACK_HPP