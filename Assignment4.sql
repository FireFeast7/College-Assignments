create table Borrower(roll_no int not null , name varchar(25) , date_of_issue date , name_of_book varchar(25) , status varchar(25));
 INSERT INTO Borrower (roll_no, name, date_of_issue, name_of_book) VALUES
         (1, 'John', '2023-10-15', 'Book A'),
         (2, 'Alice', '2023-09-20', 'Book B'),
         (3, 'Bob', '2023-09-25', 'Book C'),
         (4, 'Eve', '2023-10-01', 'Book D'),
         (5, 'Grace', '2023-10-05', 'Book E'),
         (6, 'David', '2023-10-10', 'Book F'),
         (7, 'Carol', '2023-10-02', 'Book G');

update table set status = "I";

create table Fine(Roll_no int not null , Return_date date ,  Fine_Amount int );

alter table Fine add column Returned_book varchar(25) after Roll_no;

delimiter $$
create procedure fine(Roll_no int)
begin
    declare issue_date date;
    declare fine_amt int;
    declare no_of_days int;
    declare eligible_fine boolean;
    declare cur_date date;
    declare details varchar(100);
    declare book varchar(25);
    declare roll_exists int;
    select roll_no into roll_exists from Borrower b where b.roll_no = Roll_no;
    
    if roll_exists <> -1 then
        set cur_date = curdate();
        set eligible_fine = false;
        select date_of_issue into issue_date from Borrower b where b.roll_no = Roll_no;
        set no_of_days = datediff(cur_date, issue_date);
        
        if (no_of_days >= 15 and no_of_days <= 30) then
            set eligible_fine = true;
            set fine_amt = 5 * no_of_days;
        elseif (no_of_days > 30) then
            set eligible_fine = true;
            set fine_amt = 50 * no_of_days;
        else
            select "No Fine Issued" into details;
        end if;
        
        update Borrower b set status = "R" where b.roll_no = Roll_no;
        
        if eligible_fine then
            select name_of_book into book from Borrower b where b.roll_no = Roll_no;
            insert into Fine(Roll_no, Returned_book, Return_date, Fine_Amount) values (Roll_no, book, curdate(), fine_amt);
            select concat("Fine Issued: ", fine_amt) into details;
        end if;
    else
        select "Roll no not present in table" into details;
    end if;
    
    select details;
end
$$
delimiter ;
