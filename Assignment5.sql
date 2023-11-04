create table Stud_marks(Name varchar(25), Total_marks int);

create table Result(Name varchar(25),Total_marks int, Class varchar(25));

INSERT INTO Stud_marks (Name, Total_marks) VALUES
     ('John', 1200),
     ('Alice', 950),
     ('Bob', 1350),
     ('Eve', 800),
     ('Grace', 1100),
     ('David', 1400),
     ('Carol', 750),
     ('Michael', 1600),
     ('Sophia', 720),
     ('Oliver', 1480);

/*Only Procedure*/
demlimter $$
create procedure class(Name varchar(25), total_marks int)
begin
if (total_marks >=990 and total_marks<=1500) then
	insert into Result (Name , Total_marks , Class ) values ( Name , total_marks , "Distinction");
elseif (total_marks >=900 and total_marks<=989) then
	insert into Result (Name , Total_marks , Class ) values ( Name , total_marks , "First Class");
elseif (total_marks >=825 and total_marks<=899) then
	insert into Result (Name , Total_marks , Class ) values ( Name , total_marks , "Second Class");
else
select "Marks out of Range" as Error;
end if;
end
$$ 

/*Procedure and Function*/
DELIMITER $$
CREATE FUNCTION calculate_grade(total_marks INT)
RETURNS VARCHAR(25)
DETERMINISTIC
BEGIN
    DECLARE grade VARCHAR(25);
    
    IF total_marks BETWEEN 990 AND 1500 THEN
        SET grade = 'Distinction';
    ELSEIF total_marks BETWEEN 900 AND 989 THEN
        SET grade = 'First Class';
    ELSEIF total_marks BETWEEN 825 AND 899 THEN
        SET grade = 'Second Class';
    ELSE
        SET grade = 'Marks out of Range';
    END IF;

    RETURN grade;
END
$$
DELIMITER ;

delimiter $$
create procedure calc(in Name varchar(25), in total_marks int , out grade varchar(25))
begin
set grade = calculate_grade(total_marks);
insert into Result (Name , Total_marks , Class ) values ( Name , total_marks , grade);
end;
$$
delimiter ;

/*FOR Loop*/
DELIMITER $$
CREATE PROCEDURE calculate_and_insert_grades()
BEGIN
    -- Declare a variable to indicate when the loop is done.
    DECLARE done INT DEFAULT 0;

    -- Declare variables to store student_name and marks.
    DECLARE student_name VARCHAR(25);
    DECLARE marks INT;

    -- Declare a cursor to select data from the source table.
    DECLARE cur CURSOR FOR SELECT Name, Total_marks FROM Stud_marks;

    -- Define a handler to detect the end of the cursor result set.
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;

    -- Open the cursor to start retrieving data.
    OPEN cur;

    -- Start a loop to process each record from the cursor.
    read_loop: LOOP
        -- Fetch the student_name and marks for the current record.
        FETCH  cur INTO student_name, marks;

        -- Check if there are no more records to process.
        IF done THEN
            LEAVE read_loop; -- Exit the loop.
        END IF;

        -- Declare a variable to store the calculated grade.
        DECLARE grade VARCHAR(25);
        -- Calculate the grade using the calculate_grade() function.
        SET grade = calculate_grade(marks);

        -- Insert the student's name, marks, and grade into the Result table.
        INSERT INTO Result (Name, Total_marks, Class) VALUES (student_name, marks, grade);
    END LOOP;

    -- Close the cursor as it's no longer needed.
    CLOSE cur;
END;
$$
DELIMITER ;




create procedure calculate_loop()
begin
declare done int default 0;
declare student_name varchar(25);
declare marks int;
declare grade varchar(25);
declare cur Cursor for Select Name,Total_marks from Stud_marks;
declare continue handler for not found set done = 1;
open cur;
read_loop: LOOP
fetch cur into student_name,marks;
if done then
leave read_loop;
end if;
set grade = calculate_grade(marks);
INSERT INTO Result (Name, Total_marks, Class) VALUES (student_name, marks, grade);
end LOOP;
close cur;
end;
$$
