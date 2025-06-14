## Python expression calculator
![](https://view-counter.tobyhagan.com/?user={0SouthBoss0}/{expression-calculator})

This calculator allows you to calculate mathematical expressions. Various mathematical functions, trigonometric functions and operations are supported. Parentheses are supported for grouping expressions.

### Features
* Arithmetic operations:
  * addition (+)
  * subtraction (-)
  * multiplication (*)
  * division (/)
  * exponentiation (^)
  * remainder (%)
* Trigonometric functions:
  * sin (sin)
  * cos (cos)
  * tan (tan)
  * cot (cot)
* Other mathematical functions:
  * natural logarithm (ln)
  * square root (sqrt)
  * factorial (fact or !)
  * logarithm with custom base (log(a, b))
  * minimal of two (min(a, b))
  * maximum of two (max(a, b))
 
### Algorithm base

The algorithm is based on tokenizing input expression and sorting tokens in Shunting yard algorithm (https://en.wikipedia.org/wiki/Shunting_yard_algorithm). The expression is converted to a string of postfix notation, also known as reverse Polish notation (RPN), and then its result is calculated.

### Technologies used
* Basic language is Python with GUI on Tkinter and math and numpy modules for logic
* Tests are written on unittest
* Behavior Driven Development (BDD) is written on Behave framework
