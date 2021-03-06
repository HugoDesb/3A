/**************************************************************************

PARTIE 1

**************************************************************************/
DROP TABLE usine CASCADE CONSTRAINTS;
DROP TABLE produit CASCADE CONSTRAINTS;
DROP TABLE fournisseur CASCADE CONSTRAINTS;
DROP TABLE livraison CASCADE CONSTRAINTS;

CREATE TABLE usine (
  nu INTEGER 
    CONSTRAINT pk_usine PRIMARY KEY,
  nomu varchar2(25),
  ville VARCHAR2(25)
);

INSERT INTO usine VALUES(1,'CITROEN', 'PARIS');
INSERT INTO usine VALUES(2,'PEUGEOT', 'SOCHAUX');
INSERT INTO usine VALUES(3,'CITROEN', 'SOCHAUX');
INSERT INTO usine VALUES(4,'RENAULT', 'PARIS');
INSERT INTO usine VALUES(5,'TOYOTA', 'LYON');

CREATE TABLE produit (
  np INTEGER 
    CONSTRAINT pk_produit PRIMARY KEY,
  nomp varchar2(25),
  couleur VARCHAR2(25),
  poids NUMBER(9,3) 
    CONSTRAINT chk_pds_sup_zero CHECK(poids > 0)
);

INSERT INTO produit VALUES(1,'PLAQUETTE', 'NOIR',0.257);
INSERT INTO produit VALUES(2,'SIEGE', 'ROUGE',15.230);
INSERT INTO produit VALUES(3,'SIEGE', 'VERT',15.230);
INSERT INTO produit VALUES(4,'PARE-BRISE', NULL,11.900);
INSERT INTO produit VALUES(5,'RETROVISEUR', 'VERT',1.020);

CREATE TABLE fournisseur (
  nf INTEGER 
    CONSTRAINT pk_fournisseur PRIMARY KEY,
  nomf VARCHAR2(25),
  statut VARCHAR2(25),
  ville VARCHAR2(25)
);

INSERT INTO fournisseur VALUES(1,'MONROE', 'PRODUCTEUR','LYON');
INSERT INTO fournisseur VALUES(2,'AU BON SIEGE', 'SOUS-TRAITANT','LIMOGES');
INSERT INTO fournisseur VALUES(3,'SAINT GOBAIN', 'PRODUCTEUR','PARIS');


CREATE TABLE livraison (
  np INTEGER 
    CONSTRAINT fk_produit REFERENCES produit,
  nu INTEGER 
    CONSTRAINT fk_usine REFERENCES usine,
  nf INTEGER 
    CONSTRAINT fk_fournisseur REFERENCES fournisseur,
  quantite INTEGER 
    CONSTRAINT ck_quantite_sup_zero CHECK(quantite>0),
  CONSTRAINT pk_livraison PRIMARY KEY(np,nu,nf)
);


INSERT INTO livraison VALUES(1,2,3,2500);
INSERT INTO livraison VALUES(1,3,3,3000);
INSERT INTO livraison VALUES(2,1,1,250);
INSERT INTO livraison VALUES(2,2,3,120);
INSERT INTO livraison VALUES(2,4,2,52);
INSERT INTO livraison VALUES(3,1,2,60);
INSERT INTO livraison VALUES(3,2,1,45);
INSERT INTO livraison VALUES(3,3,1,78);




/**************************************************************************

PARTIE 2

**************************************************************************/

---------------------------------   EXERCICE 1  ---------------------------------
SELECT * 
FROM USINE;

---------------------------------   EXERCICE 2  ---------------------------------
SELECT nu,nomu 
FROM usine 
WHERE ville='SOCHAUX';

---------------------------------   EXERCICE 3  ---------------------------------
SELECT nf 
FROM livraison
WHERE nu=1 AND np=3;

---------------------------------   EXERCICE 4  ---------------------------------
SELECT np, nomp
FROM produit
WHERE COULEUR IS NULL;

---------------------------------   EXERCICE 5  ---------------------------------
SELECT DISTINCT nomu
FROM usine
ORDER BY nomu ASC;

---------------------------------   EXERCICE 6  ---------------------------------
SELECT nu
FROM usine
WHERE SUBSTR(nomu,1,1)='C';

---------------------------------   EXERCICE 7  ---------------------------------
SELECT np
FROM produit
WHERE (nomp LIKE '%S%') OR (nomp LIKE '%s%');

---------------------------------   EXERCICE 8  ---------------------------------
SELECT COUNT(*) nb_fournisseur
FROM fournisseur;

---------------------------------   EXERCICE 9  ---------------------------------
SELECT COUNT(*) nb_pdt_ac_couleur
FROM produit
WHERE COULEUR IS NOT NULL;

---------------------------------   EXERCICE 10  --------------------------------
SELECT AVG(poids) moy_poids_produit
FROM PRODUIT;

---------------------------------   EXERCICE 11  --------------------------------
SELECT SUM(poids) sum_poids_produit
FROM PRODUIT
WHERE couleur='VERT';

---------------------------------   EXERCICE 12  --------------------------------
SELECT MIN(poids) moy_poids_produit
FROM PRODUIT
WHERE COULEUR IS NOT NULL;

---------------------------------   EXERCICE 13  --------------------------------
SELECT COUNT(*) nb_produit, nf
FROM livraison
GROUP BY nf;

---------------------------------   EXERCICE 14  --------------------------------
SELECT AVG(poids) moy_poids_produit, couleur
FROM PRODUIT
GROUP BY couleur;

---------------------------------   EXERCICE 15  --------------------------------
SELECT couleur
FROM PRODUIT
GROUP BY couleur HAVING AVG(poids)>10;

---------------------------------   EXERCICE 16  --------------------------------
SELECT nomf
FROM FOURNISSEUR f
  JOIN LIVRAISON l ON f.nf = l.nf
WHERE nu=1 AND np=3;
              
---------------------------------   EXERCICE 17  --------------------------------
SELECT p.nomp, p.couleur 
FROM produit p
JOIN livraison l ON p.np=l.np
WHERE l.nf = 2;

---------------------------------   EXERCICE 18  --------------------------------
SELECT l.nf
FROM produit p
JOIN livraison l ON p.np=l.np
WHERE l.nu=1 AND p.couleur='ROUGE';

---------------------------------   EXERCICE 19  --------------------------------
SELECT f.nomf
FROM fournisseur f
JOIN LIVRAISON l on f.nf = l.nf
WHERE l.nu IN (SELECT nu
               FROM usine
               WHERE ville IN ('SOCHAUX', 'PARIS')
               )
AND l.np IN (SELECT np
            FROM produit
            WHERE couleur='ROUGE');

---------------------------------   EXERCICE 20  --------------------------------
SELECT l.np
FROM LIVRAISON l
JOIN fournisseur f ON f.nf=l.nf
JOIN usine u ON u.nu=l.nu
WHERE u.ville = f.ville;

---------------------------------   EXERCICE 21  --------------------------------
SELECT u.nu
FROM livraison l
JOIN usine u ON l.nu = u.nu
JOIN FOURNISSEUR f ON l.nf=f.nf
WHERE f.ville!=u.ville
GROUP BY u.nu;

---------------------------------   EXERCICE 22  --------------------------------
SELECT nf
FROM livraison
WHERE nu=1 AND nf IN (SELECT nf
                      FROM livraison
                      WHERE nu=2);


---------------------------------   EXERCICE 23  --------------------------------
SELECT DISTINCT nu
FROM livraison
WHERE np IN (SELECT np
             FROM livraison
             WHERE nf=3);
---------------------------------   EXERCICE 24  --------------------------------
SELECT nu
FROM livraison
WHERE nu NOT IN (SELECT nu
                 FROM livraison
                 WHERE nf!=3);
                 
---------------------------------   EXERCICE 25  --------------------------------
SELECT DISTINCT nu
FROM livraison
WHERE np NOT IN (SELECT np
                 FROM produit
                 WHERE couleur='ROUGE' AND np IN (SELECT np
                                                  FROM livraison l
                                                  JOIN fournisseur f ON l.nf=f.nf
                                                  WHERE f.ville='PARIS'));
                                                  
---------------------------------   EXERCICE 26  --------------------------------
SELECT COUNT(*)
FROM livraison l
JOIN FOURNISSEUR f ON l.nf=f.nf
WHERE f.ville = 'PARIS';

---------------------------------   EXERCICE 27  --------------------------------
SELECT DISTINCT np
FROM produit p
WHERE p -- inférieur a TOUS les autres poids


---------------------------------   EXERCICE 28  --------------------------------
SELECT COUNT()

---------------------------------   EXERCICE 29  --------------------------------
-- num d'usines qui achètent au fournisseur 3 tous les produis qu'il fournit

--num d'usines qui achètent au fournisseur 3
SELECT DISTINCT nu
FROM livraison
WHERE nf=3;

--les produis qu'il fournit
SELECT COUNT(DISTINCT NP)
FROM livraison
WHERE nf=3

--FINAL --->
--num d'usines qui achètent au fournisseur 3 tous les produis qu'il fournit
SELECT DISTINCT nu
FROM livraison
WHERE nf=3
GROUP BY nu
HAVING COUNT(DISTINCT np) = (SELECT COUNT(DISTINCT NP)
                             FROM livraison
                             WHERE nf=3);


