-- EX.4
/
DECLARE
    v_id NUMBER(3) := 0 ;
    v_nr_inchiriate NUMBER(3) := 0;
    v_nr_titluri NUMBER(3):=0;
    v_procent NUMBER(3) := 0;
    name VARCHAR(101) := '&name';
BEGIN
    select count(title) 
    into v_nr_titluri
    from rental 
    join title 
    using (title_id); -- selectam numarul total de titluri disponibile
    
    select member_id into v_id from member
    where lower(last_name) like lower(name); 
        --selectam id ul ca sa vedem daca exista
            -- in caz contrar sa fie aruncata eroarea 
    
    select count (title_id) 
    into v_nr_inchiriate
    from rental  join member
    using (member_id)
    where lower(last_name) like lower(name) -- lower(first_name) like lower(name) 
    and rownum = 1; -- selectam cate titluri a inchiriat clientul cu numele dat
    
    DBMS_OUTPUT.PUT_LINE(name || ': '||v_nr_inchiriate);
    
    v_procent := (v_nr_inchiriate / v_nr_titluri)*100;
    
    if v_procent > 75 then
        DBMS_OUTPUT.PUT_LINE('Categoria 1');
    elsif v_procent > 50 then
        DBMS_OUTPUT.PUT_LINE('Categoria 2');
    elsif v_procent > 25 then
        DBMS_OUTPUT.PUT_LINE('Categoria 3');
    else
        DBMS_OUTPUT.PUT_LINE('Categoria 4');
    end if;
EXCEPTION
    when too_many_rows then
        DBMS_OUTPUT.PUT_LINE('Exista mai multi clienti cu acest nume');
    when no_data_found then
        DBMS_OUTPUT.PUT_LINE('Nu exista niciun client cu acest nume');
END;

/ 

-- EX.5


create table MEMBER_OT as (select * from member);

ALTER TABLE MEMBER_OT ADD CONSTRAINT PK_MEMBER_OT PRIMARY KEY (member_id);

alter table MEMBER_OT ADD discount number;

SET VERIFY OFF

DECLARE
    cod_membru MEMBER_OT.member_id%TYPE := &cod;
    nr_titluri_b NUMBER(3);
    nr_titluri_t NUMBER(3);
BEGIN
    select count(*)
    into nr_titluri_t
    from title;         -- selectam nr total de titluri
    
    select count(distinct title_id)
    into nr_titluri_b
    from rental r   
    join member_ot m using (member_id)
    group by member_id
    having member_id = cod_membru;
                --- selectam nr de titluri imprumutate de client
                
    CASE 
        
        WHEN nr_titluri_b * 100 / nr_titluri_t >= 75 THEN  
            UPDATE member_ot
            SET DISCOUNT = 10
            WHERE MEMBER_ID = cod_membru;
            COMMIT; -- ii adaugam discountul corespunzator in fct de ce procent de inchiriere are
            DBMS_OUTPUT.PUT_LINE('1 rand modificat');
        
        WHEN nr_titluri_b * 100 / nr_titluri_t >= 50 THEN 
            UPDATE member_ot
            SET DISCOUNT = 5
            WHERE MEMBER_ID = cod_membru;
            COMMIT;
            DBMS_OUTPUT.PUT_LINE('1 rand modificat');
        
        WHEN nr_titluri_b * 100 / nr_titluri_t >= 25 THEN
            UPDATE member_ot
            SET DISCOUNT = 3
            WHERE MEMBER_ID = cod_membru;
            COMMIT;
            DBMS_OUTPUT.PUT_LINE('1 rand modificat');
        
        
        ELSE -- daca nu se incadreaza la nicio clasa de bonus, afisam ca nu am modif nimic
            DBMS_OUTPUT.PUT_LINE('Clientul nu a atins pragul de bonus');
    END CASE;        
EXCEPTION
    WHEN NO_DATA_FOUND THEN
    DBMS_OUTPUT.PUT_LINE('Nu exista acest id de client');
END;
/ 
SET VERIFY ON;

select * from member_ot;

   