SET SERVEROUTPUT ON;

/*--------------------------------------------------*/
/*                    Exercice 1                    */
/*--------------------------------------------------*/

BEGIN
  DBMS_OUTPUT.PUT_LINE('BONJOUR !');
END;


/*--------------------------------------------------*/
/*                    Exercice 2                    */
/*--------------------------------------------------*/
/*  1  */
DECLARE
  pl_nbPlaces RESERVATIONS.nbPlaces%TYPE;
BEGIN
  SELECT SUM(nbPlaces) INTO pl_nbPlaces FROM RESERVATIONS WHERE numVol='V720';
  DBMS_OUTPUT.PUT_LINE('Nombre de places V720 = ' || pl_nbPlaces);
END;

/*  2  */
DECLARE
  pl_nbPlaces RESERVATIONS.nbPlaces%TYPE;
BEGIN
  SELECT SUM(nbPlaces) INTO pl_nbPlaces FROM RESERVATIONS WHERE numVol='V720';
  
  IF pl_nbPlaces<=250 THEN
    DBMS_OUTPUT.PUT_LINE('Capacité OK');
  ELSE
    DBMS_OUTPUT.PUT_LINE('Capacité insuffisante');
  END IF;
END;

/*  3  */
DECLARE
  pl_nbPlaces RESERVATIONS.nbPlaces%TYPE;
BEGIN
  SELECT SUM(nbPlaces) INTO pl_nbPlaces FROM RESERVATIONS WHERE numVol='V720';
  
  IF pl_nbPlaces<=250 THEN
    DBMS_OUTPUT.PUT_LINE('Capacité OK');
  ELSE
    RAISE_APPLICATION_ERROR(-20000, 'capacité insuffisante');
  END IF;
END;


/*--------------------------------------------------*/
/*                    Exercice 3                    */
/*--------------------------------------------------*/
DECLARE
  CURSOR cVOLS IS
    SELECT NumVol, NumAv, DateD, DateA
    FROM Vols
    WHERE NumAv=101 OR NumAv=720;
  duree Vols.dateA%TYPE; 
BEGIN
  FOR vVOLS IN cVOLS LOOP
    DBMS_OUTPUT.PUT_LINE('Durée du vol: ' 
          || FLOOR((vVOLS.DateA-vVOLS.DateD)*24)
          || ':' 
          || MOD((vVOLS.DateA-vVOLS.DateD)*24*60,60)
          );
  END LOOP;
END;


/*--------------------------------------------------*/
/*                    Exercice 4                    */
/*--------------------------------------------------*/



/*--------------------------------------------------*/
/*                    Exercice 5                    */
/*--------------------------------------------------*/