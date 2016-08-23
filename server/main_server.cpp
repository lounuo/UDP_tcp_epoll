#include "udp_server.h"

using namespace std;

////接收数据
//void* recv_fun(void *ser)
//{
//	udp_server *_ser = (udp_server*)ser;
//
//	while(1)
//	{
//		(*_ser).recv_data();
//	}
//}
//
////广播数据
//void* broadcast_fun(void *ser)
//{
//	udp_server *_ser = (udp_server*)ser;
//
//	while(1)
//	{
//		(*_ser).broadcast();
//	}
//}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		Usage(argv[0]);
		exit(2);
	}

	int port = atoi(argv[2]);
	udp_server listen_ser(argv[1], port);
	//daemon(0, 0);
	//udp_server* fds_ifo[_MAX_NUM_];
	//int maxfd = 0;

	int listen_sock = listen_ser.init();
	//fds_ifo[listen_sock] = listen_ser;
	//++maxfd;

	int epoll_fd = epoll_create(256);
	if(epoll_fd < 0)
	{
		print_log(strerror(errno), __FUNCTION__, __LINE__);
		exit(4);
	}

	struct epoll_event epoll_ev;
	epoll_ev.events = EPOLLIN;
	epoll_ev.data.fd = listen_sock;
	if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_sock, &epoll_ev) < 0)
	{
		print_log(strerror(errno), __FUNCTION__, __LINE__);
		exit(5);
	}

	struct epoll_event evs[_MAX_NUM_];
	int maxnum = _MAX_NUM_;
	int timeout = -1;
	int ret_ev = 0;

	while(1)
	{
		switch((ret_ev = epoll_wait(epoll_fd, evs, maxnum, timeout)))
		{
			case -1:
				print_log(strerror(errno), __FUNCTION__, __LINE__);
				break;
			case 0:
				std::cout<<"timeout..."<<std::endl;
				break;
			default:
				{
					for(int i = 0; i < ret_ev; ++i)
					{
						if((evs[i].data.fd == listen_sock) && (evs[i].events & EPOLLIN))
						{
							struct sockaddr_in client;
							socklen_t client_len = sizeof(client);
							int client_fd = accept(listen_sock, (struct sockaddr*)&client, &client_len);
							if(client_fd < 0)
							{
								print_log(strerror(errno), __FUNCTION__, __LINE__);
								continue;
							}
							char *client_ip = inet_ntoa(client.sin_addr);
							int client_port = ntohs(client.sin_port);
							std::cout<<"get a connect with client_ip: "<<client_ip<<" and client_port: "<<client_port<<std::endl;

							listen_ser.add_user(client_fd, client);
							//udp_server* client_ser = new udp_server(client_ip, client_port, client_fd);
							//it will only broadcast on itselves friend list!!!!

							epoll_ev.events = EPOLLIN;
							epoll_ev.data.fd = client_fd;
							if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &epoll_ev) < 0)
							{
								print_log(strerror(errno), __FUNCTION__, __LINE__);
								listen_ser.del_user(client_fd, client_ip, "quit");
								close(client_fd);
							}
							//fds_ifo[client_fd] = client_ser;
							//++maxfd;
						}
						else
						{
							if(evs[i].events & EPOLLIN)
							{
								int fd = evs[i].data.fd;
								int size = listen_ser.recv_data(fd);
								if(size > 0)
								{
									epoll_ev.data.fd = fd;
									epoll_ev.events = EPOLLOUT;
									while(epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, &epoll_ev) < 0)
										print_log(strerror(errno), __FUNCTION__, __LINE__);
								}
								else
								{
									if(epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL))
										print_log(strerror(errno), __FUNCTION__, __LINE__);
									close(fd);
									//delete fds_ifo[fd];
									//--maxfd;
								}
							}
							else if(evs[i].events & EPOLLOUT)
							{
								int fd = evs[i].data.fd;
								listen_ser.broadcast();
								//delete fds_ifo[fd];
								//--maxfd;
								epoll_ev.events = EPOLLIN;
								epoll_ev.data.fd = fd;
								while(epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, &epoll_ev) < 0)
									print_log(strerror(errno), __FUNCTION__, __LINE__);
							}
							else
							{
								/////////
							}
						}
					}
					break;
				}

		}
	}


	//pthread_t th1, th2;
	//pthread_create(&th1, NULL, recv_fun, (void*)&ser);
	//pthread_create(&th2, NULL, broadcast_fun, (void*)&ser);

	//pthread_join(th1, NULL);
	//pthread_join(th2, NULL);

	return 0;
}
