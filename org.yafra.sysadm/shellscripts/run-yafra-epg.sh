# run the EPG XMLTV grabber 

# run the pki with mongo and dataonly links/volumes
docker run -t -i --rm -v /work:/opt/epg --entrypoint=/bin/bash --name yafraepg yafraorg/docker-yafraepg
#docker run -t -i --rm -v /work:/opt/epg --name yafraepg yafraorg/docker-yafraepg
