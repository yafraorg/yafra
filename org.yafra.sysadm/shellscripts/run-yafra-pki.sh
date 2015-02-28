#docker run -d -p 8081:8081 --name yafrajava yafraorg/docker-yafrajava
#docker run -t -p 8081:8081 --name yafrajava -i yafraorg/docker-yafrajava /bin/bash

#assuming yaframysql runs already
#docker run -p 80:80 --rm --volumes-from yafraorg/docker-yafradb:dataonly --name yapki yafraorg/docker-yapki
docker run -p 80:80 -t -i --rm --volumes-from yafradata --name yapki yafraorg/docker-yapki /bin/bash
