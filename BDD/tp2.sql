------------------------  Question 1  ------------------------------------------
SELECT  DISTINCT VilleD
FROM VOLS;

------------------------  Question 2  ------------------------------------------
SELECT numVol
FROM vols
WHERE (NUMAV=240) AND (VILLED='Paris' OR VILLED='Marseille');

------------------------  Question 3  ------------------------------------------
SELECT NumPil
FROM PILOTES
WHERE VillePil NOT IN ('Marseille','Nice');

------------------------  Question 4  ------------------------------------------
SELECT DISTINCT NumPil
FROM VOLS
WHERE VilleD NOT IN ('Marseille','Paris');

------------------------  Question 5  ------------------------------------------
SELECT DISTINCT NumPil
FROM VOLS
WHERE NumPil NOT IN (SELECT NumPil
                     FROM VOLS
                     WHERE VilleD = 'Paris'
                     AND VilleA = 'Marseille');

------------------------  Question 6  ------------------------------------------
SELECT NumVol
FROM VOLS
WHERE (NumAV IS NULL) 
OR (NumAv!=101 AND NumAv!=401);

------------------------  Question 7  ------------------------------------------

SELECT DISTINCT NomAv, CapAv
FROM AVIONS
ORDER BY NomAv ASC, CapAv DESC;

------------------------  Question 8  ------------------------------------------
SELECT NumAv, NomAv 
FROM AVIONS
WHERE (NomAv NOT LIKE('%A%')) 
AND (NomAv NOT LIKE('%a%'));

------------------------  Question 9  ------------------------------------------
SELECT NomPil
FROM PILOTES
WHERE ('A'=SUBSTR(NomPil,2,1)) OR ('a'=SUBSTR(NomPil,2,1));

------------------------  Question 10  -----------------------------------------
SELECT NumVol
FROM VOLS
WHERE (DateA-DateD)*24 > 2 AND (DateA-DateD)*24 < 4;

------------------------  Question 11  -----------------------------------------
SELECT DISTINCT NumPil
FROM VOLS
WHERE VilleD='Marseille' AND (DateA-DateD)*24 > 1;

------------------------  Question 12  -----------------------------------------
SELECT NumVol
FROM VOLS
WHERE (DateA-DateD)*24 = (SELECT Max((DateA-DateD)*24)
                          FROM VOLS);

------------------------  Question 13  -----------------------------------------
SELECT NumVol
FROM VOLS
WHERE TO_CHAR(DateD,'DD/MM/YYYY')=(SELECT TO_CHAR(DateD,'DD/MM/YYYY') 
                                   FROM VOLS 
                                   WHERE NUMVOL='V101')
AND VilleD = (SELECT VilleD
              FROM VOLS 
              WHERE NUMVOL='V101')
AND VilleA = (SELECT VilleA
              FROM VOLS 
              WHERE NUMVOL='V101');

------------------------  Question 14  -----------------------------------------
SELECT DISTINCT cl.NumCl, cl.NomCl
FROM Clients cl JOIN RESERVATIONS re ON cl.NumCl = re.NumCl
WHERE re.NumVol IN (SELECT re.NumVol
                    FROM Clients cl
                    JOIN RESERVATIONS re ON cl.NumCl = re.NumCl
                    WHERE cl.NomCl = 'Lorentz');

------------------------  Question 15  -----------------------------------------
SELECT NumCl, COUNT(NumVol)
FROM Reservations
GROUP BY NumCl
HAVING COUNT(NumVol)>3;

------------------------  Question 16  -----------------------------------------
SELECT DISTINCT NumPil
FROM VOLS
GROUP BY NumPil
HAVING COUNT(NumVol) = (SELECT MAX(COUNT(NumVol))
                        FROM VOLS
                        GROUP BY NumPil);
                        
--variante
SELECT DISTINCT NumPil
FROM VOLS
GROUP BY NumPil
HAVING COUNT(NumVol) >= ALL(SELECT COUNT(NumVol)
                        FROM VOLS
                        GROUP BY NumPil);

------------------------  Question 17  -----------------------------------------


------------------------  Question 18  -----------------------------------------
------------------------  Question 19  -----------------------------------------


