USE cinema_booking_system; 

# Shows movie sessions where each film is over 2 hours long.
SELECT id, start_time FROM screenings WHERE film_id IN 
(SELECT id FROM films WHERE length_min > 120);

# Shows customers who reserved seats on movie session
SELECT first_name, last_name, email from customers
WHERE id IN ( SELECT customer_id FROM bookings
WHERE screening_id = 1);

# Shows average reserved seats and maximum reserved seats by customers
SELECT AVG(no_seats) AS AVG_seat, MAX(no_seats) FROM 
(SELECT booking_id, COUNT(seat_id) AS no_seats FROM reserved_seat
GROUP BY booking_id) b;

# Select the film name and count the number of screenings for each film that is over 2 hours long.
SELECT f.name, f.length_min, COUNT(s.id) FROM films f
JOIN screenings s ON f.id = s.film_id 
GROUP BY f.name, f.length_min
HAVING f.length_min > 120;

# Select the maximum number and the minimum number of screenings for a particular film.
SELECT MAX(id), MIN(id) FROM
(SELECT film_id, COUNT(id) AS id FROM screenings
GROUP BY film_id) a;

# Select each film name and the number of screenings for that film.
SELECT name, 
(SELECT COUNT(id) AS no_screenings FROM screenings 
WHERE film_id = f.id
) AS no_screenings
FROM films f;

DELIMITER //
CREATE FUNCTION check_seats(movie_session INT) RETURNS INT DETERMINISTIC
BEGIN
	DECLARE av_seats INT;
	DECLARE room_seats INT;
	SET room_seats = (SELECT COUNT(id) FROM seats 
	WHERE room_id IN (SELECT room_id FROM screenings 
	WHERE id = movie_session));
	SELECT room_seats - SUM(
	(SELECT COUNT(seat_id) FROM reserved_seat 
	WHERE booking_id = b.id)) INTO av_seats
	FROM bookings AS  b 
	WHERE (screening_id = movie_session);
	RETURN (av_seats);
END
//
# Check free seats by one movie session
SELECT check_seats(1) AS available_seats;
//
# Check free seats on movie sessions
SELECT s.id AS movie_session, check_seats(s.id) AS available_seats FROM screenings AS s ORDER BY s.id;
//
#Reserved seats
SELECT rs.seat_id FROM bookings as b INNER JOIN reserved_seat as rs INNER JOIN seats as s
	WHERE screening_id = 1 AND rs.booking_id = b.id AND rs.seat_id = s.id;
//

CREATE PROCEDURE available_seats(movie_session INT)
IF(SELECT check_seats(movie_session) > 0) THEN
	SELECT DISTINCT s.id AS seat_id, row_seat, number
    FROM bookings AS b INNER JOIN reserved_seat AS rs INNER JOIN seats AS s
	WHERE screening_id = movie_session 
    AND s.room_id = (SELECT room_id FROM screenings WHERE id = movie_session) 
    AND s.id NOT IN (SELECT rs.seat_id FROM bookings AS b INNER JOIN reserved_seat AS rs INNER JOIN seats AS s
	WHERE screening_id = movie_session AND rs.booking_id = b.id AND rs.seat_id = s.id) ORDER BY s.id ASC;
ELSE
    SELECT 'All seats on this movie session are reserved!' AS '';
END IF;
//

# Check seats
CALL available_seats(1);

//

CREATE FUNCTION create_customer(f_name VARCHAR(45), l_name VARCHAR(45), customer_email VARCHAR(45)) RETURNS INT DETERMINISTIC
	BEGIN
		DECLARE id INT;
		INSERT INTO customers(first_name, last_name, email) VALUES (f_name, l_name, customer_email);
        SELECT c.id INTO id FROM customers AS c WHERE customer_email = c.email;
        RETURN (id);
    END
//

# Create new a new customer 
SELECT create_customer('test2', 'test2', 'test2@mail.com') AS id;

//
DROP FUNCTION IF EXISTS reserve_seat;
CREATE FUNCTION reserve_seat(movie_session INT, booking_customer_id INT, booking_seat_id INT) RETURNS VARCHAR(100) DETERMINISTIC
	BEGIN
		DECLARE output VARCHAR(100);
		IF booking_seat_id NOT IN (SELECT seat_id FROM reserved_seat AS r INNER JOIN bookings AS b ON b.id = r.booking_id 
        WHERE b.screening_id = movie_session) THEN
			INSERT INTO bookings (screening_id, customer_id) VALUES (movie_session, booking_customer_id);
            INSERT INTO reserved_seat (booking_id, seat_id) VALUES (LAST_INSERT_ID(), booking_seat_id);
			SET output = CONCAT('Booking succesfull! Seat ', booking_seat_id, ' reserved by user with id ', booking_customer_id);		
		ELSE
			SET output = 'Seat already taken!';
		END IF;
		RETURN (output);
    END
//
# for new customer #movies session, user_info, seat_id
SELECT reserve_seat(1, create_customer('name','lastname','email'), 9) as booking_result;
# for exists customer #movies session, user_id, seat_id
SELECT reserve_seat(1, 124, 12) as booking_result;
//



