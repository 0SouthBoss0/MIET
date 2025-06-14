import tkinter
from unittest.mock import patch, MagicMock

from behave import *


@given('unputed "{text}" in entry')
def step_impl(context, text):
    context.view.entry.insert(0, text)
    assert context.view.entry.get() == text


@when('we press calculate button')
def step_impl(context):
    context.view.calculate_button.invoke()


@then('we will get "{text}" in result')
def step_impl(context, text):
    assert context.view.result_label.cget("text") == text


@then('we will get "{text}" exception')
def step_impl(context, text):
    context.view.display_error.assert_called_once_with(text)
