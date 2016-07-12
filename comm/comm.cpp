#include "comm.h"

using namespace std;

//打印错误消息
void print_log(const char* msg, const char* fun, const int line)
{
	cout<<msg<<" : [ "<<fun<<" ] [ "<<line<<" ] "<<endl;
}

//提示格式
void Usage(char *argc)
{
	cout<<"Usage: "<<argc<<" [ip]  [port] "<<endl;
}
