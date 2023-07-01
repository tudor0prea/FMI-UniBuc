--1
DECLARE
  x      NUMBER(1) := 5;
  y      x%TYPE  := NULL;
BEGIN
  IF x <> y THEN 
      DBMS_OUTPUT.PUT_LINE ('valoare <> null este = true');
    ELSE 
      DBMS_OUTPUT.PUT_LINE ('valoare <> null este != true');
  END IF;
  
  x := NULL; 
  IF x = y THEN 
       DBMS_OUTPUT.PUT_LINE ('null = null este = true');
    ELSE 
       DBMS_OUTPUT.PUT_LINE ('null = null este != true');
  END IF;
END;
-- NULL nu este egal cu NULL 
-- daca verificam ceva = null , mereu ne da null (fals)
/

--2
--a
-- Recorduri
DECLARE
  TYPE emp_record IS RECORD 
        (cod employees.employee_id%TYPE, 
         salariu employees.salary%TYPE, 
         job employees.job_id%TYPE);
  v_ang emp_record;
BEGIN
  v_ang.cod:=&p_ang_cod;
  select salary, job_id into v_ang.salariu, v_ang.job from employees where employee_id = v_ang.cod;
  
    --select job_id into v_ang.job from employees where employee_id = v_ang.cod ;
--  v_ang.salariu:= 9000;
--  v_ang.job:='SA_MAN';
  DBMS_OUTPUT.PUT_LINE ('Angajatul cu codul '|| v_ang.cod || 
    ' si jobul ' || v_ang.job || ' are salariul ' ||  v_ang.salariu);
END;
/

--b
BEGIN
 /********   In loc de ...
 * SELECT employee_id, salary, job_id
 * INTO   v_ang.cod, v_ang.salariu, v_ang.job
 * FROM   employees
 * WHERE  employee_id = 101;
 *******************************/

 SELECT employee_id, salary, job_id
 INTO   v_ang
 FROM   employees
 WHERE  employee_id = 101;
 DBMS_OUTPUT.PUT_LINE ('Angajatul cu codul '|| v_ang.cod || 
    ' si jobul ' || v_ang.job || ' are salariul ' ||  v_ang.salariu);
END;
/

--c

BEGIN
 DELETE FROM emp_*** 
 WHERE employee_id=100
 RETURNING employee_id, salary, job_id INTO v_ang;
 
 DBMS_OUTPUT.PUT_LINE ('Angajatul cu codul '|| v_ang.cod || 
    ' si jobul ' || v_ang.job || ' are salariul ' ||  v_ang.salariu);
END;
/
ROLLBACK;

--3
DECLARE
 v_ang1     employees%ROWTYPE;
 v_ang2     employees%ROWTYPE;
BEGIN
-- sterg angajat 100 si mentin in variabila linia stearsa
   DELETE FROM emp_*** 
   WHERE employee_id = 100 
   RETURNING employee_id, first_name, last_name, email, phone_number,
             hire_date, job_id, salary, commission_pct, manager_id,
             department_id 
   INTO v_ang1;

-- inserez in tabel linia stearsa
   INSERT INTO emp_***
   VALUES v_ang1;

-- sterg angajat 101 
   DELETE FROM emp_*** 
   WHERE employee_id = 101;


-- obtin datele din tabelul employees
   SELECT *
   INTO   v_ang2
   FROM   employees
   WHERE  employee_id = 101;

-- inserez o linie oarecare in emp_***
   INSERT INTO emp_***
   VALUES(1000,'FN','LN','E',null,sysdate, 'AD_VP',1000, null,100,90);

-- modific linia adaugata anterior cu valorile variabilei v_ang2
   UPDATE emp_***
   SET    ROW = v_ang2
   WHERE  employee_id = 1000;
 END;
/

--4
DECLARE
  TYPE tablou_indexat IS TABLE OF NUMBER INDEX BY BINARY_INTEGER;
  t    tablou_indexat;
BEGIN
-- punctul a
  FOR i IN 1..10 LOOP
    t(i):=i;
  END LOOP;
  DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
  FOR i IN t.FIRST..t.LAST LOOP
      DBMS_OUTPUT.PUT(t(i) || ' '); 
  END LOOP;
  DBMS_OUTPUT.NEW_LINE;

-- punctul b
  FOR i IN 1..10 LOOP
    IF i mod 2 = 1 THEN t(i):=null; 
    END IF;
  END LOOP;
  DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');

  FOR i IN t.FIRST..t.LAST LOOP
      DBMS_OUTPUT.PUT(nvl(t(i), 0) || ' '); 
  END LOOP;
  DBMS_OUTPUT.NEW_LINE;

-- punctul c
  t.DELETE(t.first);
  t.DELETE(5,7);
  t.DELETE(t.last);
  DBMS_OUTPUT.PUT_LINE('Primul element are indicele ' || t.first ||
         ' si valoarea ' || nvl(t(t.first),0));
  DBMS_OUTPUT.PUT_LINE('Ultimul element are indicele ' || t.last ||
         ' si valoarea ' || nvl(t(t.last),0));
  DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
  FOR i IN t.FIRST..t.LAST LOOP
     IF t.EXISTS(i) THEN 
        DBMS_OUTPUT.PUT(nvl(t(i), 0)|| ' '); 
     END IF;
  END LOOP;
  DBMS_OUTPUT.NEW_LINE;

-- punctul d
  t.delete;
  DBMS_OUTPUT.PUT_LINE('Tabloul are ' || t.COUNT ||' elemente.');
END;
/

--5
DECLARE
  TYPE tablou_indexat IS TABLE OF emp_***%ROWTYPE 
                      INDEX BY BINARY_INTEGER;
  t    tablou_indexat;
BEGIN
-- stergere din tabel si salvare in tablou 
   DELETE FROM emp_*** 
   WHERE  ROWNUM<= 2
   RETURNING employee_id, first_name, last_name, email, phone_number,
             hire_date, job_id, salary, commission_pct, manager_id,
             department_id 
   BULK COLLECT INTO t;

--afisare elemente tablou
  DBMS_OUTPUT.PUT_LINE (t(1).employee_id ||' ' || t(1).last_name);
  DBMS_OUTPUT.PUT_LINE (t(2).employee_id ||' ' || t(2).last_name);

--inserare cele 2 linii in tabel
  INSERT INTO emp_*** VALUES t(1);
  INSERT INTO emp_*** VALUES t(2);
  END;
/

--6
DECLARE
  TYPE tablou_imbricat IS TABLE OF NUMBER;
  t    tablou_imbricat := tablou_imbricat();
BEGIN
-- punctul a
  FOR i IN 1..10 LOOP
     t.extend; t(i):=i;
  END LOOP;
  DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
  FOR i IN t.FIRST..t.LAST LOOP
      DBMS_OUTPUT.PUT(t(i) || ' '); 
  END LOOP;
  DBMS_OUTPUT.NEW_LINE;

-- punctul b
  FOR i IN 1..10 LOOP
    IF i mod 2 = 1 THEN t(i):=null; 
    END IF;
  END LOOP;
  DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
  FOR i IN t.FIRST..t.LAST LOOP
      DBMS_OUTPUT.PUT(nvl(t(i), 0) || ' '); 
  END LOOP;
  DBMS_OUTPUT.NEW_LINE;

-- punctul c
  t.DELETE(t.first);
  t.DELETE(5,7);
  t.DELETE(t.last);
  DBMS_OUTPUT.PUT_LINE('Primul element are indicele ' || t.first ||
         ' si valoarea ' || nvl(t(t.first),0));
  DBMS_OUTPUT.PUT_LINE('Ultimul element are indicele ' || t.last ||
         ' si valoarea ' || nvl(t(t.last),0));
  DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
  FOR i IN t.FIRST..t.LAST LOOP
     IF t.EXISTS(i) THEN 
        DBMS_OUTPUT.PUT(nvl(t(i), 0)|| ' '); 
     END IF;
  END LOOP;
  DBMS_OUTPUT.NEW_LINE;

-- punctul d
  t.delete;
  DBMS_OUTPUT.PUT_LINE('Tabloul are ' || t.COUNT ||' elemente.');
END;
/

--7
DECLARE
  TYPE tablou_imbricat IS TABLE OF CHAR(1);
  t tablou_imbricat := tablou_imbricat('m', 'i', 'n', 'i', 'm');
  i INTEGER;
BEGIN
  i := t.FIRST;
  WHILE i <= t.LAST LOOP
    DBMS_OUTPUT.PUT(t(i));
    i := t.NEXT(i);
  END LOOP;
  DBMS_OUTPUT.NEW_LINE;
  
  i := t.LAST;
  WHILE i >= t.FIRST LOOP
    DBMS_OUTPUT.PUT(t(i));
    i := t.PRIOR(i);

  END LOOP;
  DBMS_OUTPUT.NEW_LINE;

  t.delete(2); 
  t.delete(4);

  i := t.FIRST;
  WHILE i <= t.LAST LOOP
    DBMS_OUTPUT.PUT(t(i));
    i := t.NEXT(i);
  END LOOP;
  DBMS_OUTPUT.NEW_LINE;
  
  i := t.LAST;
  WHILE i >= t.FIRST LOOP
    DBMS_OUTPUT.PUT(t(i));
    i := t.PRIOR(i);
  END LOOP;
  DBMS_OUTPUT.NEW_LINE;

END;
/

--8
DECLARE
  TYPE vector IS VARRAY(20) OF NUMBER;
  t    vector:= vector();
BEGIN
-- punctul a
  FOR i IN 1..10 LOOP
     t.extend; t(i):=i;
  END LOOP;
  DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
  FOR i IN t.FIRST..t.LAST LOOP
      DBMS_OUTPUT.PUT(t(i) || ' '); 
  END LOOP;
  DBMS_OUTPUT.NEW_LINE;
-- punctul b
  FOR i IN 1..10 LOOP
    IF i mod 2 = 1 THEN t(i):=null; 

    END IF;
  END LOOP;
  DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
  FOR i IN t.FIRST..t.LAST LOOP
      DBMS_OUTPUT.PUT(nvl(t(i), 0) || ' '); 
  END LOOP;
  DBMS_OUTPUT.NEW_LINE;

-- punctul c
-- metodele DELETE(n), DELETE(m,n) nu sunt valabile pentru vectori!!!  
-- din vectori nu se pot sterge elemente individuale!!!

-- punctul d
  t.delete;
  DBMS_OUTPUT.PUT_LINE('Tabloul are ' || t.COUNT ||' elemente.');
END;
/

--9
CREATE OR REPLACE TYPE subordonati_*** AS VARRAY(10) OF NUMBER(4);
/
CREATE TABLE manageri_*** (cod_mgr NUMBER(10),
                           nume VARCHAR2(20),
                           lista subordonati_***);

DECLARE 
  v_sub   subordonati_***:= subordonati_***(100,200,300);
  v_lista manageri_***.lista%TYPE;
BEGIN
  INSERT INTO manageri_***
  VALUES (1, 'Mgr 1', v_sub);

  INSERT INTO manageri_***
  VALUES (2, 'Mgr 2', null);
  
  INSERT INTO manageri_***
  VALUES (3, 'Mgr 3', subordonati_***(400,500));
  
  SELECT lista
  INTO   v_lista
  FROM   manageri_***
  WHERE  cod_mgr=1;
  
  FOR j IN v_lista.FIRST..v_lista.LAST loop
       DBMS_OUTPUT.PUT_LINE (v_lista(j));
  END LOOP;
END;
/
SELECT * FROM manageri_***;

DROP TABLE  manageri_***;
DROP TYPE subordonati_***;
--------------------------------------!
--10
CREATE TABLE emp_test_OT AS 
      SELECT employee_id, last_name FROM employees
      WHERE ROWNUM <= 2;
      select * from emp_test_OT;
      
CREATE OR REPLACE TYPE tip_telefon_OT IS TABLE OF VARCHAR(12);
/
ALTER TABLE emp_test_OT
ADD (telefon tip_telefon_OT) 
NESTED TABLE telefon STORE AS tabel_telefon_OT;

INSERT INTO emp_test_OT 
VALUES (500, 'XYZ',tip_telefon_OT('074XXX', '0213XXX', '037XXX'));

update  emp_test_OT
SET telefon = tip_telefon_OT('073XXX', '0214XXX')
WHERE employee_id=100;

SELECT  a.employee_id, b.*
FROM    emp_test_OT a, TABLE (a.telefon) b;

DROP TABLE emp_test_OT;
DROP TYPE  tip_telefon_OT;

--11
--Varianta 1
DECLARE
  TYPE tip_cod IS VARRAY(5) OF NUMBER(3);
  coduri tip_cod := tip_cod(205,206); 
BEGIN
  FOR i IN coduri.FIRST..coduri.LAST  LOOP
    DELETE FROM emp_OT
    WHERE  employee_id = coduri (i);
    DBMS.OUTPUT.PUT_LINE('DELETE'|| i);
  END LOOP;
END; 
/
SELECT employee_id FROM emp_ONG;
ROLLBACK;

--Varianta 2
DECLARE
  TYPE tip_cod IS VARRAY(20) OF NUMBER;
  coduri tip_cod := tip_cod(205,206);
BEGIN
  FORALL i IN coduri.FIRST..coduri.LAST
    DELETE FROM emp_***
    WHERE  employee_id = coduri (i);
    --!! DBMS.OUTPUT.PUT_LINE('DELETE'|| i); -- nu merge.i e in afara lui forall
    
END;
/
SELECT employee_id FROM emp_***;
ROLLBACK;



-- -- Exercitii lab
/
-- ex 1
--select employee_id from (select employee_id from employees 
--where commission_pct is NULL order by salary) where rownum<=5;

DECLARE
    type salarii is VARRAY(10) of NUMBER(3);
    vector salarii:=salarii();
BEGIN
    select employee_id BULK COLLECT INTO vector 
    from (select employee_id 
            from employees 
            where commission_pct is NULL 
            order by salary) 
    where rownum<=5;

    for i in vector.FIRST .. vector.LAST loop
        DBMS_OUTPUT.PUT_LINE( 'vector(i)=' || vector(i) || ' ');
    end loop;
   
END;
/

