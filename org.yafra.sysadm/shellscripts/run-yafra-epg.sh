# run the EPG XMLTV grabber 

# run the pki with mongo and dataonly links/volumes
docker run -t -i --rm -v /work:/opt/egp --entrypoint=/bin/bash --name yafraepg yafraorg/docker-yafraepg
#docker run -t -i --rm -v /work:/opt/egp --name yafraepg yafraorg/docker-yafraepg
