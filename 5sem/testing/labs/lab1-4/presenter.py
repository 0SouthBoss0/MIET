from model import Model, CalculatorException
from view import View


class Presenter:
    def __init__(self, view: View, model: Model):
        self._view = view
        self._model = model

    def execute(self):
        """
        Function to execute calculator app
        """
        # get expression string from view
        input_string = self._view.get_input()
        self._view.set_output("Результат вычисления")

        try:
            tokens = self._model.input_tokenize(input_string)
            parsed = self._model.sort_machine_algo(tokens)
            # print("Reverse Polish Notation: " + " ".join([str(item.t_value) for item in parsed]))
            result = self._model.evaluate(parsed)
            self._view.set_output(str(result))
        except CalculatorException as err:
            self._view.display_error(str(err))
