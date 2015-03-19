#assuming yaframysql runs already
#docker start yaframysql
#docker run -d -p 8081:8081 --name yafranet --link yaframysql:db yafraorg/docker-yafranet
docker run --rm -P --name yafranet --link yaframysql:db -i -t yafraorg/docker-yafranet /bin/bash
