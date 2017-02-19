// Runtime Variablen, wie Zeilennumer der Datei oder der Stack oder anderes
#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include <iostream>
#include <stack>
#include <vector>

class Runtime
{
private:
    std::stack<int> b_stack;
    bool jump;

public:
    int LineNumber = 1;
    bool Compile = false;
    std::string CommandType = "";

    void setCommandType(std::string s)
    {
        CommandType = s;
    }

    std::string getCommandType()
    {
        return CommandType;
    }

    bool isJump()
    {
        return jump;
    }

    void setJump(bool b)
    {
        jump = b;
    }

    void pushStack(int i)
    {
        b_stack.push(i);
        // std::cout << "PUSH=" << i << " STACK_SIZE:" << b_stack.size() << std::endl;
    }

    void pushVectorStack(std::vector<int> v)
    {
        for (int i = (v.size()-1); i >= 0; i--)
        {
            b_stack.push(v[i]);
        }
    }

    void popStack()
    {
        if (b_stack.size() > 0)
            b_stack.pop();
    }

    int peekStack()
    {
        if (b_stack.size() == 0)
            return -999;

        return b_stack.top();
    }

    void printStack()
    {
        std::stack<int> s = b_stack;

        for (int i = (b_stack.size()-1); i >= 0; i--)
        {
            std::cout << "[" << i << "] " << b_stack.top() << std::endl;
            b_stack.pop();
        }

        b_stack = s;
    }
} Runtime;

#endif
