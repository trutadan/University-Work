CREATE TABLE superhero (
    id serial PRIMARY KEY,
    name VARCHAR (255) UNIQUE NOT NULL,
    powers VARCHAR (255) NOT NULL
);

CREATE TABLE team (
    id serial PRIMARY KEY,
    name VARCHAR (255) UNIQUE NOT NULL,
    superherosList VARCHAR (255) NOT NULL
);

INSERT INTO superhero (name, powers) VALUES ('Superman', 'flight, strength, speed');
INSERT INTO superhero (name, powers) VALUES ('Batman', 'intelligence, wealth');

INSERT INTO team (name, superherosList) VALUES ('Justice League', 'Superman, Batman');