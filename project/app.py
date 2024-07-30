from flask import Flask, render_template, request, redirect, url_for, flash, session
from flask_login import LoginManager, UserMixin, login_user, login_required, logout_user, current_user
from werkzeug.security import generate_password_hash, check_password_hash
from werkzeug.utils import secure_filename
from datetime import datetime
from flask_sqlalchemy import SQLAlchemy
from flask_session import Session
import requests
import logging
import sqlite3
import os
import re

# Initialize the Flask application
app = Flask(__name__)

# Configure the application
app.config['SECRET_KEY'] = 'your_secret_key'  # Secret key for session management
app.config['SESSION_TYPE'] = 'sqlalchemy'  # Use SQLAlchemy for session management
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///sessions.db'  # Database URI for SQLAlchemy
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False  # Disable modification tracking
app.config['UPLOAD_FOLDER'] = 'static/uploads'  # Folder for file uploads
app.config['MAX_CONTENT_LENGTH'] = 16 * 1024 * 1024  # Maximum file size for uploads (16MB)
ALLOWED_EXTENSIONS = {'png', 'jpg', 'jpeg', 'gif'}  # Allowed file extensions for uploads
API_KEY = '84cea8e21e6d17abe17f3360'   # API key for external service
DATABASE = 'database.db'  # Path to the main database file

# Configure logging
logging.basicConfig(level=logging.DEBUG)

# Initialize SQLAlchemy
db = SQLAlchemy(app)

# Configure Flask-Session to use the existing SQLAlchemy instance
app.config['SESSION_SQLALCHEMY'] = db
Session(app)

# Helper function to check if a file is allowed based on its extension
def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

# Function to initialize the database and create tables if they do not exist
def init_db():

    # Connect to the SQLite database
    conn = sqlite3.connect(DATABASE)
    cursor = conn.cursor()

    # Create the 'users' table with specified columns
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL,
            email TEXT UNIQUE NOT NULL,
            name TEXT NOT NULL,
            lastname TEXT NOT NULL,
            confirmed INTEGER DEFAULT 0,
            profile_picture TEXT
        )
    ''')

    # Attempt to add profile_picture column if it does not exist
    try:
        cursor.execute('ALTER TABLE users ADD COLUMN profile_picture TEXT')
    except sqlite3.OperationalError:
        pass  # Column already exists, do nothing

    conn.commit()  # Commit the changes to the database
    conn.close()  # Close the connection to the database

init_db()  # Initialize the database

# Flask-Login configuration
login_manager = LoginManager()
login_manager.init_app(app)
login_manager.login_view = 'login'  # Redirect here if user is not logged in

# User model for Flask-Login
class User(UserMixin):
    def __init__(self, id, username, password, email, name, lastname, confirmed, profile_picture=None):
        self.id = id
        self.username = username
        self.password = password
        self.email = email
        self.name = name
        self.lastname = lastname
        self.confirmed = confirmed
        self.profile_picture = profile_picture

    def get_id(self):
        return self.id

# User loader callback for Flask-Login
@login_manager.user_loader
def load_user(user_id):
    conn = sqlite3.connect(DATABASE)
    cursor = conn.cursor()
    cursor.execute('SELECT * FROM users WHERE id = ?', (user_id,))
    user = cursor.fetchone()
    conn.close()
    if user:
        return User(*user)
    return None

# Function to validate email format
def is_valid_email(email):
    return re.match(r"[^@]+@[^@]+\.[^@]+", email)

# Home route
@app.route('/')
def index():
    return render_template('index.html')

# Register route
@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        confirm_password = request.form['confirm_password']
        email = request.form['email']
        name = request.form['name']
        lastname = request.form['lastname']

        # Validate form data
        if not all([username, password, confirm_password, email, name, lastname]):
            flash('All fields are required.', 'danger')
            return render_template('register.html')

        if len(password) < 6:
            flash('Password must be at least 6 characters long.', 'danger')
            return render_template('register.html')

        if password != confirm_password:
            flash('Passwords do not match.', 'danger')
            return render_template('register.html')

        if not is_valid_email(email):
            flash('Invalid email address.', 'danger')
            return render_template('register.html')

        # Check for existing users
        conn = sqlite3.connect(DATABASE)
        cursor = conn.cursor()

        cursor.execute('SELECT * FROM users WHERE username = ?', (username,))
        if cursor.fetchone():
            flash('Username already chosen. Please choose another one.', 'danger')
            conn.close()
            return render_template('register.html')

        cursor.execute('SELECT * FROM users WHERE email = ?', (email,))
        if cursor.fetchone():
            flash('An account with this email already exists.', 'danger')
            conn.close()
            return render_template('register.html')

        # Hash password and insert new user
        hashed_password = generate_password_hash(password)
        cursor.execute('INSERT INTO users (username, password, email, name, lastname) VALUES (?, ?, ?, ?, ?)',
                       (username, hashed_password, email, name, lastname))
        conn.commit()
        conn.close()

        flash('You were successfully registered', 'success')
        return redirect(url_for('login'))

    return render_template('register.html')

# Login route
@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        login_credential = request.form.get('login_credential')
        password = request.form.get('password')

        if not login_credential or not password:
            flash('Username/Email and password are required.', 'danger')
            return render_template('login.html')

        conn = sqlite3.connect(DATABASE)
        cursor = conn.cursor()
        cursor.execute('SELECT * FROM users WHERE username = ? OR email = ?', (login_credential, login_credential))
        user = cursor.fetchone()
        conn.close()

        if not user:
            flash('Username or email does not exist.', 'danger')
            return render_template('login.html')

        if not check_password_hash(user[2], password):
            flash('Incorrect password.', 'danger')
            return render_template('login.html')

        login_user(User(*user))
        session['user_id'] = user[0]
        flash('Logged in successfully.', 'success')
        return redirect(url_for('index'))

    return render_template('login.html')

# Logout route
@app.route('/logout', methods=['POST'])
@login_required  # User must be logged in to access this route
def logout():
    logging.debug("Logging out current user")  # Log the attempt to logout
    logout_user()  # Logout the user via Flask-Login
    session.clear()  # Clear all data from the session
    response = redirect(url_for('login'))
    response.set_cookie('session', '', expires=0)  # Force the session cookie to be deleted
    flash('You were logged out successfully.')  # Provide user feedback

    return render_template('index.html') # Redirect to the home page

# Currency conversion route
@app.route('/convert', methods=['GET', 'POST'])
@login_required  # User must be logged in to access this route
def convert():
    error = None
    conversion_result = None
    currencies = {}
    base_currency = ""
    target_currency = ""
    amount = ""

    # Fetch supported currency codes from the API
    try:
        currency_response = requests.get(f'https://v6.exchangerate-api.com/v6/{API_KEY}/codes')
        currency_data = currency_response.json()
        if currency_data['result'] == 'success':
            currencies = {item[0]: item[1] for item in currency_data['supported_codes']}
        else:
            error = "Failed to load currency codes."
    except requests.RequestException as e:
        error = str(e)

    if request.method == 'POST':
        # Get form data
        base_currency = request.form.get('base_currency', '').upper()
        target_currency = request.form.get('target_currency', '').upper()
        amount = request.form.get('amount', '0')

        # Validate amount input
        if amount.isdigit() or amount.replace('.', '', 1).isdigit():
            amount = float(amount)
            try:
                # Fetch conversion result from the API
                response = requests.get(f'https://v6.exchangerate-api.com/v6/{API_KEY}/pair/{base_currency}/{target_currency}/{amount}')
                data = response.json()
                logging.debug(data)

                if data['result'] == 'success':
                    conversion_result = data['conversion_result']
                    logging.debug(f"Conversion result: {conversion_result}")
                else:
                    error = "There was an error with the currency conversion."
            except requests.RequestException as e:
                error = str(e)
        else:
            error = "Please enter a valid amount."

    return render_template('convert.html', error=error, conversion_result=conversion_result,
                           currencies=currencies, base_currency=base_currency, target_currency=target_currency, amount=amount)

# Helper function to validate date format
def is_valid_date(date_str):
    try:
        datetime.strptime(date_str, '%Y-%m-%d')
        return True
    except ValueError:
        return False

# Historical exchange rates route
@app.route('/historical', methods=['GET', 'POST'])
@login_required  # User must be logged in to access this route
def historical():
    currencies = {}
    try:
         # Fetch supported currency codes from the API
        currency_response = requests.get(f'https://v6.exchangerate-api.com/v6/{API_KEY}/codes')
        currency_data = currency_response.json()
        if (currency_data['result'] == 'success'):
            currencies = {item[0]: item[1] for item in currency_data['supported_codes']}
        else:
            flash('Failed to load currency codes.', 'error')
    except requests.RequestException as e:
        flash(str(e), 'error')

    error = None
    if request.method == 'POST':
        from_currency = request.form['from_currency']
        to_currency = request.form['to_currency']
        date_str = request.form['date']

        # Validate date input
        if not is_valid_date(date_str):
            error = 'Invalid date format. Please use YYYY-MM-DD.'
        else:
            try:
                date = datetime.strptime(date_str, '%Y-%m-%d')
                rate = get_historical_rate(from_currency, to_currency, date_str)
                if rate is None:
                    flash('Failed to retrieve historical rate. Please check the input values and try again.', 'error')
            except ValueError:
                error = 'Invalid date format. Please use YYYY-MM-DD.'

        if error:
            return render_template('historical.html', error=error, currencies=currencies)

        return render_template('historical.html', rate=rate, from_currency=from_currency, to_currency=to_currency, date=date_str, currencies=currencies)

    return render_template('historical.html', currencies=currencies)

# Function to get historical exchange rates
def get_historical_rate(from_currency, to_currency, date_str):
    api_key = API_KEY
    date_obj = datetime.strptime(date_str, '%Y-%m-%d')
    year = date_obj.year
    month = date_obj.month
    day = date_obj.day

    url = f"https://v6.exchangerate-api.com/v6/{api_key}/history/{from_currency}/{year}/{month}/{day}"
    response = requests.get(url)

    if response.status_code == 403:
        return {'error': 'Access denied. Please check your API key and subscription plan.'}
    elif response.status_code != 200:
        return {'error': f"Failed to fetch data with status code {response.status_code}"}

    data = response.json()
    if data['result'] == 'success':
        return data['conversion_rates']
    else:
        return {'error': 'Failed to fetch data'}

# Profile route
@app.route('/profile', methods=['GET', 'POST'])
@login_required  # User must be logged in to access this route
def profile():
    if request.method == 'POST':
        username = request.form['username']
        email = request.form['email']
        name = request.form['name']
        lastname = request.form['lastname']
        profile_picture = current_user.profile_picture  # Default to existing picture

        if 'profile_picture' in request.files:
            file = request.files['profile_picture']
            if file and allowed_file(file.filename):
                filename = secure_filename(file.filename)
                filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
                os.makedirs(app.config['UPLOAD_FOLDER'], exist_ok=True)
                file.save(filepath)
                profile_picture = os.path.join('uploads', filename)  # Store a relative path

        new_password = request.form.get('new_password')
        confirm_password = request.form.get('confirm_password')

        has_error = False
        if new_password and confirm_password:
            if new_password != confirm_password:
                flash('Passwords do not match!', 'danger')
                has_error = True
            elif len(new_password) < 6:
                flash('Password must be at least 6 characters long', 'danger')
                has_error = True
            else:
                # Update the user's password
                current_user.password = generate_password_hash(new_password, method='pbkdf2:sha256')

        if not has_error:
            # Update user profile in the database and session
            try:
                conn = sqlite3.connect(DATABASE)
                cursor = conn.cursor()
                cursor.execute('UPDATE users SET username=?, email=?, name=?, lastname=?, profile_picture=?, password=? WHERE id=?',
                               (username, email, name, lastname, profile_picture, current_user.password, current_user.id))
                conn.commit()
                current_user.profile_picture = profile_picture  # Update current user session
                flash('Your profile has been updated!', 'success')
            except Exception as e:
                flash(str(e), 'danger')
                conn.rollback()
            finally:
                conn.close()

    return render_template('profile.html', user=current_user)

# Entry point for running the application
if __name__ == '__main__':
    app.run(debug=True)
