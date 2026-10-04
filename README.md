# ESP32 S3 based RPN Calculator

## Objectives:
- Functionalty to rival the HP42
- Parts list that costs less that $50
- Symbolic Math Solver
- Vector / Matrix Operations
- EE / Mechanical toolkits
- Allowed on Math / Engineering tests (since HP48, HP49, HP50g are not)

## General Notes:
- Built on ViennaMath-1.0.0 (Added as my own "fork" of viennamath ported to esp32's Cmake configuration)
- Matrix / Vector operations are built on Eigen (hopefully assuming that the program flash size is large enough.)

## Build:
<nothing yet>

## Hardware Description:
#### Processor:
    ESP32-S3
#### Screen:
    SSD1309 (SPI Version for faster screen operations)
#### Voltage Requirements:
    4.5v (From 3 or 6 AA Batteries)
    3.7v from LI-Ion (with recharging from the ESP32's USBc Port with applicable board)
#### Tactile Switches:
    Cheap Momentarys (easy to replace)
    Cheap mechanical keys for keyboards (Good because they are rated for a lot of cycles)
#### Other stuff:
    Resistors, Capacitors, Bus Wire, Perf-Board


## Program Description / Flow:
The program is split up into _ seperate parts:
- Physical Input / Decoding
- Character Display
- String -> Typed Variable decode
- RPN Stack Management (This does NOT refer to the stack program memory)
- Operators (Type Checking, "Casting", and Operation)
- Exception Handling

Updates That will hopefully be added in the future:
- File System (FAT32)
- Added Functionality via external applications
- Graphing / Programming build

The system works on a defined list of types that a value on the stack may belong to.
The types tell the operators how to use the values. When there are two dissimilar types
that are passed to a function, the operator may "promote" one type to be compatible with 
the operation being preformed. to determine if this promotion may take place, we will assign
each type a "priority." Any value may promoted to the type of the highest priority, however 
a type may not be promoted to a type of a lower priority. Thus demotion is not allowed 
with these types. Colloquiolly, the list of types in priority order is:

1. error
2. matrix
3. vector
4. expression
5. variable
6. float
    - Engineering
    - Scientific
    - Decimal
7. integer
8. zero


### Physical Imput / Decoding
There are not enough GPIO Pins on most of the ESP32S3 boards to route 40 buttons to the ESP 
and have room left over for a screen. Therefore, The hope is to have the buttons "Multiplexed"
so that any button gives a unique 5-bit code (giving 31 unique keys). 
(The function modifier keys will be seperate GPIOs to make the input processing more straight forward)

For the full list of key-code mappings, see [components/input/key_mappings.h](components/input/inc/key_mappings.h)

#### Function Buttons:
The function buttons will be mapped each to their own pin with high priority ISRs set up.
The appropriate flag in the global ["Modifier Flags"]("path/to/file") variable (With it's mutex (binary semaphore))
is set, and the ["Modification Available"]("path/to/file") flag also gets set to tell the input
decoder to check the ["Modifier Flags"]("path/to/file"). 
The flag re-directs the decode to a seperate key-code mapping also found in the key-codes mapping file:
[components/input/key_mappings.h](components/input/inc/key_mappings.h)


### Character Display:
The buttons are split up into 2 categories:
1. String buttons
2. Operations

The string buttons are relevant to this section. They are the set of buttons that 
yield some sort of addition or modification to the displayed **characters**. 
This may be in the form of a single character, multiple characters, or a change in formatting.

During the input process, characters are appended to the input line (internally and externally,
but as seperate processes to speed up execution). The function "append_char(char)" calls two underlying
functions to update the display and the internal string(s). One function appends a character to the display,
and the other appends a character to the string tracking the baby value that currently has focus. 

#### Space as input delimiter:
During regular input, the space acts as the seperator between values that will be put on the stack.
During the input, the values are rendered as if they are in line, however under the hood, the "baby values"
are held as seperate strings in a vector, which aids in the speed of string->value conversion later.

Any space immediately following a space is discarded, thus any whitespace counts as only a single space.
We may implement this by not allowing the space button to do anything if the last character was a space.

NOTE from my later self:
The "baby values" idea is pretty awful. It creates so many more problems than it solves, like for instance, how
in the world are you supposed to negate a value?


#### Matrix / Vector Inputs:
Matrix / vector input is defined by square brackets. Anything that happens inside the square brackets will be
decoded as matrix values. If all goes according to plan, matricies will be able to hold expressions or numbers.
During matrix or vector input, spaces are used as the delimiters for columns, and commas are used as the delimiters
for rows. For example, a matrix in the input stage that looks like this:

    [5 6 7,1 2 3,9 8 4] //NOTE: space after a comma does NOT count as a new value indicator. 
                                Any amount of whitespace after a comma should be ignored. 

Would be interpreted as:

        |-----------------|
        |  5  |  6  |  7  |
        |-----------------|
        |  1  |  2  |  3  |
        |-----------------|
        |  9  |  8  |  4  |
        |-----------------|

#### Variable / Expression Inputs:
In nature, variables, like vectors are a subset of matricies, are a subset of expressions. 
By default, for any input string that has a character, or group of characters,  

#### Display of values once they are on the stack:
Each stack value type has a seperate preferred format. Since this format is going to be different that that of the 
input text in most cases, the strings that were built during input are discarded immediately after they are decoded
into their corresponding stack values, and a "display string" is built from the value.

Again here, text that is displayed, and actual value under the hood are seperate. 
For the time being, they are kept together via a struct. The struct will be put in a vector that is essentially
the stack.

#### the +/- key:
The "+/-" key is a special string button that modifies current input by searching backwards through the string to
find the last character of homogeneous type (this will either be a variable-number junction, or at a space. If
at a space, the negative would apply regardless of matrix, expression, or numeric input.)

#### the EE key:
The EE key is a special string button that changes how numbers are displayed. Every float value by default has the
ability to be displayed in scientific notation, but will not start being displayed that way until there are at
least 3 zeros before or after the decimal point.

## String -> Typed Variable decode:
Rules for string decoding:
- Any strictly numeric string will be immediately converted into a float as long as there are not more than one decimal point. 
- integer values will not be assumed therefore, to get an int value, the user will have to use the "toint()" function
- Any string that is enclosed in square brackets [] will be decoded as a Matrix / vector.
- Any string that is enclosed in quotes "" will be decoded as an expression as long as at least one variable exists in the quotes. Otherwise, it will be decoded as numeric or invalid.
- E is not an acceptable variable to use sandwiched between two numeric types.
    If n and m are both numeric values, the string "nEm" will be translated: "n * 10^m"
- A letter or string sandwiched between two numeric values (with or without spaces) will be interpreted as a variable.

String decoding takes place when the user clicks the enter button. (The enter button will just be a normal key.)
the decode function will iterate through the input string, seperating based on the rules provided:
1. consecutive homogeneous characters are all part of the same value.
2. A space delimiter signifies the end of a value
3. expression definitions inside of matrix definitions are illegal (for now)
4. matrix definitions inside of expressions are illegal
5. nested matrix definitions are illegal
6. nested expression definitions are illegal
7. a matrix defiition begins with [ and ends with ]
8. spaces inside a matrix definition delimit column values along the current row
9. commas inside a matrix definition delimit rows. 
10. 2D matricies with uneven row lengths are illegal
11. an expression definition begins with " and ends with "


## RPN Stack Management (This does NOT refer to the stack program memory)
## Operators (Type Checking, "Casting", and Operation)
## Exception Handling