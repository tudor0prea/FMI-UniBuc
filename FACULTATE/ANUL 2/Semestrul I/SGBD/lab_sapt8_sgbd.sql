-- ref cursor
-- cursor cu un cursor in el (si ev alti param)

-- ex.10
--pt f dep angajatii cu un cursor simplu
-- un cursor cu param care sa se desch in fct de id ul departamentului respectiv

/

DECLARE

  CURSOR c IS
    (SELECT department_id, department_name 
    FROM   departments
    where department_id in (10,20,30,40) );
    
  CURSOR c2(parametru NUMBER) is
    SELECT first_name from employees where department_id=parametru;
  
BEGIN
    
    for i in c loop
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        DBMS_OUTPUT.PUT_LINE( i.department_name);
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        for j in c2( i.department_id ) loop
            DBMS_OUTPUT.PUT_LINE( j.first_name || ' ');
        end loop;
    end loop;
    
END;
/


-- ex. mai greu
--pt dep cu cei mai multi angajati in 1994, afisati doar ang cu salariul
-- mai mare decat media salariilor din dep in care lucreaza
/
DECLARE
    maxi NUMBER;
    dep  first_name%type;
    
  CURSOR c IS
    (SELECT department_id, department_name 
    FROM   departments where department_id
    where department_id is (10,20,30,40) );
    
  CURSOR c2(parametru NUMBER) is
    SELECT first_name from employees where department_id=parametru
    and TO_CHAR(hire_date, 'YYYY') = 1994 ;
  
BEGIN
    maxi=0;
    for j in (select department_id from departments) loop
       if c2(j)%rowcount>max then maxi=i%rowcount; dep=i; end if;
        end loop;
            
        
        
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        DBMS_OUTPUT.PUT_LINE( i.department_name);
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        for j in c2( i.department_id ) loop
            DBMS_OUTPUT.PUT_LINE( j.first_name || ' ');
        end loop;
    end loop;
    
END;

/


