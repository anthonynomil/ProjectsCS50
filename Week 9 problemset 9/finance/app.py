import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
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
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    transactions_db = db.execute(
        "SELECT symbol, SUM(shares) AS shares, price FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = int(cash_db[0]["cash"])

    return render_template("index.html", database=transactions_db, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    elif request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        if not symbol:
            return apology("Please enter a symbol")

        stock = lookup(symbol.upper())
        if stock == None:
            return apology("Symbol doesn't exist")

        if shares < 0:
            return apology("The share must be positive")

        transaction = shares * stock["price"]
        user_id = session["user_id"]
        user_cash_db = db.execute(
            "SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]

        if user_cash < transaction:
            return apology("Not enough currency")

        update_cash = user_cash - transaction
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   update_cash, user_id)

        date = datetime.now()
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)",
                   user_id, stock["symbol"], shares, stock["price"], date)

        flash("Stock bought")
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions_db = db.execute(
        "SELECT * from transactions WHERE user_id = ?", user_id)
    return render_template("history.html", transactions=transactions_db)


@app.route("/addcash", methods=["GET", "POST"])
@login_required
def addcash():
    """User can add money to their account"""
    if request.method == "GET":
        return render_template("addcash.html")

    elif request.method == "POST":
        cash = int(request.form.get("cash"))

        if not cash:
            return apology("Please enter a valid positive number")

        user_id = session["user_id"]
        user_cash_db = db.execute(
            "SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]

        update_cash = user_cash + cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   update_cash, user_id)

        return redirect("/")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

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
    # Redirect the user if he tries anything he shouldn't with get
    if request.method == "GET":
        return render_template("quote.html")

    # Get the symbol from the html
    elif request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Please insert a symbol")

        stock = lookup(symbol.upper())

        # Check if the symbol is valid
        if stock == None:
            return apology("Symbol is invalid")

        return render_template("quoted.html", name=stock["name"], price=stock["price"], symbol=stock["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """ Register User """

    # Send the user back to the register if he tries to register with get
    if request.method == "GET":
        return render_template("register.html")

    elif request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Check if the user entered a username
        if not username:
            return apology("Please enter a password", 400)

        # Check if the user entered a password
        if not password:
            return apology("Please enter a password", 400)

        # Check if the user entered the confirmation password
        if not confirmation:
            return apology("Please enter your confirmation password", 400)

        # Check if the password and the confirmation password matches
        if password != confirmation:
            return apology("Both passwords must match")

        # Create a hash for the password
        hash = generate_password_hash(password)

        # Add the username and the hashed password into the database
        # and if the username already exists return an apology
        try:
            user = db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        except:
            return apology("Username already exists")

        session["user_id"] = user

        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    if request.method == "GET":
        symbols_user = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", user_id)
        return render_template("sell.html", symbols=[row["symbol"] for row in symbols_user])

    elif request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        if not symbol:
            return apology("Please enter a symbol")

        stock = lookup(symbol.upper())
        if stock == None:
            return apology("Symbol doesn't exist")

        user_shares = db.execute(
            "SELECT shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, symbol)
        user_shares_total = user_shares[0]["shares"]

        if shares < 0:
            return apology("The share must be positive")

        if shares > user_shares_total:
            return apology("You don't have that many shares")

        transaction = shares * stock["price"]
        user_cash_db = db.execute(
            "SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]

        if user_cash < transaction:
            return apology("Not enough currency")

        update_cash = user_cash + transaction
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   update_cash, user_id)

        date = datetime.now()
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)",
                   user_id, stock["symbol"], -1 * shares, stock["price"], date)

        flash("Stock Sold")

        return redirect("/")
