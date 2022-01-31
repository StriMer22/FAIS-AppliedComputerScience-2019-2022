# Kolokwium
CREATE TABLE author(author_id INT PRIMARY KEY AUTO_INCREMENT, author_name VARCHAR(45), author_surname VARCHAR(45));
CREATE TABLE category(category_id INT PRIMARY KEY AUTO_INCREMENT, category_name VARCHAR(45));
CREATE TABLE books(book_id INT PRIMARY KEY AUTO_INCREMENT, name_book VARCHAR(45), autor_id INT NOT NULL, category_id INT NOT NULL, 
FOREIGN KEY (autor_id) references author(author_id),
FOREIGN KEY (category_id) REFERENCES category(category_id));
CREATE TABLE person(person_id INT PRIMARY KEY AUTO_INCREMENT, person_name VARCHAR(45), person_surname VARCHAR(45));

CREATE TABLE borrows(borrow_id INT PRIMARY KEY AUTO_INCREMENT, person_borrow INT NOT NULL, book_id INT NOT NULL, taken_date DATE, brought_date DATE, fee INT DEFAULT 1,
FOREIGN KEY (person_borrow) REFERENCES person(person_id),
FOREIGN KEY (book_id) REFERENCES books(book_id));
  
  
DELIMITER //
DROP PROCEDURE IF EXISTS chargeFee;
CREATE PROCEDURE chargeFee(take_borrow_id INT)
	BEGIN
		DECLARE difference INT;
        DECLARE days INT;
        SET difference = (SELECT DATEDIFF(CURRENT_DATE, return_time) from borrows WHERE borrow_id = take_borrow_id);
        SET days = (SELECT b.days from borrows as b where b.borrow_id = take_borrow_id);
		IF(difference > days)THEN
			UPDATE borrows as b set b.brought_date = CURRENT_DATE where b.borrow_id = take_borrow_id;
			UPDATE borrows as b set b.days = difference where b.borrow_id = take_borrow_id;
			UPDATE borrows as b set b.fee = (difference-days)*5 where b.borrow_id = take_borrow_id;
		ELSE
			SELECT 'not need to update' as '';
        END IF;
    END
//
CALL chargeFee(11);
//
DROP PROCEDURE IF EXISTS sortBorrow;
CREATE PROCEDURE sortBorrow()
	BEGIN
		SELECT person_borrow, count(person_borrow) as number_of_borrow FROM borrows GROUP BY person_borrow ORDER BY count(person_borrow) DESC;
	END;
//
CALL sortBorrow();
