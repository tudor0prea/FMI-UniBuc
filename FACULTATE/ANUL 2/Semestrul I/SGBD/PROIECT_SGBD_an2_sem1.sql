-- Pasul 1:
---------------------CREAREA TABELELOR --------------------------

--CREATE TABLE test (nume varchar(255) primary key, nota INTEGER);

CREATE TABLE Client (
ID_client INTEGER PRIMARY KEY,
nume CHAR(255) NOT NULL,
prenume VARCHAR(255) NOT NULL,
CNP CHAR(13) NOT NULL,
adresa VARCHAR(255) NOT NULL,
email VARCHAR(255) NOT NULL,
telefon CHAR(10) NOT NULL
);

CREATE TABLE Masina (
numar_inmatriculare CHAR(7) PRIMARY KEY,
model VARCHAR(255) NOT NULL,
marca VARCHAR(255) NOT NULL,
an_fabricatie INT NOT NULL,
pret_inchiriere DECIMAL(10,2) NOT NULL,
CHECK (an_fabricatie >= 1900 AND an_fabricatie <= 2023)
);

CREATE TABLE Inchiriere (
ID_inchiriere INTEGER PRIMARY KEY,
ID_client INTEGER NOT NULL,
numar_inmatriculare CHAR(7) NOT NULL,
data_inceput DATE NOT NULL,
data_sfarsit DATE NOT NULL,
pret_total DECIMAL(10,2) NOT NULL,
FOREIGN KEY (ID_client) REFERENCES Client(ID_client),
FOREIGN KEY (numar_inmatriculare) REFERENCES Masina(numar_inmatriculare),
CHECK (data_inceput<=data_sfarsit)
);

CREATE TABLE Intretinere (
ID_intretinere INTEGER PRIMARY KEY,
numar_inmatriculare CHAR(7) NOT NULL,
data DATE NOT NULL,
tip_intretinere VARCHAR(255) NOT NULL,
cost DECIMAL(10,2) NOT NULL,
FOREIGN KEY (numar_inmatriculare) REFERENCES Masina(numar_inmatriculare)
);

CREATE TABLE Reparatie (
ID_reparatie INTEGER PRIMARY KEY,
numar_inmatriculare CHAR(7) NOT NULL,
data DATE NOT NULL,
tip_reparatie VARCHAR(255) NOT NULL,
cost DECIMAL(10,2) NOT NULL,
FOREIGN KEY (numar_inmatriculare) REFERENCES Masina(numar_inmatriculare)
);

CREATE TABLE Comision (
ID_comision INTEGER PRIMARY KEY,
ID_reparatie INTEGER NOT NULL,
procent_comision DECIMAL(5,2) NOT NULL,
FOREIGN KEY (ID_reparatie) REFERENCES Reparatie(ID_reparatie)
);

CREATE TABLE Plata (
  ID_plata INTEGER PRIMARY KEY,
  ID_client INTEGER NOT NULL,
  ID_inchiriere INTEGER NOT NULL,
  data_plata DATE NOT NULL,
  pret DECIMAL(8,2) NOT NULL,
  FOREIGN KEY (ID_client) REFERENCES Client(ID_client),
  FOREIGN KEY (ID_inchiriere) REFERENCES Inchiriere(ID_inchiriere)
);

----------------------------------------------------------------------
-- Pasul 2:
--------------------INSERAREA DATELOR----------------------------------


INSERT INTO Client (ID_client, nume, prenume, CNP, adresa, email, telefon)
VALUES (1, 'Popescu', 'Ion', '1234567891234', 'Str. Morii nr. 7', 'ion.popescu@gmail.com', '0712345678');
INSERT INTO Client (ID_client, nume, prenume, CNP, adresa, email, telefon)
VALUES (2, 'Mihai', 'Ioana', '1234567890000', 'Sos. Oltenitei nr.10', 'ioana.mihai@yahoo.com', '0799887766');
INSERT INTO Client (ID_client, nume, prenume, CNP, adresa, email, telefon)
VALUES (3, 'Grigore', 'Alexandru', '523456789444', 'Str.Mihai Viteazul nr.5', 'alex.grigore@gmail.com', '0712345999');
INSERT INTO Client (ID_client, nume, prenume, CNP, adresa, email, telefon)
VALUES (4, 'Argesanu', 'Rodica', '4253475891234', 'Calea Victoriei nr.35', 'argesanu.r@yahoo.com', '0778546123');
INSERT INTO Client (ID_client, nume, prenume, CNP, adresa, email, telefon)
VALUES (5, 'Oprea', 'Tudor', '5234567891004', 'Bulevardul Unirii nr.127', 'tudor.oprea@hotmail.com', '0710986338');

INSERT INTO Masina (numar_inmatriculare, model, marca, an_fabricatie, pret_inchiriere)
VALUES ('B185WHM', 'Golf', 'Volkswagen', 2018, 150);
INSERT INTO Masina (numar_inmatriculare, model, marca, an_fabricatie, pret_inchiriere)
VALUES ('B123FUG', 'Passat', 'Volkswagen', 2013, 120);
INSERT INTO Masina (numar_inmatriculare, model, marca, an_fabricatie, pret_inchiriere)
VALUES ('B07WHM', '1310', 'Dacia', 1997, 60);
INSERT INTO Masina (numar_inmatriculare, model, marca, an_fabricatie, pret_inchiriere)
VALUES ('B01TOP', 'X5', 'BMW', 2010, 175);
INSERT INTO Masina (numar_inmatriculare, model, marca, an_fabricatie, pret_inchiriere)
VALUES ('B106VHJ', 'Scala', 'Skoda', 2022, 150);
INSERT INTO Masina (numar_inmatriculare, model, marca, an_fabricatie, pret_inchiriere)
VALUES ('B06WHM', 'Supernova', 'Dacia', 2001, 90);

INSERT INTO Inchiriere (ID_inchiriere, ID_client, numar_inmatriculare, data_inceput, data_sfarsit, pret_total)
VALUES (1, 1, 'B185WHM', TO_DATE('2022-02-03', 'YYYY-MM-DD'), TO_DATE('2022-02-07', 'YYYY-MM-DD'), 840);
INSERT INTO Inchiriere (ID_inchiriere, ID_client, numar_inmatriculare, data_inceput, data_sfarsit, pret_total)
VALUES (2, 4, 'B06WHM', TO_DATE('2022-05-09', 'YYYY-MM-DD'), TO_DATE('2022-06-24', 'YYYY-MM-DD'), 1496.25);
INSERT INTO Inchiriere (ID_inchiriere, ID_client, numar_inmatriculare, data_inceput, data_sfarsit, pret_total)
VALUES (3, 2, 'B123FUG', TO_DATE('2022-10-01', 'YYYY-MM-DD'), TO_DATE('2022-10-07', 'YYYY-MM-DD'), 498.54);
INSERT INTO Inchiriere (ID_inchiriere, ID_client, numar_inmatriculare, data_inceput, data_sfarsit, pret_total)
VALUES (4, 1, 'B185WHM', TO_DATE('2022-11-02', 'YYYY-MM-DD'), TO_DATE('2022-12-01', 'YYYY-MM-DD'), 974.20);
INSERT INTO Inchiriere (ID_inchiriere, ID_client, numar_inmatriculare, data_inceput, data_sfarsit, pret_total)
VALUES (5, 2, 'B185WHM', TO_DATE('2022-09-15', 'YYYY-MM-DD'), TO_DATE('2022-09-30', 'YYYY-MM-DD'), 758.50);
INSERT INTO Inchiriere (ID_inchiriere, ID_client, numar_inmatriculare, data_inceput, data_sfarsit, pret_total)
VALUES (6, 1, 'B185WHM', TO_DATE('2022-07-09', 'YYYY-MM-DD'), TO_DATE('2022-07-14', 'YYYY-MM-DD'), 456.12);
INSERT INTO Inchiriere (ID_inchiriere, ID_client, numar_inmatriculare, data_inceput, data_sfarsit, pret_total)
VALUES (7, 1, 'B01TOP', TO_DATE('2022-02-07', 'YYYY-MM-DD'), TO_DATE('2022-02-15', 'YYYY-MM-DD'), 550);
INSERT INTO Inchiriere (ID_inchiriere, ID_client, numar_inmatriculare, data_inceput, data_sfarsit, pret_total)
VALUES (8, 3, 'B06WHM', TO_DATE('2022-05-07', 'YYYY-MM-DD'), TO_DATE('2022-06-30', 'YYYY-MM-DD'), 1545.25);
INSERT INTO Inchiriere (ID_inchiriere, ID_client, numar_inmatriculare, data_inceput, data_sfarsit, pret_total)
VALUES (9, 4, 'B123FUG', TO_DATE('2022-07-10', 'YYYY-MM-DD'), TO_DATE('2022-07-15', 'YYYY-MM-DD'), 320.12);
INSERT INTO Inchiriere (ID_inchiriere, ID_client, numar_inmatriculare, data_inceput, data_sfarsit, pret_total)
VALUES (10, 1, 'B06WHM', TO_DATE('2022-01-03', 'YYYY-MM-DD'), TO_DATE('2022-01-09', 'YYYY-MM-DD'), 375.13);


INSERT INTO Intretinere (ID_intretinere, numar_inmatriculare, data, tip_intretinere, cost)
VALUES (1, 'B185WHM', TO_DATE('2022-12-20', 'YYYY-MM-DD'), 'schimb ulei', 100);
INSERT INTO Intretinere (ID_intretinere, numar_inmatriculare, data, tip_intretinere, cost)
VALUES (2, 'B185WHM', TO_DATE('2022-09-12', 'YYYY-MM-DD'), 'schimb anvelope', 250);
INSERT INTO Intretinere (ID_intretinere, numar_inmatriculare, data, tip_intretinere, cost)
VALUES (3, 'B06WHM', TO_DATE('2022-10-01', 'YYYY-MM-DD'), 'inspectie tehnica', 150);
INSERT INTO Intretinere (ID_intretinere, numar_inmatriculare, data, tip_intretinere, cost)
VALUES (4, 'B123FUG', TO_DATE('2022-11-25', 'YYYY-MM-DD'), 'schimb bec far', 25);
INSERT INTO Intretinere (ID_intretinere, numar_inmatriculare, data, tip_intretinere, cost)
VALUES (5, 'B185WHM', TO_DATE('2022-05-20', 'YYYY-MM-DD'), 'incarcare freon', 120);
INSERT INTO Intretinere (ID_intretinere, numar_inmatriculare, data, tip_intretinere, cost)
VALUES (6, 'B07WHM', TO_DATE('2022-12-20', 'YYYY-MM-DD'), 'schimb ulei', 100);
INSERT INTO Intretinere (ID_intretinere, numar_inmatriculare, data, tip_intretinere, cost)
VALUES (7, 'B01TOP', TO_DATE('2022-12-20', 'YYYY-MM-DD'), 'schimb filtru polen', 190);
INSERT INTO Intretinere (ID_intretinere, numar_inmatriculare, data, tip_intretinere, cost)
VALUES (8, 'B185WHM', TO_DATE('2022-05-10', 'YYYY-MM-DD'), 'schimb anvelope', 300);
INSERT INTO Intretinere (ID_intretinere, numar_inmatriculare, data, tip_intretinere, cost)
VALUES (9, 'B123FUG', TO_DATE('2022-01-05', 'YYYY-MM-DD'), 'completat antigel', 70);
INSERT INTO Intretinere (ID_intretinere, numar_inmatriculare, data, tip_intretinere, cost)
VALUES (10, 'B06WHM', TO_DATE('2022-01-15', 'YYYY-MM-DD'), 'completat solutie parbriz', 30);


INSERT INTO Reparatie (ID_reparatie, numar_inmatriculare, data, tip_reparatie, cost)
VALUES (1, 'B123FUG',  TO_DATE('2022-01-15', 'YYYY-MM-DD'), 'schimb far si bara fata', 200);
INSERT INTO Reparatie (ID_reparatie, numar_inmatriculare, data, tip_reparatie, cost)
VALUES (2, 'B185WHM',  TO_DATE('2022-01-30', 'YYYY-MM-DD'), 'inlocuit rezervor', 500);
INSERT INTO Reparatie (ID_reparatie, numar_inmatriculare, data, tip_reparatie, cost)
VALUES (3, 'B06WHM',  TO_DATE('2022-12-04', 'YYYY-MM-DD'), 'reparatie cutie de viteze', 350);
INSERT INTO Reparatie (ID_reparatie, numar_inmatriculare, data, tip_reparatie, cost)
VALUES (4, 'B185WHM',  TO_DATE('2022-11-24', 'YYYY-MM-DD'), 'macara geam stanga fata', 150);
INSERT INTO Reparatie (ID_reparatie, numar_inmatriculare, data, tip_reparatie, cost)
VALUES (5, 'B06WHM',  TO_DATE('2022-10-01', 'YYYY-MM-DD'), 'schimb stop stanga', 300);

INSERT INTO Comision (ID_comision, ID_reparatie, procent_comision)
VALUES (1, 1, 10);
INSERT INTO Comision (ID_comision, ID_reparatie, procent_comision)
VALUES (2, 4 , 15);
INSERT INTO Comision (ID_comision, ID_reparatie, procent_comision)
VALUES (3, 2 , 5);
INSERT INTO Comision (ID_comision, ID_reparatie, procent_comision)
VALUES (4, 3 , 20);
INSERT INTO Comision (ID_comision, ID_reparatie, procent_comision)
VALUES (5, 5 , 15);

INSERT INTO Plata (ID_plata , ID_client , ID_inchiriere , data_plata , pret )
VALUES (1, 1, 1, TO_DATE('2022-02-07', 'YYYY-MM-DD'), 840);
INSERT INTO Plata (ID_plata , ID_client , ID_inchiriere , data_plata , pret )
VALUES (2, 4, 2, TO_DATE('2022-06-24', 'YYYY-MM-DD'), 1496.25);
INSERT INTO Plata (ID_plata , ID_client , ID_inchiriere , data_plata , pret )
VALUES (3, 2, 3, TO_DATE('2022-10-07', 'YYYY-MM-DD'), 498.54);
INSERT INTO Plata (ID_plata , ID_client , ID_inchiriere , data_plata , pret )
VALUES (4, 1, 4, TO_DATE('2022-12-01', 'YYYY-MM-DD'), 974.20);
INSERT INTO Plata (ID_plata , ID_client , ID_inchiriere , data_plata , pret )
VALUES (5, 2, 5, TO_DATE('2022-09-30', 'YYYY-MM-DD'), 758.5);
INSERT INTO Plata (ID_plata , ID_client , ID_inchiriere , data_plata , pret )
VALUES (6, 1, 6, TO_DATE('2022-07-14', 'YYYY-MM-DD'), 456.12);
INSERT INTO Plata (ID_plata , ID_client , ID_inchiriere , data_plata , pret )
VALUES (7, 1, 7, TO_DATE('2022-02-15', 'YYYY-MM-DD'), 550);
INSERT INTO Plata (ID_plata , ID_client , ID_inchiriere , data_plata , pret )
VALUES (8, 3, 8, TO_DATE('2022-06-30', 'YYYY-MM-DD'), 1545.25);
INSERT INTO Plata (ID_plata , ID_client , ID_inchiriere , data_plata , pret )
VALUES (9, 4, 9, TO_DATE('2022-07-15', 'YYYY-MM-DD'), 320.12);
INSERT INTO Plata (ID_plata , ID_client , ID_inchiriere , data_plata , pret )
VALUES (10, 1, 10, TO_DATE('2022-01-09', 'YYYY-MM-DD'), 375.13);


/
--------------------------------------------------------------------------
-- Pasul 3:
--------------------REZOLVAREA CERINTELOR----------------------------------

-- CERINTA 6:

-- subprogram stocat independent care s� utilizeze dou� tipuri diferite de colectii
-- dat un vector cu numere de inmatriculare, sa se afiseze pentru fiecare
-- id urile inchirierilor si numele+prenumele persoanelor care au inchiriat,
-- date stocate intr un tablou de caractere 

CREATE OR REPLACE TYPE t_vector AS VARRAY(60) OF CHAR(7);
/
CREATE OR REPLACE PROCEDURE afiseaza_inchirieri (p_numar_inmatriculare t_vector)
AS
  TYPE t_inchirieri IS TABLE OF VARCHAR2(4000);
  v_inchirieri t_inchirieri;
 
BEGIN
    for it in p_numar_inmatriculare.first .. p_numar_inmatriculare.last loop
      
      DBMS_OUTPUT.PUT_LINE('->'||p_numar_inmatriculare(it)||':');
      
      SELECT i.ID_inchiriere || ' | ' || c.nume || ' ' || c.prenume
      BULK COLLECT INTO v_inchirieri
      FROM Inchiriere i
      JOIN Masina m ON i.numar_inmatriculare = m.numar_inmatriculare
      JOIN Client c ON i.ID_client = c.ID_client
      WHERE m.numar_inmatriculare = p_numar_inmatriculare(it);
      
      FOR i IN v_inchirieri.FIRST..v_inchirieri.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(v_inchirieri(i));
        
      END LOOP;
    
      DBMS_OUTPUT.PUT_LINE(' ');
      
  end loop;
END;
/
BEGIN
afiseaza_inchirieri(t_vector('B185WHM', 'B06WHM','B01TOP'));
END;

/


--------------------------------------------------------------------------
-- CERINTA 7:

-- cursor parametrizat ce primeste un numar de inmatriculare si af toate numele si prenumele
--      care au inchiriat acea masina
-- cursor non-parametrizat ce afiseaza marca si modelul pentru masinilor care au fost inchiriate
--      pentru mai mult de 1000 de lei
CREATE OR REPLACE PROCEDURE afiseaza_inchirieri_parametrizat (p_numar_inmatriculare CHAR)
AS
CURSOR c_inchirieri_parametrizat (p_numar_inmatriculare CHAR) IS
SELECT c.nume, c.prenume, m.marca
FROM Inchiriere i
JOIN Masina m ON i.numar_inmatriculare = m.numar_inmatriculare
JOIN Client c ON i.ID_client = c.ID_client
WHERE m.numar_inmatriculare = p_numar_inmatriculare;

CURSOR c_inchirieri_non_parametrizat IS
SELECT m.marca, m.model
FROM Inchiriere i
JOIN Masina m ON i.numar_inmatriculare = m.numar_inmatriculare
JOIN Client c ON i.ID_client = c.ID_client
WHERE i.pret_total > 1000;

BEGIN
-- utilizarea cursorului parametrizat
DBMS_OUTPUT.PUT_LINE('Cursor parametrizat - clienti pentru acest numar:');
FOR r_inchiriere_parametrizat IN c_inchirieri_parametrizat (p_numar_inmatriculare) LOOP
DBMS_OUTPUT.PUT_LINE(r_inchiriere_parametrizat.nume || ' ' || r_inchiriere_parametrizat.prenume|| ' '|| r_inchiriere_parametrizat.marca);
END LOOP;

-- utilizarea cursorului non-parametrizat
DBMS_OUTPUT.PUT_LINE('Cursor non-parametrizat - marca si model:');
FOR r_inchiriere_non_parametrizat IN c_inchirieri_non_parametrizat LOOP
DBMS_OUTPUT.PUT_LINE(r_inchiriere_non_parametrizat.marca || ' ' || r_inchiriere_non_parametrizat.model);
END LOOP;
END;
/

BEGIN
    afiseaza_inchirieri_parametrizat('B185WHM');
END;
/

--------------------------------------------------------------------------
-- CERINTA 8:
-- OBTINEM Datele inchirierii pentru un client care a inchiriat
--      o singura data - daca a inchiriat de mai multe ori clientul dat
--      se va afisa mesaj de eroare, la fel si daca nu a inchiriat niciodata

CREATE OR REPLACE FUNCTION obtine_inchirieri (p_id_client INT)
RETURN VARCHAR2
AS
    v_nr INT;
    v_result VARCHAR2(1000);
    v_exc1 exception;
    v_exc2 exception;
BEGIN
    SELECT count(i.ID_inchiriere || ' | ' || c.nume || ' ' || c.prenume || ' | ' || m.marca)
    INTO v_nr
    FROM Inchiriere i
    JOIN Masina m ON i.numar_inmatriculare = m.numar_inmatriculare
    JOIN Client c ON i.ID_client = c.ID_client
    WHERE c.ID_client = p_id_client;
    
    if v_nr =0 then
     RAISE v_exc1;
     end if;
    if v_nr >1 then
     RAISE v_exc2;
     end if;
    
    SELECT i.ID_inchiriere || ' | ' || c.nume || ' ' || c.prenume || ' | ' || m.marca
    INTO v_result
    FROM Inchiriere i
    JOIN Masina m ON i.numar_inmatriculare = m.numar_inmatriculare
    JOIN Client c ON i.ID_client = c.ID_client
    WHERE c.ID_client = p_id_client;
    
    RETURN v_result;

EXCEPTION
--    WHEN NO_DATA_FOUND THEN
--    RETURN 'Nu au fost g�site �nchirieri pentru acest client';
--    WHEN TOO_MANY_ROWS THEN
--    RETURN 'Acest client a inchiriat de mai multe ori';
    
    WHEN v_exc1 THEN
        RAISE_APPLICATION_ERROR(-20011,'Nu au fost g�site �nchirieri pentru acest client');
    
    WHEN v_exc2 THEN
        RAISE_APPLICATION_ERROR(-20012,'Acest client a inchiriat de mai multe ori');
     
END;
/
BEGIN

DBMS_OUTPUT.PUT_LINE(PACHET_INCHIRIERE_AUTO.obtine_inchirieri(&p_id_client));
-- apelarea functiei pentru un ID de client existent (cu o sg inchiriere)
--DBMS_OUTPUT.PUT_LINE(obtine_inchirieri(3));


-- apelarea functiei pentru un ID de client care nu exista
--DBMS_OUTPUT.PUT_LINE(obtine_inchirieri(999));

-- apelarea functiei pentru un ID cu mai multe inchirieri
--DBMS_OUTPUT.PUT_LINE(obtine_inchirieri(1));
END;

/



--------------------------------------------------------------------------
-- CERINTA 9:
-- dam un id de client, iar pentru acesta afisam, doar daca a inchiriat o singura
--   masina, datele masinii, numele sau, id ul platii, suma platita si apoi
--   numarul de intrari in service pentru intretinere pe care le a avut masina respectiva

-- erorile sunt: daca al nostru client a inchiriat mai multe masini sau de mai multe ori
--                  (too many rows)
--  sau daca nu exista acest client in baza de date ori nu a inchiriat nimic

CREATE OR REPLACE PROCEDURE afiseaza_inchirierile (p_id_client INT)
AS
v_memorare_inchiriere  VARCHAR2(4000);
BEGIN
     SELECT i.ID_inchiriere || '|' || m.numar_inmatriculare || '|' || c.nume
    || '|' ||c.prenume || '|' || p.id_plata || '|' || p.pret || '|' || COUNT(r.tip_intretinere) as numar_intretineri
    
    INTO v_memorare_inchiriere
    FROM Inchiriere i
    JOIN Masina m ON i.numar_inmatriculare = m.numar_inmatriculare
    JOIN Client c ON i.ID_client = c.ID_client
    JOIN Plata p ON p.ID_inchiriere = i.ID_inchiriere
    JOIN Intretinere r on i.numar_inmatriculare = r.numar_inmatriculare
    WHERE c.ID_client = p_id_client
    GROUP BY i.ID_inchiriere, m.numar_inmatriculare, c.nume, c.prenume, p.id_plata, p.pret;

  
    DBMS_OUTPUT.PUT_LINE(v_memorare_inchiriere);
  
EXCEPTION
  WHEN NO_DATA_FOUND THEN
    DBMS_OUTPUT.PUT_LINE('Nu exista inchirieri pentru acest client.');
  WHEN TOO_MANY_ROWS THEN
    DBMS_OUTPUT.PUT_LINE('S-au gasit mai multe inchirieri decat era de asteptat pentru acest client.');
END;
/
BEGIN
--client cu o singura inchiriere -> functioneaza corect
PACHET_INCHIRIERE_AUTO.afiseaza_inchirierile(3);
DBMS_OUTPUT.PUT_LINE(' ');

--client cu mai multe inchirieri
afiseaza_inchirierile(1);
DBMS_OUTPUT.PUT_LINE(' ');

--client existent care nu a inchiriat nimic/ inexistent in bd
afiseaza_inchirierile(5);
DBMS_OUTPUT.PUT_LINE(' ');


END;

/



--------------------------------------------------------------------------
-- CERINTA 10:
-- am creat un trigger LMD la nivel de comanda
CREATE OR REPLACE TRIGGER verifica_inserare
BEFORE INSERT OR UPDATE OR DELETE ON Masina
DECLARE
    v_numar_auto INT;
BEGIN
   SELECT COUNT(numar_inmatriculare) 
   INTO v_numar_auto
   FROM MASINA;
   
  IF v_numar_auto < 5 THEN
    RAISE_APPLICATION_ERROR(-20002, 'Nu putem avea mai putin de 5 masini in firma.');
  END IF;
  
  IF v_numar_auto > 20 THEN 
    RAISE_APPLICATION_ERROR (-20003, 'Nu putem avea mai mult de 20 masini');
   END IF;
END;


/
-- DECLANSARE:
INSERT INTO Masina (numar_inmatriculare, model, marca, an_fabricatie, pret_inchiriere)
VALUES ('B01ERO', 'Duster', 'Dacia', 2012, 120);


delete from masina where numar_inmatriculare='B01ERO';


/

--------------------------------------------------------------------------
-- CERINTA 11:
-- am creat un trigger LMD la nivel de linie


CREATE OR REPLACE TRIGGER verificare_adaugare_masina
BEFORE INSERT ON Masina
FOR EACH ROW
DECLARE
    v_numar_auto INT;
BEGIN

  SELECT COUNT (numar_inmatriculare) into v_numar_auto
  from MASINA
  where marca = :new.marca;
  DBMS_OUTPUT.PUT_LINE('S-a adaugat o noua masina cu numarul de inmatriculare ' || :NEW.numar_inmatriculare);
  DBMS_OUTPUT.PUT_LINE('Este masina marca '||:new.marca ||' cu numarul ' || v_numar_auto+1);
END;
/
INSERT INTO Masina (numar_inmatriculare, model, marca, an_fabricatie, pret_inchiriere)
VALUES ('B108XAD', 'Vitara', 'Suzuki', 2020, 190);

/
COMMIT;

/

-- CERINTA 12:
-- LDD
CREATE TABLE ev_modif
(user_logat VARCHAR2(30),
eveniment VARCHAR2(20),
data TIMESTAMP(3));
/
CREATE OR REPLACE TRIGGER modif_bd
    AFTER CREATE OR DROP OR ALTER ON SCHEMA
    
DECLARE
    ora_op TIMESTAMP;
BEGIN
    ora_op:=SYSDATE;
    INSERT INTO ev_modif
    VALUES ( SYS.LOGIN_USER,
    SYS.SYSEVENT, SYSTIMESTAMP(3));
  
    IF (TO_CHAR(ora_op,'HH24') NOT BETWEEN 7 AND 21)THEN
        RAISE_APPLICATION_ERROR(-20005,'Nu poti modifica tabelele in afara orelor de program');
    END IF;
END;
/
CREATE TABLE nou (col INT);
ALTER TABLE nou ADD (col_ INT);
--INSERT INTO nou VALUES (1,2);
/
SELECT * FROM ev_modif;
/
SELECT * from nou;
/



-- CERINTA 13: 
-- un pachet care sa contina tot ce este implementat anterior

CREATE OR REPLACE PACKAGE PACHET_INCHIRIERE_AUTO AS
    --6
    TYPE t_vector IS VARRAY(60) OF CHAR(7);               
    PROCEDURE afiseaza_inchirieri (p_numar_inmatriculare t_vector);
    --7
    PROCEDURE afiseaza_inchirieri_parametrizat (p_numar_inmatriculare CHAR);
    --8
    FUNCTION obtine_inchirieri (p_id_client INT) RETURN VARCHAR2;
    --9 
    PROCEDURE afiseaza_inchirierile (p_id_client INT);
    
END PACHET_INCHIRIERE_AUTO;

/
CREATE OR REPLACE PACKAGE BODY  PACHET_INCHIRIERE_AUTO AS 

    --6
    PROCEDURE afiseaza_inchirieri (p_numar_inmatriculare t_vector)
        IS
        TYPE t_inchirieri IS TABLE OF VARCHAR2(4000);
          v_inchirieri t_inchirieri;
         
        BEGIN
            for it in p_numar_inmatriculare.first .. p_numar_inmatriculare.last loop
              
              DBMS_OUTPUT.PUT_LINE('->'||p_numar_inmatriculare(it)||':');
              
              SELECT i.ID_inchiriere || ' | ' || c.nume || ' ' || c.prenume
              BULK COLLECT INTO v_inchirieri
              FROM Inchiriere i
              JOIN Masina m ON i.numar_inmatriculare = m.numar_inmatriculare
              JOIN Client c ON i.ID_client = c.ID_client
              WHERE m.numar_inmatriculare = p_numar_inmatriculare(it);
              
              FOR i IN v_inchirieri.FIRST..v_inchirieri.LAST LOOP
                DBMS_OUTPUT.PUT_LINE(v_inchirieri(i));
                
              END LOOP;
            
              DBMS_OUTPUT.PUT_LINE(' ');
              
          end loop;
        END afiseaza_inchirieri;


      --7
        PROCEDURE afiseaza_inchirieri_parametrizat (p_numar_inmatriculare CHAR)
            IS
            CURSOR c_inchirieri_parametrizat (p_numar_inmatriculare CHAR) IS
            SELECT c.nume, c.prenume
            FROM Inchiriere i
            JOIN Masina m ON i.numar_inmatriculare = m.numar_inmatriculare
            JOIN Client c ON i.ID_client = c.ID_client
            WHERE m.numar_inmatriculare = p_numar_inmatriculare;
            
            CURSOR c_inchirieri_non_parametrizat IS
            SELECT m.marca, m.model
            FROM Inchiriere i
            JOIN Masina m ON i.numar_inmatriculare = m.numar_inmatriculare
            JOIN Client c ON i.ID_client = c.ID_client
            WHERE i.pret_total > 1000;
            
            BEGIN
            -- utilizarea cursorului parametrizat
            DBMS_OUTPUT.PUT_LINE('Cursor parametrizat - clienti pentru acest numar:');
            FOR r_inchiriere_parametrizat IN c_inchirieri_parametrizat (p_numar_inmatriculare) LOOP
            DBMS_OUTPUT.PUT_LINE(r_inchiriere_parametrizat.nume || ' ' || r_inchiriere_parametrizat.prenume);
            END LOOP;
            
            -- utilizarea cursorului non-parametrizat
            DBMS_OUTPUT.PUT_LINE('Cursor non-parametrizat - marca si model:');
            FOR r_inchiriere_non_parametrizat IN c_inchirieri_non_parametrizat LOOP
            DBMS_OUTPUT.PUT_LINE(r_inchiriere_non_parametrizat.marca || ' ' || r_inchiriere_non_parametrizat.model);
            END LOOP;
        END afiseaza_inchirieri_parametrizat;
        
        -- 8
      FUNCTION obtine_inchirieri (p_id_client INT)
            RETURN VARCHAR2
            IS
                v_result VARCHAR2(1000);
            BEGIN
                SELECT i.ID_inchiriere || ' | ' || c.nume || ' ' || c.prenume || ' | ' || m.marca
                INTO v_result
                FROM Inchiriere i
                JOIN Masina m ON i.numar_inmatriculare = m.numar_inmatriculare
                JOIN Client c ON i.ID_client = c.ID_client
                WHERE c.ID_client = p_id_client;
                RETURN v_result;
            EXCEPTION
            --    WHEN NO_DATA_FOUND THEN
            --    RETURN 'Nu au fost g�site �nchirieri pentru acest client';
            --    WHEN TOO_MANY_ROWS THEN
            --    RETURN 'Acest client a inchiriat de mai multe ori';
                
                WHEN NO_DATA_FOUND THEN
                RAISE_APPLICATION_ERROR(-20010, 'Nu exista inchirieri pentru acest client');
                
                WHEN TOO_MANY_ROWS THEN
                RAISE_APPLICATION_ERROR(-20011, 'Acest cleint a inchiriat de mai multe ori');
                 
        END obtine_inchirieri;
            
            
            -- 9
        PROCEDURE afiseaza_inchirierile (p_id_client INT)
                IS
                v_memorare_inchiriere  VARCHAR2(4000);
                BEGIN
                     SELECT i.ID_inchiriere || '|' || m.numar_inmatriculare || '|' || c.nume
                    || '|' ||c.prenume || '|' || p.id_plata || '|' || p.pret || '|' || COUNT(r.tip_intretinere) as numar_intretineri
                    
                    INTO v_memorare_inchiriere
                    FROM Inchiriere i
                    JOIN Masina m ON i.numar_inmatriculare = m.numar_inmatriculare
                    JOIN Client c ON i.ID_client = c.ID_client
                    JOIN Plata p ON p.ID_inchiriere = i.ID_inchiriere
                    JOIN Intretinere r on i.numar_inmatriculare = r.numar_inmatriculare
                    WHERE c.ID_client = p_id_client
                    GROUP BY i.ID_inchiriere, m.numar_inmatriculare, c.nume, c.prenume, p.id_plata, p.pret;
                
                  
                    DBMS_OUTPUT.PUT_LINE(v_memorare_inchiriere);
                  
                EXCEPTION
                  WHEN NO_DATA_FOUND THEN
                    DBMS_OUTPUT.PUT_LINE('Nu exista inchirieri pentru acest client.');
                  WHEN TOO_MANY_ROWS THEN
                    DBMS_OUTPUT.PUT_LINE('S-au gasit mai multe inchirieri decat era de asteptat pentru acest client.');
            END afiseaza_inchirierile;
            
END PACHET_INCHIRIERE_AUTO;

/
BEGIN
--6
PACHET_INCHIRIERE_AUTO.afiseaza_inchirieri(PACHET_INCHIRIERE_AUTO.t_vector('B185WHM', 'B06WHM','B01TOP'));
DBMS_OUTPUT.PUT_LINE(' ');


--7
PACHET_INCHIRIERE_AUTO.afiseaza_inchirieri_parametrizat('B185WHM');

--8
DBMS_OUTPUT.PUT_LINE(PACHET_INCHIRIERE_AUTO.obtine_inchirieri(&p_id_client));
-- apelarea functiei pentru un ID de client existent (cu o sg inchiriere)
--DBMS_OUTPUT.PUT_LINE(PACHET_INCHIRIERE_AUTO.obtine_inchirieri(3));


-- apelarea functiei pentru un ID de client care nu exist�
-- DBMS_OUTPUT.PUT_LINE(PACHET_INCHIRIERE_AUTO.obtine_inchirieri(999));

-- apelarea functiei pentru un ID cu mai multe inchirieri
-- DBMS_OUTPUT.PUT_LINE(PACHET_INCHIRIERE_AUTO.obtine_inchirieri(1));

--9

--client cu o singura inchiriere -> functioneaza corect
PACHET_INCHIRIERE_AUTO.afiseaza_inchirierile(3);
DBMS_OUTPUT.PUT_LINE(' ');

--client cu mai multe inchirieri
PACHET_INCHIRIERE_AUTO.afiseaza_inchirierile(1);
DBMS_OUTPUT.PUT_LINE(' ');

--client existent care nu a inchiriat nimic/ inexistent in bd
afiseaza_inchirierile(5);
DBMS_OUTPUT.PUT_LINE(' ');

END;
/











-- CERINTA 14:

/
-- pachet 
CREATE OR REPLACE PACKAGE PACHET_C AS
    FUNCTION total_comision(p_numar_auto CHAR) RETURN INT; 
    
END PACHET_C;
/
CREATE OR REPLACE PACKAGE BODY PACHET_C  IS
    
-- functie care ne ia un numar de inmatriculare si returneaza 
-- cati bani s au cheltuit pe comisionul de la reparatiile sale
    FUNCTION total_comision (p_numar_auto CHAR) RETURN INT
    IS
    v_suma_comision INT;
    BEGIN
        SELECT SUM(r.cost * c.procent_comision/100) 
        INTO v_suma_comision
        FROM MASINA m
        JOIN REPARATIE r ON r.numar_inmatriculare=m.numar_inmatriculare
        JOIN COMISION c ON c.id_reparatie=r.id_reparatie
        WHERE m.numar_inmatriculare=p_numar_auto;
        
        RETURN v_suma_comision;
        
    END total_comision;
    
END PACHET_C;
/

/

    