
# Project Title: Currencity
#### Video Demo: https://youtu.be/gSLRo04L0h4
#### Description:

This project is a comprehensive web application designed for currency conversion and historical exchange rate analysis. The application allows users to convert between different currencies and view historical exchange rates over specified periods. The project is built using Python, Flask, and SQLite, along with Bootstrap for front-end design.

### Project Structure:

1. **app.py**: This is the main application file that initializes the Flask app, sets up routes, and handles the main logic for currency conversion and retrieving historical exchange rates.

2. **database.db**: This SQLite database file stores user information, including login credentials and session data. It also contains the historical exchange rates for various currencies.

3. **init_db.py**: A script to initialize the database with necessary tables and seed it with initial data. This script sets up the schema for user data and historical rates.

4. **requirements.txt**: This file lists all the Python dependencies required to run the application. It includes Flask, SQLAlchemy, and other necessary libraries.

5. **instance/sessions.db**: This SQLite database file stores session information for logged-in users. It is used to manage user sessions securely.

### Static Files:

- **static/css**: Contains CSS files for styling the application, including Bootstrap, FontAwesome, and custom styles.
- **static/fonts**: Holds font files used by FontAwesome for icons.
- **static/images**: Contains various images used throughout the application, such as background images, slider images, team photos, and icons.
- **static/js**: JavaScript files for additional functionality, including jQuery and custom scripts.

### Templates:

- **templates/convert.html**: The template for the currency conversion page, allowing users to convert between different currencies.
- **templates/historical.html**: The template for displaying historical exchange rates over a specified period.
- **templates/index.html**: The home page of the application, providing an overview and navigation options.
- **templates/login.html**: The login page for user authentication.
- **templates/profile.html**: The user profile page, where users can view and edit their information.
- **templates/register.html**: The registration page for new users to create an account.

### Design Choices:

#### Database Design:
The project uses SQLite for simplicity and ease of use. The database schema includes tables for user information and historical exchange rates. This design ensures efficient data retrieval and storage.

#### Front-End Framework:
Bootstrap is used for the front-end design due to its responsiveness and ease of integration. The custom CSS and JavaScript files enhance the user experience with additional styling and functionality.

#### Currency Conversion Logic:
The main currency conversion logic is implemented in the `app.py` file, which interacts with an external API to fetch real-time exchange rates. The historical exchange rates are stored in the database and retrieved as needed for historical analysis.

#### Security:
User authentication is handled securely using Flask's built-in session management. Passwords are hashed before storage in the database to ensure user data protection.

### Future Improvements:

- **Enhanced User Interface**: Further improvement of the user interface for a more seamless and interactive experience.
- **Additional Features**: Adding features such as user preferences for default currencies, notifications for exchange rate changes, and more detailed historical data analysis.
- **Deployment**: Deploying the application on a cloud platform for broader accessibility and scalability.

