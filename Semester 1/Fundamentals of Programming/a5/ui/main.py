from src.ui.ui import ExpensesUI
from src.services.unittests import *


def main():
    start_program = ExpensesUI()
    start_program.start_menu()


if __name__ == '__main__':
    tests_for_service_functionalities()
    main()
