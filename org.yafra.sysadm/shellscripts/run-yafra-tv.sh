# run the SageTV server

docker run -d -P --net=host --name yafratv yafraorg/docker-yafratv

#docker run -p 80:80 -p 7818:7818 -p 8080:8080 -p 8270:8270/udp -p 31100:31100/udp -p 31099:31099 -p 42024:42024 --net=host -t -i --rm --name yafratv yafraorg/docker-yafratv /bin/bash
#docker run -P --net=host -t -i --rm --name yafratv yafraorg/docker-yafratv /bin/bash
#docker exec -it yafratv /bin/bash
