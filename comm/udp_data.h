#pragma once

#include <iostream>
#include <string>
#include "my_json.h"

class udp_data
{
	public:
		udp_data(std::string nickname = "", std::string school = "", std::string msg = "", std::string cmd = "");
		void val_to_str(std::string &out_str);
		void str_to_val(std::string &in_str);
		void print_val();
		std::string get_nickname();
		std::string get_school();
		std::string get_msg();
		std::string get_cmd();
		~udp_data();

	private:
		myjson _myjson;
		std::string _nickname;
		std::string _school;
		std::string _msg;
		std::string _cmd;
};
