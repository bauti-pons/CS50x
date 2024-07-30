import sqlite3

DATABASE = 'database.db'  # Path to the main database file

# Function to recreate the 'users' table in the database
def recreate_users_table():
    # Connect to the SQLite database
    conn = sqlite3.connect(DATABASE)
    cursor = conn.cursor()

    # Drop the 'users' table if it already exists
    cursor.execute('DROP TABLE IF EXISTS users')

    # Create the 'users' table with specified columns
    cursor.execute('''
        CREATE TABLE users (
            id INTEGER PRIMARY KEY,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL,
            email TEXT UNIQUE NOT NULL,
            name TEXT NOT NULL,
            lastname TEXT NOT NULL,
            confirmed INTEGER DEFAULT 0
        )
    ''')

    conn.commit()  # Commit the changes to the database
    conn.close()  # Close the connection to the database

recreate_users_table()  # Call the function to recreate the 'users' table
