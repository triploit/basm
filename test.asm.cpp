#include <iostream>
#include <stack>
#include <vector>

int _r_a = 0;
int _r_b = 0;
int _r_c = 0;
int _r_d = 0;
int _r_e = 0;
int _r_f = 0;
int _r_g = 0;
int _r_h = 0;

int *ax = &_r_a;
int *bx = &_r_b;
int *cx = &_r_c;
int *dx = &_r_d;
int *ex = &_r_e;
int *fx = &_r_f;
int *gx = &_r_g;
int *hx = &_r_h;

std::stack<int> stack;

int main();
int main()
{
	int __realINT_x;
	int *x = &__realINT_x;
	ax = &__realINT_x;
	*ax = 100;
	stack.push(*x);
	std::cout << stack.top() << std::endl;
	exit(0);
	return 0;
}

