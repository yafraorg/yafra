# run the yaframongo 
#./run-yafra-mongodb.sh

# run the pki with mongo and dataonly links/volumes
docker run -p 3000:3000 -d --link yaframongo:db --name yafranodejs yafraorg/docker-yafranodejs
#docker run -p 3000:3000 -t -i --rm --link yaframongo:db --name yafranodejs yafraorg/docker-yafranodejs /bin/bash
