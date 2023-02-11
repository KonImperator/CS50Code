SELECT DISTINCT name FROM people WHERE id IN
(SELECT person_id FROM stars WHERE movie_id IN
(SELECT id FROM movies WHERE year = 2004))
ORDER BY birth ASC;

-- SELECT DISTINCT name
-- FROM people
-- JOIN stars
-- ON stars.person_id = people.id
-- JOIN movies
-- ON stars.movie_id = movies.id
-- WHERE movies.year = 2004
-- ORDER BY people.birth ASC;