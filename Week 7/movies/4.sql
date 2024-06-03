SELECT COUNT(*) AS number_of_movies_with_10_rating
FROM movies
WHERE id IN
(
    SELECT movie_id
    FROM ratings
    WHERE rating = 10
);
