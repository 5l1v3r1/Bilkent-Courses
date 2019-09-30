CREATE TABLE customer (
  cid CHAR(12),
  name VARCHAR(50),
  bdate DATE,
  address VARCHAR(50),
  city VARCHAR(20),
  nationality VARCHAR(20),
  PRIMARY KEY (cid)
) ENGINE = InnoDB;

CREATE TABLE account (
  aid CHAR(8),
  branch VARCHAR(20),
  balance FLOAT,
  openDate DATE,
  PRIMARY KEY (aid)
) ENGINE = InnoDB;

CREATE TABLE owns (
  cid CHAR(12),
  aid CHAR(8),
  PRIMARY KEY (cid, aid),
  FOREIGN KEY (cid) REFERENCES customer(cid),
  FOREIGN KEY (aid) REFERENCES account(aid)
) ENGINE = InnoDB;

INSERT INTO customer
(cid, name, bdate, address, city, nationality) VALUES
  (?, ?, ?, ?, ?, ?);

INSERT INTO account
(aid, branch, balance, openDate) VALUES
(?, ?, ?, ?);

INSERT INTO owns
(cid, aid) VALUES
(?, ?);