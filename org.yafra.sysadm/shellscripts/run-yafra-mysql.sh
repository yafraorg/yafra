docker run -d -p 3306:3306 --name yaframysql --volumes-from yafradata yafraorg/docker-yafradb:mysql
#docker run --rm -t -p 3306:3306 --name yaframysql --volumes-from yafradata -i yafraorg/docker-yafradb:mysql /bin/bash
