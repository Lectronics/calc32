#ifndef _OPERATORS_H
#define _OPERATORS_H

#include "stack.h"


enum op_arg_type {
    ONE_SCAL,
    ONE_MAT,
    ONE_ARR,
    ONE_SYM,

    TWO_SCAL_SCAL,
    TWO_SCAL_MAT,
    TWO_SCAL_ARR,
    TWO_SCAL_SYM,

    TWO_MAT_SCAL,
    TWO_MAT_MAT,
    TWO_MAT_ARR,
    TWO_MAT_SYM,

    TWO_ARR_SCAL,
    TWO_ARR_MAT,
    TWO_ARR_ARR,
    TWO_ARR_SYM,

    TWO_SYM_SCAL,
    TWO_SYM_MAT,
    TWO_SYM_ARR,
    TWO_SYM_SYM,
};

// Supporting Functions:
op_arg_type get_one_arg(const std::vector<stack_val_t>& operational_stack);
op_arg_type get_two_arg(const std::vector<stack_val_t>& operational_stack);


// ******************************************
// **       General Operations             **
// ******************************************

// Basic Operations:
void op_add(std::vector<stack_val_t>& stack);
void op_subtract(std::vector<stack_val_t>& stack);
void op_multiply(std::vector<stack_val_t>& stack);
void op_divide(std::vector<stack_val_t>& stack);
void op_exponent(std::vector<stack_val_t>& stack);
void op_square(std::vector<stack_val_t>& stack);
void op_sqrt(std::vector<stack_val_t>& stack);
void op_root(std::vector<stack_val_t>& stack);

// Trancendental Operations
//      Exponentials:
void op_etox(std::vector<stack_val_t>& stack);
void op_ln(std::vector<stack_val_t>& stack);
void op_tentox(std::vector<stack_val_t>& stack);
void op_log(std::vector<stack_val_t>& stack);

// Basic Trig:
void op_sin(std::vector<stack_val_t>& stack);
void op_cos(std::vector<stack_val_t>& stack);
void op_tan(std::vector<stack_val_t>& stack);
void op_arcsin(std::vector<stack_val_t>& stack);
void op_arccos(std::vector<stack_val_t>& stack);
void op_arctan(std::vector<stack_val_t>& stack);
void op_arctan2(std::vector<stack_val_t>& stack);

// Constants:
void op_e(std::vector<stack_val_t>& stack);
void op_pi(std::vector<stack_val_t>& stack);



// **************************************************
// **          Type Specific Operations            **
// **************************************************

// Scalar Operations:
void op_scal_add(std::vector<stack_val_t>& stack);
void op_scal_subtract(std::vector<stack_val_t>& stack);
void op_scal_multiply(std::vector<stack_val_t>& stack);
void op_scal_divide(std::vector<stack_val_t>& stack);
void op_scal_exponent(std::vector<stack_val_t>& stack);
void op_scal_square(std::vector<stack_val_t>& stack);
void op_scal_sqrt(std::vector<stack_val_t>& stack);
void op_scal_root(std::vector<stack_val_t>& stack);
// Trancendental Operations
//      Exponentials:
void op_scal_ln(std::vector<stack_val_t>& stack);
void op_scal_tentox(std::vector<stack_val_t>& stack);
void op_scal_log(std::vector<stack_val_t>& stack);
// Basic Trig:
void op_scal_sin(std::vector<stack_val_t>& stack);
void op_scal_cos(std::vector<stack_val_t>& stack);
void op_scal_tan(std::vector<stack_val_t>& stack);
void op_scal_arcsin(std::vector<stack_val_t>& stack);
void op_scal_arccos(std::vector<stack_val_t>& stack);
void op_scal_arctan(std::vector<stack_val_t>& stack);
void op_scal_arctan2(std::vector<stack_val_t>& stack);
// Scalar Conversions:
void op_scal_to_arr(std::vector<stack_val_t>& stack);
void op_scal_to_mat(std::vector<stack_val_t>& stack);
void op_scal_to_sym(std::vector<stack_val_t>& stack);



// Matrix / Vector Operations
void op_mat_det(std::vector<stack_val_t>& stack);
void op_mat_norm(std::vector<stack_val_t>& stack);
void op_mat_to_arr(std::vector<stack_val_t>& stack);
void op_vec_unit(std::vector<stack_val_t>& stack);
void op_vec_magnitude(std::vector<stack_val_t>& stack);
void op_vec_cross(std::vector<stack_val_t>& stack);
void op_vec_dot(std::vector<stack_val_t>& stack);


// Array Operations:
void op_arr_add_mat(std::vector<stack_val_t>& stack);
void op_arr_add_scal(std::vector<stack_val_t>& stack);
void op_arr_subtract_mat(std::vector<stack_val_t>& stack);
void op_arr_subtract_scal(std::vector<stack_val_t>& stack);
void op_arr_mul_mat(std::vector<stack_val_t>& stack);
void op_arr_mul_scal(std::vector<stack_val_t>& stack);
void op_arr_div_mat(std::vector<stack_val_t>& stack);
void op_arr_div_scal(std::vector<stack_val_t>& stack);
// Trancendental Operations
//      Exponentials:
void op_arr_ln(std::vector<stack_val_t>& stack);
void op_arr_tentox(std::vector<stack_val_t>& stack);
void op_arr_log(std::vector<stack_val_t>& stack);
// Basic Trig:
void op_arr_sin(std::vector<stack_val_t>& stack);
void op_arr_cos(std::vector<stack_val_t>& stack);
void op_arr_tan(std::vector<stack_val_t>& stack);
void op_arr_arcsin(std::vector<stack_val_t>& stack);
void op_arr_arccos(std::vector<stack_val_t>& stack);
void op_arr_arctan(std::vector<stack_val_t>& stack);
void op_arr_arctan2(std::vector<stack_val_t>& stack);


// Symbolic Operations



//
#endif // _OPERATORS_H