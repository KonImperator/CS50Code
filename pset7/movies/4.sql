SELECT COUNT(title)
FROM movies
WHERE id
IN (SELECT movie_id FROM ratings WHERE rating = 10);


-- SELECT COUNT(movies.title) AS tally
-- FROM movies
--     JOIN ratings
--     ON movies.id = ratings.movie_id
--     WHERE rating = 10;