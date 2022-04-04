import random
import sys

from domain.sentence import SentenceValidator, Sentence, SentenceException
from repository.repository import RepositoryException


class UI:
    def __init__(self, controller):
        self.__controller = controller
        self.__validator = SentenceValidator()

    @staticmethod
    def starting_game_menu():
        print("\n[1] Add new sentence to repository.")
        print("[2] Start new game.")
        print("[3] Exit.\n")

    def add_sentence_to_repository_ui(self):
        string_sentence = input("\nEnter the sentence you want to add: ").lower().strip()

        if string_sentence == 'exit':
            print("Thank you for playing the game!")
            sys.exit()

        self.__validator.validate(string_sentence)

        sentence_instance = Sentence(string_sentence)
        self.__controller.add_sentence(sentence_instance)

        print("A new sentence has been successfully added!")

    def run_game(self):
        all_sentences = self.__controller.get_all_sentences()

        sentence_to_be_revealed = random.choice(all_sentences)
        sentence_to_be_revealed.set_print_mode(0)

        string_sentence = sentence_to_be_revealed.get_string_sentence()
        words_in_sentence = string_sentence.split(' ')

        hangman_letters = ['h', 'a', 'n', 'g', 'm', 'a', 'n']
        hangman_word = ''

        for word in words_in_sentence:
            first_letter = word[0]
            sentence_to_be_revealed.reveal_letter(first_letter)

            last_letter = word[-1]
            sentence_to_be_revealed.reveal_letter(last_letter)

        while True:
            print("\nSENTENCE - HANGMAN WORD")
            print(f'{sentence_to_be_revealed} - "{hangman_word}"')

            if sentence_to_be_revealed.get_number_of_unrevealed_letters() == 0:
                print("\nCongratulations! You've won the game.")
                print("Thank you for playing the game! See you next time.")
                sys.exit()

            if len(hangman_letters) == 0:
                print("\nUnlucky! You've lost the game.")
                print("Thank you for playing the game! See you next time.")
                sys.exit()

            while True:
                letter_to_be_checked = input("\nEnter a letter you want to check the sentence for: ").lower()

                if len(letter_to_be_checked) == 1 and ord('a') <= ord(letter_to_be_checked) <= ord('z'):
                    break

                print("The input is invalid! Try again.")

            status_of_reveal = sentence_to_be_revealed.reveal_letter(letter_to_be_checked)

            if not status_of_reveal:
                hangman_word += hangman_letters[0]
                hangman_letters.pop(0)

    def run_program(self):
        print("Hello! Welcome to Hangman - the Game!")
        print("You can type 'exit' at any time to end the game.")

        while True:
            self.starting_game_menu()
            option = input("Choose an operation from above: ")

            if option == '1':
                try:
                    self.add_sentence_to_repository_ui()

                except SentenceException as validator_errors:
                    for error in validator_errors.get_errors():
                        print(error)

                except RepositoryException as repository_error:
                    print(repository_error)

            elif option == '2':
                self.run_game()

            elif option == '3':
                break

            else:
                print("Not a valid operation number!")

        print("Thank you for playing the game! See you next time.")
