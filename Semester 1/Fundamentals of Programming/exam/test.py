import unittest

from domain.domain import Question
from repository.repository import MasterQuestionFileRepository, RepositoryException
from services.services import Services


class TestRepositoryServices(unittest.TestCase):
    def setUp(self) -> None:
        self.__question_repository = MasterQuestionFileRepository('tests.txt', Question.from_line, Question.to_line)
        self.__services = Services(self.__question_repository)

    def test_add__existing_question__throws_exception(self):
        with self.assertRaises(RepositoryException):
            self.__question_repository.add(Question(1, 'Which number is the largest', 1, 4, 3, 4, 'easy.'))

    def test_add__new_question__question_successfully_added(self):
        self.__question_repository.add(Question(12, 'Which number is the largest', 1, 4, 3, 4, 'easy.'))
        self.assertEqual(len(self.__question_repository.get_all_questions()), 11)

    def test_get_all_difficulty_questions__easy_questions__correct_number_of_questions(self):
        self.assertEqual(len(self.__question_repository.get_all_difficulty_questions('easy')), 3)

    def test_services_add__existing_question__throws_exception(self):
        with self.assertRaises(RepositoryException):
            self.__question_repository.add(Question(1, 'Which number is the largest', 1, 4, 3, 4, 'easy.'))

    def tearDown(self) -> None:
        pass
