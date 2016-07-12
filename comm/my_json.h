#pragma once

#include <iostream>
#include <string>
#include "json/json.h"

class myjson
{
	public:
		myjson();
		void Serialize(Json::Value &in_val, std::string &out_str);//序列化
		void Deserialize(Json::Value &out_val, std::string &in_str);//反序列化
		~myjson();
	private:

};

