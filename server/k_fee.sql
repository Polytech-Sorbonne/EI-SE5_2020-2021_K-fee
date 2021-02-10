-- commande de destruction des tables
DROP TABLE IF EXISTS Routine;
DROP TABLE IF EXISTS Recette;
DROP TABLE IF EXISTS Jour;
DROP TABLE IF EXISTS heure;
DROP TABLE IF EXISTS Possede_RoutineJour;
DROP TABLE IF EXISTS Possede_JourHeure;
DROP TABLE IF EXISTS Possede_HeureRecette;


-- commandes de creation des tables
CREATE TABLE Routine (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nom TEXT NOT NULL,
    etat TEXT NOT NULL);

CREATE TABLE Recette (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nom TEXT NOT NULL,
    nb_dose_cafe INTEGER NOT NULL,
    nb_dose_sucre INTEGER NOT NULL,
    taille TEXT NOT NULL,
    temperature INTEGER NOT NULL);

CREATE TABLE Jour (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nom TEXT NOT NULL);

CREATE TABLE Heure (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    heure INTEGER NOT NULL,
    minute INTEGER NOT NULL);

--Associations
CREATE TABLE Possede_RoutineJour (
    idRoutine INTEGER NOT NULL,
    idJour INTEGER NOT NULL,
    FOREIGN KEY (idRoutine) REFERENCES Routine(id)
    FOREIGN KEY (idJour) REFERENCES Jour(id)
    PRIMARY KEY (idRoutine,idJour));

CREATE TABLE Possede_JourHeure (
    idJour INTEGER NOT NULL,
    idHeure INTEGER NOT NULL,
    FOREIGN KEY (idJour) REFERENCES Jour(id)
    FOREIGN KEY (idHeure) REFERENCES Heure(id)
    PRIMARY KEY (idJour,idHeure));

CREATE TABLE Possede_HeureRecette (
    idHeure INTEGER NOT NULL,
    idRecette INTEGER NOT NULL,
    FOREIGN KEY (idHeure) REFERENCES Heure(id)
    FOREIGN KEY (idRecette) REFERENCES Recette(id)
    PRIMARY KEY (idHeure,idRecette));
-- insertion de données

INSERT INTO Recette (nom,nb_dose_cafe,nb_dose_sucre, taille, temperature) VALUES
       ("Cafe Long", 4, 1, "Grand", "Chaud"),
       ("Cafe Court", 2, 0, "Petit", "Très Chaud"),
       ("Cafe Matin", 3, 1, "Grand", "Chaud");
