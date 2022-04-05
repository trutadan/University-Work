from exception import VertexException, EdgeException


class DirectedGraph:
    def __init__(self, vertices_number=0):
        self.__vertices = list(vertex for vertex in range(vertices_number))
        self.__in_vertices = {vertex: list() for vertex in self.__vertices}
        self.__out_vertices = {vertex: list() for vertex in self.__vertices}
        self.__cost = dict()

    def get_vertices_number(self):
        return len(self.__vertices)

    def get_edges_number(self):
        return len(self.__cost)

    def vertices_iterator(self):
        for vertex in self.__vertices:
            yield vertex

    def is_edge_from_first_to_second_vertex(self, source_vertex, destination_vertex):
        return source_vertex in self.__out_vertices and destination_vertex in self.__out_vertices[source_vertex]

    def get_in_degree(self, vertex):
        if vertex not in self.__in_vertices:
            raise VertexException("The mentioned vertex does not belong to the current graph.")

        in_degree = len(self.__in_vertices[vertex])

        return in_degree

    def get_out_degree(self, vertex):
        if vertex not in self.__out_vertices:
            raise VertexException("The mentioned vertex does not belong to the current graph.")

        out_degree = len(self.__out_vertices[vertex])

        return out_degree

    def get_in_vertices(self):
        return self.__in_vertices

    def out_vertices_iterator(self, vertex):
        if vertex not in self.__vertices:
            raise VertexException("The mentioned vertex does not belong to the current graph.")

        for out_vertex in self.__out_vertices[vertex]:
            yield out_vertex

    def in_vertices_iterator(self, vertex):
        if vertex not in self.__vertices:
            raise VertexException("The mentioned vertex does not belong to the current graph.")

        for in_vertex in self.__in_vertices[vertex]:
            yield in_vertex

    def edges_iterator(self):
        for key, value in self.__cost.items():
            yield key[0], key[1], value

    def get_cost(self, edge):
        if edge not in self.__cost.keys():
            raise EdgeException("The mentioned edge does not belong to the current graph.")

        return self.__cost[edge]

    def set_cost(self, edge, new_cost):
        if edge not in self.__cost.keys():
            raise EdgeException("The mentioned edge does not belong to the current graph.")

        self.__cost[edge] = new_cost

    def add_edge(self, source_vertex, destination_vertex, cost=0):
        if source_vertex not in self.__vertices:
            raise VertexException("The source vertex does not belong to the current graph.")

        if destination_vertex not in self.__vertices:
            raise VertexException("The destination vertex does not belong to the current graph.")

        if (source_vertex, destination_vertex) in self.__cost.keys():
            raise EdgeException("The mentioned edge already belongs to the current graph.")

        self.__in_vertices[destination_vertex].append(source_vertex)
        self.__out_vertices[source_vertex].append(destination_vertex)

        self.__cost[(source_vertex, destination_vertex)] = cost

    def remove_edge(self, source_vertex, destination_vertex):
        if source_vertex not in self.__vertices:
            raise VertexException("The source vertex does not belong to the current graph.")

        if destination_vertex not in self.__vertices:
            raise VertexException("The destination vertex does not belong to the current graph.")

        if (source_vertex, destination_vertex) not in self.__cost.keys():
            raise EdgeException("The mentioned edge doesn't belong to the current graph.")

        del self.__cost[(source_vertex, destination_vertex)]

        self.__in_vertices[destination_vertex].remove(source_vertex)
        self.__out_vertices[source_vertex].remove(destination_vertex)

    def add_vertex(self, vertex_to_be_added):
        if vertex_to_be_added in self.__vertices:
            raise VertexException("The mentioned vertex already belongs to the current graph.")

        self.__in_vertices[vertex_to_be_added] = list()
        self.__out_vertices[vertex_to_be_added] = list()

        self.__vertices.append(vertex_to_be_added)

    def remove_vertex(self, vertex_to_be_removed):
        if vertex_to_be_removed not in self.__vertices:
            raise VertexException("The mentioned vertex doesn't belong to the current graph.")

        edges_to_remove = []
        for vertex in self.__in_vertices[vertex_to_be_removed]:
            edges_to_remove.append(vertex)
        for edge in edges_to_remove:
            self.remove_edge(vertex_to_be_removed, edge)

        edges_to_remove = []
        for vertex in self.__out_vertices[vertex_to_be_removed]:
            edges_to_remove.append(vertex)
        for edge in edges_to_remove:
            self.remove_edge(edge, vertex_to_be_removed)

        del self.__in_vertices[vertex_to_be_removed]
        del self.__out_vertices[vertex_to_be_removed]

        self.__vertices.remove(vertex_to_be_removed)

    def create_copy(self):
        from copy import deepcopy
        return deepcopy(self)


def read_directed_graph_from_file(file_name):
    with open(file_name, 'r') as file:
        elements_from_first_line = file.readline().split()

        number_of_vertices, number_of_edges = map(int, elements_from_first_line)

        graph_read = DirectedGraph(number_of_vertices)

        for edge_counter in range(number_of_edges):
            elements_from_each_line = file.readline().split()
            starting_vertex, ending_vertex, cost = map(int, elements_from_each_line)
            graph_read.add_edge(starting_vertex, ending_vertex, cost)

    return graph_read


def write_directed_graph_to_file(directed_graph, file_name):
    with open(file_name, 'w') as file:
        first_line = f"{directed_graph.get_vertices_number()} {directed_graph.get_edges_number()}\n"
        file.write(first_line)

        for starting_vertex in directed_graph.vertices_iterator():
            for ending_vertex in directed_graph.out_vertices_iterator(starting_vertex):
                each_line = f"{starting_vertex} {ending_vertex} {directed_graph.get_cost((starting_vertex, ending_vertex))}"
                file.write(each_line)


def generate_random_graph(number_of_vertices, number_of_edges):
    from random import randrange

    directed_graph = DirectedGraph()

    for index in range(number_of_vertices):
        directed_graph.add_vertex(index)

    while number_of_edges:
        out_vertex = randrange(number_of_vertices)
        in_vertex = randrange(number_of_vertices)

        if not directed_graph.is_edge_from_first_to_second_vertex(out_vertex, in_vertex):
            cost = randrange(1000)
            directed_graph.add_edge(out_vertex, in_vertex, cost)
            number_of_edges -= 1

    return directed_graph


def construct_path(parent, target_node):
    path = [target_node]

    # go from node to node until the starting node is found
    while parent[target_node] is not None:
        path.append(parent[target_node])
        target_node = parent[target_node]

    return path


def backward_bfs(graph, start_node, target_node):
    # we use set for the visited nodes avoid loops
    visited = set()
    queue = list()

    # add the start_node to the queue and visited list
    queue.append(start_node)
    visited.add(start_node)
    parent = dict()
    parent[start_node] = None

    path_found = False
    while len(queue):
        current_node = queue.pop(0)

        # if we never reach the target node, that means there's no path
        if current_node == target_node:
            path_found = True
            break

        if current_node in graph.get_in_vertices():
            for next_node in graph.get_in_vertices()[current_node]:
                if next_node not in visited:

                    # add to the queue the adjacent nodes which are not already in the visited set.
                    queue.append(next_node)
                    parent[next_node] = current_node

                    # add to the visited set the nodes added in the queue
                    visited.add(next_node)

    if path_found is False:
        return []

    # path reconstruction
    return construct_path(parent, target_node)
