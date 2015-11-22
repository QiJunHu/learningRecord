// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <list>
#include <string>


class Screen
{
public:
	typedef std::string::size_type index;

	Screen();

	//constructor
	Screen(index h, index w, std::string cont) :height(h), width(w), contents(cont) {}

	//get char where cursor points to
	char get() const { return contents[cursor]; }
	//get char where column and row points to
	char get(index ht, index wd)  const;

	// get cursor
	index get_cursor()  const { return cursor; }

	// set content where cursor points to
	Screen& set(char);
	//set content where column and row points to
	Screen& set(index, index, char);

	//move cursor to where column and row points to
	Screen& move(index, index);

	//show contents
	const Screen& display(std::ostream& os) const;

private:
	std::string contents;
	index  cursor;
	index  height;
	index  width;



};


Screen::Screen()
{

}




char Screen::get(index ht, index wd) const
{
	index row = wd*width;
	return contents[row + ht];
}

Screen& Screen::set(char c)
{
	contents[cursor] = c;
	return *this;
}

Screen& Screen::set(index r, index col, char  c)
{
	index row = r *width;
	contents[row + col] = c;
	return *this;
}

Screen& Screen::move(index r, index c)
{
	index row = r*width;
	cursor = row + c;
	return *this;
}

const Screen& Screen::display(std::ostream& os) const
{
	os << contents;
	return *this;
}




int main(int argc, char* argv[])
{
	Screen myScreen(5,2,"helloworld");

	myScreen.move(4, 0).set('#').display(std::cout);

	
	
	return 0;
}