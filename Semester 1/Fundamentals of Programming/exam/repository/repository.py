class RepositoryException(Exception):
    pass


class MasterQuestionRepository:
    def __init__(self):
        self._data_dictionary = dict()

    def add(self, question):
        """
        Add a new question to the repository list.
        :param question: an instance of the class Question.
        :return: an exception in case the given sentence already exists in the repository
        """

        if question.get_id() in self._data_dictionary.keys():
            raise RepositoryException("The question ID already exists!")

        self._data_dictionary[question.get_id()] = question

    def get_all_difficulty_questions(self, difficulty):
        questions = list()

        for question in self._data_dictionary.values():
            if question.get_difficulty_level() == difficulty:
                questions.append(question)

        return questions

    def get_all_questions(self):
        """
        Get all sentences from the repository.
        :return: a list of sentences.
        """

        return list(self._data_dictionary.values())

    def __len__(self):
        return len(list(self._data_dictionary.values()))


class MasterQuestionFileRepository(MasterQuestionRepository):
    def __init__(self, file_path, read_questions, write_questions):
        self.__file_path = file_path
        self.__read_questions = read_questions
        self.__write_questions = write_questions
        MasterQuestionRepository.__init__(self)

    def __read_from_file(self):
        """
        Given a file path, considering each line is a sentence, create an instance of Sentence class for each line,
        then clear the repository list and refill it with the updated Question class instances.
        """

        with open(self.__file_path, 'r') as file:
            lines = file.readlines()
            self._data_dictionary.clear()

            for line in lines:
                line = line.strip()

                if len(line):
                    new_question = self.__read_questions(line)
                    self._data_dictionary[new_question.get_id()] = new_question

    def __write_to_file(self):
        """
        Given a file path, take each instances of Sentence class from
        the repository list and write it in the file, each sentence on a different line.
        """

        with open(self.__file_path, 'w') as file:
            for question in self._data_dictionary.values():
                file.write(str(self.__write_questions(question)) + '\n')

    def add(self, question):
        """
        Read all the sentences from the updated text file in order to update the repository list,
        add a new sentence to the repository containing all the sentences from the file, and then
        write all of them back in the file, including the one just added.
        :param question: an instance of the class Question.
        """

        self.__read_from_file()
        MasterQuestionRepository.add(self, question)
        self.__write_to_file()

    def get_all_questions(self):
        """
        Read all the sentences from the updated text file in order to update the repository list,
        then get all sentences from that repository.
        :return: a list of questions.
        """

        self.__read_from_file()
        return MasterQuestionRepository.get_all_questions(self)

    def get_all_difficulty_questions(self, difficulty):
        """
        Read all the sentences from the updated text file in order to update the repository list,
        then get all sentences from that repository for the given difficulty.
        :return: a list of questions with given difficulty.
        """

        self.__read_from_file()
        return MasterQuestionRepository.get_all_difficulty_questions(self, difficulty)
