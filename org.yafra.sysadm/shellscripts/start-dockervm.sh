#!/bin/bash
export WORKDIR=/work/repos

docker-machine start default
docker-machine env
eval "$(docker-machine env default)"
docker images
docker ps
