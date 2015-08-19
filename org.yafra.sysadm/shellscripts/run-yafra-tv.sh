# run the SageTV server

docker run -p 80:80 -p 7818:7818 -p 8080:8080 -p 8270:8270/udp -p 31100:31100/udp -p 31099:31099 -p 42024:42024 -t -i --rm --name yafratv yafraorg/docker-yafratv /bin/bash
