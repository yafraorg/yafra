#assuming yaframysql runs already
#docker start yaframysql
#docker run -d -p 80:80 --name yafraphp --link yaframysql:db yafraorg/docker-yafraphp
docker run --rm -p 80:80 --name yafraphp --link yaframysql:db -i -t yafraorg/docker-yafraphp /bin/bash
