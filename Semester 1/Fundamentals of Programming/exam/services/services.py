import random

from domain.domain import Question
from repository.repository import MasterQuestionFileRepository, RepositoryException


class Services:
    def __init__(self, question_repository):
        self.__question_repository = question_repository

    def add(self, question):
        """
        Add a new question to the repository.
        :param question: Question instance.
        """

        self.__question_repository.add(question)

    def create_new_quiz(self, difficulty, number_of_questions, file_path):
        """
        Create a new quiz for the given information.
        :param difficulty: the difficulty of the quiz.
        :param number_of_questions: the number of the questions.
        :param file_path: the path of the file.
        """

        file = open(file_path, "w+")

        file.close()
        quiz_repository = MasterQuestionFileRepository(file_path, Question.from_line, Question.to_line)

        questions = self.__question_repository.get_all_difficulty_questions(difficulty)

        if len(questions) < number_of_questions//2:
            raise RepositoryException(f"Not enough {difficulty} questions!")

        quiz = list()

        starting_index = 0

        while starting_index < len(questions)//2:
            random_question = random.choice(questions)
            if random_question not in quiz:
                quiz.append(random_question)
                starting_index += 1

        new_questions = self.__question_repository.get_all_questions()

        while starting_index < len(questions):
            random_quiz = random.choice(new_questions)
            if random_quiz not in quiz:
                quiz.append(random_quiz)
                starting_index += 1

        for each_question in quiz:
            quiz_repository.add(each_question)

    @staticmethod
    def start_new_file(file_path):
        """
        Create a repository for a given file path.
        :param file_path: the name of the file.
        :return: the list of all the questions.
        """

        quiz_repository = MasterQuestionFileRepository(file_path, Question.from_line, Question.to_line)
        questions = quiz_repository.get_all_questions()
        return questions
