from exceptions import UndoServiceException


class UndoRedoServices:
    def __init__(self):
        # history of program operations, is a stack
        self.__history = []
        # where are we in the operation history
        self.__index = -1

    def undo(self):
        if self.__index < 0:
            raise UndoServiceException("No more operations to be undone!")
        else:
            self.__history[self.__index].undo()
            self.__index -= 1

    def redo(self):
        if self.__index + 1 >= len(self.__history):
            raise UndoServiceException("No more operations to be redone!")
        else:
            self.__index += 1
            self.__history[self.__index].redo()

    def record(self, operation):
        self.__history.append(operation)
        self.__index += 1


class Operation:
    def __init__(self, undo_call, redo_call):
        self.__undo_call = undo_call
        self.__redo_call = redo_call

    def undo(self):
        self.__undo_call.call()

    def redo(self):
        self.__redo_call.call()


class ComplexOperation:
    def __init__(self, operations):
        self.__operations = operations

    def undo(self):
        for operation in self.__operations:
            operation.undo()

    def redo(self):
        for operation in self.__operations:
            operation.redo()


class Call:
    def __init__(self, function_name, *function_params):
        self.__function_name = function_name
        self.__function_params = function_params

    def call(self):
        self.__function_name(*self.__function_params)
