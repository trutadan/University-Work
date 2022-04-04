from exceptions_and_validators.exception import RepositoryException, ValidatorException


class UI:
    def __init__(self, client_services, movie_services, rental_services):
        self.__client_services = client_services
        self.__movie_services = movie_services
        self.__rental_services = rental_services

    @staticmethod
    def display_general_menu():
        print()
        print("[1] Manage clients.")
        print("[2] Manage movies.")
        print("[3] Manage rentals.")
        print("[4] Exit program.")
        print()

    @staticmethod
    def display_client_menu():
        print()
        print("[1] Add new client.")
        print("[2] Remove client.")
        print("[3] Update client data.")
        print("[4] List all clients.")
        print("[5] Search client by id.")
        print("[6] Search client by name.")
        print("[7] Exit client menu.")
        print()

    @staticmethod
    def display_movie_menu():
        print()
        print("[1] Add new movie.")
        print("[2] Remove movie.")
        print("[3] Update movie data.")
        print("[4] List all movies.")
        print("[5] Search movie by id.")
        print("[6] Search movie by title.")
        print("[7] Search movie by description.")
        print("[8] Search movie by genre.")
        print("[9] Exit movie menu.")
        print()

    @staticmethod
    def display_rental_menu():
        print()
        print("[1] Rent a movie.")
        print("[2] Return a movie.")
        print("[3] List rentals.")
        print("[4] List most rented movies.")
        print("[5] List most active clients.")
        print("[6] List late rentals")
        print("[7] Exit rental menu.")
        print()

    def run_program(self):

        print("Welcome to the Movie Rental Manager! Follow the instructions mentioned below.")

        self.__client_services.generate_clients_data()
        self.__movie_services.generate_movies_data()
        self.__rental_services.generate_random_rental_data()

        while True:
            self.display_general_menu()

            user_menu_command = input("Enter a valid command number: ")

            if user_menu_command == '1':
                while True:
                    self.display_client_menu()
                    user_operation_command = input("Enter a number: ")
                    try:
                        if user_operation_command == '1':
                            self.__ui_add_client()
                        elif user_operation_command == '2':
                            self.__ui_remove_client()
                        elif user_operation_command == '3':
                            self.__ui_update_client()
                        elif user_operation_command == '4':
                            self.__list_all_clients()
                        elif user_operation_command == '5':
                            self.__list_client_by_given_id()
                        elif user_operation_command == '6':
                            self.__list_clients_by_given_name()
                        elif user_operation_command == '7':
                            break
                        else:
                            print("Not a valid number option. Choose between 1 and 5.")
                    except RepositoryException as repository_error:
                        print(str(repository_error))
                    except ValidatorException as validation_errors:
                        errors = ValidatorException.get_errors(validation_errors)
                        for error in errors:
                            print(error)

            elif user_menu_command == '2':
                while True:
                    self.display_movie_menu()
                    user_operation_command = input("Enter a number: ")
                    try:
                        if user_operation_command == '1':
                            self.__ui_add_movie()
                        elif user_operation_command == '2':
                            self.__ui_remove_movie()
                        elif user_operation_command == '3':
                            self.__ui_update_movie()
                        elif user_operation_command == '4':
                            self.__list_all_movies()
                        elif user_operation_command == '5':
                            self.__list_movie_by_given_id()
                        elif user_operation_command == '6':
                            self.__list_movie_by_given_title()
                        elif user_operation_command == '7':
                            self.__list_movie_by_given_description()
                        elif user_operation_command == '8':
                            self.__list_movie_by_given_genre()
                        elif user_operation_command == '9':
                            break
                        else:
                            print("Not a valid number option. Choose between 1 and 5.")
                    except RepositoryException as repository_error:
                        print(str(repository_error))
                    except ValidatorException as validation_errors:
                        errors = ValidatorException.get_errors(validation_errors)
                        for error in errors:
                            print(error)

            elif user_menu_command == '3':
                while True:
                    self.display_rental_menu()
                    user_operation_command = input("Enter a number: ")
                    try:
                        if user_operation_command == '1':
                            self.__ui_rent_new_movie()
                        elif user_operation_command == '2':
                            self.__ui_return_a_movie()
                        elif user_operation_command == '3':
                            self.__list_all_rentals()
                        elif user_operation_command == '4':
                            self.__list_most_rented_movies()
                        elif user_operation_command == '5':
                            self.__list_most_active_clients()
                        elif user_operation_command == '6':
                            self.__list_late_rentals()
                        elif user_operation_command == '7':
                            break
                        elif user_operation_command == '8':
                            self.__list_all_clients_from_rental()
                        else:
                            print("Not a valid number option. Choose between 1 and 4.")
                    except RepositoryException as repository_error:
                        print(str(repository_error))
                    except ValidatorException as validation_errors:
                        errors = ValidatorException.get_errors(validation_errors)
                        for error in errors:
                            print(error)

            elif user_menu_command == '4':
                break

            else:
                print("Not a valid number option. Choose between 1 and 4.")

        print("Thank you for using the Movie Rental Manager! See you next time.")

    def __ui_add_client(self):
        print("\nIn order to add a client, you need to provide some information:")

        try:
            client_id = int(input("Client ID: "))
        except ValueError:
            print("Client ID must be an integer!")
            return
        client_name = input("Client name: ")
        self.__client_services.add_client_to_repository(client_id, client_name)

        print("The client has been successfully added!")

    def __ui_remove_client(self):
        print("\nIn order to remove a client, you need to provide some information:")

        try:
            client_id = int(input("Client ID: "))
        except ValueError:
            print("Client ID must be an integer!")
            return
        self.__client_services.remove_client_from_repository(client_id)
        self.__rental_services.remove_rentals_for_given_client_id(client_id)

        print("The client has been successfully removed!")

    def __ui_update_client(self):
        print("\nIn order to update a client, you need to provide some information:")

        try:
            client_id = int(input("Client ID: "))
        except ValueError:
            print("Client ID must be an integer!")
            return
        client_name = input("Updated client name: ")
        self.__client_services.update_client_from_repository(client_id, client_name)

        print("The client has been successfully updated!")

    def __list_all_clients(self):
        print()
        clients = self.__client_services.get_all_clients()
        if len(clients) == 0:
            print("No more clients left.")
            return
        print("client's id - client's name")
        for client in clients:
            print(client)

    def __list_client_by_given_id(self):
        print("\nIn order to search for a client, you need to provide the client's id: ")

        try:
            client_id = int(input("Client ID: "))
        except ValueError:
            print("Client ID must be an integer!")
            return
        client = self.__client_services.search_client_by_id(client_id)
        if client is None:
            print("No client was found for given ID.")
        else:
            print("client's id - client's name")
            print(client)

    def __list_clients_by_given_name(self):
        print("\nIn order to search for clients, you need to provide a name: ")

        client_name = input("Client name: ")
        clients_with_given_name = self.__client_services.search_clients_by_name(client_name)
        if len(clients_with_given_name) == 0:
            print("No clients with given name.")
            return
        print("client's id - client's name")
        for client in clients_with_given_name:
            print(client)

    def __ui_add_movie(self):
        print("\nIn order to add a movie, you need to provide some information:")

        try:
            movie_id = int(input("Movie ID: "))
        except ValueError:
            print("Movie ID must be an integer!")
            return
        movie_title = input("Movie title: ")
        movie_description = input("Movie description: ")
        movie_genre = input("Movie genre: ")
        self.__movie_services.add_movie_to_repository(movie_id, movie_title, movie_description, movie_genre)

        print("The movie has been successfully added!")

    def __ui_remove_movie(self):
        print("\nIn order to remove a movie, you need to provide some information:")

        try:
            movie_id = int(input("Movie ID: "))
        except ValueError:
            print("Movie ID must be an integer!")
            return
        self.__movie_services.remove_movie_from_repository(movie_id)
        self.__rental_services.remove_rentals_for_given_movie_id(movie_id)

        print("The movie has been successfully removed!")

    def __ui_update_movie(self):
        print("\nIn order to update a movie, you need to provide some information:")

        try:
            movie_id = int(input("Movie ID: "))
        except ValueError:
            print("Movie ID must be an integer!")
            return
        movie_title = input("Updated movie title: ")
        movie_description = input("Updated movie description: ")
        movie_genre = input("Updated movie genre: ")
        self.__movie_services.update_movie_from_repository(movie_id, movie_title, movie_description, movie_genre)

        print("The movie has been successfully updated!")

    def __list_all_movies(self):
        print()
        movies = self.__movie_services.get_all_movies()
        if len(movies) == 0:
            print("No more movies left.")
            return
        print("movie's id - movie's name - movie's description - movie's genre")
        for movie in movies:
            print(movie)

    def __list_movie_by_given_id(self):
        print("\nIn order to search for a movie, you need to provide the movie's id: ")

        try:
            movie_id = int(input("Movie ID: "))
        except ValueError:
            print("Movie ID must be an integer!")
            return
        movie = self.__movie_services.search_movie_by_id(movie_id)
        if movie is None:
            print("No movie was found for given ID.")
        else:
            print("movie's id - movie's name - movie's description - movie's genre")
            print(movie)

    def __list_movie_by_given_title(self):
        print("\nIn order to search for a movie, you need to provide the movie's title: ")

        movie_title = input("Movie title: ")
        movies_with_given_title = self.__movie_services.search_movies_by_title(movie_title)
        if len(movies_with_given_title) == 0:
            print("No movies with given title.")
            return
        print("movie's id - movie's name - movie's description - movie's genre")
        for movie in movies_with_given_title:
            print(movie)

    def __list_movie_by_given_description(self):
        print("\nIn order to search for a movie, you need to provide the movie's description: ")

        movie_description = input("Movie description: ")
        movies_with_given_description = self.__movie_services.search_movies_by_description(movie_description)
        if len(movies_with_given_description) == 0:
            print("No movies with given description.")
            return
        print("movie's id - movie's name - movie's description - movie's genre")
        for movie in movies_with_given_description:
            print(movie)

    def __list_movie_by_given_genre(self):
        print("\nIn order to search for a movie, you need to provide the movie's genre: ")

        movie_genre = input("Movie genre: ")
        movies_with_given_genre = self.__movie_services.search_movies_by_genre(movie_genre)
        if len(movies_with_given_genre) == 0:
            print("No movies with given genre.")
            return
        print("movie's id - movie's name - movie's description - movie's genre")
        for movie in movies_with_given_genre:
            print(movie)

    def __ui_rent_new_movie(self):
        print("\nIn order to rent a new movie, you need to provide some information: ")

        try:
            rental_id = int(input("Rental ID: "))
        except ValueError:
            print("Rental ID must be an integer!")
            return
        try:
            movie_id = int(input("Movie ID: "))
        except ValueError:
            print("Movie ID must be an integer!")
            return
        try:
            client_id = int(input("Client ID: "))
        except ValueError:
            print("Client ID must be an integer!")
            return
        rental_date = input("Rental date: ")

        self.__rental_services.rent_new_movie(rental_id, movie_id, client_id, rental_date)

        print("The movie has been successfully rented!")

    def __ui_return_a_movie(self):
        print("\nIn order to return a movie, you need to provide some information: ")

        try:
            rental_id = int(input("Rental ID: "))
        except ValueError:
            print("Rental ID must be an integer!")
            return
        return_date = input("Return date: ")

        self.__rental_services.return_a_movie(rental_id, return_date)

        print("The movie has been successfully returned!")

    def __list_all_rentals(self):
        print()
        rentals = self.__rental_services.get_all_rentals()
        if len(rentals) == 0:
            print("No more rentals left.")
            return
        print("rental's id - client's name - movie's name - rental date - due date - return date")
        for rental in rentals:
            print(rental)

    def __list_most_rented_movies(self):
        print()
        most_rented_movies = self.__rental_services.get_most_rented_movies()
        if len(most_rented_movies) == 0:
            print("No movie has been rented yet.")
            return
        print("movie's name - number of rental days")
        for movie in most_rented_movies:
            print(movie)

    def __list_most_active_clients(self):
        print()
        clients = self.__rental_services.get_most_active_clients()
        if len(clients) == 0:
            print("No clients has rentals yet.")
            return
        print("client's name - number of rental days")
        for client in clients:
            print(client)

    def __list_late_rentals(self):
        print()
        late_rental_movies = self.__rental_services.get_late_rentals_descending_order()
        if len(late_rental_movies) == 0:
            print("No late rental movies exist yet.")
            return
        print("movie's name - number of late rental days")
        for movie in late_rental_movies:
            print(movie)

    def __list_all_clients_from_rental(self):
        print()
        clients = self.__rental_services.get_all_clients_in_rental()
        if len(clients) == 0:
            print("No more clients left.")
            return
        print("client's id - client's name")
        for client in clients:
            print(client)
