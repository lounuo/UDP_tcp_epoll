#include "udp_server.h"

using namespace std;

//接收数据
void* recv_fun(void *ser)
{
	udp_server *_ser = (udp_server*)ser;

	while(1)
	{
		(*_ser).recv_data();
	}
}

//广播数据
void* broadcast_fun(void *ser)
{
	udp_server *_ser = (udp_server*)ser;

	while(1)
	{
		(*_ser).broadcast();
	}
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		Usage(argv[0]);
		exit(2);
	}

	int port = atoi(argv[2]);
	//cout<<"this is udp server"<<endl;
	udp_server ser(argv[1], port);
	//daemon(0, 0);
	ser.init();

	pthread_t th1, th2;
	pthread_create(&th1, NULL, recv_fun, (void*)&ser);
	pthread_create(&th2, NULL, broadcast_fun, (void*)&ser);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);

	return 0;
}
