class Movie:
    def __init__(self, movie_id, title, description, genre):
        self.__movie_id = movie_id
        self.__title = title
        self.__description = description
        self.__genre = genre

    def get_id(self):
        return self.__movie_id

    def get_title(self):
        return self.__title

    def set_title(self, title):
        self.__title = title

    def get_description(self):
        return self.__description

    def set_description(self, description):
        self.__description = description

    def get_genre(self):
        return self.__genre

    def set_genre(self, genre):
        self.__genre = genre

    def __eq__(self, other):
        if not isinstance(other, Movie):
            return False

        return self.__movie_id == other.__movie_id and self.__title == other.__title and \
               self.__description == other.__description and self.__genre == other.__genre

    def __str__(self):
        return f"{self.__movie_id} - {self.__title} - {self.__description} - {self.__genre}"

    def to_dictionary(self):
        return {"id": self.__movie_id, "title": self.__title, "description": self.__description, "genre": self.__genre}

    @staticmethod
    def from_line(line):
        parts_of_line = line.split(" - ")
        movie_id = int(parts_of_line[0])
        movie_title = parts_of_line[1]
        movie_description = parts_of_line[2]
        movie_genre = parts_of_line[3]
        return Movie(movie_id, movie_title, movie_description, movie_genre)

    @staticmethod
    def to_line(movie):
        line = f"{movie.__movie_id} - {movie.__title} - {movie.__description} - {movie.__genre}"
        return line
