# run the yaframongo 
#./run-yafra-mongodb.sh

# run the pki with mongo and dataonly links/volumes
#docker run -p 8080:8080 -d --link yaframongo:db --name yafranodejs yafraorg/docker-yafranodejs
docker run -p 8080:8080 -t -i --rm --link yaframongo:db --name yafranodejs yafraorg/docker-yafranodejs /bin/bash
