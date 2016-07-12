#!/bin/bash

ROOT_PATH=$(pwd)
CONF=$ROOT_PATH/conf/server.conf
PROGRAM=udp_client

IP=$( grep -E 'IP:' $CONF  | cut -c 4-)
PORT=$( grep -E 'PORT:' $CONF | cut -c 6-)

${ROOT_PATH}/${PROGRAM} $IP $PORT 

