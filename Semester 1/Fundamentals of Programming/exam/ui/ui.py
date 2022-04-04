from domain.domain import Question, QuestionValidator, QuestionException, QuestionDTO
from repository.repository import RepositoryException


class UI:
    def __init__(self, question_services):
        self.__question_services = question_services
        self.__validator = QuestionValidator()

    @staticmethod
    def print_menu():
        print("\nadd <id>;<text>;<choice_a>;<choice_b>;<choice_c>;<correct_choice>;<difficulty>.")
        print("create <difficulty> <number_of_questions> <file>")
        print("start <file>")
        print("exit")

    def start_quiz(self, file_name):
        all_questions = self.__question_services.start_new_file(file_name)
        if len(all_questions) == 0:
            raise RepositoryException("The file has no question!")

        starting_score = 0
        print(f"Starting score: {starting_score}")

        for question in all_questions:
            print(QuestionDTO(question))
            option = input("What is the correct answer?")
            if option == question.get_correct_answer():
                if question.get_difficulty_level() == 'easy':
                    starting_score += 1
                elif question.get_difficulty_level() == 'medium':
                    starting_score += 2
                else:
                    starting_score += 3

        print(f"Your final score is: {starting_score}. Congratulations!")

    def create_quiz(self, difficulty, number_of_questions, file):
        self.__question_services.create_new_quiz(difficulty, number_of_questions, file)
        print("Quiz has been successfully created!")

    def run_program(self):
        print("Welcome to Quizz - the game!")
        print("You can choose between the following commands: ")

        while True:
            self.print_menu()

            try:
                option = input("> ")

                elements = option.split(";")

                if len(elements) == 7:
                    id_elements = elements[0].split(" ")
                    if len(id_elements) != 2:
                        if type(id_elements[1]) != int:
                            print("ID must be integer.")
                        print("Not valid id.")
                        continue

                    question_id = id_elements[1]

                    question_difficulty = elements[6]
                    if question_difficulty[-1] == '.':
                        question_difficulty = question_difficulty[:-1]
                    else:
                        print("Not valid difficulty.")
                        continue

                    question = Question(int(question_id), elements[1], elements[2], elements[3], elements[4], elements[5], question_difficulty)

                    self.__validator.validate(question)

                    self.__question_services.add(question)
                    print("The question has been successfully added!")
                    continue

                space_elements = option.split(" ")

                if len(space_elements) == 4:
                    if space_elements[0].lower() == 'create':
                        if space_elements[1].lower() in ['easy', 'medium', 'hard']:
                            if type(space_elements[2]) != int:
                                if '.txt' in space_elements[3]:
                                    self.create_quiz(space_elements[1], int(space_elements[2]), space_elements[3])

                                else:
                                    print("Not valid file name!")

                            else:
                                print("Not valid number of question_list.txt.txt!")

                        else:
                            print("Not valid difficulty!")

                    else:
                        print("Not valid command!")

                if len(space_elements) == 2:
                    if space_elements[0].lower() == 'start':
                        if '.txt' in space_elements[1]:
                            self.start_quiz(space_elements[1])

                        else:
                            print("Not valid file name!")

                    else:
                        print("Not valid command!")

                if option.lower() == 'exit':
                    break

            except QuestionException as validator_errors:
                for error in validator_errors.get_errors():
                    print(error)

            except RepositoryException as error:
                print(error)

            except IOError:
                print("Given file could not be opened!")

        print("Thank you for playing the game!")
