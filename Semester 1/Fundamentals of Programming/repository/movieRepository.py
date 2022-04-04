import pickle

from exceptions import RepositoryException


class MovieRepository:
    def __init__(self):
        self._movie_data = dict()

    def search(self, movie_id):
        if movie_id not in self._movie_data:
            raise RepositoryException("Movie ID does not exist!")
        return self._movie_data[movie_id]

    def add(self, movie):
        if movie.get_id() in self._movie_data:
            raise RepositoryException("Movie ID already existing!")
        self._movie_data[movie.get_id()] = movie

    def update(self, movie):
        if movie.get_id() not in self._movie_data:
            raise RepositoryException("Movie ID does not exist!")
        self._movie_data[movie.get_id()] = movie

    def remove(self, movie_id):
        if movie_id not in self._movie_data:
            raise RepositoryException("Movie ID does not exist!")
        del self._movie_data[movie_id]

    def get_all(self):
        return self._movie_data.values()

    def __len__(self):
        return len(self._movie_data)


class MovieFileRepository(MovieRepository):
    def __init__(self, file_path, read_movie, write_movie):
        self.__file_path = file_path
        self.__read_movie = read_movie
        self.__write_movie = write_movie
        MovieRepository.__init__(self)

    def __read_all_from_file(self):
        with open(self.__file_path, 'r') as file:
            self._movie_data.clear()
            lines = file.readlines()
            for line in lines:
                line = line.strip()
                if len(line):
                    movie = self.__read_movie(line)
                    self._movie_data[movie.get_id()] = movie

    def __write_all_to_file(self):
        with open(self.__file_path, 'w') as file:
            for movie_id in self._movie_data:
                file.write(self.__write_movie(self._movie_data[movie_id]) + '\n')

    def __append_to_file(self, movie):
        with open(self.__file_path, 'a') as file:
            file.write(self.__write_movie(movie) + '\n')

    def search(self, movie_id):
        self.__read_all_from_file()
        return MovieRepository.search(self, movie_id)

    def add(self, movie):
        self.__read_all_from_file()
        MovieRepository.add(self, movie)
        self.__append_to_file(movie)

    def remove(self, movie_id):
        self.__read_all_from_file()
        MovieRepository.remove(self, movie_id)
        self.__write_all_to_file()

    def update(self, movie):
        self.__read_all_from_file()
        MovieRepository.update(self, movie)
        self.__write_all_to_file()

    def get_all(self):
        self.__read_all_from_file()
        return MovieRepository.get_all(self)

    def __len__(self):
        self.__read_all_from_file()
        return MovieRepository.__len__(self)


class MovieBinaryFileRepository(MovieRepository):
    def __init__(self, file_path):
        super().__init__()
        self.__file_path = file_path

    def __read_movies_from_file(self):
        with open(self.__file_path, 'rb') as f:
            try:
                self._movie_data = pickle.load(f)
            except EOFError:
                pass

    def __write_movies_to_file(self):
        with open(self.__file_path, 'wb') as f:
            pickle.dump(self._movie_data, f)

    def __append_movies_to_file(self):
        with open(self.__file_path, 'wb') as f:
            pickle.dump(self._movie_data, f)

    def search(self, movie_id):
        self.__read_movies_from_file()
        return super().search(movie_id)

    def add(self, movie):
        self.__read_movies_from_file()
        super().add(movie)
        self.__append_movies_to_file()

    def remove(self, movie_id):
        self.__read_movies_from_file()
        super().remove(movie_id)
        self.__write_movies_to_file()

    def update(self, movie):
        self.__read_movies_from_file()
        super().update(movie)
        self.__write_movies_to_file()

    def get_all(self):
        self.__read_movies_from_file()
        return super().get_all()

    def __len__(self):
        self.__read_movies_from_file()
        return super().__len__()
