class QuestionException(Exception):
    def __init__(self, errors):
        self.__errors = errors

    def get_errors(self):
        return self.__errors


class QuestionValidator:
    @staticmethod
    def validate(question):
        errors = list()

        if type(question.get_id()) != int:
            errors.append("ID must be a number!")

        if question.get_correct_answer() not in (question.get_first_answer(), question.get_second_answer(), question.get_third_answer()):
            errors.append("Wrong correct answer!")

        if question.get_difficulty_level() not in ['easy', 'medium', 'hard']:
            errors.append("Wrong difficulty level!")

        if len(errors):
            raise QuestionException(errors)


class Question:
    def __init__(self, question_id, text, first_answer, second_answer, third_answer, correct_answer, difficulty_level):
        self.__id = question_id
        self.__text = text
        self.__first_answer = first_answer
        self.__second_answer = second_answer
        self.__third_answer = third_answer
        self.__correct_answer = correct_answer
        self.__difficulty_level = difficulty_level

    def get_id(self):
        return self.__id

    def get_text(self):
        return self.__text

    def get_first_answer(self):
        return self.__first_answer

    def get_second_answer(self):
        return self.__second_answer

    def get_third_answer(self):
        return self.__third_answer

    def get_correct_answer(self):
        return self.__correct_answer

    def get_difficulty_level(self):
        return self.__difficulty_level

    def __str__(self):
        return f"{self.__id};{self.__text};{self.__first_answer};{self.__second_answer};{self.__third_answer};{self.__correct_answer};{self.__difficulty_level}."

    @staticmethod
    def from_line(line):
        parts_of_line = line.split(";")
        question_id = int(parts_of_line[0])
        text = parts_of_line[1]
        first_answer = parts_of_line[2]
        second_answer = parts_of_line[3]
        third_answer = parts_of_line[4]
        correct_answer = parts_of_line[5]
        difficulty = parts_of_line[6]
        if difficulty[-1] == '.':
            difficulty = difficulty[:-1]
        return Question(question_id, text, first_answer, second_answer, third_answer, correct_answer, difficulty)

    @staticmethod
    def to_line(question):
        line = f"{question.get_id()};{question.get_text()};{question.get_first_answer()};{question.get_second_answer()};{question.get_third_answer()};{question.get_correct_answer()};{question.get_difficulty_level()}."
        return line


class QuestionDTO:
    def __init__(self, question):
        self.__question = question

    def get_question(self):
        return self.__question

    def __str__(self):
        return f"{self.__question.get_id()};{self.__question.get_text()};{self.__question.get_first_answer()};{self.__question.get_second_answer()};{self.__question.get_third_answer()};{self.__question.get_difficulty_level()}."
