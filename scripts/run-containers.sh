#!/bin/sh

IF_IP="10.1.1.1"
IF_NAME="br4"

if [ "$#" -lt 1 ]; then
	echo "usage: $0 hosts"
	exit 1
fi

docker rm $(docker ps -a -q)

docker daemon & 

docker build -t ubuntu_sshd ../

for HOSTNAME in "$@"
do
	CONTAINER=$(docker run -dit ubuntu_sshd /bin/bash)
	echo $CONTAINER

	./pipework.sh $IF_NAME $CONTAINER $HOSTNAME/24
done

ip addr add $IF_IP/24 dev $IF_NAME
