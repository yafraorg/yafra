#docker run -d -p 8081:8081 --name yafrajava yafraorg/docker-yafrajava
#docker run -t -p 8081:8081 --name yafrajava -i yafraorg/docker-yafrajava /bin/bash

#assuming yaframysql runs already
docker run -d -p 3306:3306 --name yaframysql yafraorg/docker-yafradb:mysql
docker run -P --name java --link yaframysql:db -i -t yafraorg/docker-yafrajava /bin/bash
