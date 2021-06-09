DROP TABLE PlayerToTeam;
DROP TABLE Games;
DROP TABLE Teams;
DROP TABLE Players;

CREATE TABLE Teams (
    teamId NUMBER(2),
    name VARCHAR(32),
    city VARCHAR(32),
    coach VARCHAR(32),
    
    PRIMARY KEY (teamId));
    
CREATE TABLE Players (
    playerId NUMBER(3),
    name VARCHAR(32),
    position VARCHAR(16),
    skillLevel NUMBER(1),
    
    PRIMARY KEY (playerId));
    
CREATE TABLE PlayerToTeam (
    playerId NUMBER(3),
    teamId NUMBER(2),
    captainInd CHAR(1),
    
    PRIMARY KEY (playerId),
    FOREIGN KEY (playerId) REFERENCES Players(playerId) ON DELETE CASCADE,
    FOREIGN KEY (teamId) REFERENCES Teams(teamId) ON DELETE CASCADE);
    
CREATE TABLE Games (
    hostTeamId NUMBER(3),
    guestTeamId NUMBER(3),
    datePlayed DATE,
    hostTeamScore NUMBER(2),
    guestTeamScore NUMBER(2),
    
    PRIMARY KEY (hostTeamId, guestTeamId, datePlayed),
    FOREIGN KEY (hostTeamId) REFERENCES Teams(teamId),
    FOREIGN KEY (guestTeamId) REFERENCES Teams(teamId));
    
INSERT INTO Teams VALUES (1, 'Texans', 'Houston', 'Bill O''Brien');
INSERT INTO Teams VALUES (2, 'Colts', 'Indianapolis', 'Frank Reich');

INSERT INTO Players VALUES (1, 'DeShaun Watson', 'QB', 9);
INSERT INTO Players VALUES (2, 'Lamar Miller', 'RB', 7);
INSERT INTO Players VALUES (3, 'Andrew Luck', 'QB', 8);
INSERT INTO Players VALUES (4, 'T.Y. Hilton', 'WR', 7);

INSERT INTO PlayerToTeam VALUES (1, 1, 'Y');
INSERT INTO PlayerToTeam VALUES (2, 1, 'N');
INSERT INTO PlayerToTeam VALUES (3, 2, 'Y');
INSERT INTO PlayerToTeam VALUES (4, 2, 'N');

INSERT INTO Games VALUES (2, 1, TO_DATE('20171231', 'YYYYMMDD'), 22, 13);
INSERT INTO Games VALUES (1, 2, TO_DATE('20171105', 'YYYYMMDD'), 14, 20);

SELECT * FROM Teams;
SELECT * FROM Players;
SELECT * FROM PlayerToTeam;
SELECT * FROM Games;