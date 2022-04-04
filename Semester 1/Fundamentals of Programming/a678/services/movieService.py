from src.domain.movie import Movie
from src.exceptions_and_validators.validator import MovieValidator


class MovieServices:
    def __init__(self, movie_repository):
        self.__movie_repository = movie_repository

    def generate_movies_data(self):
        """Create 21 procedurally generated movies in the application at startup."""
        self.__movie_repository.add(Movie(11, 'The Shawshank Redemption', 'Two imprisoned men bond over a number of years, finding solace and eventual redemption through acts of common decency.', 'Drama'))
        self.__movie_repository.add(Movie(3, 'The Godfather', 'The Godfather follows Vito Corleone Don of the Corleone family as he passes the mantel to his son Michael.', 'Crime'))
        self.__movie_repository.add(Movie(23, 'The Dark Knight', 'When the menace known as the Joker wreaks havoc and chaos on the people of Gotham, Batman must accept one of the greatest psychological and physical tests of his ability to fight injustice.', 'Action'))
        self.__movie_repository.add(Movie(8, '12 Angry Men', 'The jury in a New York City murder trial is frustrated by a single member whose skeptical caution forces them to more carefully consider the evidence before jumping to a hasty verdict.', 'Crime'))
        self.__movie_repository.add(Movie(91, 'The Lord of the Rings: The Return of the King', "Gandalf and Aragorn lead the World of Men against Sauron's army to draw his gaze from Frodo and Sam as they approach Mount Doom with the One Ring.", 'Adventure'))
        self.__movie_repository.add(Movie(54, "Schindler's List", 'In German-occupied Poland during World War II, industrialist Oskar Schindler gradually becomes concerned for his Jewish workforce after witnessing their persecution by the Nazis.', 'Biography'))
        self.__movie_repository.add(Movie(82, 'Pulp Fiction', 'The lives of two mob hitmen, a boxer, a gangster and his wife, and a pair of diner bandits intertwine in four tales of violence and redemption.', 'Drama'))
        self.__movie_repository.add(Movie(42, 'The Matrix', 'When a beautiful stranger leads computer hacker Neo to a forbidding underworld, he discovers the shocking truth--the life he knows is the elaborate deception of an evil cyber-intelligence.', 'Sci-Fi'))
        self.__movie_repository.add(Movie(19, 'Goodfellas', 'The story of Henry Hill and his life in the mob, covering his relationship with his wife Karen Hill and his mob partners Jimmy Conway and Tommy DeVito in the Italian-American crime syndicate.', 'Biography'))
        self.__movie_repository.add(Movie(77, 'Gisaengchung', 'Greed and class discrimination threaten the newly formed symbiotic relationship between the wealthy Park family and the destitute Kim clan.', 'Thriller'))
        self.__movie_repository.add(Movie(30, 'Cidade de Deus', "In the slums of Rio, two kids' paths diverge as one struggles to become a photographer and the other a kingpin.", 'Drama'))
        self.__movie_repository.add(Movie(13, 'Saving Private Ryan', 'Following the Normandy Landings, a group of U.S. soldiers go behind enemy lines to retrieve a paratrooper whose brothers have been killed in action.', 'War'))
        self.__movie_repository.add(Movie(71, 'La vita è bella', 'When an open-minded Jewish waiter and his son become victims of the Holocaust, he uses a perfect mixture of will, humor, and imagination to protect his son from the dangers around their camp.', 'Romance'))
        self.__movie_repository.add(Movie(64, 'Shichinin no samurai', 'A poor village under attack by bandits recruits seven unemployed samurai to help them defend themselves.', 'Action'))
        self.__movie_repository.add(Movie(1, 'Whiplash', "A promising young drummer enrolls at a cut-throat music conservatory where his dreams of greatness are mentored by an instructor who will stop at nothing to realize a student's potential.", 'Music'))
        self.__movie_repository.add(Movie(98, 'Gladiator', 'A former Roman General sets out to exact vengeance against the corrupt emperor who murdered his family and sent him into slavery.', 'Adventure'))
        self.__movie_repository.add(Movie(55, 'Back to the Future', 'Marty McFly, a 17-year-old high school student, is accidentally sent thirty years into the past in a time-traveling DeLorean invented by his close friend, the eccentric scientist Doc Brown.', 'Sci-Fi'))
        self.__movie_repository.add(Movie(34, 'Casablanca', 'A cynical expatriate American cafe owner struggles to decide whether or not to help his former lover and her fugitive husband escape the Nazis in French Morocco.', 'War'))
        self.__movie_repository.add(Movie(94, 'Joker', 'In Gotham City, mentally troubled comedian Arthur Fleck is disregarded and mistreated by society. He then embarks on a downward spiral of revolution and bloody crime. This path brings him face-to-face with his alter-ego: the Joker.', 'Drama'))
        self.__movie_repository.add(Movie(58, 'Django Unchained', 'With the help of a German bounty-hunter, a freed slave sets out to rescue his wife from a brutal plantation-owner in Mississippi.', 'Western'))
        self.__movie_repository.add(Movie(5, 'Hamilton', "The real life of one of America's foremost founding fathers and first Secretary of the Treasury, Alexander Hamilton. Captured live on Broadway from the Richard Rodgers Theater with the original Broadway cast.", 'History'))

    def add_movie_to_repository(self, movie_id, movie_title, movie_description, movie_genre):
        movie = Movie(movie_id, movie_title, movie_description, movie_genre)
        MovieValidator.validate(movie)
        self.__movie_repository.add(movie)

    def remove_movie_from_repository(self, movie_id):
        movie = Movie(movie_id, "Test title", "Test description", "Test genre")
        MovieValidator.validate(movie)
        self.__movie_repository.remove(movie_id)

    def update_movie_from_repository(self, movie_id, movie_title, movie_description, movie_genre):
        movie = Movie(movie_id, movie_title, movie_description, movie_genre)
        MovieValidator.validate(movie)
        self.__movie_repository.update(movie)

    def search_movie_by_id(self, movie_id):
        movies = self.__movie_repository.get_all()
        for movie in movies:
            if movie.get_id() == movie_id:
                return movie
        return None

    def search_movies_by_title(self, movie_title):
        movies = self.__movie_repository.get_all()
        movies_with_given_name = list()
        for movie in movies:
            if movie.get_title().lower() == movie_title.lower() or movie_title.lower() in movie.get_title().lower():
                movies_with_given_name.append(movie)
        return movies_with_given_name

    def search_movies_by_description(self, movie_description):
        movies = self.__movie_repository.get_all()
        movies_with_given_description = list()
        for movie in movies:
            if movie.get_description().lower() == movie_description.lower() or movie_description.lower() in movie.get_description().lower():
                movies_with_given_description.append(movie)
        return movies_with_given_description

    def search_movies_by_genre(self, movie_genre):
        movies = self.__movie_repository.get_all()
        movies_with_given_genre = list()
        for movie in movies:
            if movie.get_genre().lower() == movie_genre.lower() or movie_genre.lower() in movie.get_genre().lower():
                movies_with_given_genre.append(movie)
        return movies_with_given_genre

    def get_all_movies(self):
        return self.__movie_repository.get_all()
