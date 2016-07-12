#pragma once

#include <iostream>
#include <vector>
#include <semaphore.h>

class data_pool
{
	public:
		data_pool();
		void data_put(std::string &in);
		void data_get(std::string &out);
		~data_pool();

	private:
		int _capacity;
		std::vector<std::string> _buf;
		sem_t _blank;
		sem_t _data;
		int _put_index;
		int _get_index;
};
