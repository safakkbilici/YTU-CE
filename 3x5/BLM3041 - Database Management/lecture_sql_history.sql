CREATE TABLE employee (
  fname    varchar(15) not null, 
  minit    varchar(1),
  lname    varchar(15) not null,
  ssn      char(9),
  bdate    date,
  address  varchar(50),
  sex      char,
  salary   int,
  superssn char(9),
  dno smallint,
  primary key (ssn),
  foreign key (superssn) references employee(ssn)
  --foreign key (dno) references department(dnumber)
);

CREATE TABLE department (
  dname        varchar(25) not null,
  dnumber smallint,
  mgrssn       char(9) not null, 
  mgrstartdate date,
  primary key (dnumber),
  unique (dname),
  foreign key (mgrssn) references employee(ssn)
);

ALTER TABLE employee ADD 
  foreign key (dno) references department(dnumber);
  
ALTER TABLE employee ADD CONSTRAINT foreign_key_const
  foreign key (dno) references department(dnumber);
  
CREATE TABLE dept_locations (
  dnumber smallint,
  dlocation varchar(15), 
  primary key (dnumber,dlocation),
  foreign key (dnumber) references department(dnumber)
);

CREATE TABLE project (
  pname      varchar(25) not null,
  pnumber smallint,
  plocation  varchar(15),
  dnum       smallint not null,
  primary key (pnumber),
  unique (pname),
  foreign key (dnum) references department(dnumber)
);

CREATE TABLE works_on (
  essn   char(9),
  pno    smallint,
  hours  smallint,
  primary key (essn,pno),
  foreign key (essn) references employee(ssn),
  foreign key (pno) references project(pnumber)
);
  
CREATE TABLE dependent (
  essn           char(9),
  dependent_name varchar(15),
  sex            char,
  bdate          date,
  relationship   varchar(8),
  primary key (essn,dependent_name),
  foreign key (essn) references employee(ssn)
);

INSERT INTO employee VALUES 
  ('James','E','Borg','888665555','10-NOV-27','450 Stone, Houston, TX','M',55000,null,null);
INSERT INTO employee VALUES 
  ('Franklin','T','Wong','333445555','08-DEC-45','638 Voss, Houston, TX','M',40000,'888665555',null);
INSERT INTO employee VALUES 
  ('Jennifer','S','Wallace','987654321','20-JUN-31','291 Berry, Bellaire, TX','F',43000,'888665555',null);
INSERT INTO employee VALUES
  ('Jared','D','James','111111100','10-OCT-1966','123 Peachtree, Atlanta, GA','M',85000,null,null);
INSERT INTO employee VALUES
  ('Alex','D','Freed','444444400','09-OCT-1950','4333 Pillsbury, Milwaukee, WI','M',89000,null,null);
INSERT INTO employee VALUES
  ('John','C','James','555555500','30-JUN-1975','7676 Bloomington, Sacramento, CA','M',81000,null,null);
--
INSERT INTO department VALUES ('Research', 5, '333445555', '22-MAY-78');
INSERT INTO department VALUES ('Administration', 4, '987654321', '01-JAN-85');
INSERT INTO department VALUES ('Headquarters', 1, '888665555', '19-JUN-71');
INSERT INTO department VALUES ('Software',6,'111111100','15-MAY-1999');
INSERT INTO department VALUES ('Hardware',7,'444444400','15-MAY-1998');
INSERT INTO department VALUES ('Sales',8,'555555500','01-JAN-1997');
--
UPDATE employee SET dno = 5 WHERE ssn = '333445555';
UPDATE employee SET dno = 4 WHERE ssn = '987654321';
UPDATE employee SET dno = 1 WHERE ssn = '888665555';
UPDATE employee SET dno = 6 WHERE ssn = '111111100';
UPDATE employee SET dno = 7 WHERE ssn = '444444400';
UPDATE employee SET dno = 6 WHERE ssn = '555555500';
--
INSERT INTO employee VALUES 
  ('John','B','Smith','123456789','09-Jan-55','731 Fondren, Houston, TX','M',30000,'333445555',5);
INSERT INTO employee VALUES 
  ('Alicia','J','Zelaya','999887777','19-JUL-58','3321 Castle, Spring, TX','F',25000,'987654321',4);
INSERT INTO employee VALUES 
  ('Ramesh','K','Narayan','666884444','15-SEP-52','971 Fire Oak, Humble, TX','M',38000,'333445555',5);
INSERT INTO employee VALUES 
  ('Joyce','A','English','453453453','31-JUL-62','5631 Rice Oak, Houston, TX','F',25000,'333445555',5);
INSERT INTO employee VALUES 
  ('Ahmad','V','Jabbar','987987987','29-MAR-59','980 Dallas, Houston, TX','M',25000,'987654321',4);
insert into EMPLOYEE values
  ('Jon','C','Jones','111111101','14-NOV-1967','111 Allgood, Atlanta, GA','M',45000,'111111100',6);
insert into EMPLOYEE values
  ('Justin',null,'Mark','111111102','12-JAN-1966','2342 May, Atlanta, GA','M',40000,'111111100',6);
insert into EMPLOYEE values
  ('Brad','C','Knight','111111103','13-FEB-1968','176 Main St., Atlanta, GA','M',44000,'111111100',6);
insert into EMPLOYEE values
  ('Evan','E','Wallis','222222200','16-JAN-1958','134 Pelham, Milwaukee, WI','M',92000,null,7);
insert into EMPLOYEE values
  ('Josh','U','Zell','222222201','22-MAY-1954','266 McGrady, Milwaukee, WI','M',56000,'222222200',7);
insert into EMPLOYEE values
  ('Andy','C','Vile','222222202','21-JUN-1944','1967 Jordan, Milwaukee, WI','M',53000,'222222200',7);
insert into EMPLOYEE values
  ('Tom','G','Brand','222222203','16-DEC-1966','112 Third St, Milwaukee, WI','M',62500,'222222200',7);
insert into EMPLOYEE values
  ('Jenny','F','Vos','222222204','11-NOV-1967','263 Mayberry, Milwaukee, WI','F',61000,'222222201',7);
insert into EMPLOYEE values
  ('Chris','A','Carter','222222205','21-MAR-1960','565 Jordan, Milwaukee, WI','F',43000,'222222201',7);
insert into EMPLOYEE values
  ('Kim','C','Grace','333333300','23-OCT-1970','6677 Mills Ave, Sacramento, CA','F',79000,null,6);
insert into EMPLOYEE values
  ('Jeff','H','Chase','333333301','07-JAN-1970','145 Bradbury, Sacramento, CA','M',44000,'333333300',6);
insert into EMPLOYEE values
  ('Bonnie','S','Bays','444444401','19-JUN-1956','111 Hollow, Milwaukee, WI','F',70000,'444444400',7);
insert into EMPLOYEE values
  ('Alec','C','Best','444444402','18-JUN-1966','233 Solid, Milwaukee, WI','M',60000,'444444400',7);
insert into EMPLOYEE values
  ('Sam','S','Snedden','444444403','31-JUL-1977','987 Windy St, Milwaukee, WI','M',48000,'444444400',7);
insert into EMPLOYEE values
  ('Nandita','K','Ball','555555501','16-APR-1969','222 Howard, Sacramento, CA','M',62000,'555555500',6);
insert into EMPLOYEE values
  ('Bob','B','Bender','666666600','17-APR-1968','8794 Garfield, Chicago, IL','M',96000,null,8);
insert into EMPLOYEE values
  ('Jill','J','Jarvis','666666601','14-JAN-1966','6234 Lincoln, Chicago, IL','F',36000,'666666600',8);
insert into EMPLOYEE values
  ('Kate','W','King','666666602','16-APR-1966','1976 Boone Trace, Chicago, IL','F',44000,'666666600',8);
insert into EMPLOYEE values
  ('Lyle','G','Leslie','666666603','09-JUN-1963','417 Hancock Ave, Chicago, IL','M',41000,'666666601',8);
insert into EMPLOYEE values
  ('Billie','J','King','666666604','01-JAN-1960','556 Washington, Chicago, IL','F',38000,'666666603',8);
insert into EMPLOYEE values
  ('Jon','A','Kramer','666666605','22-AUG-1964','1988 Windy Creek, Seattle, WA','M',41500,'666666603',8);
insert into EMPLOYEE values
  ('Ray','H','King','666666606','16-AUG-1949','213 Delk Road, Seattle, WA','M',44500,'666666604',8);
insert into EMPLOYEE values
  ('Gerald','D','Small','666666607','15-MAY-1962','122 Ball Street, Dallas, TX','M',29000,'666666602',8);
insert into EMPLOYEE values
  ('Arnold','A','Head','666666608','19-MAY-1967','233 Spring St, Dallas, TX','M',33000,'666666602',8);
insert into EMPLOYEE values
  ('Helga','C','Pataki','666666609','11-MAR-1969','101 Holyoke St, Dallas, TX','F',32000,'666666602',8);
insert into EMPLOYEE values
  ('Naveen','B','Drew','666666610','23-MAY-1970','198 Elm St, Philadelphia, PA','M',34000,'666666607',8);
insert into EMPLOYEE values
  ('Carl','E','Reedy','666666611','21-JUN-1977','213 Ball St, Philadelphia, PA','M',32000,'666666610',8);
insert into EMPLOYEE values
  ('Sammy','G','Hall','666666612','11-JAN-1970','433 Main Street, Miami, FL','M',37000,'666666611',8);
insert into EMPLOYEE values
  ('Red','A','Bacher','666666613','21-MAY-1980','196 Elm Street, Miami, FL','M',33500,'666666612',8);
--
INSERT INTO project VALUES ('ProductX',1,'Bellaire',5);
INSERT INTO project VALUES ('ProductY',2,'Sugarland',5);
INSERT INTO project VALUES ('ProductZ',3,'Houston',5);
INSERT INTO project VALUES ('Computerization',10,'Stafford',4);
INSERT INTO project VALUES ('Reorganization',20,'Houston',1);
INSERT INTO project VALUES ('Newbenefits',30,'Stafford',4);
INSERT INTO project VALUES ('OperatingSystems',61,'Jacksonville',6);
INSERT INTO project VALUES ('DatabaseSystems',62,'Birmingham',6);
INSERT INTO project VALUES ('Middleware',63,'Jackson',6);
INSERT INTO project VALUES ('InkjetPrinters',91,'Phoenix',7);
INSERT INTO project VALUES ('LaserPrinters',92,'LasVegas',7);
--
INSERT INTO dept_locations VALUES (1,'Houston');
INSERT INTO dept_locations VALUES (4,'Stafford');
INSERT INTO dept_locations VALUES (5,'Bellaire');
INSERT INTO dept_locations VALUES (5,'Sugarland');
INSERT INTO dept_locations VALUES (5,'Houston');
INSERT INTO dept_locations VALUES (6,'Atlanta');
INSERT INTO dept_locations VALUES (6,'Sacramento');
INSERT INTO dept_locations VALUES (7,'Milwaukee');
INSERT INTO dept_locations VALUES (8,'Chicago');
INSERT INTO dept_locations VALUES (8,'Dallas');
INSERT INTO dept_locations VALUES (8,'Philadephia');
INSERT INTO dept_locations VALUES (8,'Seattle');
INSERT INTO dept_locations VALUES (8,'Miami');
--
INSERT INTO dependent VALUES ('333445555','Alice','F','05-APR-76','Daughter');
INSERT INTO dependent VALUES ('333445555','Theodore','M','25-OCT-73','Son');
INSERT INTO dependent VALUES ('333445555','Joy','F','03-MAY-48','Spouse');
INSERT INTO dependent VALUES ('987654321','Abner','M','29-FEB-32','Spouse');
INSERT INTO dependent VALUES ('123456789','Michael','M','01-JAN-78','Son');
INSERT INTO dependent VALUES ('123456789','Alice','F', '31-DEC-78','Daughter');
INSERT INTO dependent VALUES ('123456789','Elizabeth','F','05-MAY-57','Spouse');
INSERT INTO dependent VALUES ('444444400','Johnny','M','04-APR-1997','Son');
INSERT INTO dependent VALUES ('444444400','Tommy','M','07-JUN-1999','Son');
INSERT INTO dependent VALUES ('444444401','Chris','M','19-APR-1969','Spouse');
INSERT INTO dependent VALUES ('444444402','Sam','M','14-FEB-1964','Spouse');
INSERT INTO dependent VALUES ('222222205','Chris','M','19-APR-1969','Spouse');
--
INSERT INTO works_on VALUES ('123456789',1, 32.5);
INSERT INTO works_on VALUES ('123456789',2,  7.5);
INSERT INTO works_on VALUES ('666884444',3, 40.0);
INSERT INTO works_on VALUES ('453453453',1, 20.0);
INSERT INTO works_on VALUES ('453453453',2, 20.0);
INSERT INTO works_on VALUES ('333445555',2, 10.0);
INSERT INTO works_on VALUES ('333445555',3, 10.0);
INSERT INTO works_on VALUES ('333445555',10,10.0);
INSERT INTO works_on VALUES ('333445555',20,10.0);
INSERT INTO works_on VALUES ('999887777',30,30.0);
INSERT INTO works_on VALUES ('999887777',10,10.0);
INSERT INTO works_on VALUES ('987987987',10,35.0);
INSERT INTO works_on VALUES ('987987987',30, 5.0);
INSERT INTO works_on VALUES ('987654321',30,20.0);
INSERT INTO works_on VALUES ('987654321',20,15.0);
INSERT INTO works_on VALUES ('888665555',20,null);
INSERT INTO works_on VALUES ('111111100',61,40.0);
INSERT INTO works_on VALUES ('111111101',61,40.0);
INSERT INTO works_on VALUES ('111111102',61,40.0);
INSERT INTO works_on VALUES ('111111103',61,40.0);
INSERT INTO works_on VALUES ('222222200',62,40.0);
INSERT INTO works_on VALUES ('222222201',62,48.0);
INSERT INTO works_on VALUES ('222222202',62,40.0);
INSERT INTO works_on VALUES ('222222203',62,40.0);
INSERT INTO works_on VALUES ('222222204',62,40.0);
INSERT INTO works_on VALUES ('222222205',62,40.0);
INSERT INTO works_on VALUES ('333333300',63,40.0);
INSERT INTO works_on VALUES ('333333301',63,46.0);
INSERT INTO works_on VALUES ('444444400',91,40.0);
INSERT INTO works_on VALUES ('444444401',91,40.0);
INSERT INTO works_on VALUES ('444444402',91,40.0);
INSERT INTO works_on VALUES ('444444403',91,40.0);
INSERT INTO works_on VALUES ('555555500',92,40.0);
INSERT INTO works_on VALUES ('555555501',92,44.0);
INSERT INTO works_on VALUES ('666666601',91,40.0);
INSERT INTO works_on VALUES ('666666603',91,40.0);
INSERT INTO works_on VALUES ('666666604',91,40.0);
INSERT INTO works_on VALUES ('666666605',92,40.0);
INSERT INTO works_on VALUES ('666666606',91,40.0);
INSERT INTO works_on VALUES ('666666607',61,40.0);
INSERT INTO works_on VALUES ('666666608',62,40.0);
INSERT INTO works_on VALUES ('666666609',63,40.0);
INSERT INTO works_on VALUES ('666666610',61,40.0);
INSERT INTO works_on VALUES ('666666611',61,40.0);
INSERT INTO works_on VALUES ('666666612',61,40.0);
INSERT INTO works_on VALUES ('666666613',61,30.0);
INSERT INTO works_on VALUES ('666666613',62,10.0);
INSERT INTO works_on VALUES ('666666613',63,10.0);
  

--bdate and address of john b smith
SELECT e.bdate, e.address
FROM employee e
WHERE e.fname='John' AND e.minit='B' AND e.lname='Smith';


--name and address of all employees who work for the research
SELECT e.fname, e.lname, e.address
FROM employee e, department d
WHERE d.dnumber=e.dno AND d.dname='Research';

-- for every project located in 'Stafford', list the project number, the controllling department number,
-- and the department's manager last name, address and birthdate
SELECT p.pnumber, p.dnum, e.lname, e.address, e.bdate
FROM project p, department d, employee e
WHERE p.plocation='Stafford' AND p.dnum=d.dnumber AND d.mgrssn = e.ssn

-- make a list of all project numbers for projects that involve an employee
-- whose lastname is 'Smith', either as a worker or as a manager of the department
-- that controls the project
SELECT DISTINCT p.pnumber
FROM project p
WHERE p.pnumber IN(
	SELECT p.pnumber
	FROM project p, department d, employee e
	WHERE p.dnum = d.dnumber AND d.mgrssn=e.ssn AND e.lname = 'Smith')
	OR
	p.pnumber IN(
	SELECT p.pnumber
	FROM works_on w, employee e
	WHERE w.essn=e.ssn AND e.lname='Smith');

--retrieve the name of each employee who has a dependent with the first name and is the same sex
--as the employee
SELECT e.fname, e.lname
FROM employee e
WHERE e.ssn IN  (
	SELECT e.ssn
	FROM dependent d
	WHERE e.fname=d.dependent_name AND e.sex = d.sex);

--find the sum of the salaries of all employes of the 'Research' department,
--as well as the maximum salary, the minimum salary, and the average salary in this department

SELECT SUM(e.salary), MAX(e.salary), MIN(e.salary), AVG(e.salary)
FROM employee e
JOIN department d ON e.dno = d.dnumber
WHERE d.dname='Research';


--for each department that has more than five employees,
--retrieve the department number and the number of its employees who are making 
--more than $40,000
--wrong!
SELECT d.dnumber, COUNT(*)
FROM department d, employee e
WHERE e.salary > 40000 AND d.dnumber = e.dno AND
(	SELECT e.dno
	FROM employee e
	GROUP BY e.dno
	HAVING COUNT(*)>5);


--elizabeth isminde akrabası olanın
--supervisor isim ve soyisim

SELECT e.fname, e.lname
FROM employee e
WHERE e.ssn IN
(SELECT e.superssn
FROM employee e, dependent dp
WHERE e.ssn = dp.essn AND dp.dependent_name = 'Elizabeth');
--aynısı: (hoca)
SELECT e2.fname, e2.lname
FROM dependent, employee e1, employee e2
WHERE dependent_name='Elizabeth' AND essn = e1.ssn AND e1.superssn = e2.ssn;

--maaşı 20000 ile 40000 arasında olan
--elemanların isimlerini ve maaşlarını gösteren
--bir view yazınız
CREATE VIEW maaslar
AS
SELECT e.fname, e.lname, e.salary
FROM employee e
WHERE e.salary BETWEEN 20000 AND 40000;

SELECT * FROM maaslar;


--operating systems projede VE software isimli
--departmanda çalışanların ad soyadı
SELECT e.fname, e.lname
FROM employee e, project p, works_on w
WHERE p.pname='OperatingSystems' AND p.pnumber=w.pno AND e.ssn = w.essn
INTERSECT
SELECT e.fname, e.lname
FROM department d, employee e
WHERE d.dname='Software' AND d.dnumber = e.dno;

--operating systems projede VEYA software isimli
--departmanda çalışanların ad soyadı
SELECT e.fname, e.lname
FROM employee e, project p, works_on w
WHERE p.pname='OperatingSystems' AND p.pnumber=w.pno AND e.ssn = w.essn
UNION
SELECT e.fname, e.lname
FROM department d, employee e
WHERE d.dname='Software' AND d.dnumber = e.dno;

--”OperatingSystems” isimli projede çalışıp, “Software” departmanında
--çalışmayanların ad, soyad bilgilerini bulunuz.
SELECT e.fname, e.lname
FROM employee e, project p, works_on w
WHERE p.pname='OperatingSystems' AND p.pnumber = w.pno AND e.ssn = w.essn
EXCEPT 
SELECT e.fname, e.lname
FROM department d, employee e
WHERE d.dname='Software' AND d.dnumber = e.dno;

--hiçbir departmanın veya hiçbir çalışanın yöneticisi olmayan
--çalışanların isimlerini bulunuz.
SELECT e.fname, e.lname
FROM employee e
WHERE NOT EXISTS (SELECT null FROM department d WHERE d.mgrssn = e.ssn)
				AND
	  NOT EXISTS (SELECT null FROM employee e2 WHERE e.ssn = e2.superssn);
	  
	  
--İsmi ‘John’ olan işçilerin çalıştıkları departmanların isimlerini IN
--kullanarak bulunuz.	
SELECT d.dname
FROM department d
WHERE d.dnumber IN(
	SELECT e.dno
	FROM employee e
	WHERE e.fname='John');

--‘Sales’ departmanında kaç kişinin çalıştığını, en düşük, en yüksek,
--ortalama ve toplam maaşı bulunuz.
SELECT COUNT(*), MIN(e.salary), MAX(e.salary), AVG(e.salary)
FROM employee e
JOIN department d ON d.dnumber = e.dno
WHERE d.dname = 'Sales';

--«Sales» departmanında kaç kişinin çalıştığını, toplam maaşlarını,
--en yüksek maaşı, en düşük maaşı ve ortalama maaşı bulunuz.
SELECT COUNT(*), SUM(e.salary), MAX(e.salary), MIN(e.salary), AVG(e.salary)
FROM employee e, department d
WHERE d.dnumber = e.dno AND d.dname = 'Sales'

--8 numaralı departmanda çalışan işçilerin ortalama ve
--toplam maaşlarını bulunuz.
SELECT SUM(e.salary) AS sum_of_salaries , AVG(e.salary) AS average_of_salaries
FROM employee e
WHERE e.dno = 8;

--«Middleware» projesinde kaç kişinin çalıştığını ve bu
--çalışanların ortalama maaşlarını bulunuz.

SELECT COUNT(*), AVG(e.salary)
FROM employee e, works_on w, project p
WHERE p.pnumber = w.pno AND w.essn = e.ssn AND p.pname = 'Middleware';

--En genç çalışanın çalıştığı projelerin numaralarını listeleyiniz .
SELECT w.pno
FROM employee e, works_on w
WHERE w.essn = e.ssn AND e.bdate IN (
	SELECT MAX(bdate)
	FROM employee e);
	
--Project tablosunu dnum kolonuna göre gruplandırmak,
--ve herbir departmanda kaç tane proje olduğunu yazdırmak istersek:

SELECT p.dnum, COUNT(*)
FROM project p
GROUP BY p.dnum;

--Her bir projede çalışanların ortalama maaşını bulup proje ismine göre
--alfabetik olarak sıralayınız.
SELECT p.pname, AVG(e.salary)
FROM project p, employee e, works_on w
WHERE p.pnumber = w.pno AND w.essn = e.ssn 
GROUP BY p.pname
ORDER BY p.pname ASC;

--Her bir departmanda her bir cinsiyetten kaçar işçi olduğunu
--ve bu işçilerin ortalama maaşlarını bulunuz.
SELECT e.dno, e.sex, COUNT(*), AVG(e.salary)
FROM employee e
GROUP BY e.dno, e.sex;

--Ortalama maaşın 40000’den fazla olduğu departmanların numaralarını
--listeleyin.
SELECT e.dno
FROM employee e
GROUP BY e.dno
HAVING AVG(e.salary)>40000

--5 numaralı departman dışındaki departmanlar arasından,
--ortalama maaşı 40000$’dan fazla olan departmanların
--numaralarını ve bu departmandaki ortalama maaşları bulan
--sorguyu yazınız.

SELECT e.dno, AVG(e.salary)
FROM employee e
WHERE e.dno != 5
GROUP BY e.dno
HAVING AVG(e.salary)>40000

--En çok maaşı alan işçinin ismini ve soyismini gösteren sorguyu
--yazınız. (ORDER BY ve LIMIT kullanarak)
SELECT e.fname, e.lname
FROM employee e
ORDER BY e.salary
LIMIT 1

SELECT e.fname, e.lname, e.salary
FROM employee e
WHERE e.salary IN(
	SELECT MIN(e.salary)
	FROM employee e)

--Yöneticisi olmayan kişileri bulunuz.
SELECT e.ssn, e.superssn
FROM employee e
WHERE e.superssn IS null

--Girdi olarak verilen 2 sayının toplamını bulan fonksiyonu yazınız ve (22,63)
--parametreleri için çalıştırınız.
CREATE FUNCTION ornek1 (num1 NUMERIC, num2 NUMERIC) --create or replace function
RETURNS numeric AS'
DECLARE
toplam NUMERIC;
BEGIN
	toplam := num1+num2;
	RETURN toplam;
END;
'LANGUAGE plpgsql;

SELECT * FROM ornek1(10,11)

--Girdi olarak verilen 2 sayının toplamını bulan fonksiyonu yazınız ve (22,63)
--parametreleri için çalıştırınız. (return olmadan)

CREATE FUNCTION ornek2 (num1 NUMERIC, num2 NUMERIC, OUT num3 NUMERIC)
AS'
BEGIN
	num3:=num2+num1;
END;
'LANGUAGE plpgsql;

SELECT * FROM ornek2(11,12)
-- silmek için DROP FUNCTION ornek1 (NUMERIC, NUMERIC);

--Adı verilen bir departmandaki çalışanların ortalama maaşını bulan bir fonksiyon yazınız.


CREATE OR REPLACE FUNCTION dep_avg_salary(depname department.dname%type)
RETURNS real AS'
DECLARE
maas REAL;
BEGIN	
	SELECT AVG(e.salary) INTO maas
	FROM employee e, department d
	WHERE e.dno = d.dnumber AND d.dname = depname;
	RETURN maas;
END;
'LANGUAGE plpgsql;

SELECT * FROM dep_avg_salary('Research');

--Departman tablosundaki minimum ve maksimum departman numarasını bulup
--min_deptno ve max_deptno değişkenlerine atan fonksiyonu yazınız.
CREATE OR REPLACE FUNCTION min_max_depno(OUT min_deptno department.dnumber%type,
										 OUT max_deptno department.dnumber%type)
AS'
BEGIN 
	SELECT MAX(d.dnumber), MIN (d.dnumber) INTO max_deptno, min_deptno
	FROM department d;
END;
'LANGUAGE plpgsql;

SELECT * FROM min_max_depno();

--6 no’lu departmanda çalışanların sayısını bulunuz
CREATE OR REPLACE FUNCTION worker_number(depno INTEGER)
RETURNS NUMERIC AS'
DECLARE
worker_number NUMERIC;
BEGIN
	SELECT COUNT(*) INTO worker_number
	FROM employee e, department d
	WHERE e.dno = d.dnumber AND d.dnumber = depno;
	RETURN worker_number;
END;
'LANGUAGE plpgsql;

SELECT * FROM worker_number(6)


--6 no’lu departmanda çalışanların sayısı 10’dan azsa departmandaki tüm
--çalışanların maaşına %5 zam yapın.

CREATE OR REPLACE FUNCTION raise_payment()
RETURNS void AS'
DECLARE
num_worker NUMERIC(3):=0;
BEGIN
	SELECT COUNT(*) INTO num_worker
	FROM employee e
	WHERE e.dno=6;
	
	IF (num_worker < 10) THEN
		UPDATE employee
		SET salary = salary * 1.05
		WHERE dno=6;
	END IF;
END;
'LANGUAGE plpgsql;	

SELECT raise_payment()


--another example
CREATE OR REPLACE FUNCTION case_orn(x INTEGER)
RETURNS text AS $$
DECLARE
msg TEXT;
BEGIN
	CASE x
		WHEN 1,2 THEN
			msg:='one or two';
		WHEN 3,4 THEN
			msg:='three or four';
		ELSE 
			msg:='other value';
	END CASE;
	RETURN msg;
END;
$$ LANGUAGE plpgsql;

SELECT case_orn(5)



--Verilen bir sayıyı 1 arttıran fonksiyonu yazınız.
CREATE OR REPLACE FUNCTION add_one(t INTEGER)
RETURNS INTEGER AS'
BEGIN
	RETURN t+1;
END;
' LANGUAGE plpgsql;

SELECT add_one(15)

--İsmi verilen bir departmanda çalışanların ortalama maaşı, verilen bir değerden düşük
--ve o departmandaki kadın çalışanların maaşlarının toplamı verilen bir limitin
--üstündeyse, o departmanda 1’den fazla projede çalışanların maaşlarına yine verilen bir
--oranda zam yapan fonksiyonu yazınız.
CREATE OR REPLACE FUNCTION reaise_by_xxx(depname department.dname%type,
										 upper_bound_avg INTEGER, 
										 lower_bound_women INTEGER,
										 raise_percent INTEGER)	
RETURNS void AS '
DECLARE
average_salary REAL;
sum_salary_women REAL;
depno department.dnumber%type;
BEGIN
	SELECT d.dnumber INTO depno
	FROM department d
	WHERE d.dname = depname;
	
	SELECT SUM(e.salary) INTO sum_salary_women
	FROM employee e
	WHERE e.sex = ''F''  AND e.dno = depno;
	
	SELECT AVG(e.salary) INTO average_salary
	FROM employee e
	WHERE e.dno = depno;
	
	IF average_salary < upper_bound_avg AND sum_salary_women > lower_bound_women THEN
		UPDATE employee
			SET salary = salary * raise_percent/100 + salary
			WHERE ssn IN(
				SELECT w.essn
				FROM employee e, works_on w
				WHERE e.ssn = w.essn AND e.dno = depno
				GROUP BY w.essn
				HAVING COUNT(*)>1);
	END IF;
END;
' LANGUAGE plpgsql;

SELECT reaise_by_xxx('Research', 50000, 20000, 5);


--RAISE NOTICE
CREATE OR REPLACE FUNCTION tr_ornek1(num1 NUMERIC, num2 NUMERIC)
RETURNS NUMERIC AS $$
DECLARE
toplam NUMERIC;
BEGIN
	toplam := num1 + num2;
	RAISE NOTICE 'sayi1:%, sayi2:%', num1, num2;
	RETURN toplam;
END;
$$ LANGUAGE plpgsql;

SELECT tr_ornek1(2,3);

--Record -Tür tanımlama
--PL/pgSQL fonksiyonları, sadece tek bir değer döndürmek zorunda değildir. Karmaşık
--sonuçları veya bir tabloyu da döndürebiliriz
--Bu tarz composit veri tiplerini döndürmek için RECORD tanımları kullanılmaktadır.
--CREATE TYPE tür_ismi AS (isim1 tür1, isim2 tür2, ...);

--‘123456789’ ssn’i olan çalışanın ismini, çalıştığı departmanın ismini ve maaşını
--bulunuz.
SELECT e.fname, e.lname, e.dno, d.dname, e.salary
FROM employee e, department d
WHERE e.ssn = '123456789' AND e.dno = d.dnumber;

-- CREATE TYPE ÖRNEĞİ
--SSN'i parametre olarak verilen çalışanın ismini, çalıştığı departmanın ismini ve maaşını ekrana yazdıran PL/pgSQL
--bloğunu yazın. Bir ssn vererek fonksiyonu çağırınız.
CREATE TYPE yeni_tur AS (isim VARCHAR(15), dep_isim VARCHAR(25), maas INTEGER);

CREATE OR REPLACE FUNCTION create_type_orn(e_ssn employee.ssn%type)
RETURNS yeni_tur AS '
DECLARE
bilgi yeni_tur;
BEGIN
	SELECT e.fname, d.dname, e.salary INTO bilgi
	FROM employee e, department d
	WHERE e.dno = d.dnumber AND e.ssn = e_ssn;
	
	RAISE NOTICE ''The name is: %, his/her department name is: %, and salary is: %'',bilgi.isim, bilgi.dep_isim, bilgi.maas;
	RETURN bilgi;
END;
' LANGUAGE plpgsql;

SELECT create_type_orn('123456789');
--DROP FUNCTION ornek2 (employee.ssn%type);

--CURSOR örneği
--Eğer bir tablo döndürmek istiyorsak CURSOR tanımlayarak sonucu bunun üzerinden
--döndürebiliriz
--cursor_ismi CURSOR FOR sql_query;
--ÖRNEK: curs_all CURSOR FOR SELECT * FROM employee;

--Numarası verilen bir departmandaki çalışanların isimlerini bulan bir fonksiyon yazınız. Bir departman
--numarası vererek fonksiyonu çağırınız
CREATE OR REPLACE FUNCTION dep_worker_names(dnum NUMERIC)
RETURNS VOID AS'
DECLARE
	new_cursor CURSOR FOR 
	SELECT e.fname, e.lname
	FROM employee e
	WHERE e.dno = dnum;
BEGIN
	FOR row IN new_cursor LOOP
		RAISE INFO ''Employee name is % %'',row.fname, row.lname;
	END LOOP;
END;
' LANGUAGE plpgsql;

SELECT * FROM dep_worker_names(6);

--Departman numarası verilen bir departmandaki çalışanların toplam maaşını (SUM()
--fonksiyonundan yararlanmadan) bulan bir fonksiyon yazınız.

CREATE OR REPLACE FUNCTION sum_dep_salary(dnum INTEGER)
RETURNS INTEGER AS'
DECLARE
	toplam INTEGER:=0;
	new_cursor CURSOR FOR
	SELECT e.salary
	FROM employee e
	WHERE e.dno = dnum;
BEGIN
	FOR row IN new_cursor LOOP
		toplam:=toplam+row.salary;
	END LOOP;
	RETURN toplam;
END;
'LANGUAGE plpgsql;

SELECT sum_dep_salary(6);

-- sum ile çözülmüş hali
SELECT SUM(e.salary)
FROM employee e
WHERE e.dno = 6;

-- out ile çözülmüş hali
CREATE OR REPLACE FUNCTION sum_dep_salary_out(dnum INTEGER, OUT toplam INTEGER)
AS'
DECLARE
	new_cursor CURSOR FOR
	SELECT e.salary
	FROM employee e
	WHERE e.dno = dnum;
BEGIN
	toplam:=0;
	FOR row IN new_cursor LOOP
		toplam:=toplam+row.salary;
	END LOOP;
END;
'LANGUAGE plpgsql;

SELECT sum_dep_salary_out(6);

--Numarası verilen bir projede çalışanların maaşları verilen bir değere tam bölünebiliyorsa, o
--kişilerin ad, soyad ve maaş bilgilerini HAVING fonksiyonu kullanmadan listeleyen ve geri döndüren
--fonksiyonu yazınız.
CREATE TYPE workers AS (firstname varchar(15), lastname varchar(15), salary integer);

CREATE OR REPLACE FUNCTION weird_func(project_no INTEGER, divideby INTEGER)
RETURNS workers[] AS'
DECLARE
	employee_cursor CURSOR FOR
	SELECT e.fname, e.lname, e.salary
	FROM employee e, works_on w
	WHERE w.essn = e.ssn AND w.pno = project_no;

	worker workers[];
	i INTEGER;
BEGIN
	i:=1;
	FOR row IN employee_cursor LOOP
		IF row.salary % divideby = 0 THEN
			worker[i] = row;
			i:=i+1;
		END IF;
	END LOOP;
	RETURN worker;
END;
'LANGUAGE plpgsql;

SELECT weird_func('61',16);
	
--TRIGGERS
--Fonksiyonlar gibi veri tabanına kaydedilirler.
--VTYS tarafından trigger’ın şartları oluştuğunda otomatik olarak çağrılırlar.
--Tablolar üzerinde değişiklik yapılmak istendiğinde çalışırlar.
--INSERT, UPDATE, DELETE

--CREATE TRIGGER trigger_isim
--{ BEFORE | AFTER } { events }
--ON tablo_adı
--FOR EACH ROW EXECUTE PROCEDURE trigger_fonk_adi();

--Trigger fonksiyonları:
--Parametre almazlar VE Trigger döndürürler.

--1.  Tablo ile trigger fonksiyonu bağlanır:
--CREATE TRIGGER trig_isim

--2.  Trigger fonksiyonu yazılır.
--CREATE or REPLACE FUNCTION trig_fonk_isim()

--INSERT = Sadece NEW kullanılır.
--UPDATE = OLD ve NEW kullanılır.
--DELETE = Sadece OLD kullanılır.

--Sadece tatil günleri dışında ve mesai saatleri içinde employee tablosuna insert
--yapılmasına izin veren trigger’ı yazınız.

CREATE TRIGGER t_ornek6
BEFORE INSERT
ON employee
FOR EACH ROW EXECUTE PROCEDURE trig_fonk_ornek6();

CREATE FUNCTION trig_fonk_ornek6()
RETURNS TRIGGER AS '
BEGIN
	IF ( to_char(now(), ''DY'') in (''SAT'', ''SUN'') OR to_char(now(), ''HH24'') not between ''08'' and ''18'') THEN
		RAISE EXCEPTION ''Sadece mesai günlerinde ve mesai saatlerinde insert yapabilirsiniz.’'';
		RETURN null;
	ELSE
		RETURN new;
	END IF;
END;
' LANGUAGE plpgsql;

INSERT INTO employee VALUES('Vlademir', 'S', 'Putin', '666666666', '1952-10-07', '8975 Rusya', 'M', '125000', '333445555', '5');

--Düşürülmesi:
--Önce:
--DROP TRIGGER t_ornek6 on employee;
--Sonra:
--DROP FUNCTION trig_fonk_ornek6();


--Departman tablosunda dnumber kolonundaki değer değişince employee tablosunda
--da dno’nun aynı şekilde değişmesini sağlayan trigger’ı yazınız.
--Öncelikle departman tablosundaki yabancı anahtar olma kısıtlarını kaldırmalıyız.
ALTER TABLE project DROP CONSTRAINT project_dnum_fkey;
ALTER TABLE dept_locations DROP CONSTRAINT dept_locations_dnumber_fkey;
ALTER TABLE employee DROP CONSTRAINT foreign_key_const;

CREATE TRIGGER trigger7
AFTER UPDATE
ON department
FOR EACH ROW EXECUTE PROCEDURE changeDep();

CREATE OR REPLACE FUNCTION changeDep()
RETURNS TRIGGER AS'
BEGIN 
	UPDATE employee
	SET dno = new.dnumber
	WHERE dno = old.dnumber;
	RETURN new;
END;
'LANGUAGE plpgsql;

--Maaş inişine ve %10’dan fazla maaş artışına izin vermeyen trigger’ı
--yazınız.

CREATE TRIGGER trigger8
BEFORE UPDATE
ON employee
FOR EACH ROW EXECUTE PROCEDURE control_salary();

CREATE OR REPLACE FUNCTION control_salary()
RETURNS TRIGGER AS'
BEGIN
	IF(old.salary > new.salary OR new.salary>1.1*old.salary) THEN
		RAISE EXCEPTION ''You cannot decrease the payment or increase the payment above 10 percent raise'';
		RETURN old;
	ELSE
		return new;
	END IF;
END;
'LANGUAGE plpgsql;

UPDATE employee SET salary = salary*1.12;

--Departman tablonuza salary ile aynı tipte total_salary kolonu ekleyin. Employee
--tablosunda maaş sütununda değişiklik olduğunda department tablosundaki
--total_salary kolonunda gerekli güncellemeyi yapacak trigger’ı yazınız.
ALTER TABLE department ADD COLUMN total_salary INTEGER default 0;
UPDATE department
SET total_salary = (SELECT SUM(salary) FROM employee WHERE dno = dnumber);

CREATE TRIGGER trigger9
AFTER INSERT OR UPDATE OR DELETE
ON EMPLOYEE
FOR EACH ROW EXECUTE PROCEDURE check_sum_salaries();

CREATE OR REPLACE FUNCTION check_sum_salaries()
RETURNS TRIGGER AS'
BEGIN
	IF(TG_OP = ''DELETE'') THEN
		UPDATE department
		SET total_salary = total_salary - old.salary
		WHERE dnumber = old.dno;
	ELSIF(TG_OP = ''UPDATE'') THEN
		UPDATE department
		SET total_salary = total_salary + new.salary - old.salary
		WHERE dnumber = old.dno;
	ELSE
		UPDATE department
		SET total_salary = total_salary + new.salary
		WHERE dnumber = old.dno;
	END IF;
	RETURN new;
END;
'LANGUAGE plpgsql;

UPDATE employee SET salary = salary*1.07 WHERE dno = 1;
