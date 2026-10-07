The purpose of this file is to take a string that was conglomerated during input and determining:
1. whether the string is valid 
2. how many stack spaces need to be taken up
3. what operands need to converted immediately for an operation
4. whether any operations need to take place


This calculator is built on the C++ library ViennaMath 1.0.0 and thus uses as 
the various stack types, the builtin types in viennamath, however for optimization
the numeric types will only be promoted to a different type IF it is required by
an operator, and that conversion will happen inside the operator.

Note that Eigen will be used for the vector operations, if possible.
The only constraint here is space, We have not compiled ViennaMath yet, so there
is no estimation on how needy it will be.


The stack can take values of a few different types (in priority order):
-  ERROR
- 


The rules for strings in input are:
