#include "udp_client.h"

//构造函数
udp_client::udp_client(std::string ip, int port)
	:_ip(ip)
	,_port(port)
	,_sock(-1)
{}

//初始化客户端，创建socket
void udp_client::init()
{
	_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(_sock < 0)
	{
		print_log(strerror(errno), __FUNCTION__, __LINE__);
		exit(1);
	}

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(_port);
	server.sin_addr.s_addr = inet_addr(_ip.c_str());

	if(connect(_sock, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		print_log(strerror(errno), __FUNCTION__, __LINE__);
		exit(2);
	}
}

//从服务器接收数据
ssize_t udp_client::recv_data(std::string& msg)
{
	struct sockaddr_in server;
	socklen_t server_len = sizeof(server);
	char buf[_SIZE_];

	ssize_t _size = recvfrom(_sock, buf, sizeof(buf)-1, 0, (struct sockaddr*)&server, &server_len);
	//std::cout<<"client recv:"<<_size<<std::endl;
	if(_size < 0)
		print_log(strerror(errno), __FUNCTION__, __LINE__);
	else if(_size == 0)
	{
		char *server_ip = inet_ntoa(server.sin_addr);
		int server_port = ntohs(server.sin_port);
		//std::cout<<"server->[ip]: "<<server_ip<<"  [port]: "<<server_port<<"  closed..."<<std::endl;
	}
	else
	{
		buf[_size] = '\0';
		msg = buf;
	}

	return _size;
}

//向服务器发送消息
ssize_t udp_client::send_data(std::string msg)
{
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(_port);
	server.sin_addr.s_addr = inet_addr(_ip.c_str());

	socklen_t server_len = sizeof(server);
	ssize_t _size = sendto(_sock, msg.c_str(), msg.size(), 0, (struct sockaddr*)&server, server_len);
	if(_size < 0)
		print_log(strerror(errno), __FUNCTION__, __LINE__);

	return _size;
}

//析构函数
udp_client::~udp_client()
{
	if(_sock >= 0)
	{
		close(_sock);
	}
}











