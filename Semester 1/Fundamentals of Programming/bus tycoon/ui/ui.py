from repository.repository import RepositoryException


class UI:
    def __init__(self, services):
        self.__services = services

    @staticmethod
    def print_menu():
        print("\n[1] Display buses on route X.")
        print("[2] Increase usage.")
        print("[3] Display buses in decreased order of kilometers travelled.")
        print("[4] Exit.\n")

    def display_buses_for_given_route_ui(self):
        route_chosen = input("\nEnter the route code for which you want the search to be done: ")

        buses_for_given_code = self.__services.get_buses_for_given_route_code(route_chosen)

        if len(buses_for_given_code) == 0:
            print("\nThere were no buses found for the given route!")

        else:
            print("\nThe buses for the given route are:")
            for bus in buses_for_given_code:
                print(bus)

    def increase_usage_ui(self):
        bus_id = input("\nEnter the bus id: ")
        route_code = input("Enter the route code: ")

        self.__services.increase_usage_of_a_bus(bus_id, route_code)

        print("\nThe bus usage has been successfully updated!")

    def display_buses_based_on_kilometers_travelled_ui(self):
        sorted_list_with_buses_and_kilometers = self.__services.find_buses_list_in_decreasing_order_of_kilometers_travelled()

        if len(sorted_list_with_buses_and_kilometers) == 0:
            print("\nThere are no more buses/routes left on their file repository! Add some.")

        else:
            print("\nThe buses in decreasing order of kilometers travelled:")
            for bus_information in sorted_list_with_buses_and_kilometers:
                print(bus_information)

    def run_program(self):
        print("Welcome to our Bus monitor!")
        print("You can gather information about bus route usage.")

        while True:
            self.print_menu()

            option = input("Choose a digit representing the option from above: ")

            try:

                if option == '1':
                    self.display_buses_for_given_route_ui()

                elif option == '2':
                    self.increase_usage_ui()

                elif option == '3':
                    self.display_buses_based_on_kilometers_travelled_ui()

                elif option == '4':
                    break

                else:
                    print("\nThe number option entered is not valid! Try again.")

            except RepositoryException as error:
                print(error)

        print("\nThanks for using our application! See you next time.")
