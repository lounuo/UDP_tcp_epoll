#!/bin/bash

[ $# -ne 1 ] && echo "Usage: $0 start(-s) || stop(-p) || restart(-r) || status(-t)" && exit 1

ROOT_PATH=$(pwd)
CONF=$ROOT_PATH/conf/server.conf
PROGRAM=udp_server

IP=$( grep -E 'IP:' $CONF  | cut -c 4-)
PORT=$( grep -E 'PORT:' $CONF | cut -c 6-)

#查看进程运行状态
function status_fun()
{
	PID=$(pidof ${PROGRAM})
	if [ -z $PID ];then
		return 1
	else
		return 0
	fi
}

#启动进程
function start_fun()
{
	if status_fun;then
		echo "The programming is already start"
	else
		echo "programming start..."
		${ROOT_PATH}/${PROGRAM} $IP $PORT 
	fi
}

#停止进程
function stop_fun()
{
	if status_fun;then
		echo "programming stop..."
		kill $(pidof ${PROGRAM})
	else
		echo "programming is already stop..."
	fi
}

#重启进程
function restart_fun()
{
	stop_fun
	start_fun
}

case "$1" in
	"start"|"-s")
		start_fun
		;;
	"stop"|"-p")
		stop_fun
		;;
	"restart"|"-r")
		restart_fun
		;;
	"status"|"-t")
		if status_fun;then
			echo "The programming is already start, PID:$(pidof $PROGRAM)"
		else
			echo "The programming is stop..."
		fi
		;;
	*)
		echo "error command"
		exit 2
		;;
esac

