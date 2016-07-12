#pragma once

#include <iostream>
#include <curses.h>
#include <pthread.h>
#include <string.h>

class chat_window
{
	public:
		chat_window();
		~chat_window();
		
		void win_refresh(WINDOW *win);
		WINDOW *create_newwin(int heigth, int width, int starty, int startx);
		void put_str_to_win(WINDOW* win, int starty, int startx, const std::string msg);
		void clear_win_line(WINDOW *win, int begin, int line);
		std::string get_input_msg(WINDOW* win);
		void create_header();
		void create_output();
		void create_friend_list();
		void create_input();

	//private:
	public:
		WINDOW *_header;
		WINDOW *_output;
		WINDOW *_friend_list;
		WINDOW *_input;
};
