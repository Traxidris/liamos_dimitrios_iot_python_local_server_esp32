import time
from flask import Flask, render_template, request, url_for, redirect, session


app = Flask(__name__)
app.secret_key = "iotihu"
F1 = 0
led = 0


creds = {"username": "liamos", "password": "dimitris"}

""" @app.before_request
def before_request():
    if 'user' not in session and request.endpoint != 'login':
        return redirect(url_for('login'))
 """

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'GET':
        username = request.args.get('username')
        password = request.args.get('password')
        if (not username) and (not password):
            return render_template("login.html")
    elif request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

    if (username == creds['username']) and (password == creds['password']):
        session['user'] = username
        return redirect('/dashboard')  # url_for(app.dashboard))
    return redirect ('/login')


@app.route('/dashboard', methods=['GET'])
def dashboard():

    global F1
    F1 = request.args.get("f1", F1)
    return render_template("dashboard.html", f1=F1)

@app.route("/led")
def led_template():
    return render_template("led.html", led=led)

@app.route("/update_led/<int:value>", methods=["POST"])
def update_led(value):
    global led
    led = value
    return redirect(url_for("light"))


@app.route("/light", methods=['GET', 'POST'])
def light():
    if led == 1:
        return "1"
    else:
        return "0"




if __name__ == '__main__':
    app.run(host='0.0.0.0', port='4000')  #, debug=True)
