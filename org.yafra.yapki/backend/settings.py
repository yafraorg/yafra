# Let's just use the local mongod instance. Edit as needed.

# Please note that MONGO_HOST and MONGO_PORT could very well be left
# out as they already default to a bare bones local 'mongod' instance.
MONGO_HOST = os.environ.get('DB_PORT_27017_TCP_ADDR')
MONGO_PORT = 27017
MONGO_USERNAME = 'yafraadmin'
MONGO_PASSWORD = 'yafra'
MONGO_DBNAME = 'yapki'

DOMAIN = {'people': {}}