create table Employee(Name varchar(25),E_id int primary key  , E_dept varchar(25));

create table Intern(Name varchar(25),I_id int auto_increment primary key  , I_dept varchar(25));

INSERT INTO Intern (Name, I_dept) VALUES
    ('Alice', 'HR'),
    ('Bob', 'Marketing'),
    ('Carol', 'IT'),
    ('David', 'Finance'),
    ('Eve', 'HR'),
    ('Frank', 'IT'),
    ('Grace', 'Marketing'),
    ('Helen', 'IT'),
    ('Isabel', 'Finance'),
    ('John', 'Marketing');

/*Implicit Cursor
Implicit cursors are used when executing SQL statements within PL/SQL blocks,
such as in the WHERE clause of a SELECT statement, or during DML (Data Manipulation Language) 
operations like INSERT, UPDATE, and DELETE.
Implicit cursors are limited in terms of flexibility and control. They are suitable 
for simple queries or single-row operations and do not provide direct control over result set navigation.
*/
insert into Intern (Name , I_dept) values ("Ameya" , "Flutter Developer");

/*Explicit Cursor*/
delimiter $$
create procedure explicit_cursor()
begin
declare intern_name varchar(25);
declare dept varchar(25);
declare id int;
declare done int default 0;
declare explicit Cursor for select Name,I_id,I_dept from Intern;
declare continue handler for not found set done = 1;
open explicit;
label:LOOP
fetch explicit into intern_name,id,dept;
if done then
leave label;
end if;
insert into Employee (Name,E_id,E_dept) values (intern_name,id,dept);
end LOOP;
close explicit;
end;
$$
delimiter ;


/*Explicit Cursor (Parameterized)*/
delimiter $$
create procedure parameterized_cursor(start_val int, end_val int)
begin
declare intern_name varchar(25);
declare dept varchar(25);
declare id int;
declare done int default 0;
declare p_cursor Cursor(p_start int, p_end int) for select Name,I_id,I_dept from Intern where I_id between p_start and p_end;
declare continue handler for not found set done = 1;
open p_cursor(start_val,end_val);
label:LOOP
fetch p_cursor into intern_name,id,dept;
if done then
leave label;
end if;
insert into Employee (Name,E_id,E_dept) values (intern_name,id,dept);
end LOOP;
close p_cursor;
end;
$$
delimiter ;

create procedure parameterizedcursor(start_val int, end_val int)
begin
declare intern_name varchar(25);
declare dept varchar(25);
declare id int;
declare done int default 0;
declare p_cursor Cursor(p_start int, p_end int) for select Name,I_id,I_dept from Intern where (I_id between p_start and p_end) and I_dept = "HR" ;
declare continue handler for not found set done = 1;
open p_cursor(start_val,end_val);
label:LOOP
fetch p_cursor into intern_name,id,dept;
if done then
leave label;
end if;
insert into Employee (Name,E_id,E_dept) values (intern_name,id,dept);
end LOOP;
close p_cursor;
end;
$$