#assuming yaframysql runs already
#docker start yaframysql
#docker run -d --name yafranet --link yaframysql:db yafraorg/docker-yafranet
docker run --rm --name yafranet --link yaframysql:db -i -t yafraorg/docker-yafranet /bin/bash
