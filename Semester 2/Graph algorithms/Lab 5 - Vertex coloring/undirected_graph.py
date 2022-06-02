from exception import VertexException, EdgeException


class UndirectedGraph:
    def __init__(self, vertices_number=0):
        self.__vertices = list(vertex for vertex in range(vertices_number))
        self.__edges_and_costs = dict()
        self.__neighbors = {vertex: list() for vertex in self.__vertices}

    def get_vertices_number(self):
        return len(self.__vertices)

    def get_edges_number(self):
        return len(self.__edges_and_costs)

    def vertices_iterator(self):
        for vertex in self.__vertices:
            yield vertex

    def is_edge(self, source_vertex, destination_vertex):
        return (source_vertex, destination_vertex) in self.__edges_and_costs.keys()

    def get_degree(self, vertex):
        if vertex not in self.__vertices:
            raise VertexException("The mentioned vertex does not belong to the current graph.")

        return len(self.__neighbors[vertex])

    def vertex_neighbors_iterator(self, vertex):
        if vertex not in self.__vertices:
            raise VertexException("The mentioned vertex does not belong to the current graph.")

        for neighbor in self.__neighbors[vertex]:
            yield neighbor

    def edges_and_costs_iterator(self):
        for key, value in self.__edges_and_costs.items():
            yield key[0], key[1], value

    def get_cost(self, edge):
        if edge not in self.__edges_and_costs.keys():
            raise EdgeException("The mentioned edge does not belong to the current graph.")

        return self.__edges_and_costs[edge]

    def set_cost(self, edge, new_cost):
        if edge not in self.__edges_and_costs.keys():
            raise EdgeException("The mentioned edge does not belong to the current graph.")

        self.__edges_and_costs[edge] = new_cost

    def add_edge(self, source_vertex, destination_vertex, cost=0):
        if source_vertex not in self.__vertices:
            raise VertexException("The source vertex does not belong to the current graph.")

        if destination_vertex not in self.__vertices:
            raise VertexException("The destination vertex does not belong to the current graph.")

        if (source_vertex, destination_vertex) in self.__edges_and_costs.keys() or (destination_vertex, source_vertex) in self.__edges_and_costs.keys():
            raise EdgeException("The mentioned edge already belongs to the current graph.")

        self.__edges_and_costs[(source_vertex, destination_vertex)] = cost

        self.__neighbors[source_vertex].append(destination_vertex)
        self.__neighbors[destination_vertex].append(source_vertex)

    def remove_edge(self, source_vertex, destination_vertex):
        if source_vertex not in self.__vertices:
            raise VertexException("The source vertex does not belong to the current graph.")

        if destination_vertex not in self.__vertices:
            raise VertexException("The destination vertex does not belong to the current graph.")

        if (source_vertex, destination_vertex) not in self.__edges_and_costs.keys():
            if (destination_vertex, source_vertex) not in self.__edges_and_costs.keys():
                raise EdgeException("The mentioned edge doesn't belong to the current graph.")

            else:
                del self.__edges_and_costs[(destination_vertex, source_vertex)]

        else:
            del self.__edges_and_costs[(source_vertex, destination_vertex)]

        self.__neighbors[source_vertex].remove(destination_vertex)
        self.__neighbors[destination_vertex].remove(source_vertex)

    def add_vertex(self, vertex_to_be_added):
        if vertex_to_be_added in self.__vertices:
            raise VertexException("The mentioned vertex already belongs to the current graph.")

        self.__vertices.append(vertex_to_be_added)
        self.__neighbors[vertex_to_be_added] = list()

    def remove_vertex(self, vertex_to_be_removed):
        if vertex_to_be_removed not in self.__vertices:
            raise VertexException("The mentioned vertex doesn't belong to the current graph.")

        edges_to_remove = []
        for vertex in self.__neighbors[vertex_to_be_removed]:
            edges_to_remove.append(vertex)
        for edge in edges_to_remove:
            self.remove_edge(vertex_to_be_removed, edge)

        del self.__neighbors[vertex_to_be_removed]

        self.__vertices.remove(vertex_to_be_removed)

    def create_copy(self):
        from copy import deepcopy
        return deepcopy(self)


def read_undirected_graph_from_file(file_name):
    with open(file_name, 'r') as file:
        elements_from_first_line = file.readline().split()

        number_of_vertices, number_of_edges = map(int, elements_from_first_line)

        graph_read = UndirectedGraph(number_of_vertices)

        for edge_counter in range(number_of_edges):
            elements_from_each_line = file.readline().split()
            starting_vertex, ending_vertex, cost = map(int, elements_from_each_line)
            graph_read.add_edge(starting_vertex, ending_vertex, cost)

    return graph_read


def write_undirected_graph_to_file(directed_graph, file_name):
    with open(file_name, 'w') as file:
        first_line = f"{directed_graph.get_vertices_number()} {directed_graph.get_edges_number()}\n"
        file.write(first_line)

        for starting_vertex in directed_graph.vertices_iterator():
            for ending_vertex in directed_graph.vertex_neighbors_iterator(starting_vertex):
                each_line = f"{starting_vertex} {ending_vertex} {directed_graph.get_cost((starting_vertex, ending_vertex))}"
                file.write(each_line)


def generate_random_graph(number_of_vertices, number_of_edges):
    from random import randrange

    undirected_graph = UndirectedGraph()

    for index in range(number_of_vertices):
        undirected_graph.add_vertex(index)

    while number_of_edges:
        starting_vertex = randrange(number_of_vertices)
        destination_vertex = randrange(number_of_vertices)

        if not undirected_graph.is_edge(destination_vertex, starting_vertex) and not undirected_graph.is_edge(starting_vertex, destination_vertex):
            cost = randrange(1000)
            undirected_graph.add_edge(starting_vertex, destination_vertex, cost)
            number_of_edges -= 1

    return undirected_graph


def find_vertex_coloring_with_minimum_colors_number_using_greedy(undirected_graph):
    vertices_number = undirected_graph.get_vertices_number()
    if vertices_number < 1:
        raise ValueError("The current graph has no vertices!")

    # an array with the color of each vertex
    result = dict()
    for vertex in undirected_graph.vertices_iterator():
        result[vertex] = -1

    # an dictionary to keep track of the unavailable/available colors
    unavailable = dict()
    for vertex in undirected_graph.vertices_iterator():
        unavailable[vertex] = False

    # the first color goes to the first vertex in the graph
    result[0] = 0

    for vertex in undirected_graph.vertices_iterator():
        # make all the neighbor's vertices colors available
        for neighbor in undirected_graph.vertex_neighbors_iterator(vertex):
            if result[neighbor] != -1:
                unavailable[result[neighbor]] = True

        # search for the first available color
        color = 0
        while color < vertices_number:
            if not unavailable[color]:
                break

            color += 1

        # assign the newly found color
        result[vertex] = color

        # reset and prepare the variables for the next iteration
        for neighbor in undirected_graph.vertex_neighbors_iterator(vertex):
            if result[neighbor] != -1:
                unavailable[result[neighbor]] = False

    return result
