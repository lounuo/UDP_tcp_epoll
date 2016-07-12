#include "udp_server.h"

//构造函数
udp_server::udp_server(std::string ip, int port)
	:_ip(ip)
	,_port(port)
	,_sock(-1)
{}

//初始化服务器，创建socket并绑定端口号等信息
void udp_server::init()
{
	_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(_sock < 0)
	{
		print_log(strerror(errno), __FUNCTION__, __LINE__);
		exit(1);
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(_port);
	if(_ip == "any")
		local.sin_addr.s_addr = INADDR_ANY;
	else
		local.sin_addr.s_addr = inet_addr(_ip.c_str());

	if(bind(_sock, (struct sockaddr*)&local, sizeof(local)) < 0)
	{
		print_log(strerror(errno), __FUNCTION__, __LINE__);
		exit(2);
	}
}

//删除用户
void udp_server::del_user(std::string ip, std::string msg)
{
	udp_data ud;
	ud.str_to_val(msg);
	std::string client_cmd = ud.get_cmd();
	if(strcmp(client_cmd.c_str(), "quit") == 0)
	{
		std::map<std::string, struct sockaddr_in>::iterator it = _online_user.find(ip);
		if(it != _online_user.end())
		{
			_online_user.erase(it);
			std::cout<<"Delete user "<<ip<<" success..."<<std::endl;
		}
	}
}

//添加用户
void udp_server::add_user(struct sockaddr_in &client)
{
	std::string ip = inet_ntoa(client.sin_addr);
	std::map<std::string, struct sockaddr_in>::iterator it = _online_user.find(ip);
	if(it == _online_user.end())
	{
		std::pair<std::map<std::string, struct sockaddr_in>::iterator, bool> ret;
		ret = _online_user.insert(std::pair<std::string, struct sockaddr_in>(ip, client));
		if(ret.second == false)
			std::cout<<"Add user failed..."<<std::endl;
		else
			std::cout<<"Add client user "<<ip<<" success..."<<std::endl;
	}
	else
		return;
}

//接收远端发送的消息
ssize_t udp_server::recv_data()
{
	struct sockaddr_in client;
	socklen_t client_len = sizeof(client);
	char buf[_SIZE_];

	ssize_t _size = recvfrom(_sock, buf, sizeof(buf)-1, 0, (struct sockaddr*)&client, &client_len);
	if(_size < 0)
		print_log(strerror(errno), __FUNCTION__, __LINE__);
	else if(_size == 0)
	{
		char *client_ip = inet_ntoa(client.sin_addr);
		int client_port = ntohs(client.sin_port);
		std::cout<<"client->[ip]: "<<client_ip<<"  [port]: "<<client_port<<"  closed..."<<std::endl;
	}
	else
	{
		buf[_size] = '\0';
		std::string msg;
		msg = buf;
		_data_buf.data_put(msg);
		std::cout<<"client [ip]: "<<inet_ntoa(client.sin_addr)<<"# "<<msg<<std::endl;

		add_user(client);
		del_user(inet_ntoa(client.sin_addr), msg);
	}

	return _size;
}

//向远端发送消息
ssize_t udp_server::send_data(struct sockaddr_in &client, socklen_t len, std::string& msg)
{
	//struct sockaddr_in server;
	//server.sin_family = AF_INET;
	//server.sin_port = htons(_port);
	//server.sin_addr.s_addr = inet_addr(_ip.c_str());

	//socklen_t server_len = sizeof(server);
	ssize_t _size = sendto(_sock, msg.c_str(), msg.size(), 0, (struct sockaddr*)&client, len);
	if(_size < 0)
		print_log(strerror(errno), __FUNCTION__, __LINE__);

	return _size;
}

//以广播的形式
void udp_server::broadcast()
{
	std::string _msg;
	_data_buf.data_get(_msg);

	std::map<std::string, struct sockaddr_in>::iterator it = _online_user.begin();

	for(; it != _online_user.end(); ++it)
	{
		send_data(it->second, sizeof((it->second)), _msg);
		//std::cout<<"broadcast:"<<_msg<<std::endl;
	}
}

//析构函数
udp_server::~udp_server()
{
	if(_sock >= 0)
	{
		close(_sock);
	}
}














