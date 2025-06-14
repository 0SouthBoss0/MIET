import math

import numpy as np


class CalculatorException(Exception):
    pass


class CalculatorToken:
    priority_dict = {"+": 1, "-": 1, "%": 1, "/": 2, "*": 2, "^": 3, "~": 4}

    def __init__(self, t_type, t_value):
        self.t_type = t_type
        self.t_value = t_value

        if t_type == "Operator":
            self.t_priority = self.priority_dict[t_value]

    def __eq__(self, other):
        return self.t_type == other.t_type and self.t_value == other.t_value


def save_number_buff(tokenized_input: list, number_buff: str, add_mult=False) -> tuple[list, str]:
    """
    Function to save number buffer to tokenized_input
    :param tokenized_input: list of tokenized expression
    :param number_buff: number buffer
    :param add_mult: flag to add mult operator
    :return: tuple with updated tokenized_input and cleaned number buffer
    """
    try:
        float(number_buff)
    except ValueError:
        raise CalculatorException(f"Некорректное число {number_buff} !")
    tokenized_input.append(CalculatorToken("Digit", number_buff))
    if add_mult:
        tokenized_input.append(CalculatorToken("Operator", "*"))
    return tokenized_input, ""


def save_letter_buff(tokenized_input: list, letter_buff: str) -> tuple[list, str]:
    """
    Function to save letter buffer to tokenized_input
    :param tokenized_input: list of tokenized expression
    :param letter_buff: letter buffer
    :return: tuple with updated tokenized_input and cleaned letter buffer
    """
    tokenized_input.append(CalculatorToken("Function", letter_buff))
    return tokenized_input, ""


def save_constants(tokenized_input: list, letter_buff: str) -> tuple[list, str] | CalculatorException:
    """
    Function to save constants in letter buffer to tokenized_input
    :param tokenized_input: list of tokenized expression
    :param letter_buff: letter buffer
    :return: tuple with updated tokenized_input and cleaned letter buffer
    """
    if letter_buff == "pi" or letter_buff == "π":
        tokenized_input.append(CalculatorToken("Digit", np.pi))
    elif letter_buff == "e":
        tokenized_input.append(CalculatorToken("Digit", np.e))
    else:
        raise CalculatorException(f"Некорректное значение: {letter_buff}")
    return tokenized_input, ""


def factorial_check(a):
    """
    Function to check if factorial parameter is an integer
    :param a: factorial parameter
    :return: factorial value of parameter or CalculatorException
    """
    if a.is_integer():
        return math.factorial(int(a))
    else:
        raise CalculatorException("Невозможно вычислить факториал нецелого числа!")


class Model:
    def __init__(self):
        pass

    def evaluate(self, expression: list[CalculatorToken]):
        """
        Function to evaluate expression in Reverse Polish Notation (RPN)
        Algorithm taken from https://www.geeksforgeeks.org/evaluation-of-postfix-expression/?ysclid=m3a2cblkdp275675497
        :param expression: list with CalculatorTokens sorted in RPN
        :return: value of evaluated expression
        """
        stack = []
        unary_dict = {"~": lambda a: -a, "sin": lambda a: np.sin(a), "cos": lambda a: np.cos(a),
                      "tan": lambda a: np.tan(a), "cot": lambda a: 1 / np.tan(a), "sqrt": lambda a: math.sqrt(a),
                      "ln": lambda a: math.log(a), "fact": factorial_check,
                      "!": factorial_check}
        binary_dict = {"+": lambda a, b: a + b, "-": lambda a, b: a - b, "/": lambda a, b: a / b,
                       "*": lambda a, b: a * b, "^": lambda a, b: a ** b, "log": lambda a, b: math.log(b, a),
                       "min": lambda a, b: min(a, b), "max": lambda a, b: max(a, b), "%": lambda a, b: a % b}

        for token in expression:
            if token.t_type == "Digit":
                # token is a digit -> push to stack
                stack.append(float(token.t_value))
            else:
                if token.t_value in binary_dict:
                    # token is a binary operator or function
                    try:
                        a = stack.pop()
                        b = stack.pop()
                    except IndexError as err:
                        raise CalculatorException(
                            f"Некорректное выражение. Проверьте корректность использования {token.t_value} !")
                    try:
                        stack.append(binary_dict[token.t_value](b, a))
                    except KeyError as err:
                        raise CalculatorException(f"Функции {token.t_value} не существует!")
                    except Exception as err:
                        raise CalculatorException(f"Ошибка во время вычисления {token.t_value} !")
                else:
                    # token is a unary operator or function
                    try:
                        stack.append(unary_dict[token.t_value](stack.pop()))
                    except KeyError as err:
                        raise CalculatorException(f"Функции {token.t_value} не существует!")
                    except Exception as err:
                        raise CalculatorException(f"Ошибка во время вычисления {token.t_value} !")

        try:
            return stack.pop()
        except Exception as err:
            raise CalculatorException(f"Некорректное выражение!")

    def input_tokenize(self, input_string: str) -> list:
        """
        Function to parse and tokenize input expression for CalculatorToken objects
        Algorithm taken from https://proglib.io/p/math-expression-tokenizer?ysclid=m3a11zy0gv176555469
        :param input_string: expression inputted
        :return: list of CalculatorToken objects
        """
        tokenized_input = []
        operators = ["+", "-", "*", "/", "%", "^"]

        number_buffer = ""
        letter_buffer = ""
        try:
            for i, symbol in enumerate(input_string.replace(" ", "")):
                if symbol.isdigit():
                    # if symbol is a digit -> send symbol to number buffer
                    number_buffer += symbol

                elif symbol.isalpha():
                    # if symbol is a letter -> save number buffer and send symbol to letter buffer
                    if len(number_buffer) > 0:
                        tokenized_input, number_buffer = save_number_buff(tokenized_input, number_buffer, add_mult=True)
                    letter_buffer += symbol

                elif symbol == "!":
                    # checking for postfix factorial function
                    if len(number_buffer) > 0:
                        tokenized_input, number_buffer = save_number_buff(tokenized_input, number_buffer)
                    tokenized_input.append(CalculatorToken("Function", symbol))

                elif symbol in operators:
                    # if symbol is an operator -> save number buffer and check for constants in letter buffer
                    if len(number_buffer) > 0:
                        tokenized_input, number_buffer = save_number_buff(tokenized_input, number_buffer)
                    if len(letter_buffer) > 0:
                        tokenized_input, letter_buffer = save_constants(tokenized_input, letter_buffer)

                    # checking if minus is unary minus -> if it is a first char or previous token is OpenBracket
                    if symbol == "-" and (
                            i == 0 or (i > 1 and input_string.replace(" ", "")[i - 1] in operators + ["("])):
                        symbol = "~"
                    tokenized_input.append(CalculatorToken("Operator", symbol))

                elif symbol == "(":
                    # if symbol is a OpenBracket -> save letter buffer and number buffer
                    if len(tokenized_input) > 0 and tokenized_input[-1].t_type == "CloseBracket":
                        # checking for ignored multiply operator in construction as (1+2)(3+4)
                        tokenized_input.append(CalculatorToken("Operator", "*"))

                    if len(letter_buffer) > 0:
                        tokenized_input, letter_buffer = save_letter_buff(tokenized_input, letter_buffer)

                    elif len(number_buffer) > 0:
                        tokenized_input, number_buffer = save_number_buff(tokenized_input, number_buffer, add_mult=True)
                    tokenized_input.append(CalculatorToken("OpenBracket", symbol))

                elif symbol == ")":
                    # if symbol is a CloseBracket -> save number buffer and check for constants in letter buffer
                    if len(number_buffer) > 0:
                        tokenized_input, number_buffer = save_number_buff(tokenized_input, number_buffer)
                    if len(letter_buffer) > 0:
                        tokenized_input, letter_buffer = save_constants(tokenized_input, letter_buffer)
                    tokenized_input.append(CalculatorToken("CloseBracket", symbol))

                elif symbol == ".":
                    # if symbol is a decimal point -> send symbol to number buffer
                    number_buffer += "."

                elif symbol == ",":
                    # if symbol is a delimiter -> save number buffer and check for constants in letter buffer
                    if len(number_buffer) > 0:
                        tokenized_input, number_buffer = save_number_buff(tokenized_input, number_buffer)
                    if len(letter_buffer) > 0:
                        tokenized_input, letter_buffer = save_constants(tokenized_input, letter_buffer)
                    tokenized_input.append(CalculatorToken("Separator", symbol))
                else:
                    raise CalculatorException(f'Некорректный символ в выражении - {symbol}')

            # after-saving number buffer
            if len(number_buffer) > 0:
                tokenized_input, number_buffer = save_number_buff(tokenized_input, number_buffer)
            # after-saving letter buffer
            if len(letter_buffer) > 0:
                tokenized_input, letter_buffer = save_constants(tokenized_input, letter_buffer)
        except CalculatorException as e:
            raise CalculatorException(f'Ошибка во время токенизации: {e}')
        return tokenized_input

    def sort_machine_algo(self, parsed_tokens: list[CalculatorToken]):
        """
        Realizationg of Shunting yard algorithm
        Taken from https://en.wikipedia.org/wiki/Shunting_yard_algorithm (without separators)
        and https://habr.com/ru/articles/777368/ (with separators)
        :param parsed_tokens: CalculatorTokens of inputted expression
        :return: list with CalculatorTokens in a postfix notation string, also known as reverse Polish notation (RPN)
        """
        queue = []
        stack = []
        for token in parsed_tokens:
            match token.t_type:
                case "Digit":
                    # token is a digit -> put it into the output queue
                    queue.append(token)

                case "Function":
                    # token is a function -> push it onto the operator stack
                    if token.t_value == "!":
                        # handling postfix factorial function
                        queue.append(token)
                    else:
                        stack.append(token)

                case "OpenBracket":
                    # token in an OpenBracket -> push it onto the operator stack
                    stack.append(token)

                case "CloseBracket":
                    # token in an CloseBracket
                    try:
                        # while the operator at the top of the operator stack is not a OpenBracket
                        while stack[-1].t_type != "OpenBracket":
                            # pop the operator from the operator stack into the output queue
                            queue.append(stack.pop())
                        else:
                            # pop the OpenBracket from the operator stack and discard it
                            stack.pop()
                        if len(stack) > 0 and stack[-1].t_type == "Function":
                            # if there is a function token at the top of the operator stack ->
                            # pop the function from the operator stack into the output queue
                            queue.append(stack.pop())

                    except IndexError as err:
                        raise CalculatorException(
                            f"В выражении либо неверно поставлен разделитель, либо не согласованы скобки!")

                case "Separator":
                    # while the operator at the top of the operator stack is not a OpenBracket
                    try:
                        while stack[-1].t_type != "OpenBracket":
                            # pop the operator from the operator stack into the output queue
                            queue.append(stack.pop())

                    except IndexError as err:
                        raise CalculatorException(
                            f"Проблема с разделителем - вероятно, использована десятичная запятая вместо точки!")

                case "Operator":
                    # while there is an operator o2 at the top of the operator stack
                    # and o2 has same or greater precedence than o1
                    while (len(stack) > 0 and stack[-1].t_type == "Operator" and
                           stack[-1].t_priority >= token.t_priority):
                        # pop o2 from the operator stack into the output queue
                        queue.append(stack.pop())
                    # push o1 onto the operator stack
                    stack.append(token)

        while len(stack) > 0:
            # while there are tokens on the operator stack
            temp = stack.pop()
            if temp.t_type != "Operator":
                # there are mismatched parentheses
                raise CalculatorException("в выражении не согласованы скобки")
            else:
                #  pop the operator from the operator stack onto the output queue
                queue.append(temp)
        return queue
