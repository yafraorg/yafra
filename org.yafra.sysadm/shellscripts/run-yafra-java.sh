#docker run -d -p 8081:8081 --name yafrajava yafraorg/docker-yafrajava
#docker run -t -p 8081:8081 --name yafrajava -i yafraorg/docker-yafrajava /bin/bash
#assuming yaframysql runs already
docker run -P --name java --link yaframysql:yaframysql -i -t yafraorg/docker-yafrajava /bin/bash
