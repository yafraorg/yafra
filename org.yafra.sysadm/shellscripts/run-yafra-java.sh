#assuming yaframysql runs already
#docker start yaframysql
#docker run -d -p 8080:8080 -p 4201:4201 --name yafrajava --link yaframysql:db yafraorg/docker-yafrajava
docker run --rm -p 8080:8080 -p 4201:4201 --name yafrajava --link yaframysql:db -i -t yafraorg/docker-yafrajava /bin/bash
