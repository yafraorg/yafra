#assuming yaframysql runs already
#docker start yaframysql
docker run -d -p 8083:8083 --name yafraphp --link yaframysql:db yafraorg/docker-yafraphp
#docker run --rm -p 8083:8083 --name yafraphp --link yaframysql:db -i -t yafraorg/docker-yafraphp /bin/bash
