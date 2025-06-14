import unittest
from unittest.mock import patch, MagicMock, Mock, call

import numpy as np

from model import Model
from view import View
from presenter import Presenter
from model import CalculatorToken
from model import CalculatorException


class TestModel(unittest.TestCase):
    def setUp(self) -> None:
        self.model = Model()

    def test_input_tokenize_sum2(self):
        self.assertEqual(self.model.input_tokenize("2+3"),
                         [CalculatorToken("Digit", "2"), CalculatorToken("Operator", "+"),
                          CalculatorToken("Digit", "3")])

    def test_input_tokenize_sum3(self):
        self.assertEqual(self.model.input_tokenize("2+3+4"),
                         [CalculatorToken("Digit", "2"), CalculatorToken("Operator", "+"),
                          CalculatorToken("Digit", "3"), CalculatorToken("Operator", "+"),
                          CalculatorToken("Digit", "4")])

    def test_input_tokenize_unary_minus(self):
        self.assertEqual(self.model.input_tokenize("-2-4+(-3)-(-5)"),
                         [CalculatorToken("Operator", "~"), CalculatorToken("Digit", "2"),
                          CalculatorToken("Operator", "-"),
                          CalculatorToken("Digit", "4"), CalculatorToken("Operator", "+"),
                          CalculatorToken("OpenBracket", "("), CalculatorToken("Operator", "~"),
                          CalculatorToken("Digit", "3"), CalculatorToken("CloseBracket", ")"),
                          CalculatorToken("Operator", "-"), CalculatorToken("OpenBracket", "("),
                          CalculatorToken("Operator", "~"), CalculatorToken("Digit", "5"),
                          CalculatorToken("CloseBracket", ")")])

    def test_input_tokenize_with_brackets(self):
        self.assertEqual(self.model.input_tokenize("2+(3+(4+5))"),
                         [CalculatorToken("Digit", "2"), CalculatorToken("Operator", "+"),
                          CalculatorToken("OpenBracket", "("), CalculatorToken("Digit", "3"),
                          CalculatorToken("Operator", "+"), CalculatorToken("OpenBracket", "("),
                          CalculatorToken("Digit", "4"), CalculatorToken("Operator", "+"),
                          CalculatorToken("Digit", "5"), CalculatorToken("CloseBracket", ")"),
                          CalculatorToken("CloseBracket", ")")])

    def test_input_tokenize_with_functions_and_constants(self):
        self.assertEqual(self.model.input_tokenize("0.1+sin(pi)-log(2, 64)"),
                         [CalculatorToken("Digit", "0.1"), CalculatorToken("Operator", "+"),
                          CalculatorToken("Function", "sin"), CalculatorToken("OpenBracket", "("),
                          CalculatorToken("Digit", np.pi), CalculatorToken("CloseBracket", ")"),
                          CalculatorToken("Operator", "-"), CalculatorToken("Function", "log"),
                          CalculatorToken("OpenBracket", "("), CalculatorToken("Digit", "2"),
                          CalculatorToken("Separator", ","), CalculatorToken("Digit", "64"),
                          CalculatorToken("CloseBracket", ")")])

    def test_input_tokenize_with_brackets_and_ignored_mult(self):
        self.assertEqual(self.model.input_tokenize("2+(3+4(5+6))"),
                         [CalculatorToken("Digit", "2"), CalculatorToken("Operator", "+"),
                          CalculatorToken("OpenBracket", "("), CalculatorToken("Digit", "3"),
                          CalculatorToken("Operator", "+"), CalculatorToken("Digit", "4"),
                          CalculatorToken("Operator", "*"), CalculatorToken("OpenBracket", "("),
                          CalculatorToken("Digit", "5"), CalculatorToken("Operator", "+"),
                          CalculatorToken("Digit", "6"), CalculatorToken("CloseBracket", ")"),
                          CalculatorToken("CloseBracket", ")")])

    def test_sort_machine_algo_sum2(self):
        self.assertEqual(self.model.sort_machine_algo(
            [CalculatorToken("Digit", "2"), CalculatorToken("Operator", "+"), CalculatorToken("Digit", "3")]),
            [CalculatorToken("Digit", "2"), CalculatorToken("Digit", "3"),
             CalculatorToken("Operator", "+")])

    def test_sort_machine_algo_sum3(self):
        self.assertEqual(self.model.sort_machine_algo(
            [CalculatorToken("Digit", "2"), CalculatorToken("Operator", "+"), CalculatorToken("Digit", "3"),
             CalculatorToken("Operator", "+"), CalculatorToken("Digit", "4")]),
            [CalculatorToken("Digit", "2"), CalculatorToken("Digit", "3"),
             CalculatorToken("Operator", "+"), CalculatorToken("Digit", "4"), CalculatorToken("Operator", "+")])

    def test_sort_machine_algo_unary_minus(self):
        self.assertEqual(self.model.sort_machine_algo(
            [CalculatorToken("Operator", "~"), CalculatorToken("Digit", "2"),
             CalculatorToken("Operator", "-"),
             CalculatorToken("Digit", "4"), CalculatorToken("Operator", "+"),
             CalculatorToken("OpenBracket", "("), CalculatorToken("Operator", "~"),
             CalculatorToken("Digit", "3"), CalculatorToken("CloseBracket", ")"),
             CalculatorToken("Operator", "-"), CalculatorToken("OpenBracket", "("),
             CalculatorToken("Operator", "~"), CalculatorToken("Digit", "5"),
             CalculatorToken("CloseBracket", ")")]),

            [CalculatorToken("Digit", "2"), CalculatorToken("Operator", "~"), CalculatorToken("Digit", "4"),
             CalculatorToken("Operator", "-"), CalculatorToken("Digit", "3"), CalculatorToken("Operator", "~"),
             CalculatorToken("Operator", "+"), CalculatorToken("Digit", "5"), CalculatorToken("Operator", "~"),
             CalculatorToken("Operator", "-")])

    def test_sort_machine_algo_with_functions_and_constants(self):
        self.assertEqual(
            self.model.sort_machine_algo([CalculatorToken("Digit", "0.1"), CalculatorToken("Operator", "+"),
                                          CalculatorToken("Function", "sin"), CalculatorToken("OpenBracket", "("),
                                          CalculatorToken("Digit", np.pi), CalculatorToken("CloseBracket", ")"),
                                          CalculatorToken("Operator", "-"), CalculatorToken("Function", "log"),
                                          CalculatorToken("OpenBracket", "("), CalculatorToken("Digit", "2"),
                                          CalculatorToken("Separator", ","), CalculatorToken("Digit", "64"),
                                          CalculatorToken("CloseBracket", ")")]),
            [CalculatorToken("Digit", "0.1"), CalculatorToken("Digit", np.pi), CalculatorToken("Function", "sin"),
             CalculatorToken("Operator", "+"),
             CalculatorToken("Digit", "2"), CalculatorToken("Digit", "64"), CalculatorToken("Function", "log"),
             CalculatorToken("Operator", "-")])

    def test_sort_machine_algo_with_brackets_and_ignored_mult(self):
        self.assertEqual(self.model.sort_machine_algo(
            [CalculatorToken("Digit", "2"), CalculatorToken("Operator", "+"),
             CalculatorToken("OpenBracket", "("), CalculatorToken("Digit", "3"),
             CalculatorToken("Operator", "+"), CalculatorToken("Digit", "4"),
             CalculatorToken("Operator", "*"), CalculatorToken("OpenBracket", "("),
             CalculatorToken("Digit", "5"), CalculatorToken("Operator", "+"),
             CalculatorToken("Digit", "6"), CalculatorToken("CloseBracket", ")"),
             CalculatorToken("CloseBracket", ")")]),
            [CalculatorToken("Digit", "2"), CalculatorToken("Digit", "3"), CalculatorToken("Digit", "4"),
             CalculatorToken("Digit", "5"), CalculatorToken("Digit", "6"),
             CalculatorToken("Operator", "+"), CalculatorToken("Operator", "*"),
             CalculatorToken("Operator", "+"), CalculatorToken("Operator", "+"), ])

    def test_sort_machine_algo_incorrect_separator_exception(self):
        with self.assertRaises(CalculatorException) as exc:
            self.model.sort_machine_algo(
                [CalculatorToken("Digit", "1"), CalculatorToken("Separator", ","), CalculatorToken("Digit", "01")])
        self.assertEqual(str(exc.exception),
                         "Проблема с разделителем - вероятно, использована десятичная запятая вместо точки!")

    def test_evaluate_sum2(self):
        self.assertEqual(self.model.evaluate([CalculatorToken("Digit", "2"), CalculatorToken("Digit", "3"),
                                              CalculatorToken("Operator", "+")]), 5)

    def test_evaluate_sum3(self):
        self.assertEqual(self.model.evaluate([CalculatorToken("Digit", "2"), CalculatorToken("Digit", "3"),
                                              CalculatorToken("Operator", "+"), CalculatorToken("Digit", "4"),
                                              CalculatorToken("Operator", "+")]), 9)

    def test_evaluate_unary_minus(self):
        self.assertEqual(self.model.evaluate(
            [CalculatorToken("Digit", "2"), CalculatorToken("Operator", "~"), CalculatorToken("Digit", "4"),
             CalculatorToken("Operator", "-"), CalculatorToken("Digit", "3"), CalculatorToken("Operator", "~"),
             CalculatorToken("Operator", "+"), CalculatorToken("Digit", "5"), CalculatorToken("Operator", "~"),
             CalculatorToken("Operator", "-")]), -4)

    def test_evaluate_with_functions_and_constants(self):
        self.assertAlmostEqual(self.model.evaluate(
            [CalculatorToken("Digit", "0.1"), CalculatorToken("Digit", np.pi), CalculatorToken("Function", "sin"),
             CalculatorToken("Operator", "+"),
             CalculatorToken("Digit", "2"), CalculatorToken("Digit", "64"), CalculatorToken("Function", "log"),
             CalculatorToken("Operator", "-")]), -5.9)

    def test_evaluate_with_brackets_and_ignored_mult(self):
        self.assertEqual(self.model.evaluate(
            [CalculatorToken("Digit", "2"), CalculatorToken("Digit", "3"), CalculatorToken("Digit", "4"),
             CalculatorToken("Digit", "5"), CalculatorToken("Digit", "6"),
             CalculatorToken("Operator", "+"), CalculatorToken("Operator", "*"),
             CalculatorToken("Operator", "+"), CalculatorToken("Operator", "+"), ]), 49)

    def test_evaluate_incorrect_expression_exception(self):
        with self.assertRaises(CalculatorException) as exc:
            self.model.evaluate([CalculatorToken("Digit", "2"), CalculatorToken("Operator", "+")])
        self.assertEqual(str(exc.exception), "Некорректное выражение. Проверьте корректность использования + !")

    def test_evaluate_divizion_zero_exception(self):
        with self.assertRaises(CalculatorException) as exc:
            self.model.evaluate(
                [CalculatorToken("Digit", "2"), CalculatorToken("Digit", "0"), CalculatorToken("Operator", "/")])
        self.assertEqual(str(exc.exception), "Ошибка во время вычисления / !")

    def test_evaluate_sqrt_negative_exception(self):
        with self.assertRaises(CalculatorException) as exc:
            self.model.evaluate(
                [CalculatorToken("Digit", "-1"), CalculatorToken("Function", "sqrt")])
        self.assertEqual(str(exc.exception), "Ошибка во время вычисления sqrt !")


class TestPresenter(unittest.TestCase):
    def setUp(self):
        self._view = Mock()
        self._model = Mock()
        self._presenter = Presenter(self._view, self._model)

    def test_execute_functions_work_correct(self):
        """
        Testing execute function of presenter with no errors
        """
        self._view.get_input = MagicMock(return_value="2+4")
        self._view.set_output = MagicMock()
        self._model.input_tokenize = MagicMock(
            return_value=[CalculatorToken("Digit", "2"), CalculatorToken("Operator", "+"),
                          CalculatorToken("Digit", "4")])
        self._model.sort_machine_algo = MagicMock(
            return_value=[CalculatorToken("Digit", "2"), CalculatorToken("Digit", "4"),
                          CalculatorToken("Operator", "+")])
        self._model.evaluate = MagicMock(return_value=6)

        self._presenter.execute()

        self._model.input_tokenize.assert_called_once_with("2+4")
        self._model.sort_machine_algo.assert_called_once_with(
            [CalculatorToken("Digit", "2"), CalculatorToken("Operator", "+"), CalculatorToken("Digit", "4")])
        self._model.evaluate.assert_called_once_with(
            [CalculatorToken("Digit", "2"), CalculatorToken("Digit", "4"), CalculatorToken("Operator", "+")])
        self._view.set_output.assert_has_calls([call("Результат вычисления"), call("6")])

    def test_execute_functions_work_error(self):
        """
        Testing execute function of presenter with error
        """
        self._view.get_input = MagicMock(return_value="2/0")
        self._view.set_output = MagicMock()
        self._model.input_tokenize = MagicMock(
            return_value=[CalculatorToken("Digit", "2"), CalculatorToken("Operator", "/"),
                          CalculatorToken("Digit", "0")])
        self._model.sort_machine_algo = MagicMock(
            return_value=[CalculatorToken("Digit", "2"), CalculatorToken("Digit", "0"),
                          CalculatorToken("Operator", "/")])
        self._model.evaluate = MagicMock(return_value=CalculatorException("Ошибка во время вычисления / !"))

        self._presenter.execute()

        self._model.input_tokenize.assert_called_once_with("2/0")
        self._model.sort_machine_algo.assert_called_once_with(
            [CalculatorToken("Digit", "2"), CalculatorToken("Operator", "/"), CalculatorToken("Digit", "0")])
        self._model.evaluate.assert_called_once_with(
            [CalculatorToken("Digit", "2"), CalculatorToken("Digit", "0"), CalculatorToken("Operator", "/")])
        self._view.set_output.assert_has_calls([call("Результат вычисления"), call("Ошибка во время вычисления / !")])


class TestView(unittest.TestCase):

    def setUp(self):
        self._view = View()
        self._model = Mock()
        self._presenter = Mock(self._view, self._model)
        self._presenter.execute = Mock()
        self._view.init_gui(self._presenter)  # Инициализация GUI для теста

    @patch('tkinter.messagebox.showerror')
    def test_display_error(self, mock_showerror):
        """
        Testing display_error function in view
        :param mock_showerror: tkinter.messagebox.showerror mock
        """
        error_message = "Произошла ошибка!"
        self._view.display_error(error_message)
        mock_showerror.assert_called_once_with("Ошибка!", error_message)

    def test_set_output(self):
        """
        Testing set_output function in view
        """
        message_to_output = "Message to output!"
        self._view.set_output(message_to_output)
        self.assertEqual(self._view.result_label.cget("text"), message_to_output)

    def test_init_gui(self):
        """
        Testing init_gui function in view
        """
        self.assertIsNotNone(self._view._presenter)
        self.assertIsNotNone(self._view.window)
        self.assertEqual(self._view.window.title(), "Калькулятор")
        self.assertIsNotNone(self._view.entry)
        self.assertIsNotNone(self._view.calculate_button)
        self.assertIsNotNone(self._view.result_label)

    def test_get_input(self):
        """
        Testing get_input function in view
        """
        message = "Message to get"
        self._view.entry.insert(0, message)
        self.assertEqual(self._view.get_input(), message)

    def tearDown(self):
        self._view.window.destroy()  # Очистка окна после каждого теста
