#include "udp_data.h"

//构造函数
udp_data::udp_data(std::string nickname, std::string school, std::string msg, std::string cmd)
	:_nickname(nickname)
	,_school(school)
	,_msg(msg)
	,_cmd(cmd)
{}

//进行序列化
void udp_data::val_to_str(std::string &out_str)
{
	Json::Value in_val;
	in_val["Nickname"] = _nickname;
	in_val["School"]   = _school;
	in_val["Msg"]      = _msg;
	in_val["Cmd"]      = _cmd;

	_myjson.Serialize(in_val, out_str);
}

//进行反序列化
void udp_data::str_to_val(std::string &in_str)
{
	Json::Value out_val;
	_myjson.Deserialize(out_val, in_str);
	
	_nickname = out_val["Nickname"].asString();
	_school = out_val["School"].asString();
	_msg = out_val["Msg"].asString();
	_cmd = out_val["Cmd"].asString();
}


std::string udp_data::get_nickname()
{
	return _nickname;
}

std::string udp_data::get_school()
{
	return _school;
}

std::string udp_data::get_msg()
{
	return _msg;
}

std::string udp_data::get_cmd()
{
	return _cmd;
}

void udp_data::print_val()
{
	std::cout<<"Nickname:"<<_nickname<<" School:"<<_school<<" Msg:"<<_msg<<" Cmd:"<<_cmd<<std::endl;
}

udp_data::~udp_data()
{}


//int main()
//{
//	udp_data ud("huahua", "XPU", "hello", "None");
//	std::string str;
//	ud.val_to_str(str);
//	std::cout<<"serialize: "<<str<<std::endl;
//
//	std::string _str = "{\"Nickname\":\"xiaobai\", \"School\":\"XTU\", \"Msg\":\"love you\", \"Cmd\":\"None\"}";
//	ud.str_to_val(_str);
//	ud.print_val();
//
//	return 0;
//}










