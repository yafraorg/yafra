from flask import Flask, render_template
#from flask.ext.mail import Mail
from flask.ext.sqlalchemy import SQLAlchemy

__author__ = 'mwn'
#mail = Mail()
db = SQLAlchemy()
app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+pymysql://yafraadmin:yafra@webdev/yafra'
app.config['SQLALCHEMY_ECHO'] = True
db.init_app(app)

from app import viewPerson
'''
def create_app(config_name):
    app = Flask(__name__)
    app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+pymysql://yafraadmin:yafra@webdev/yafra'
    app.config['SQLALCHEMY_ECHO'] = True
    #app.config.from_object(config[config_name])
    #config[config_name].init_app(app)

    #bootstrap.init_app(app)
    #mail.init_app(app)
    #moment.init_app(app)
    db.init_app(app)

    # attach routes and custom error pages here

    return app
'''
