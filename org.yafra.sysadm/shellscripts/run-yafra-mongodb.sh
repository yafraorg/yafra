docker run -d -p 27017:27017 --name yaframongo --volumes-from yafradata yafraorg/docker-yafradb:mongodb
#docker run --rm -t -p 27017:27017 --name yaframongo --volumes-from yafradata -i yafraorg/docker-yafradb:mongodb /bin/bash
