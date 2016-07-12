#include "chat_window.h"

//构造函数
chat_window::chat_window()
{
	//初始化窗口
	initscr();
}

//析构函数
chat_window::~chat_window()
{
	//销毁窗口释放资源
	delwin(_header);
	delwin(_friend_list);
	delwin(_output);
	delwin(_input);
	endwin();
}

//刷新窗口
void chat_window::win_refresh(WINDOW *win)
{
	wrefresh(win);
}

//创建新的窗口
WINDOW* chat_window::create_newwin(int heigth, int width, int starty, int startx)
{
	WINDOW *local_win = newwin(heigth, width, starty, startx);
	box(local_win, 0, 0);
	return local_win;
}

//向窗口中投递数据
void chat_window::put_str_to_win(WINDOW* win, int starty, int startx, const std::string msg)
{
	mvwaddstr(win, starty, startx, msg.c_str());
}

//从窗口中获取数据
std::string chat_window::get_input_msg(WINDOW* win)
{
	char msg[1024];
	memset(msg, '\0', sizeof(msg));
	wgetnstr(win, msg, 1024);
	return msg;
}

//清除窗口中的指定行
void chat_window::clear_win_line(WINDOW *win, int begin, int line)
{
	while(line-- > 0)
	{
		wmove(win, begin++, 0);
		wclrtoeol(win);
	}
}

//创建首部窗口
void chat_window::create_header()
{
	int starty = 0;
	int startx = 0;
	int heigth = LINES/5;
	int width = 0;
	_header = create_newwin(heigth, width, starty, startx);

}

//创建输出消息窗口
void chat_window::create_output()
{
	int starty = LINES/5;
	int startx = 0;
	int heigth = (LINES*3)/5;
	int width = (COLS*3)/4;
	_output = create_newwin(heigth, width, starty, startx);
}

//创建好友列表窗口
void chat_window::create_friend_list()
{
	int starty = LINES/5;
	int startx = (COLS*3)/4;
	int heigth = (LINES*3)/5;
	int width = COLS/4;
	_friend_list = create_newwin(heigth, width, starty, startx);
}

//创建输入消息窗口
void chat_window::create_input()
{
	int starty = (LINES*4)/5;
	int startx = 0;
	int heigth = LINES/5;
	int width = 0;
	_input = create_newwin(heigth, width, starty, startx);
}

