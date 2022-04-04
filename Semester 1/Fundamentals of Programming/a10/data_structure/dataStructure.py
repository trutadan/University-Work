from copy import deepcopy


class IterableDataStructure:
    def __init__(self, new_dictionary=None):
        if new_dictionary is None:
            new_dictionary = dict()
        self._dictionary = new_dictionary

    def __setitem__(self, key, value):
        self._dictionary[key] = value

    def __getitem__(self, item):
        return self._dictionary[item]

    def __delitem__(self, key):
        del self._dictionary[key]

    def __iter__(self):
        self.key = -1
        return self

    def __next__(self):
        self.key += 1
        if self.key >= len(self._dictionary):
            raise StopIteration()
        return self._dictionary[list(self._dictionary.keys())[self.key]]

    def __len__(self):
        return len(self._dictionary)

    def clear(self):
        self.clear()

    @property
    def values(self):
        return list(self._dictionary.values())

    def keys(self):
        return list(self._dictionary.keys())

    @staticmethod
    def gnome_sort(object_to_be_sorted, key=None, comparison_function=None, reverse_order=False):
        """
        The gnome sort is a sorting algorithm which is similar to insertion sort. The algorithm finds the first place
        where two adjacent elements are in the wrong order and swaps them.
        :param object_to_be_sorted: a list.
        :param key: a parameter which takes a function as its value.
        :param comparison_function: a function that expresses the sign by which the comparison is made.
        :param reverse_order: if True, the sort is in descending order, if False, the sort is in ascending order.
        :return: the sorted list.
        """

        def default_key(obj):
            return obj

        def default_compare(first_object, second_object):
            return first_object >= second_object

        sorted_object = deepcopy(object_to_be_sorted)

        if key is None:
            key = default_key

        if comparison_function is None:
            comparison_function = default_compare

        iteration_index = 1

        while iteration_index < len(sorted_object):
            if iteration_index == 0 or comparison_function(key(sorted_object[iteration_index]), key(sorted_object[iteration_index - 1])):
                iteration_index += 1
            else:
                sorted_object[iteration_index], sorted_object[iteration_index - 1] = sorted_object[iteration_index - 1], sorted_object[iteration_index]
                iteration_index -= 1

        if reverse_order:
            left_iteration_index = 0
            right_iteration_index = len(sorted_object) - 1

            while left_iteration_index < right_iteration_index:
                sorted_object[left_iteration_index], sorted_object[right_iteration_index] = \
                    sorted_object[right_iteration_index], sorted_object[left_iteration_index]
                left_iteration_index += 1
                right_iteration_index -= 1

        return sorted_object

    @staticmethod
    def filter_elements_from_a_list(list_to_be_filtered, acceptance_function):
        """
        Filter a list by the function established by the acceptance_function parameter.
        :param list_to_be_filtered: a list.
        :param acceptance_function: a function which decides the item by which to sort the list.
        :return: the filtered list.
        """

        try:
            filtered_list = type(list_to_be_filtered)()
        except TypeError:
            filtered_list = []

        for element in list_to_be_filtered:
            if acceptance_function(element):
                filtered_list.append(element)

        return filtered_list
