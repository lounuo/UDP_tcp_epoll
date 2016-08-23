#pragma once

#include "data_pool.h"
#include "comm.h"
#include "udp_data.h"
#include <iostream>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
#include <stdlib.h>
//#include <pthread.h>
#include <unistd.h>
#include <map>

#define _BACKLOG_ 65532
#define _MAX_NUM_ 65532
#define _SIZE_ 10240

//typedef struct data_buf
//{
//	int _fd;
//	char _buf[_SIZE_];
//	char *_pbuf;
//}data_buf_t, *data_buf_p;


class udp_server
{
	public:
		void add_user(int fd, struct sockaddr_in &client);
		ssize_t send_data(int fd, struct sockaddr_in &client, socklen_t len, std::string& msg);
	
	public:
		udp_server(std::string ip = _IP_, int port = _PORT_, int fd = -1);
		int init();
		int recv_data(int fd);
		int del_user(int fd, std::string ip, std::string msg);
		void broadcast();
		~udp_server();
	private:
		std::string _ip;
		int _port;
		int _sock;
		std::map<int, struct sockaddr_in> _fds;
		//char _buf[_SIZE_];
		//char *_pbuf;

		std::map<std::string, struct sockaddr_in> _online_user;
		data_pool _data_buf;
};






