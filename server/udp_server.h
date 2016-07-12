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
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <map>


class udp_server
{
	void add_user(struct sockaddr_in &client);
	ssize_t send_data(struct sockaddr_in &client, socklen_t len, std::string& msg);
	
	public:
		udp_server(std::string ip = _IP_, int port = _PORT_);
		void init();
		ssize_t recv_data();
		void del_user(std::string ip, std::string msg);
		void broadcast();
		~udp_server();
	private:
		std::string _ip;
		int _port;
		int _sock;

		std::map<std::string, struct sockaddr_in> _online_user;
		data_pool _data_buf;
};






