import math

from exception import VertexException, EdgeException


class UndirectedGraph:
    def __init__(self, vertices_number=0):
        self.__vertices = list(vertex for vertex in range(1, vertices_number + 1))
        self.__edges_and_costs = dict()
        self.__neighbors = {vertex: list() for vertex in self.__vertices}

    def get_vertices_number(self):
        return len(self.__vertices)

    def get_vertices(self):
        return self.__vertices

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

        self.__edges_and_costs[(edge[1], edge[0])] = new_cost
        self.__edges_and_costs[edge] = new_cost

    def add_edge(self, source_vertex, destination_vertex, cost=0):
        if source_vertex not in self.__vertices:
            raise VertexException("The source vertex does not belong to the current graph.")

        if destination_vertex not in self.__vertices:
            raise VertexException("The destination vertex does not belong to the current graph.")

        if (source_vertex, destination_vertex) in self.__edges_and_costs.keys():
            raise EdgeException("The mentioned edge already belongs to the current graph.")

        self.__edges_and_costs[(source_vertex, destination_vertex)] = cost
        self.__edges_and_costs[(destination_vertex, source_vertex)] = cost

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

        if not undirected_graph.is_edge(destination_vertex, starting_vertex):
            cost = randrange(1000)
            undirected_graph.add_edge(starting_vertex, destination_vertex, cost)
            number_of_edges -= 1

    return undirected_graph


def bfs(undirected_graph, starting_vertex):
    queue = list()
    queue.append(starting_vertex)

    visited = list()
    visited.append(starting_vertex)

    while queue:
        current_vertex = queue.pop(0)

        for neighbor in undirected_graph.vertex_neighbors_iterator(current_vertex):
            if neighbor not in visited:
                queue.append(neighbor)
                visited.append(neighbor)

    return visited


def dfs(undirected_graph, starting_vertex):
    stack = list()
    stack.append(starting_vertex)

    visited = list()
    visited.append(starting_vertex)

    while stack:
        current_vertex = stack.pop()

        for neighbor in undirected_graph.vertex_neighbors_iterator(current_vertex):
            if neighbor not in visited:
                stack.append(neighbor)

        if current_vertex not in visited:
            visited.append(current_vertex)

    return visited


def minimum_length_path(undirected_graph, starting_vertex):
    # using bfs
    queue = list()
    queue.append(starting_vertex)

    distance = dict()
    previous = dict()

    visited = list()
    visited.append(starting_vertex)

    distance[starting_vertex] = 0

    while queue:
        current_vertex = queue.pop(0)

        for neighbor in undirected_graph.vertex_neighbors_iterator(current_vertex):
            if neighbor not in visited:
                previous[neighbor] = current_vertex
                distance[neighbor] = distance[current_vertex] + 1

                queue.append(neighbor)
                visited.append(neighbor)

    return distance, previous


def find_connected_components(undirected_graph):
    # using dfs
    connected_components = []
    available_vertices = undirected_graph.get_vertices()

    if not available_vertices:
        raise ValueError("The graph has no vertices!")

    while available_vertices:
        currently_visited = dfs(undirected_graph, available_vertices[0])
        available_vertices = list(set(available_vertices) - set(currently_visited))
        connected_components.append(currently_visited)

    return connected_components


def dijkstra_minimum_cost(undirected_graph, starting_vertex):
    from queue import PriorityQueue
    priority_queue = PriorityQueue()
    priority_queue.put((0, starting_vertex))

    distances = dict()
    distances[starting_vertex] = 0

    visited = set()
    visited.add(starting_vertex)

    previous = dict()

    while not priority_queue.empty():
        current_vertex = priority_queue.get()
        current_vertex = current_vertex[1]
        for neighbor in undirected_graph.vertex_neighbors_iterator(current_vertex):
            if neighbor not in visited or distances[neighbor] > distances[current_vertex] + undirected_graph.get_cost((current_vertex, neighbor)):
                distances[neighbor] = distances[current_vertex] + undirected_graph.get_cost((current_vertex, neighbor))
                priority_queue.put((distances[neighbor], neighbor))
                previous[neighbor] = current_vertex
                visited.add(neighbor)

    return distances, previous


def bellman_ford_minimum_cost(undirected_graph, source_vertex):
    distances = dict()
    for vertex in undirected_graph.vertices_iterator():
        distances[vertex] = math.inf
    distances[source_vertex] = 0

    previous = dict()

    # NOT WORKING IF THE GRAPH HAS NEGATIVE CYCLES
    # HOW TO SOLVE: loop only (number_of_vertices-1) times
    changed = True
    while changed:
        changed = False

        for (vertex1, vertex2, cost) in undirected_graph.edges_and_costs_iterator():
            if distances[vertex2] > distances[vertex1] + cost:
                distances[vertex2] = distances[vertex1] + cost
                previous[vertex2] = vertex1
                changed = True

    return distances, previous


def find_all_cycles(undirected_graph):
    def cycle_dfs(graph, start, end):
        fringe = [(start, [])]

        while fringe:
            state, path = fringe.pop()

            if path and state == end:
                yield path
                continue

            for next_state in graph.vertex_neighbors_iterator(state):
                if next_state in path:
                    continue

                fringe.append((next_state, path+[next_state]))

    cycles = [[node] + path for node in undirected_graph.vertices_iterator() for path in cycle_dfs(undirected_graph, node, node)]

    return cycles


def is_tree(undirected_graph):
    visited = list()
    queue = list()

    if not undirected_graph.get_vertices_number():
        raise ValueError("The graph has no vertices!")

    queue.append(undirected_graph.get_vertices()[0])

    while queue:
        current_vertex = queue.pop(0)

        for neighbor in undirected_graph.vertex_neighbors_iterator(current_vertex):
            if neighbor not in visited:
                if neighbor in queue:
                    return False

                queue.append(neighbor)

        visited.append(current_vertex)

    return True


def kruskal_minimum_spanning_tree(undirected_graph):
    class DisjointSet:
        def __init__(self, vertices):
            self.parent = {}
            self.height = {}
            for x in vertices:
                self.parent[x] = None
                self.height[x] = 0

        def checkAndMerge(self, x, y):
            '''Checks if x and y are verices belonging to the same connected component or not.
            If they are in the same component, the function returns False
            If they are in distinct components, it merges the two components and returns True
            '''
            rx = self.getRoot(x)
            ry = self.getRoot(y)
            print("root(%s)=%s, root(%s)=%s" % (x, rx, y, ry))
            if rx == ry:
                return False
            hx = self.height[rx]
            hy = self.height[ry]
            if hx < hy:
                self.parent[rx] = ry
                del self.height[rx]
                print("%s->%s" % (rx, ry))
            elif hx > hy:
                self.parent[ry] = rx
                del self.height[ry]
                print("%s->%s" % (ry, rx))
            else:
                self.parent[ry] = rx
                del self.height[ry]
                self.height[rx] = self.height[rx] + 1
                print("%s->%s" % (ry, rx))
            return True

        def getRoot(self, x):
            while self.parent[x] is not None:
                x = self.parent[x]
            return x

    edges = []

    for x in undirected_graph.vertices_iterator():
        for y in undirected_graph.vertex_neighbors_iterator(x):

            if x < y:
                edges.append((undirected_graph.get_cost((x, y)), x, y))

    edges.sort()
    components = DisjointSet(undirected_graph.vertices_iterator())
    tree = []
    tree_cost = 0

    for cost, x, y in edges:
        if components.checkAndMerge(x, y):
            tree.append((x, y))
            tree_cost = tree_cost + cost

    return tree, tree_cost


def prim_minimum_spanning_tree(undirected_graph):
    from heapq import heappop, heappush

    if not undirected_graph.get_vertices_number():
        raise ValueError("The graph has no vertices!")

    start = undirected_graph.get_vertices()[0]

    q = []
    for x in undirected_graph.vertex_neighbors_iterator(start):
        heappush(q, (undirected_graph.get_cost((start, x)), start, x,))
        print(f"New candidate edge: ({start},{x}) of cost {undirected_graph.get_cost((start, x))}")

    tree_vertices = {start}
    tree_edges = []
    tree_cost = 0

    while len(q) > 0:
        cost, x, y = heappop(q)
        print("Processing: (%x,%x) of cost %s" % (x, y, cost))

        if y in tree_vertices:
            print("Skip")
            continue

        tree_vertices.add(y)
        tree_edges.append((x, y))
        tree_cost = tree_cost + cost

        for z in undirected_graph.vertex_neighbors_iterator(y):
            if z not in tree_vertices:
                heappush(q, (undirected_graph.get_cost((y, z)), y, z))
                print(f"New candidate edge: ({y},{z}) of cost {undirected_graph.get_cost((y, z))}")

    return tree_edges, tree_cost

