#pragma once

#include "comm.h"
#include "udp_data.h"
#include "chat_window.h"
#include <iostream>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


class udp_client
{
	public:
		udp_client(std::string ip, int port);
		void init();

		ssize_t recv_data(std::string& msg);
		ssize_t send_data(std::string msg);

		~udp_client();
	private:
		std::string _ip;
		int _port;
		int _sock;
		//chat_window _win;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
};
