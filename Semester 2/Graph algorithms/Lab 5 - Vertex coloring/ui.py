from undirected_graph import *


class UI:
    def __init__(self):
        self.__available_graphs = []
        self.__current_graph = None

    def create_empty_undirected_graph(self):
        undirected_graph = UndirectedGraph()

        self.__available_graphs.append(undirected_graph)
        self.__current_graph = len(self.__available_graphs) - 1

        print("\nThe new empty undirected graph has been successfully generated.")

    def create_random_undirected_graph(self):
        number_of_vertices = input("\nEnter the number of vertices: ")
        if number_of_vertices.isnumeric():
            number_of_vertices = int(number_of_vertices)
        else:
            raise ValueError("Number of vertices must be a positive integer!")

        number_of_edges = input("Enter the number of edges: ")
        if number_of_edges.isnumeric():
            number_of_edges = int(number_of_edges)
        else:
            raise ValueError("Number of edges must be a positive integer!")

        if number_of_edges > ((number_of_vertices * (number_of_vertices - 1))/2):
            raise ValueError("Too many edges!")

        random_undirected_graph = generate_random_graph(number_of_vertices, number_of_edges)

        self.__available_graphs.append(random_undirected_graph)
        self.__current_graph = len(self.__available_graphs) - 1

        print("\nThe new random undirected graph has been successfully generated.")

    def read_undirected_graph_from_file_ui(self):
        file_name = input("\nEnter the name of the file: ")

        undirected_graph = read_undirected_graph_from_file(file_name)
        self.__available_graphs.append(undirected_graph)
        self.__current_graph = len(self.__available_graphs) - 1

        print("\nYou are now working on the undirected graph read from the file.")

    def write_undirected_graph_to_file_ui(self):
        output_file_name = input("\nEnter the name of the output file: ") + ".txt"

        current_graph = self.__available_graphs[self.__current_graph]
        write_undirected_graph_to_file(current_graph, output_file_name)

        print(f"\nA file with the name {output_file_name} has been created, containing the current undirected graph.")

    def switch_to_other_undirected_graph(self):
        print(f"\nYou are now on the graph number: {self.__current_graph}.")
        print(f"There are in total {len(self.__available_graphs)} undirected graphs available.")

        graph_number = input("Enter the number of the graph you want to switch to: ")

        if graph_number.isnumeric():
            graph_number = int(graph_number)
        else:
            raise ValueError("The number of the graph must be a positive integer!")

        if not 0 <= graph_number < len(self.__available_graphs):
            raise ValueError("There is no undirected graph for the given index!")

        self.__current_graph = graph_number

        print(f"\nYou are now working on the undirected graph number {graph_number}.")

    def display_all_vertices_and_neighbors(self):
        for source_vertex in self.__available_graphs[self.__current_graph].vertices_iterator():
            line = f"{source_vertex}: "

            for destination_vertex in self.__available_graphs[self.__current_graph].vertex_neighbors_iterator(source_vertex):
                line += f"{destination_vertex}; "

            print(line)

    def get_number_of_vertices_ui(self):
        print(f"\nThe current undirected graph has {self.__available_graphs[self.__current_graph].get_vertices_number()} vertices.")

    def get_number_of_edges_ui(self):
        print(f"\nThe current undirected graph has {self.__available_graphs[self.__current_graph].get_edges_number()} edges.")

    def get_degree_of_vertex(self):
        searched_vertex = input("\nEnter the number of the vertex: ")
        if searched_vertex.isnumeric():
            searched_vertex = int(searched_vertex)
        else:
            raise ValueError("The vertex must be a positive integer!")

        degree = self.__available_graphs[self.__current_graph].get_degree(searched_vertex)

        print(f"\nThe degree of the vertex {searched_vertex} is {degree}.")

    def display_all_edges_and_their_costs(self):
        if self.__available_graphs[self.__current_graph].get_edges_number() == 0:
            print("\nThe current undirected graph has no edges. Add some.")
            return

        print("\nThe edges and their costs:")
        for source, destination, cost in self.__available_graphs[self.__current_graph].edges_and_costs_iterator():
            print(f"edge ({source}, {destination}) - cost {cost}")

    def add_vertex_ui(self):
        new_vertex = input("\nEnter the number of the new vertex: ")
        if new_vertex.isnumeric():
            new_vertex = int(new_vertex)
        else:
            raise ValueError("The number of the new vertex must be a positive integer!")

        self.__available_graphs[self.__current_graph].add_vertex(new_vertex)

        print("\nThe vertex has been successfully added!")

    def remove_vertex_ui(self):
        vertex_to_be_removed = input("\nEnter the number of the vertex you want to remove: ")
        if vertex_to_be_removed.isnumeric():
            vertex_to_be_removed = int(vertex_to_be_removed)
        else:
            raise ValueError("The number of the vertex must be a positive integer!")

        self.__available_graphs[self.__current_graph].remove_vertex(vertex_to_be_removed)

        print("\nThe vertex has been successfully deleted!")

    def add_edge_ui(self):
        source_vertex = input("\nEnter the source vertex: ")
        if source_vertex.isnumeric():
            source_vertex = int(source_vertex)
        else:
            raise ValueError("The source vertex must be a positive integer!")

        destination_vertex = input("Enter the destination vertex: ")
        if destination_vertex.isnumeric():
            destination_vertex = int(destination_vertex)
        else:
            raise ValueError("The destination vertex must be a positive integer!")

        cost = input("Enter the cost of the edge: ")
        if cost.isnumeric():
            cost = int(cost)
        else:
            raise ValueError("The cost must be a positive integer!")

        self.__available_graphs[self.__current_graph].add_edge(source_vertex, destination_vertex, cost)

        print("\nThe edge has been successfully added!")

    def remove_edge_ui(self):
        source_vertex = input("\nEnter the source vertex: ")
        if source_vertex.isnumeric():
            source_vertex = int(source_vertex)
        else:
            raise ValueError("The source vertex must be a positive integer!")

        destination_vertex = input("Enter the destination vertex: ")
        if destination_vertex.isnumeric():
            destination_vertex = int(destination_vertex)
        else:
            raise ValueError("The destination vertex must be a positive integer!")

        self.__available_graphs[self.__current_graph].remove_edge(source_vertex, destination_vertex)

        print("\nThe edge has been successfully deleted!")

    def modify_cost_of_edge(self):
        source_vertex = input("\nEnter the source vertex: ")
        if source_vertex.isnumeric():
            source_vertex = int(source_vertex)
        else:
            raise ValueError("The source vertex must be a positive integer!")

        destination_vertex = input("Enter the destination vertex: ")
        if destination_vertex.isnumeric():
            destination_vertex = int(destination_vertex)
        else:
            raise ValueError("The destination vertex must be a positive integer!")

        new_cost = input("Enter the new cost of the edge: ")

        self.__available_graphs[self.__current_graph].set_cost((source_vertex, destination_vertex), new_cost)

        print("\nCost has been successfully modified!")

    def check_if_edge_between_vertices(self):
        source_vertex = input("\nEnter the source vertex: ")
        if source_vertex.isnumeric():
            source_vertex = int(source_vertex)
        else:
            raise ValueError("The source vertex must be a positive integer!")

        destination_vertex = input("Enter the destination vertex: ")
        if destination_vertex.isnumeric():
            destination_vertex = int(destination_vertex)
        else:
            raise ValueError("The destination vertex must be a positive integer!")

        check_status = self.__available_graphs[self.__current_graph].is_edge(source_vertex, destination_vertex)

        if check_status is not False:
            print(f"\n({source_vertex}, {destination_vertex}) is an edge!")
        else:
            print(f"\n({source_vertex}, {destination_vertex}) is not an edge!")

    def parse_vertices(self):
        if self.__available_graphs[self.__current_graph].get_vertices_number() == 0:
            print("\nThe current undirected graph has no vertices. Add some.")
            return

        print("\nThe existent vertices of the current graph are: ")
        for vertex in self.__available_graphs[self.__current_graph].vertices_iterator():
            print(f"vertex ({vertex})")

    def create_copy_of_current_graph(self):
        graph_copy = self.__available_graphs[self.__current_graph].create_copy()
        self.__available_graphs.append(graph_copy)
        print("\nA copy of the current graph has been successfully created!")

    def find_vertex_coloring_with_minimum_colors_number(self):
        result = find_vertex_coloring_with_minimum_colors_number_using_greedy(self.__available_graphs[self.__current_graph])

        print("The vertex coloring with minimum number of colors:\n")
        for vertex in range(self.__available_graphs[self.__current_graph].get_vertices_number()):
            print(f"Color {result[vertex]} assigned to vertex {vertex}.")

    @staticmethod
    def print_menu():
        print("\n"
              "[1] Create an empty graph.\n"
              "[2] Create a random graph.\n"
              "[3] Read the graph from a text file.\n"
              "[4] Write the graph in a text file.\n"
              "[5] Switch the graph.\n" 
              "[6] Display all vertices and their neighbors for the current graph.\n"
              "[7] Get the number of vertices.\n"
              "[8] Get the number of edges.\n"
              "[9] Get the degree of a vertex.\n"
              "[10] Display all the edges and their costs.\n"
              "[11] Add a vertex.\n"
              "[12] Remove a vertex.\n"
              "[13] Add an edge.\n"
              "[14] Remove an edge.\n"
              "[15] Modify the cost of an edge.\n"
              "[16] Check if there is an edge between two given vertices.\n"
              "[17] Parse all the vertices.\n"
              "[18] Create a copy of the current graph.\n"
              "[19] Find vertex coloring with minimum colors number.\n"
              "[0] Exit."
              )

    def start_program(self):
        dictionary_with_commands = {"1": self.create_empty_undirected_graph, "2": self.create_random_undirected_graph,
                                    "3": self.read_undirected_graph_from_file_ui, "4": self.write_undirected_graph_to_file_ui,
                                    "5": self.switch_to_other_undirected_graph, "6": self.display_all_vertices_and_neighbors,
                                    "7": self.get_number_of_vertices_ui, "8": self.get_number_of_edges_ui,
                                    "9": self.get_degree_of_vertex, "10": self.display_all_edges_and_their_costs,
                                    "11": self.add_vertex_ui, "12": self.remove_vertex_ui,
                                    "13": self.add_edge_ui, "14": self.remove_edge_ui,
                                    "15": self.modify_cost_of_edge, "16": self.check_if_edge_between_vertices,
                                    "17": self.parse_vertices, "18": self.create_copy_of_current_graph,
                                    "19": self.find_vertex_coloring_with_minimum_colors_number
                                    }

        print("Welcome to the Undirected Graph Manager!")
        self.create_empty_undirected_graph()
        print("You are assigned an empty undirected graph at start up. You can choose other one at any time.")

        while True:
            try:
                self.print_menu()
                user_option = input("Choose your option from the menu above: ")

                if user_option == '0':
                    print("\nThank you for using this application! See you next time.")
                    break

                elif user_option in dictionary_with_commands:
                    dictionary_with_commands[user_option]()

                else:
                    print("\nYou provided a wrong input. Choose a number between 1 and 23.")

            except ValueError as value_error:
                print(value_error)

            except VertexException as vertex_error:
                print(vertex_error)

            except EdgeException as edge_error:
                print(edge_error)

            except FileNotFoundError as file_error:
                print(str(file_error).strip("[Errno 2] ") + ".")

