from controller.controller import Controller
from domain.sentence import Sentence
from repository.repository import FileRepository
from ui.ui import UI


def main():
    file_name = 'sentences.txt'
    repository = FileRepository(file_name, Sentence.from_line, Sentence.to_line)
    controller = Controller(repository)
    ui = UI(controller)
    ui.run_program()


main()
