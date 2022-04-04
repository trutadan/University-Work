from unittest import TestCase

from controller.controller import Controller
from domain.sentence import Sentence
from repository.repository import FileRepository, RepositoryException


class TestFileRepository(TestCase):
    def setUp(self) -> None:
        self.__file_repository = FileRepository('tests.txt', Sentence.from_line, Sentence.to_line)
        open('tests.txt', 'w').close()

    def test_add__new_sentence__successfully_added(self):
        self.__file_repository.add(Sentence("new sentence"))
        self.assertEqual(self.__file_repository.get_all(), [Sentence("new sentence")])

    def test_add__already_existing_sentence__throws_exception(self):
        self.__file_repository.add(Sentence("new sentence"))
        with self.assertRaises(RepositoryException):
            self.__file_repository.add(Sentence("new sentence"))

    def test_get_all__empty_repository__empty_list(self):
        self.assertEqual(self.__file_repository.get_all(), [])

    def tearDown(self) -> None:
        pass


class TestController(TestCase):
    def setUp(self) -> None:
        self.__file_repository = FileRepository('tests.txt', Sentence.from_line, Sentence.to_line)
        self.__controller = Controller(self.__file_repository)
        open('tests.txt', 'w').close()

    def test_add_sentence__new_sentence__successfully_added(self):
        self.__controller.add_sentence(Sentence("new sentence"))
        self.assertEqual(self.__controller.get_all_sentences(), [Sentence("new sentence")])

    def test_get_all_sentences__empty_repository__empty_list(self):
        self.assertEqual(self.__controller.get_all_sentences(), [])

    def tearDown(self) -> None:
        pass
