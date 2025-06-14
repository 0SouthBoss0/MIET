import tkinter as tk
import tkinter.messagebox


class View:
    def __init__(self):
        self.result_label = None
        self.calculate_button = None
        self.entry = None
        self.window = None
        self._presenter = None

    def init_gui(self, presenter):
        """
        Function to init interface
        :param presenter: Presenter object linked to this object
        """
        self._presenter = presenter
        # Создаем главное окно
        self.window = tk.Tk()
        self.window.title("Калькулятор")

        # Строка ввода
        self.entry = tk.Entry(self.window, width=35, font=("arial", 10))
        self.entry.grid(row=0, column=0, columnspan=3, padx=5, pady=5)

        # обработка нажатия enter
        self.entry.bind("<Return>", lambda e: self._presenter.execute())

        # Кнопка "Вычислить"
        self.calculate_button = tk.Button(self.window, text="Вычислить", width=15, command=self._presenter.execute)
        self.calculate_button.grid(row=0, column=3, padx=5, pady=5, columnspan=2)

        # Окно вывода
        self.result_label = tk.Label(self.window, text="Результат вычисления", width=25, borderwidth=5, bg="#9da1aa")
        self.result_label.grid(row=0, column=5, columnspan=2, padx=5, pady=5)

        # Цифры
        button_list = [
            "7", "8", "9",
            "4", "5", "6",
            "1", "2", "3",
            "0", ".", "π"
        ]
        row = 1
        col = 0
        for button_text in button_list:
            button = tk.Button(self.window, text=button_text, width=10,
                               command=lambda text=button_text: self.entry.insert(tk.END, text))
            button.grid(row=row, column=col, padx=2, pady=2)
            col += 1
            if col > 2:
                col = 0
                row += 1

        # Операции
        operation_list = [
            "sin", "tan",
            "sqrt", "log",
            "(",
            "cos", "cot", "fact",
            "ln", ")"
        ]
        row = 1
        col = 3
        for operation_text in operation_list:
            button = tk.Button(self.window, text=operation_text, width=5,
                               command=lambda text=operation_text: self.entry.insert(tk.END, text))
            button.grid(row=row, column=col, padx=2, pady=2)
            row += 1
            if row > 5:
                row = 1
                col += 1

        # Backspace и Clear
        button = tk.Button(self.window, text="Backspace", width=10,
                           command=lambda: self.entry.delete(self.entry.index(tkinter.END) - 1))
        button.grid(row=1, column=5, padx=2, pady=2, )

        button = tk.Button(self.window, text="Clear", width=10,
                           command=lambda: self.entry.delete(0, tkinter.END))
        button.grid(row=1, column=6, padx=2, pady=2)

        # Арифметические операции
        arith_list = [
            "+", "-",
            "*", "/",
            "^", "%",
            "!", ","
        ]
        row = 2
        col = 5
        for arith_text in arith_list:
            button = tk.Button(self.window, text=arith_text, width=10,
                               command=lambda text=arith_text: self.entry.insert(tk.END, text))
            button.grid(row=row, column=col, padx=2, pady=2)
            row += 1
            if row > 5:
                col += 1
                row = 2

        self.window.resizable(False, False)

    def set_output(self, output):
        self.result_label.config(text=output)

    def get_input(self):
        return self.entry.get()

    def display_error(self, error):
        tkinter.messagebox.showerror("Ошибка!", error)
