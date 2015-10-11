#!/bin/bash
export WORKDIR=/work/repos

docker-machine start default
docker-machine env default
eval "$(docker-machine env default)"
docker images
docker ps
