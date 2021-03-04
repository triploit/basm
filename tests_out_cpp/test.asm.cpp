#include <iostream>
#include <stack>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

int _r_a = 0;
int _r_b = 0;
int _r_c = 0;
int _r_d = 0;
int _r_e = 0;
int _r_f = 0;
int _r_g = 0;
int _r_h = 0;
int _r_var_ax = 0;
int _r_var_bx = 0;
int _r_var_cx = 0;

int *ax = &_r_a;
int *bx = &_r_b;
int *cx = &_r_c;
int *dx = &_r_d;
int *ex = &_r_e;
int *fx = &_r_f;
int *gx = &_r_g;
int *hx = &_r_h;
int *var_ax = &_r_var_ax;
int *var_bx = &_r_var_bx;
int *var_cx = &_r_var_cx;

std::stack<int> stack;
std::vector<int> list_ax;
std::vector<int> list_bx;
std::vector<int> list_cx;
std::string _str_sys_tmp_ = "";

bool _sys_is_number_(const std::string& s) { std::string::const_iterator it = s.begin(); while (it != s.end() && std::isdigit(*it)) ++it; return !s.empty() && it == s.end(); }
int stack_to_array();
int array_to_stack();
int write_string();
int write_array();
int new_line();
int main();
int stack_to_array()
{
	int __realINT_len;
	int *len = &__realINT_len;
	*len = *hx;
ar:
	list_ax.push_back(0);
	*hx = *hx - 1;
	
	if (*hx > 0)
		goto ar;

	stack.push(*len);
	*hx = stack.top();
	stack.pop();
beg:
	*hx = *hx - 1;
	*gx = stack.top();
	list_ax[*hx] = *gx;
	stack.pop();
	
	if (*hx > 0)
		goto beg;

	
	return *gx;
	return 0;
}

int array_to_stack()
{
	*hx = list_ax.size();
	*fx = 0;
beg:
	*gx = list_ax[*fx];
	stack.push(*gx);
	*hx = *hx - 1;
	*fx = *fx + 1;
	
	if (*hx != 0)
		goto beg;

	
	return *gx;
	return 0;
}

int write_string()
{
beg:
	*hx = *hx - 1;
	std::cout << (char) stack.top();
	stack.pop();
	
	if (*hx > 0)
		goto beg;

	
	return *gx;
	return 0;
}

int write_array()
{
	*hx = list_ax.size();
	*ax = 0;
beg:
	*bx = list_ax[*ax];
	stack.push(*bx);
	std::cout << (char) stack.top();
	stack.pop();
	*ax = *ax + 1;
	*hx = *hx - 1;
	
	if (*hx > 0)
		goto beg;

	
	return *gx;
	return 0;
}

int new_line()
{
	stack.push(10);
	std::cout << (char) stack.top();
	stack.pop();
	
	return *gx;
	return 0;
}

int main()
{
	int __realINT_o_in;
	int *o_in = &__realINT_o_in;
	
	_str_sys_tmp_ = "";
		std::getline(std::cin, _str_sys_tmp_);
	if (_sys_is_number_(_str_sys_tmp_))
	{
		*hx = 0;
		*gx = std::stoi(_str_sys_tmp_);
	}
	else
	{
		for (int _int_sys_i_ = _str_sys_tmp_.size(); _int_sys_i_ >= 0; _int_sys_i_--)
			stack.push((int) _str_sys_tmp_[_int_sys_i_]);
		*hx = _str_sys_tmp_.size();

	}
	*o_in = *hx;
	*fx = stack_to_array();
	*fx = array_to_stack();
	stack.push(*o_in);
	*hx = stack.top();
	stack.pop();
	*fx = write_string();
	*fx = new_line();
	exit(0);
	return 0;
}

