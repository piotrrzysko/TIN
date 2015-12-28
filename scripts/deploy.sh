#!/bin/sh

USER="root"
PASSWORD="screencast"
REMOTE_DIR="/home/advert-cast"
LOCAL_DIR=$1

if [ "$#" -lt 2 ]; then
	echo "usage: $0 local_dir hosts"
	exit 1
fi

make clean -C ../
make -C ../

shift
for HOSTNAME in "$@"
do
	echo Deploying to host "$HOSTNAME"...

	sshpass -p "$PASSWORD" ssh -o StrictHostKeychecking=no "$USER"@"$HOSTNAME" -t -t "rm -r $REMOTE_DIR & mkdir -p $REMOTE_DIR"

	sshpass -p "$PASSWORD" scp -r $LOCAL_DIR "$USER"@"$HOSTNAME":"$REMOTE_DIR"
done

exit 0
