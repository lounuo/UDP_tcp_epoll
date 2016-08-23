#include "udp_client.h"

using namespace std;

udp_client* cli_p;
char nickname[20];
char school[256];

void* header_fun(void *arg)//首部的格式
{
	//pthread_detach(pthread_self());
	chat_window *win = (chat_window *)arg;
	int index = 1;
	std::string msg = "Hello, this is my chat window";//实现跑马灯的效果

	while(1)
	{
		win->create_header();
		int max_y, max_x;
		getmaxyx(win->_header, max_y, max_x);

		int starty = max_y/2;
		index %= max_x;
		index = index<1?1:index;
		int startx = index;

		win->put_str_to_win(win->_header, starty, startx, msg);
		win->win_refresh(win->_header);
		usleep(100000);
		index++;
		win->clear_win_line(win->_header, starty, 1);
		if(index == max_x)
			win->clear_win_line(win->_header, starty+1, 1);
	}
	return NULL;
}

void* mid_win_fun(void *arg)//中间部分，包括输出消息窗口和好友列表窗口
{
	//pthread_detach(pthread_self());
	chat_window *win = (chat_window *)arg;
	std::string output_msg;
	win->create_output();
	win->create_friend_list();
	win->win_refresh(win->_output);
	win->win_refresh(win->_friend_list);

	vector<std::string> fd_list;

	int index_o = 1;
	int index_f = 1;
	while(1)
	{
		int maxo_y, maxo_x;
		getmaxyx(win->_output, maxo_y, maxo_x);
		index_o %= (maxo_y-1);
		index_o = index_o<1?1:index_o;
		int startoy = index_o;

		int maxf_y, maxf_x;
		getmaxyx(win->_friend_list, maxf_y, maxf_x);
		index_f %= (maxf_y-1);
		index_f = index_f<1?1:index_f;
		int startfy = index_f;

		//udp_data ud(NULL, NULL, NULL, NULL);!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		udp_data ud;	
		std::string in;
		if(cli_p->recv_data(in) == 0)//接收消息并将其反序列化
			continue;

		ud.str_to_val(in);

		output_msg = ud.get_nickname();
		//std::cout<<output_msg<<std::endl;
		output_msg += "-";
		output_msg += ud.get_school();
		//std::cout<<output_msg<<std::endl;

		//添加好友列表
		if(fd_list.size() == 0)
		{
			fd_list.push_back(output_msg);
			win->put_str_to_win(win->_friend_list, startfy, 2, output_msg);
			++index_f;
		}
		else
		{
			int i = 0;
			for(; i < fd_list.size(); ++i)
			{
				if(strcmp((fd_list[i]).c_str(), output_msg.c_str()) == 0)
					break;
			}
			if(i == fd_list.size())
			{
				fd_list.push_back(output_msg);
				win->put_str_to_win(win->_friend_list, startfy, 2, output_msg);
				++index_f;
			}
		}
		win->win_refresh(win->_friend_list);
		if(index_f == (maxf_y-1))
		{
			//win->clear_win_line(win->_friend_list, 1, maxf_y-2);
			//win->create_friend_list();
		}
		
		output_msg += " # ";
		output_msg += ud.get_msg();

		//输出消息
		win->put_str_to_win(win->_output, startoy, 3, output_msg);

		win->win_refresh(win->_output);
		usleep(100000);

		index_o++;
		if(index_o == (maxo_y-1))//如果消息大于屏幕则进行清屏
		{
			win->clear_win_line(win->_output, 1, maxo_y-2);
			win->create_output();
		}
	}
	return NULL;
}

void* input_fun(void *arg)//输入消息框
{
	//pthread_detach(pthread_self());
	chat_window *win = (chat_window *)arg;
	std::string prompt = "Enter Your Message #";
	std::string input_msg;
	std::string cmd;

	while(1)
	{
		win->create_input();
		win->put_str_to_win(win->_input, 1, 2, prompt);
		input_msg = win->get_input_msg(win->_input);

		if(strcmp(input_msg.c_str(), "quit") == 0 || strcmp(input_msg.c_str(), "q") == 0 || strcmp(input_msg.c_str(), "Q") == 0)
			cmd = "quit";
		else
			cmd = "None";
		
		udp_data ud(nickname, school, input_msg, cmd);
		std::string out;
		ud.val_to_str(out);//将收到的数据序列化之后发送出去
		cli_p->send_data(out);

		win->win_refresh(win->_input);
		usleep(100000);

		if(strcmp(cmd.c_str(), "quit") == 0)
		{
			win->~chat_window();
			exit(0);
		}

		win->clear_win_line(win->_input, 1, 1);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		Usage(argv[0]);
		exit(1);
	}

	int port = atoi(argv[2]);
	udp_client cli(argv[1], port);
	cli.init();
	cli_p = &cli;

	//cout<<"this is udp client"<<endl;
	memset(nickname, '\0', sizeof(nickname));
	memset(school, '\0', sizeof(school));

	cout<<"Please enter your nickname: ";
	//cin>>nickname;
	fgets(nickname, sizeof(nickname)-1, stdin);
	nickname[strlen(nickname)-1] = '\0';

	cout<<"Please enter your school: ";
	//cin>>school;
	fgets(school, sizeof(school)-1, stdin);
	school[strlen(school)-1] = '\0';

	chat_window win;
	pthread_t hth, mth, ith;

	pthread_create(&hth, NULL, header_fun, (void *)&win);
	pthread_create(&mth, NULL, mid_win_fun, (void *)&win);
	pthread_create(&ith, NULL, input_fun, (void *)&win);

	//sleep(10);
	pthread_join(hth, NULL);
	pthread_join(mth, NULL);
	pthread_join(ith, NULL);

	return 0;
}
