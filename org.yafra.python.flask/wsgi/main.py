from flask import Flask
from flask.ext.sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+pymysql://yafraadmin:yafra@webdev/yafra'
app.config['SQLALCHEMY_ECHO'] = True
db = SQLAlchemy(app)

import viewPerson

if __name__ == "__main__":
    app.run()
    #port = int(os.environ.get('PORT', 5000))
    #app.run(host='0.0.0.0', port=port)


