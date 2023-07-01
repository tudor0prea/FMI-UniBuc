--LAB PLSQL 1

--1
--a
DECLARE
    v_nume, v_prenume VARCHAR2(35);

--b
DECLARE
       v_nr  NUMBER(5);

--c
DECLARE
       v_nr NUMBER(5,2) = 10;

--d
DECLARE
       v_test   BOOLEAN:= SYSDATE;

--e
DECLARE
       v1  NUMBER(5) :=10;
       v2  NUMBER(5) :=15;
       v3  NUMBER(5) := v1< v2;

--2
<< principal >> 
DECLARE
    v_client_id       NUMBER(4) := 1600;
    v_client_nume     VARCHAR2(50) := 'N1';
    v_nou_client_id   NUMBER(3) := 500;
BEGIN
    << secundar >> 
    DECLARE
        v_client_id         NUMBER(4) := 0;
        v_client_nume       VARCHAR2(50) := 'N2';
        v_nou_client_id     NUMBER(3) := 300;
        v_nou_client_nume   VARCHAR2(50) := 'N3';
    BEGIN
        v_client_id := v_nou_client_id; -- 300
        principal.v_client_nume := v_client_nume
                                   || ' '
                                   || v_nou_client_nume; --n2 n3
       --pozitia 1 
        
    END;
    v_client_id := ( v_client_id * 12 ) / 10; 
    --pozitia 2 
END;
/

--3
VARIABLE g_mesaj VARCHAR2(50)
BEGIN
  :g_mesaj := 'Invat PL/SQL';
END;
/
PRINT g_mesaj


BEGIN
  DBMS_OUTPUT.PUT_LINE('Invat PL/SQL');
END;
/

--4
DECLARE
  v_dep departments.department_name%TYPE;
BEGIN
  SELECT department_name
  INTO   v_dep
  FROM   employees e, departments d
  WHERE  e.department_id=d.department_id 
  GROUP BY department_name
  HAVING COUNT(*) = (SELECT MAX(COUNT(*)) -- DACA PUNEM MIN, INTRA PE EXCEPTIE
                     FROM   employees
                     GROUP BY department_id);
  DBMS_OUTPUT.PUT_LINE('Departamentul '|| v_dep);
  
  EXCEPTION 
        WHEN TOO_MANY_ROWS THEN
        DBMS_OUTPUT.PUT_LINE('Mai multe departamente au numarul minim/maxim de angajati');
END;
/
select department_id, Count(*)
from employees where department_id is not null
group by department_id;

--5
VARIABLE rezultat VARCHAR2(35)
BEGIN
  SELECT department_name
  INTO   :rezultat
FROM   employees e, departments d
  WHERE  e.department_id=d.department_id 
  GROUP BY department_name
  HAVING COUNT(*) = (SELECT MAX(COUNT(*))
                     FROM   employees
                     GROUP BY department_id);
  DBMS_OUTPUT.PUT_LINE('Departamentul '|| :rezultat);
END;
/
PRINT rezultat
/
--6
DECLARE
  v_dep departments.department_name%TYPE;
  v_nra INTEGER;
BEGIN
  SELECT d.department_name, COUNT(e.employee_id)
  INTO   v_dep, v_nra
  FROM   employees e, departments d
  WHERE  e.department_id=d.department_id 
  GROUP BY department_name
  HAVING COUNT(*) = (SELECT MAX(COUNT(*)) -- DACA PUNEM MIN, INTRA PE EXCEPTIE
                     FROM   employees
                     GROUP BY department_id);
  DBMS_OUTPUT.PUT_LINE('Departamentul '|| v_dep
  ||' si are '|| v_nra || ' angajati.' );
  
  EXCEPTION 
        WHEN TOO_MANY_ROWS THEN
        DBMS_OUTPUT.PUT_LINE('Mai multe departamente au numarul minim/maxim de angajati');
END;
/
--7
SET VERIFY OFF
DECLARE
   v_cod           employees.employee_id%TYPE:=&p_cod;
   v_bonus         NUMBER(8);
   v_salariu_anual NUMBER(8);
BEGIN
   SELECT salary*12 
   INTO   v_salariu_anual
   FROM   employees 
   WHERE  employee_id = v_cod;
   IF v_salariu_anual>=200001 
      THEN v_bonus:=20000;
   ELSIF v_salariu_anual BETWEEN 100001 AND 200000 
      THEN v_bonus:=10000;
      ELSE v_bonus:=5000;
   END IF;
   DBMS_OUTPUT.PUT_LINE('Bonusul este ' || v_bonus);
   
   EXCEPTION
    WHEN NO_DATA_FOUND THEN 
    DBMS_OUTPUT.PUT_LINE('Nu exista angajatul cu acest id!');
END;
/
SET VERIFY ON
/
-- 7.1 -> se da numele angajatului, nu id ul

SET VERIFY OFF
DECLARE
   v_nume           employees.last_name%TYPE:='&p_nume'; -- variabila cu numele ' '!!!
   v_bonus         NUMBER(8);
   v_salariu_anual NUMBER(8);
BEGIN
   SELECT salary*12 
   INTO   v_salariu_anual
   FROM   employees 
   WHERE  trim(lower(last_name)) = trim(lower( v_nume)); --trim ca sa ignore/scoata spatiile
   IF v_salariu_anual>=200001 
      THEN v_bonus:=20000;
   ELSIF v_salariu_anual BETWEEN 100001 AND 200000 
      THEN v_bonus:=10000;
      ELSE v_bonus:=5000;
   END IF;
   DBMS_OUTPUT.PUT_LINE('Bonusul este ' || v_bonus);
   
   EXCEPTION
    WHEN NO_DATA_FOUND THEN 
        DBMS_OUTPUT.PUT_LINE('Nu exista angajatul cu acest id!');
    
    WHEN TOO_MANY_ROWS THEN
        DBMS_OUTPUT.PUT_LINE('Exista mai multi angajati cu acest nume!');


END;
/
SET VERIFY ON

--8
DECLARE
   v_cod           employees.employee_id%TYPE:=&p_cod;
   v_bonus         NUMBER(8);
   v_salariu_anual NUMBER(8);
BEGIN
   SELECT salary*12 INTO v_salariu_anual
   FROM   employees 
   WHERE  employee_id = v_cod;
   CASE WHEN v_salariu_anual>=200001 
             THEN v_bonus:=20000;
        WHEN v_salariu_anual BETWEEN 100001 AND 200000 
             THEN v_bonus:=10000;
      --  ELSE v_bonus:=5000; -- daca o comentam, nu gaseste pe ce ramura sa intre
      
   END CASE;
   DBMS_OUTPUT.PUT_LINE('Bonusul este ' || v_bonus);
END;
/
-- proiect instalare si configurare sql
--9
DEFINE p_cod_sal= 200
DEFINE p_cod_dept = 80
DEFINE p_procent =20
DECLARE
  v_cod_sal   emp_***.employee_id%TYPE:= &p_cod_sal;
  v_cod_dept  emp_***.department_id%TYPE:= &p_cod_dept;
  v_procent   NUMBER(8):=&p_procent;
BEGIN
  UPDATE emp_***
  SET department_id = v_cod_dept, 
      salary=salary + (salary* v_procent/100)
  WHERE employee_id= v_cod_sal;
  IF SQL%ROWCOUNT =0 THEN --cate randuri au fost modificate
     DBMS_OUTPUT.PUT_LINE('Nu exista un angajat cu acest cod');
  ELSE 
     DBMS_OUTPUT.PUT_LINE('Actualizare realizata');
  END IF;
END;
/
ROLLBACK;

--10
DECLARE
  contor  NUMBER(6) := 1;
  v_data  DATE;
  maxim   NUMBER(2) := LAST_DAY(SYSDATE)-SYSDATE;
BEGIN
  LOOP
    v_data := sysdate+contor;
    INSERT INTO zile_***
    VALUES (contor,v_data,to_char(v_data,'Day'));
    contor := contor + 1;
    EXIT WHEN contor > maxim;
  END LOOP;
END;
/

--11
DECLARE
  contor  NUMBER(6) := 1;
  v_data  DATE;
  maxim   NUMBER(2) := LAST_DAY(SYSDATE)-SYSDATE;
BEGIN
  WHILE contor <= maxim LOOP
    v_data := sysdate+contor;
    INSERT INTO zile_***
    VALUES (contor,v_data,to_char(v_data,'Day'));
    contor := contor + 1;
  END LOOP;
END;
/

--12
DECLARE
  v_data  DATE;
  maxim   NUMBER(2) := LAST_DAY(SYSDATE)-SYSDATE;
BEGIN
  FOR contor IN 1..maxim LOOP
    v_data := sysdate+contor;
    INSERT INTO zile_***
    VALUES (contor,v_data,to_char(v_data,'Day'));
  END LOOP;
END;
/


--13
--Varianta 1
DECLARE
   i        POSITIVE:=1;
   max_loop CONSTANT POSITIVE:=10;
BEGIN
  LOOP
    i:=i+1;
    IF i>max_loop THEN
      DBMS_OUTPUT.PUT_LINE('in loop i=' || i);
      GOTO urmator;
    END IF;
  END LOOP;
  <<urmator>>
  i:=1;
  DBMS_OUTPUT.PUT_LINE('dupa loop i=' || i);
END;
/

--Varianta 2
DECLARE
  i        POSITIVE:=1;
  max_loop CONSTANT POSITIVE:=10;
BEGIN
  i:=1;
  LOOP
    i:=i+1;
    DBMS_OUTPUT.PUT_LINE('in loop i=' || i);
    EXIT WHEN i>max_loop;
  END LOOP;
  i:=1;
  DBMS_OUTPUT.PUT_LINE('dupa loop i=' || i);
END;
/












-- Exercitiul 3
/
DECLARE
    v_nume member.last_name%TYPE:='&p_nume';
    v_numar NUMBER(2);
    v_id member.member_id%TYPE;
BEGIN
    select member_id into v_id from member 
    where trim(lower(last_name)) = trim(lower(v_nume));
    
    select count( DISTINCT r.title_id)
     into v_numar
     from member m 
     join rental r 
     on (m.member_id=r.member_id)
    where trim(lower(m.last_name)) = trim(lower(v_nume)) ;
       
    if v_numar >0 then
    DBMS_OUTPUT.PUT_LINE(initcap(v_nume) || ' ' || v_numar);
    else 
    DBMS_OUTPUT.PUT_LINE('Nu a imprumutat titluri');
    endif;
    
    EXCEPTION
        when no_data_found then
        DBMS_OUTPUT.PUT_LINE('nu ex membrul');
        when too_many_rows then
        DBMS_OUTPUT.PUT_LINE('prea multi cu acest nume');
END;
/