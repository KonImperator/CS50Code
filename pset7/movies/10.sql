SELECT DISTINCT name FROM people WHERE id IN
(SELECT person_id from directors WHERE movie_id IN
(SELECT movie_id FROM ratings WHERE rating >= 9));

-- SELECT DISTINCT name
-- FROM people
-- JOIN directors
-- ON directors.person_id = people.id
-- JOIN ratings
-- ON ratings.movie_id = directors.movie_id
-- WHERE ratings.rating >= 9;