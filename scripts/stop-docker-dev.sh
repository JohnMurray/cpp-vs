#!/bin/bash

container_id=$(docker ps -f label=cpp-vs-dev -f status=running | tail -n1 | awk '{print $1}');
echo "Stopping container $container_id";
docker kill $container_id &>/dev/null;
