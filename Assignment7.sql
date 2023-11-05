create table Library(book_id int primary key , book_name varchar(25),author varchar(25),published_year int);

CREATE TABLE Library_Audit (
         audit_id INT PRIMARY KEY,
         action_type VARCHAR(10),
         book_id INT,
         book_name VARCHAR(255),
         author VARCHAR(255),
         published_year INT,
         audit_timestamp TIMESTAMP
);

/*Before Insert*/
create trigger before_insert 
before insert on Library 
for each row 
begin 
insert into Library_Audit (action_type,book_id,book_name,author,published_year,audit_timestamp) values 
("Before Insert",NEW.book_id,NEW.book_name,NEW.author,NEW.published_year,NOW());
end;
$$

/*After Insert*/
create trigger after_insert 
after insert on Library 
for each row 
begin 
insert into Library_Audit (action_type,book_id,book_name,author,published_year,audit_timestamp) values 
("After Insert",NEW.book_id,NEW.book_name,NEW.author,NEW.published_year,NOW());
end;
$$

alter table Library_Audit modify column action_type varchar(25);

INSERT INTO Library (book_id, book_name, author, published_year) VALUES (2, 'Book 2', 'Author 2', 2002);
/* 
select * from Library_Audit;
+---------------+---------+-----------+----------+----------------+---------------------+
| action_type   | book_id | book_name | author   | published_year | audit_timestamp     |
+---------------+---------+-----------+----------+----------------+---------------------+
| Before Insert |       1 | Book 1    | Author 1 |           2022 | 2023-11-05 18:29:22 |
| After Insert  |       1 | Book 1    | Author 1 |           2022 | 2023-11-05 18:29:22 |
+---------------+---------+-----------+----------+----------------+---------------------+
*/

/*Before Update*/
create trigger before_update 
before update on Library 
for each row 
begin 
insert into Library_Audit (action_type,book_id,book_name,author,published_year,audit_timestamp) values 
("Before Update",OLD.book_id,OLD.book_name,OLD.author,OLD.published_year,NOW());
end;
$$
UPDATE Library SET book_name = 'Updated 2' WHERE book_id = 2;
+---------------+---------+-----------+----------+----------------+---------------------+
| action_type   | book_id | book_name | author   | published_year | audit_timestamp     |
+---------------+---------+-----------+----------+----------------+---------------------+
| Before Insert |       1 | Book 1    | Author 1 |           2022 | 2023-11-05 18:29:22 |
| After Insert  |       1 | Book 1    | Author 1 |           2022 | 2023-11-05 18:29:22 |
| Before Insert |       2 | Book 2    | Author 2 |           2002 | 2023-11-05 18:41:17 |
| After Insert  |       2 | Book 2    | Author 2 |           2002 | 2023-11-05 18:41:17 |
| Before Update |       2 | Book 2    | Author 2 |           2002 | 2023-11-05 18:42:54 | <-------
+---------------+---------+-----------+----------+----------------+---------------------+

/*After Update*/
create trigger after_update 
after update on Library 
for each row 
begin 
insert into Library_Audit (action_type,book_id,book_name,author,published_year,audit_timestamp) values 
("After Update",NEW.book_id,NEW.book_name,NEW.author,NEW.published_year,NOW());
end;
$$
UPDATE Library SET book_name = 'Updated 1' WHERE book_id = 2;
+---------------+---------+-----------+----------+----------------+---------------------+
| action_type   | book_id | book_name | author   | published_year | audit_timestamp     |
+---------------+---------+-----------+----------+----------------+---------------------+
| Before Insert |       1 | Book 1    | Author 1 |           2022 | 2023-11-05 18:29:22 |
| After Insert  |       1 | Book 1    | Author 1 |           2022 | 2023-11-05 18:29:22 |
| Before Insert |       2 | Book 2    | Author 2 |           2002 | 2023-11-05 18:41:17 |
| After Insert  |       2 | Book 2    | Author 2 |           2002 | 2023-11-05 18:41:17 |
| Before Update |       2 | Book 2    | Author 2 |           2002 | 2023-11-05 18:42:54 |
| After Update  |       2 | Updated 1 | Author 2 |           2002 | 2023-11-05 18:45:26 |
+---------------+---------+-----------+----------+----------------+---------------------+

/*Before Delete*/
create trigger before_delete 
before delete on Library 
for each row 
begin 
insert into Library_Audit (action_type,book_id,book_name,author,published_year,audit_timestamp) values 
("Before Delete",OLD.book_id,OLD.book_name,OLD.author,OLD.published_year,NOW());
end;
$$

DELETE FROM Library WHERE book_id = 2;
+---------------+---------+-----------+----------+----------------+---------------------+
| action_type   | book_id | book_name | author   | published_year | audit_timestamp     |
+---------------+---------+-----------+----------+----------------+---------------------+
| Before Insert |       1 | Book 1    | Author 1 |           2022 | 2023-11-05 18:29:22 |
| After Insert  |       1 | Book 1    | Author 1 |           2022 | 2023-11-05 18:29:22 |
| Before Insert |       2 | Book 2    | Author 2 |           2002 | 2023-11-05 18:41:17 |
| After Insert  |       2 | Book 2    | Author 2 |           2002 | 2023-11-05 18:41:17 |
| Before Update |       2 | Book 2    | Author 2 |           2002 | 2023-11-05 18:42:54 |
| After Update  |       2 | Updated 1 | Author 2 |           2002 | 2023-11-05 18:45:26 |
| Before Delete |       2 | Updated 1 | Author 2 |           2002 | 2023-11-05 18:50:34 |
+---------------+---------+-----------+----------+----------------+---------------------+
