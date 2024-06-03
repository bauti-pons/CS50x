-- IDENTIFY: Who the thief is.
SELECT name
FROM people
WHERE id IN (
    SELECT people.id
    FROM people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    WHERE atm_transactions.year = 2023 AND atm_transactions.month = 7 AND atm_transactions.day = 28
    AND atm_transactions.atm_location = 'Leggett Street'
    AND atm_transactions.transaction_type = 'withdraw'
)
AND name IN (
    SELECT people.name
    FROM people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    WHERE atm_transactions.year = 2023 AND atm_transactions.month = 7 AND atm_transactions.day = 28
    AND atm_transactions.atm_location = 'Leggett Street'
    AND atm_transactions.transaction_type = 'withdraw'
)
AND phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2023 AND month = 7 AND day = 28
    AND duration < 60
)
AND passport_number IN (
    SELECT passengers.passport_number
    FROM passengers
    JOIN flights ON passengers.flight_id = flights.id
    JOIN airports ON flights.origin_airport_id = airports.id
    WHERE flights.id IN (
        SELECT id
        FROM flights
        WHERE year = 2023 AND month = 7 AND day = 29
        ORDER BY hour
        LIMIT 1
    )
    AND airports.id = (
        SELECT id
        FROM airports
        WHERE city = 'Fiftyville'
    )
)
AND license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2023 AND month = 7 AND day = 28
    AND hour = 10 AND minute >= 15 AND minute <= 25
    AND activity = 'exit'
);


-- IDENTIFY: What city the thief escaped to.
SELECT city
FROM airports
WHERE id = (
    SELECT destination_airport_id
    FROM flights
    WHERE id = (
        SELECT id
        FROM flights
        WHERE year = 2023 AND month = 7 AND day = 29
        ORDER BY hour
        LIMIT 1
    )
);


-- IDENTIFY: Who the thief’s accomplice is who helped them escape town.
SELECT people.name
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE year = 2023 AND month = 7 AND day = 28
AND duration < 60
AND phone_calls.caller = (
    SELECT phone_number
    FROM people
    WHERE id IN (
        SELECT people.id
        FROM people
        JOIN bank_accounts ON people.id = bank_accounts.person_id
        JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
        WHERE atm_transactions.year = 2023 AND atm_transactions.month = 7 AND atm_transactions.day = 28
        AND atm_transactions.atm_location = 'Leggett Street'
        AND atm_transactions.transaction_type = 'withdraw'
    )
    AND name IN (
        SELECT people.name
        FROM people
        JOIN bank_accounts ON people.id = bank_accounts.person_id
        JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
        WHERE atm_transactions.year = 2023 AND atm_transactions.month = 7 AND atm_transactions.day = 28
        AND atm_transactions.atm_location = 'Leggett Street'
        AND atm_transactions.transaction_type = 'withdraw'
    )
    AND phone_number IN (
        SELECT caller
        FROM phone_calls
        WHERE year = 2023 AND month = 7 AND day = 28
        AND duration < 60
    )
    AND passport_number IN (
        SELECT passengers.passport_number
        FROM passengers
        JOIN flights ON passengers.flight_id = flights.id
        JOIN airports ON flights.origin_airport_id = airports.id
        WHERE flights.id IN (
            SELECT id
            FROM flights
            WHERE year = 2023 AND month = 7 AND day = 29
            ORDER BY hour
            LIMIT 1
        )
        AND airports.id = (
            SELECT id
            FROM airports
            WHERE city = 'Fiftyville'
        )
    )
    AND license_plate IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE year = 2023 AND month = 7 AND day = 28
        AND hour = 10 AND minute >= 15 AND minute <= 25
        AND activity = 'exit'
    )
);


--------------------------------------------------------------------------


-- Find crime scene description.
SELECT description
FROM crime_scene_reports
WHERE year = 2023 AND month = 7 AND day = 28
AND street = 'Humphrey Street';
--> "Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
--   Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery."
--  "Littering took place at 16:36. No known witnesses."


-- Find crime scene interviews.
SELECT transcript
FROM interviews
WHERE year = 2023 AND month = 7 AND day = 28;
--> TIME CLUE:  "Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--              If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame."
--  ATM CLUE: "I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
--             I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money. "
--  FLIGHT CLUE: "As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call,
--                I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--                The thief then asked the person on the other end of the phone to purchase the flight ticket."


-- Follow the bakery clue.
-- Get the potential plate of the thief, who had to leave the bakery between 10:15am and 10:25am.
SELECT hour, minute, license_plate
FROM bakery_security_logs
WHERE year = 2023 AND month = 7 AND day = 28
AND hour = 10 AND minute >= 15 AND minute <= 25
AND activity = 'exit';


-- Follow the ATM clue.
-- Get the potential id and name of the thief by his account number.
SELECT people.id, people.name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.year = 2023 AND atm_transactions.month = 7 AND atm_transactions.day = 28
AND atm_transactions.atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw';


-- Follow the phone call clue.
-- Get a list of potential phone numbers of the thief and his accomplice.
SELECT caller, receiver
FROM phone_calls
WHERE year = 2023 AND month = 7 AND day = 28
AND duration < 60;


-- Follow the flight clue.
-- Get a list of potential passport numbers of the thief and his accomplice.
SELECT passengers.passport_number
FROM passengers
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.origin_airport_id = airports.id
WHERE flights.id IN (
    SELECT id
    FROM flights
    WHERE year = 2023 AND month = 7 AND day = 29
    ORDER BY hour
    LIMIT 1
)
AND airports.id = (
    SELECT id
    FROM airports
    WHERE city = 'Fiftyville'
);
