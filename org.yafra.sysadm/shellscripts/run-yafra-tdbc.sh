#assuming yaframysql runs already
#docker start yaframysql
#docker run -d -p 8081:8081 --name yafrac --link yaframysql:db yafraorg/docker-yafrac
docker run --rm -P --name yafrac --link yaframysql:db -i -t yafraorg/docker-yafrac /bin/bash
