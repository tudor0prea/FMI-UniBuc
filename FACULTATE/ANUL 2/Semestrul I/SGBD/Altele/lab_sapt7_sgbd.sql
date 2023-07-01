-- Cursoare


--1
DECLARE
  v_nr    number(4);
  v_nume  jobs.job_title%TYPE;
  CURSOR c IS
    SELECT job_title nume, COUNT(employee_id) nr  
    FROM   jobs d, employees e
    WHERE  d.job_id=e.job_id(+) 
    GROUP BY job_title; 
BEGIN
  OPEN c;
  LOOP
      FETCH c INTO v_nume,v_nr;
      EXIT WHEN c%NOTFOUND;
      IF v_nr=0 THEN
         DBMS_OUTPUT.PUT_LINE('La jobul '|| v_nume||
                           ' nu lucreaza angajati');
      ELSIF v_nr=1 THEN
           DBMS_OUTPUT.PUT_LINE('La jobul '|| v_nume||
                           ' lucreaza un angajat');
      ELSE
         DBMS_OUTPUT.PUT_LINE('La jobul '|| v_nume||
                           ' lucreaza '|| v_nr||' angajati');
     END IF;
 END LOOP;
 CLOSE c;
END;

/
-- ex.2
DECLARE
--  v_nr    number(4);
--  v_nume  jobs.job_title%TYPE;
  
  type tip_job IS table of jobs.job_title%type;
  type tip_nr is table of NUMBER(4);
  
  t_job      tip_job;
  t_nr       tip_nr;
  
  CURSOR c IS
    SELECT job_title nume, COUNT(employee_id) nr  
    FROM   jobs d, employees e
    WHERE  d.job_id=e.job_id(+) 
    GROUP BY job_title; 
BEGIN
  OPEN c;
  FETCH c BULK COLLECT INTO t_job, t_nr;
  CLOSE c;
  for i in t_job.first..t_job.last loop
      
          IF t_nr(i)=0 THEN
             DBMS_OUTPUT.PUT_LINE('La jobul '|| t_job(i)||
                               ' nu lucreaza angajati');
          ELSIF t_nr(i)=1 THEN
               DBMS_OUTPUT.PUT_LINE('La jobul '|| t_job(i)||
                               ' lucreaza un angajat');
          ELSE
             DBMS_OUTPUT.PUT_LINE('La jobul '|| t_job(i)||
                               ' lucreaza '|| t_nr(i)||' angajati');
         END IF;
  END LOOP;

END;

/
-- ex.2.1
DECLARE
  
  type tip_record is RECORD (t_job jobs.job_title%TYPE,
                                t_nr NUMBER(4));
  type tab_info is TABLE of tip_record;
  t_record   tab_info;
  
  CURSOR c IS
    SELECT job_title nume, COUNT(employee_id) nr  
    FROM   jobs d, employees e
    WHERE  d.job_id=e.job_id(+) 
    GROUP BY job_title; 
BEGIN
  OPEN c;
  FETCH c BULK COLLECT INTO t_record;
  CLOSE c;
  for i in t_record.first..t_record.last loop
      
          IF t_record(i).t_nr=0 THEN
             DBMS_OUTPUT.PUT_LINE('La jobul '|| t_record(i).t_job||
                               ' nu lucreaza angajati');
          ELSIF t_record(i).t_nr=1 THEN
               DBMS_OUTPUT.PUT_LINE('La jobul '|| t_record(i).t_job||
                               ' lucreaza un angajat');
          ELSE
             DBMS_OUTPUT.PUT_LINE('La jobul '|| t_record(i).t_job||
                               ' lucreaza '|| t_record(i).t_nr||' angajati');
         END IF;
  END LOOP;

END;

/
-- TOP 3 corect in lab3_plsql_sursa.sql
-- cursor cu parametru (NUMBER , nu NUMBER(4)) -> ciclu cursor

-- pentru fiecare job sa afisam si lista de angajati
DECLARE
  v_nr    number(4);
  v_nume  jobs.job_title%TYPE;
  v_angajat employees.first_name%TYPE;
  
  CURSOR c IS
    SELECT job_title nume, COUNT(employee_id) nr  
    FROM   jobs d, employees e
    WHERE  d.job_id=e.job_id(+) 
    GROUP BY job_title; 
    
  CURSOR ang(parametru NUMBER) is
    SELECT first_name from employees 
    where job_title = parametru;
  
BEGIN
  OPEN c;
  LOOP
      FETCH c INTO v_nume,v_nr;
      EXIT WHEN c%NOTFOUND;
      IF v_nr=0 THEN
         DBMS_OUTPUT.PUT_LINE('La jobul '|| v_nume||
                           ' nu lucreaza angajati');
      ELSIF v_nr=1 THEN
           DBMS_OUTPUT.PUT_LINE('La jobul '|| v_nume||
                           ' lucreaza un angajat');
          OPEN ang(v_nume);
          FETCH ang into v_angajat;
          DBMS_OUTPUT.PUT_LINE(v_angajat);
          CLOSE ang;
      ELSE
            DBMS_OUTPUT.PUT_LINE('La jobul '|| v_nume||
                           ' lucreaza '|| v_nr||' angajati:');
            
            OPEN ang(v_nume);
            for i in 1..v_nr loop
                FETCH ang into v_angajat;
                DBMS_OUTPUT.PUT_LINE(i||' '||v_angajat);
            end loop;
            CLOSE ang;
                
     END IF;
 END LOOP;
 CLOSE c;
END;
--nu merge ultimul (trebuie cursorul cu param sa caute job_title)
