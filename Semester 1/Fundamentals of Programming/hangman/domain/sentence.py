class SentenceException(Exception):
    def __init__(self, errors):
        self.__errors = errors

    def get_errors(self):
        return self.__errors


class Sentence:
    def __init__(self, sentence, print_mode=1):
        self.__string_sentence = sentence.lower()
        self.__print_mode = print_mode
        self.__initialize_sentence_properties()

    def __initialize_sentence_properties(self):
        self.__number_of_unrevealed_letters = 0
        self.__game_string_representation_dictionary = dict()

        for character in self.__string_sentence:
            if ord('a') <= ord(character) <= ord('z'):
                self.__number_of_unrevealed_letters += 1

        for character in self.__string_sentence:

            if character not in self.__game_string_representation_dictionary.keys():

                if character == ' ':
                    self.__game_string_representation_dictionary[' '] = ' '
                else:
                    self.__game_string_representation_dictionary[character] = '_'

    def get_string_sentence(self):
        return self.__string_sentence

    def get_number_of_unrevealed_letters(self):
        return self.__number_of_unrevealed_letters

    def set_print_mode(self, print_mode):
        self.__print_mode = print_mode

    def reveal_letter(self, letter):
        if letter not in self.__game_string_representation_dictionary.keys():
            return False

        if self.__game_string_representation_dictionary[letter] == letter:
            return False

        for character in self.__string_sentence:
            if character == letter:
                self.__number_of_unrevealed_letters -= 1

        self.__game_string_representation_dictionary[letter] = letter

        return True

    def __str__(self):
        if self.__print_mode == 1:
            return self.__string_sentence

        elif self.__print_mode == 0:
            hidden_string_format = ""

            for character in self.__string_sentence:
                hidden_string_format += self.__game_string_representation_dictionary[character]

            return hidden_string_format

    def __eq__(self, other):
        return self.__string_sentence == other.get_string_sentence()

    @staticmethod
    def to_line(sentence_string):
        return sentence_string

    @staticmethod
    def from_line(sentence_string):
        return Sentence(sentence_string)


class SentenceValidator:
    @staticmethod
    def validate(string_sentence):
        errors = list()

        for character in string_sentence:
            if (ord('a') > ord(character) and character != ' ') or (ord('z') < ord(character) and character != ' '):
                errors.append("The sentence must contain only white spaces and letters!")
                break

        words = string_sentence.split(" ")

        for word in words:
            if len(word) < 3:
                errors.append("The sentence must contain words of minimum length of 3!")
                break

        if len(errors):
            raise SentenceException(errors)
