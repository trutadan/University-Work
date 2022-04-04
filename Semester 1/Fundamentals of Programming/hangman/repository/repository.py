class RepositoryException(Exception):
    pass


class Repository:
    def __init__(self):
        self._sentences_list = list()

    def add(self, sentence):
        """
        Add a new sentence to the repository list.
        :param sentence: an instance of the class Sentence.
        :return: an exception in case the given sentence already exists in the repository
        """

        if sentence in self._sentences_list:
            raise RepositoryException("The sentence is already in the repository!")

        self._sentences_list.append(sentence)

    def get_all(self):
        """
        Get all sentences from the repository.
        :return: a list of sentences.
        """

        return self._sentences_list


class FileRepository(Repository):
    def __init__(self, file_name, read_sentence, write_sentence):
        self.__file_name = file_name
        self.__read_sentence = read_sentence
        self.__write_sentence = write_sentence
        Repository.__init__(self)

    def __read_from_file(self):
        """
        Given a file path, considering each line is a sentence, create an instance of Sentence class for each line,
        then clear the repository list and refill it with the updated Sentence class instances.
        """

        with open(self.__file_name, 'r') as file:

            lines = file.readlines()
            self._sentences_list.clear()

            for line in lines:
                line = line.strip()

                if len(line):
                    new_sentence = self.__read_sentence(line)
                    self._sentences_list.append(new_sentence)

    def __write_to_file(self):
        """
        Given a file path, take each instances of Sentence class from
        the repository list and write it in the file, each sentence on a different line.
        """

        with open(self.__file_name, 'w') as file:
            for sentence in self._sentences_list:
                file.write(str(self.__write_sentence(sentence)) + "\n")

    def add(self, sentence):
        """
        Read all the sentences from the updated text file in order to update the repository list,
        add a new sentence to the repository containing all the sentences from the file, and then
        write all of them back in the file, including the one just added.
        :param sentence: an instance of the class Sentence.
        """

        self.__read_from_file()
        Repository.add(self, sentence)
        self.__write_to_file()

    def get_all(self):
        """
        Read all the sentences from the updated text file in order to update the repository list,
        then get all sentences from that repository.
        :return: a list of sentences.
        """

        self.__read_from_file()
        return Repository.get_all(self)
