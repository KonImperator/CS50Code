-- Keep a log of any SQL queries you execute as you solve the mystery.
-- ************ The THIEF is: Bruce ************
/*Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.*/
-- ************ The city the thief ESCAPED TO: New York City ************
/*I don't know the thief's name, but it was someone I recognized.
Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.*/
-- ************ The ACCOMPLICE is: Robin ************
/*As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
The thief then asked the person on the other end of the phone to purchase the flight ticket.*/

SELECT * FROM crime_scene_reports WHERE description LIKE "%duck%"; -- Getting info on the crime scene details to know what to go after. Specifying with duck.

/* Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
Interviews with three witnesses – transcripts mentions the bakery. Description from July 28th 2021.*/

SELECT * FROM interviews WHERE transcript LIKE "%bakery%"; -- Getting info from the stories of the witnesses. Specifying with bakery.

SELECT * -- Getting licence plates to search for the thief's car. Specifying time and activity.
FROM bakery_security_logs
WHERE year = 2021 AND day = 28 AND month = 7 AND hour = 10 AND minute >= 5 AND minute <= 25 AND activity = "exit";

SELECT * -- Getting all ATM transactions. Specifying location, type and date. (post-factum - Did I use this one? I don't think I did :/)
FROM atm_transactions
WHERE year = 2021 AND day = 28 AND month = 7 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";

SELECT * -- Getting the phone numbers of the caller and receiver. Specifying duration and date.
FROM phone_calls
WHERE duration < 60 AND year = 2021 AND day = 28 AND month = 7;

SELECT * -- Getting the origin and destination of the thief. (8/4)
FROM flights
WHERE year = 2021 AND day = 29 AND month = 7
ORDER BY hour ASC, minute ASC;

SELECT id -- Getting exact id of thief's flight to reference after
FROM flights
WHERE origin_airport_id = 8 AND destination_airport_id = 4 AND year = 2021 AND day = 29 AND month = 7;

/*Building up query (post-factum - eventually started doing it wihout adding the separate queries on new rows so I built it up in one go)*/
SELECT passport_number FROM passengers
WHERE flight_id IN
(SELECT id FROM flights WHERE origin_airport_id = 8 AND destination_airport_id = 4 AND year = 2021 AND day = 29 AND month = 7);

SELECT * FROM airports; -- Checking IDs 8 and 4 > Fiftyville Regional (origin) and LaGuardia (destination - New York City) > Escaped to this city

/* Queued up a lot of queries by reverse engineering step by step using all the info for
licence plates, passport numbers, phone numbers and flight id
and eventually narrowed down the person_id of the thief, who took out money from the ATM */
SELECT *
FROM bank_accounts
WHERE person_id
IN
(SELECT id FROM people WHERE passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id FROM flights WHERE origin_airport_id = 8 AND destination_airport_id = 4 AND year = 2021 AND day = 29 AND month = 7))
INTERSECT
SELECT id FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs
WHERE year = 2021 AND day = 28 AND month = 7 AND hour = 10 AND minute >= 5 AND minute <= 25 AND activity = "exit")
INTERSECT
SELECT id FROM people WHERE phone_number IN
(SELECT caller FROM phone_calls WHERE duration < 60 AND year = 2021 AND day = 28 AND month = 7));

SELECT *
FROM people
WHERE id = 686048; -- Locating thief

SELECT * -- Locating accomplice through his phone number
FROM people
WHERE phone_number
IN
(SELECT receiver FROM phone_calls WHERE caller IN
(SELECT phone_number FROM people WHERE id = 686048)
AND duration < 60 AND year = 2021 AND day = 28 AND month = 7);

-- Style looks janky, not sure if you still need to do newlines for everything after IN, would make for a veeery tall query :/