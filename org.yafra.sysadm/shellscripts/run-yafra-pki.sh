# run the yaframongo 
docker run -d -p 27017:27017 --name yaframongo yafraorg/docker-yafradb:mongodb

# run the pki with mongo and dataonly links/volumes
#docker run -p 80:80  -p 8080:8080 -d --volumes-from yafraorg/docker-yafradb:dataonly --link yaframongo:db --name yapki yafraorg/docker-yapki
docker run -p 80:80 -p 8080:8080 -t -i --rm --volumes-from yafradata --link yaframongo:db --name yapki yafraorg/docker-yapki /bin/bash
