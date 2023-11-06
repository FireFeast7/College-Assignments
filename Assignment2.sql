create table Student( s_id int , Drive_id int ,t_id int , s_name varchar(25) , cgpa int , s_branch varchar(25) , s_dob date);

alter table Student add primary key (s_id);

create table PlacementDrive(Drive_id int unique primary key , Comp_name varchar(25) , package int , location varchar(25));

alter table Student add foreign key (Drive_id) references PlacementDrive(Drive_id);

create table Training(t_id int unique primary key , t_comp_name varchar(25) , t_fees int , t_year int);

INSERT INTO PlacementDrive (Drive_id, Comp_name, package, location)
VALUES
    (101, 'Company A', 9.5, 'New York'),
    (102, 'Company B', 8.2, 'San Fran'),
    (103, 'Company C', 10.0, 'Seattle'),
    (104, 'Company D', 7.8, 'Chicago');

INSERT INTO Student (s_id, Drive_id, s_name, cgpa, s_branch, s_dob)
VALUES
    (1, 101, 'Alice', 3.8, 'CSE', '2000-05-15'),
    (2, 102, 'Bob', 3.6, 'ECE', '1999-09-22'),
    (3, 103, 'Carol', 3.9, 'Mech', '2001-03-10'),
    (4, 104, 'David', 3.5, 'CSE', '2000-12-05');
    (5, 101, 'Eve', 3.7, 'ECE', '2000-07-12'),
    (6, 104, 'Frank', 3.4, 'Mech', '2000-10-25'),
    (7, 102, 'Grace', 3.9, 'CSE', '2001-01-19'),
    (8, 103, 'Helen', 3.5, 'ECE', '2001-04-30');

INSERT INTO Training (t_id, t_comp_name, t_fees, t_year)
VALUES
    (1, 'Training Co', 2000, 2022),
    (2, 'Training X', 2500, 2023);
    (3, 'Training Y', 2200, 2023),
    (4, 'Training Z', 1800, 2022);

/*Query 1*/
select * from Student where (s_branch = "CSE") and s_name like "A%" or s_name like "D%" ;

/*Query 2*/
select count(distinct Comp_name) as Different_Companies from placementDrive;

/*Query 3*/
update training set t_fees = t_fees + t_fees*1.5 where t_year = 2023;

/*Query 4*/
delete from student where cgpa < 4;

/*Query 5*/
select Comp_name from placementDrive where location in ("New York","San Fran");

/*Query 6*/
select s_name from student s,training t where s.t_id = t.t_id and t_year between 2020 and 2022;

/*Query 7*/
select s_name,cgpa from student where cgpa = (select max(cgpa) from student);
select s_name,cgpa from student where cgpa between 7 and 9;

/*Query 8*/
select s.s_name ,t.t_fees from student s , training t where t.t_id = s.t_id order by t_fees desc;

/*Query 9*/
select p.Comp_name,s.s_name,p.location,p.package from student s, placementDrive p where s.Drive_id = p.Drive_id and package in (8,10);

create index index_1 on student(s_id,cgpa);
create unique index index_2 on student(s_id,cgpa,dob,s_branch); 