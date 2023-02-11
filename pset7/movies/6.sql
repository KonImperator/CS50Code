SELECT AVG(rating)
FROM ratings
WHERE movie_id IN
(SELECT id FROM movies WHERE year = 2012);

-- SELECT AVG(ratings.rating)
-- FROM ratings
-- JOIN movies
-- ON movies.id = ratings.movie_id
-- WHERE movies.year = 2012;