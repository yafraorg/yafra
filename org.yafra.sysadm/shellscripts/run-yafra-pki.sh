# run the yaframongo 
#./run-yafra-mongodb.sh

# run the pki with mongo and dataonly links/volumes
docker run -p 8081:8081  -p 8082:8082 -d --volumes-from yafradata --link yaframongo:db --name yapki yafraorg/docker-yapki
#docker run -p 8081:8081 -p 8082:8082 -t -i --rm --volumes-from yafradata --link yaframongo:db --name yapki yafraorg/docker-yapki /bin/bash
#docker exec -it yapki /bin/bash
