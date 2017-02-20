#include <iostream>
#include <stack>
#include <vector>

int ax = 0;
int bx = 0;
int cx = 0;
int dx = 0;
int ex = 0;
int fx = 0;
int gx = 0;
int hx = 0;

std::stack<int> stack;

int main();
int d_();
int e_();
int main()
{
main:
	stack.push(1);
	std::cout << stack.top() << std::endl;
	
	if (stack.size() > 0)
		stack.pop();

	fx = d_();
	goto main;

	exit(0);
	return 0;
}

int d_()
{
	stack.push(2);
	std::cout << stack.top() << std::endl;
	
	if (stack.size() > 0)
		stack.pop();

	fx = e_();
	stack.push(4);
	std::cout << stack.top() << std::endl;
	stack.push(fx);
	std::cout << stack.top() << std::endl;
	
	if (stack.size() > 0)
		stack.pop();

	return 0;
}

int e_()
{
	stack.push(3);
	std::cout << stack.top() << std::endl;
	
	if (stack.size() > 0)
		stack.pop();

	gx = 13;
	gx = 13;
	
	return gx;
	return 0;
}

