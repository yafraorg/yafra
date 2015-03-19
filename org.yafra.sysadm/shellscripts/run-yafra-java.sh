#assuming yaframysql runs already
#docker start yaframysql
#docker run -d -p 8081:8081 --name yafrajava --link yaframysql:db yafraorg/docker-yafrajava
docker run --rm -P --name yafrajava --link yaframysql:db -i -t yafraorg/docker-yafrajava /bin/bash
