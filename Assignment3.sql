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
select * from Student s natural join placementDrive p;

/*Query 2*/
select Group_Concat(s.s_name),p.Comp_name from Student s inner join placementDrive p on s.Drive_id = p.Drive_id group by p.Comp_name;
insert into placementDrive (Drive_id,Comp_name ,package , location) values (105 , "Microsoft" , 30000,"Cali");
select Group_Concat(s.s_name),p.Comp_name from Student s right join placementDrive p on s.Drive_id = p.Drive_id group by p.Comp_name;
/*+------------------------+-----------+
| Group_Concat(s.s_name) | Comp_name |
+------------------------+-----------+
| Alice,Eve              | Company A |
| Bob,Grace,Ameya        | Company B |
| Carol,Helen            | Company C |
| David                  | Company D |
| NULL                   | Microsoft |
+------------------------+-----------+*/

/*Query 3*/
select s.s_name , s.s_branch from student s inner join placementDrive p on s.Drive_id=p.Drive_id where p.package = 8;

/*Query 4*/
select s.s_name , t.t_comp_name from student s inner join training t on t.t_id = s.t_id where t.t_fees > 3000;

/*Query 5*/
select * from training t left join student s on s.t_id = t.t_id where t.t_year = 2023 and s.s_name= "Ameya";

/*Query 6*/
select count(t_comp_name) as list from training where t_year < 2023 ;
OR
SELECT COUNT(t_comp_name) AS list
FROM (SELECT t_comp_name FROM training WHERE t_year < 2023) AS subquery;

/*Query 7*/
select s.s_name from student s inner join placementDrive p on s.Drive_id = p.Drive_id where location = "New York" and p.Comp_name = "Company A";
OR
select s_name from student where Drive_id in (select Drive_id from placementDrive where location = "New York" and Comp_name = "Company A");
/*Query 8*/
select s.s_name from student s left join placementDrive p on s.Drive_id = p.Drive_id where p.Comp_name = "Company D";

/*Query 9*/
create view simple_view as select s.s_name,s.s_branch,s.cgpa,t.t_id,t.t_comp_name,t_fees from student s left join training t on s.t_id = t.t_id;

/*Query 10*/
insert into simple_view (s_name,s_branch,cgpa,t_id,t_comp_name,t_fees) values ("John" , "CSE",5,2,"Training Z",3222);
ERROR 1471 (HY000): The target table simple_view of the INSERT is not insertable-into

update simple_view set s_name = "John" where t_id = 4;

delete from simple_view where cgpa = 9;
ERROR 1288 (HY000): The target table simple_view of the DELETE is not updatable

drop view simple_view;
