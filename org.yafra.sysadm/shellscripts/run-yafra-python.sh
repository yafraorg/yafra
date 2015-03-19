# run the yaframongo 
#./run-yafra-mongodb.sh

# run the pki with mongo and dataonly links/volumes
#docker run -p 80:80  -p 8080:8080 -d --link yaframongo:db --name yafrapython yafraorg/docker-yafrapython
docker run -p 80:80 -p 8080:8080 -t -i --rm --link yaframongo:db --name yafrapython yafraorg/docker-yafrapython /bin/bash
