import sys
import tkinter as tk
from unittest.mock import patch, MagicMock

sys.path.append("D:\pyprj\expression-calculator")

from model import Model
from view import View
from presenter import Presenter


def before_all(context):
    context.view = View()
    context.model = Model()
    context.presenter = Presenter(context.view, context.model)
    context.view.init_gui(context.presenter)
    context.view.display_error = MagicMock()


def after_scenario(context, scenario):
    context.view.entry.delete(0, tk.END)
    context.view.display_error = MagicMock()
