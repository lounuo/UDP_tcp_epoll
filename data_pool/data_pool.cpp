#include "data_pool.h"

//构造函数
data_pool::data_pool()
	:_buf(_capacity)
	,_capacity(256)
	,_put_index(0)
	,_get_index(0)
{
	//初始化信号量
	sem_init(&_blank, 0, _capacity);
	sem_init(&_data, 0, 0);
}

//向数据池中投递数据
void data_pool::data_put(std::string &in)
{
	sem_wait(&_blank);

	_buf[_put_index++] = in;
	_put_index %= _capacity;

	sem_post(&_data);
}

//从数据池中获取数据
void data_pool::data_get(std::string &out)
{
	sem_wait(&_data);

	out = _buf[_get_index];
	++_get_index;
	_get_index %= _capacity;

	sem_post(&_blank);
}

//析构函数
data_pool::~data_pool()
{
	sem_destroy(&_blank);
	sem_destroy(&_data);
}





