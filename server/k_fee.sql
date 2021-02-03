-- commande de destruction des tables
DROP TABLE IF EXISTS Routine;
DROP TABLE IF EXISTS Recette;

-- commandes de creation des tables
CREATE TABLE Routine (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    debut TEXT NOT NULL,
    valeur INTEGER NOT NULL,
    unite TEXT NOT NULL);

CREATE TABLE Recette (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nom TEXT NOT NULL,
    nb_dose INTEGER NOT NULL,
    nb_cafe INTEGER NOT NULL,
    taille TEXT NOT NULL,
    temperature INTEGER NOT NULL);

--Associations
CREATE TABLE Possede_RoutineRecette (
    idRoutine INTEGER NOT NULL,
    idRecette INTEGER NOT NULL,
    FOREIGN KEY (idRoutine) REFERENCES Routine(id)
    FOREIGN KEY (idRecette) REFERENCES Recette(id)
    PRIMARY KEY (idRoutine,idRecette));

-- insertion de données
