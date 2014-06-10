from flask import render_template
from model import Person
from app import app

@app.route("/")
def IndexPage():
    user = 'mwn'
    persons = Person.query.all()
    return render_template('home.html', persons = persons)
#    return render_template('home.html')

