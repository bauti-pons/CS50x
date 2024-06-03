SELECT AVG(rating) AS average_rating_of_movies_released_in_2012
FROM ratings
WHERE movie_id IN (
    SELECT id
    FROM movies
    WHERE year = 2012
);
