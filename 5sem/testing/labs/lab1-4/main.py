from model import Model
from presenter import Presenter
from view import View

if __name__ == "__main__":
    view = View()
    model = Model()
    presenter = Presenter(view, model)

    view.init_gui(presenter)
    view.window.mainloop()
