class Controller:
    def __init__(self, repository):
        self.__repository = repository

    def add_sentence(self, sentence):
        """
        Add a new sentence to the repository containing all the sentences from the file.
        :param sentence: an instance of the class Sentence.
        """
        self.__repository.add(sentence)

    def get_all_sentences(self):
        """
        Get all sentences from the repository.
        :return: a list of sentences.
        """
        return self.__repository.get_all()
