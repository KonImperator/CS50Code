import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

import datetime
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


# I thought we were doing fractional shares too...
def can_be_int(value):
  try:
     int(value)
     return True
  except:
    return False

def can_be_float(value):
  try:
     float(value)
     return True
  except:
    return False

def parse(value):
  if can_be_int(value):
      return int(value)
  elif can_be_float(value):
      return float(value)


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():

    # Getting logged in user's ID, current cash and stock info
    userId = session.get("user_id")
    cash = db.execute("SELECT cash FROM users WHERE id = ?", userId)[0]["cash"]
    stocks = db.execute("SELECT stock, shares FROM portfolio WHERE user_id = ?", userId)
    # Initializing assets as being equal to cash in order to add to it easily
    assets = cash

    # Looping through stocks and adding necessary info for the HTML template
    for stock in stocks:
        stock["price"] = lookup(stock["stock"])["price"]
        stock["total"] = lookup(stock["stock"])["price"] * stock["shares"]
        stock["name"] = lookup(stock["stock"])["name"]
        assets += stock["total"]

    return render_template("index.html", stocks=stocks, cash=cash, assets=assets, usd=usd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    # Getting id from current user's session
    userId = session.get("user_id")
    # Getting current cash from users table
    currentCash = db.execute("SELECT cash FROM users WHERE id = ?", userId)[0]["cash"]
    # Getting current time in UTC
    timeNow = datetime.datetime.now().replace(microsecond = 0)
    # Setting action for current route
    action = "Buy"

    if request.method == "POST":
        # Initiating variables
        stockTicker = (request.form.get("symbol")).upper().strip()
        result = lookup(stockTicker)
        shares = parse(request.form.get("shares"))
        # Checking for user input errors
        if not result or not shares or shares <= 0 or type(shares) == float:
            return apology("must provide valid input", 400)

        # Adding price later since result can be empty and cause a crash
        price = result["price"]
        spent = price * shares

        if currentCash < spent:
            return apology("insufficient funds for purchase", 400)


        # Checking length of returned value to know if the user owns the stock or not
        checkLength = db.execute("SELECT stock FROM portfolio WHERE stock = ? AND user_id = ?", stockTicker, userId)
        # If returned list length is 0, insert the stock as a new value and update cash
        if len(checkLength) == 0:
            db.execute("INSERT INTO portfolio (user_id, stock, shares) VALUES (?, ?, ?)", userId, stockTicker, shares)
            db.execute("UPDATE users set cash = ? WHERE id = ?", currentCash - spent, userId)
        # Else update the old value of shares and cash
        else:
            oldShares = db.execute("SELECT shares FROM portfolio WHERE stock = ? AND user_id = ?", stockTicker, userId)[0]["shares"]
            db.execute("UPDATE portfolio SET shares = ? WHERE stock = ? AND user_id = ?", shares + oldShares, stockTicker, userId)
            db.execute("UPDATE users set cash = ? WHERE id = ?", currentCash - spent, userId)

        # Inserting info in transactions table needed for the tx history
        db.execute("INSERT INTO transactions (user_id, type, stock, price, date, shares) VALUES (?, ?, ?, ?, ?, ?)", userId, action, stockTicker, usd(price), timeNow, shares)
        flash("Purchase successful", category='message')
        return redirect("/")
    """Buy shares of stock"""
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    userId = session.get("user_id")
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?", userId)
    """Show history of transactions"""
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        stockTicker = request.form.get("symbol")
        result = lookup(stockTicker)

        if not result:
            return apology("must enter valid stock ticker", 400)

        price = usd(result["price"])
        return render_template("quoted.html", result=result, price=price)
    else:
        return render_template("quote.html")
    # """Get stock quote."""

# User registration
@app.route("/register", methods=["GET", "POST"])
def register():
    username = request.form.get("username")
    checkUsername = db.execute("SELECT username FROM users WHERE username = ?", username)
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")

    # Checking for errors in user input
    if request.method == "POST":

        if not username and not password and not confirmation:
            return apology("must not leave blanks", 400)

        if not username:
            return apology("must provide username", 400)
        elif len(checkUsername) > 0:
            return apology("username already taken", 400)

        if not password:
            return apology("must provide password", 400)

        if not confirmation:
            return apology("must confirm password", 400)
        elif confirmation != password:
            return apology("passwords must match", 400)
    # If no errors, add user input to database after hashing password

        hash = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        id = db.execute("SELECT id FROM users WHERE username = ?", username)[0]
        session["user_id"] = id["id"]
        flash("Registration successful", category='message')
        return render_template("login.html")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
      # Getting id from current user's session
    userId = session.get("user_id")
    # Getting current cash from users table
    currentCash = db.execute("SELECT cash FROM users WHERE id = ?", userId)[0]["cash"]
    # Getting current time in UTC
    timeNow = datetime.datetime.now().replace(microsecond = 0)
    # Setting action for current route
    action = "Sell"

    tickers = db.execute("SELECT stock FROM portfolio WHERE user_id = ?", userId)
    if request.method == "POST":
        # Initiating variables
        stockTicker = (request.form.get("symbol"))
        result = lookup(stockTicker)
        shares = parse(request.form.get("shares"))

        # Checking for user input errors
        if not result or not shares or shares <= 0 or type(shares) == float:
            return apology("must provide valid input", 400)

        # Adding price later since result can be empty and cause a crash
        price = result["price"]
        spent = price * shares

        if currentCash < spent:
            return apology("insufficient funds for purchase", 400)

        # Inserting info in transactions table needed for the tx history
        db.execute("INSERT INTO transactions (user_id, type, stock, price, date, shares) VALUES (?, ?, ?, ?, ?, ?)", userId, action, stockTicker, usd(price), timeNow, shares)
        # Checking length of returned value to know if user owns the stock or not
        check = db.execute("SELECT stock, shares FROM portfolio WHERE stock = ? AND user_id = ?", stockTicker, userId)

        # If returned list length is 0, stock is not owned, return apology
        if len(check) == 0:
            return apology("must own stock in order to sell")
        # If attempting to sell more shares than owned, return apology
        if check[0]["shares"] < shares:
            return apology("unable to sell more shares than you own")

        oldShares = db.execute("SELECT shares FROM portfolio WHERE stock = ? AND user_id = ?", stockTicker, userId)[0]["shares"]
        newShares = round(oldShares - shares, 2)
        db.execute("UPDATE portfolio SET shares = ? WHERE stock = ? AND user_id = ?", newShares, stockTicker, userId)
        db.execute("UPDATE users set cash = ? WHERE id = ?", currentCash + spent, userId)
        if newShares == 0:
            db.execute("DELETE FROM portfolio WHERE stock = ? AND user_id = ?", stockTicker, userId)
    # """Sell shares of stock"""
        flash("Sale successful", category='message')
        return redirect("/")

    return render_template("sell.html", tickers=tickers)

@app.route("/reset", methods=["GET", "POST"])
@login_required
def reset():

    if request.method == "POST":

        userId = session.get("user_id")
        currentPassword = request.form.get("currentpassword")
        newPassword = request.form.get("newpassword")
        confirmation = request.form.get("confirmation")
        password = db.execute("SELECT hash FROM users WHERE id = ?", userId)[0]["hash"]

        if not currentPassword or not newPassword or not confirmation:
            return apology("must not leave blanks", 400)
        if currentPassword == newPassword:
            return apology("new password cannot be the same", 400)

        check = check_password_hash(password, currentPassword)
        if not check:
            return apology("wrong password", 400)
        if newPassword != confirmation:
            return apology("passwords don't match", 400)

        newPassword = generate_password_hash(request.form.get("newpassword"), method='pbkdf2:sha256', salt_length=8)
        db.execute("UPDATE users SET hash = ? WHERE id = ?", newPassword, userId)
        flash("Password changed successfully", category='message')
        return redirect("/")

    return render_template("reset.html")