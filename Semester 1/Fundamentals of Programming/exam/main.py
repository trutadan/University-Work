from domain.domain import Question
from repository.repository import MasterQuestionFileRepository
from services.services import Services
from ui.ui import UI


def main():
    question_repository = MasterQuestionFileRepository('question_list.txt', Question.from_line, Question.to_line)
    services = Services(question_repository)
    ui = UI(services)

    ui.run_program()


main()
