Feature: raising exceptions

  Scenario Outline: handle <exception>
    Given unputed "<expression>" in entry
    When we press calculate button
    Then we will get "<exception>" exception



    Examples: exceptions
      | expression | exception                                                                         |
      | 2/0        | Ошибка во время вычисления / !                                                    |
      | sqrt(-1)   | Ошибка во время вычисления sqrt !                                                 |
      | ((2+1)     | в выражении не согласованы скобки                                                 |
      | 1..01 + 2  | Ошибка во время токенизации: Некорректное число 1..01 !                           |
      | 1.1!       | Ошибка во время вычисления ! !                                                    |
      | 1,1 + 2,2  | Проблема с разделителем - вероятно, использована десятичная запятая вместо точки! |