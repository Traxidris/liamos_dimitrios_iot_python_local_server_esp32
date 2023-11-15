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
    elif led == 0:
        return "0"