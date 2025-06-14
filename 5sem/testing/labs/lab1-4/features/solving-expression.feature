Feature: solving expression

  Scenario Outline: Calculate <expression>
    Given unputed "<expression>" in entry
    When we press calculate button
    Then we will get "<result>" in result


    Examples: one operation expressions
      | expression | result |
      | 2+3        | 5.0    |
      | 3-2        | 1.0    |
      | 2-3        | -1.0   |
      | 2*3        | 6.0    |
      | 4/2        | 2.0    |
      | 3*3        | 9.0    |
      | 4%3        | 1.0    |
      | 2^3        | 8.0    |
      | 2^3        | 8.0    |
      | -1-3       | -4.0   |

    Examples: many operation expressions
      | expression  | result |
      | 2+3+4       | 9.0    |
      | 3-2+5       | 6.0    |
      | 3-(2+5)     | -4.0   |
      | (2-3)+(3-4) | -2.0   |
      | 4*(2+3)     | 20.0   |
      | 4(2+3)      | 20.0   |
      | -4(-2+3)    | -4.0   |
      | 4(-2-(-3))  | 4.0    |
      | 2+2*2       | 6.0    |

    Examples: long expressions
      | expression                                                                                              | result              |
      | 15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1))) | -30.072164948453608 |


    Examples: trigonometric expressions
      | expression                                                     | result             |
      | (sin(2pi * (3 + (4 / (5 - 2)))) ^ 2) / (1 + (sin(pi / 4)) ^ 3) | 0.5540970937771961 |

    Examples: function  expressions
      | expression | result |
      | fact(3)    | 6      |
      | 3!         | 6      |
      | min(2, 5)  | 2.0    |
      | max(-2, 5) | 5.0    |
      | log(2, 64) | 6.0    |
      | ln(e)      | 1.0    |