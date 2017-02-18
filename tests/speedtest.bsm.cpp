#include <iostream>
#include <stack>
#include <vector>

int main()
{
	int ax = 0;
	int bx = 0;
	int cx = 0;
	int dx = 0;
	int ex = 0;
	int fx = 0;
	int gx = 0;
	int hx = 0;
	std::stack<int> stack;

	hx = 1000000;
	hx = 1000000;
main:
	ax = ax + 1;
	stack.push(ax);
	std::cout << stack.top() << std::endl;
	hx = hx - 1;
	
	if (hx > 0)
		goto main;

	exit(0);
	return 0;
}

