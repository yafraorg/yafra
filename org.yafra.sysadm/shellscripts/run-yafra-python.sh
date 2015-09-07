# run the yaframongo 
#./run-yafra-mongodb.sh

# run the pki with mongo and dataonly links/volumes
docker run -p 8081:8081  -p 8082:8082 -d --link yaframongo:db --name yafrapython yafraorg/docker-yafrapython
#docker run -p 8081:8081 -p 8082:8082 -t -i --rm --link yaframongo:db --name yafrapython yafraorg/docker-yafrapython /bin/bash
