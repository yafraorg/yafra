#assuming yaframysql runs already
#docker start yaframysql
#docker run -d -p 5000:5000 -p 5001:5001 -p 5002:5002 --name yafrac --link yaframysql:db yafraorg/docker-yafrac
docker run --rm -p 5000:5000 -p 5001:5001 -p 5002:5002 --name yafrac --link yaframysql:db -i -t yafraorg/docker-yafrac /bin/bash
