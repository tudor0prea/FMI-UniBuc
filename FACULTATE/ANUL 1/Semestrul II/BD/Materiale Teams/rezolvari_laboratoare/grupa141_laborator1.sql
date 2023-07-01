select * from employees;

--exe 1.1.7  
select employee_id "cod angajat", last_name nume,
       salary * 12 "annual Salary"  --"pt spatii sau case sensitive"
from   employees;

--exe 1.2.5   1.2.6 
--cod ang, nume, cod job, data angajarii

select employee_id cod, last_name nume, job_id "cod job", hire_date "data angajarii"
from employees;

--1.2.7 sa se listeze cu si fara duplicate codurile job-urilor din tabelul emp
select job_id from employees;
select distinct job_id from employees;
select job_id from employees group by  job_id ;

select distinct job_id, hire_date from employees order by job_id, hire_date;

--1.2.12 numele si sal pt cei al caror sal nu se afla in intervalul [12000, 13500]
select last_name, salary
from employees
where salary < 12000 or salary >13500  --and not ()    <>  !=   >= <=  =
order by salary;

select last_name, salary
from employees
where salary not between 12000 and 13500  --and not ()    <>  !=   >= <=  =
order by salary;

--1.2.13 
select last_name, job_id, hire_date, sysdate
from employees
where hire_date between '20-FEB-1987' and '1-MAY-1989'; /*nu se poate converti 'MAY-01-1989' */ 

select sysdate
from dual; --o singura linie in dual

select * from dual;

select to_char(sysdate, 'ddmmyyyy') from dual;

select distinct sysdate from employees; --ineficient, 107 linii scanate

select to_char(sysdate, 'dd mm yyyy hh24:mi ss') from dual;
select to_char(sysdate  + 1/2 , 'dd mm yyyy hh24:mi ss')   from dual;
select to_char(sysdate  + 12 , 'dd mm yyyy hh24:mi ss')   from dual;

select trunc(sysdate) - hire_date  
from employees;

select to_date('31-12-2022' , 'dd-mm-yyyy') - sysdate from dual;


--L1.3.20
--nume, sal, comision pt toti ang care castiga comision. se sorteaza in ordinea des a salariilor
select last_name, salary, commission_pct
from employees
where commission_pct IS NOT NULL;  /*commission_pct <> 0  se evalueaza NULL    NULL se trateaza false */

--nume, sal, comision pt toti ang care nu castiga comision. se sorteaza in ordinea des a salariilor
select last_name, salary, commission_pct
from employees
where commission_pct IS NULL;  /*commission_pct = 0  null   false */

select last_name, salary, commission_pct
from employees
order by salary desc , commission_pct desc;

select last_name, salary, commission_pct
from employees
order by salary desc , commission_pct desc nulls last;



select last_name, salary, commission_pct, nvl(commission_pct, 0)
from employees
order by salary desc , commission_pct desc nulls last;

