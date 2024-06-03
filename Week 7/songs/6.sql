-- The names of songs that are by Post Malone.
SELECT name FROM songs WHERE artist_id =
(
    -- Identify Post Malone's artist id
    SELECT id FROM artists WHERE name = 'Post Malone'
);
