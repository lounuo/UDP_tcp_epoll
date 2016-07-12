#include "my_json.h"


myjson::myjson()
{}

//序列化
void myjson::Serialize(Json::Value &in_val, std::string &out_str)
{
#ifdef _DEBUG_
	Json::FastWriter write;
	out_str = write.write(in_val);
#else
	Json::StyledWriter write;
	out_str = write.write(in_val);
#endif
}

//反序列化
void myjson::Deserialize(Json::Value &out_val, std::string &in_str)
{
	Json::Reader read;
	read.parse(in_str, out_val, false);
}

myjson::~myjson()
{}

