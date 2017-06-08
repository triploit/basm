#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include <iostream>
#include <stack>
#include <vector>
#include <fstream>
#include "../tstring.hpp"
#include "objs/variable.hpp"

class Runtime
{
private:
    std::stack<int> b_stack;
	std::vector<std::string> names;
    std::vector<std::string> included_files;
    bool jump;

public:
    int LineNumber = 0;
    bool Compile = false;
    std::string CommandType = "";
    bool Verbose = false;
    std::string AktScope;

    std::string M_Code;
    std::string M__M;
    std::string M_Line;
    std::string M_Binary;
    std::ifstream M_File;

	bool nameDefined(std::string name)
	{
		for (std::string n : names)
		{
			if (n == name)
			{
				return true;
			}
		}

		return false;
	}

	void defineName(std::string n)
	{
		names.push_back(n);
	}

    void addFile(std::string name)
    {
        included_files.push_back(name);
    }

    bool existsFile(std::string name)
    {
        for (int i = 0; i < included_files.size(); i++)
        {
            if (included_files[i] == name)
                return true;
        }

        return false;
    }

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

	void clearDefinedVariableNames(std::vector<Variable> vars)
	{
		int i = 0;
		std::string s;

		for (Variable v : vars)
		{
			for (i = 0; i < names.size(); i++)
			{
				s = names[i];

				if (s == "var_ax" || s == "var_bx" || s == "var_cx")
					continue;

				if (v.getName() == s)
				{
					names.erase(names.begin()+i);

					if (Verbose)
						std::cout << "[RTE] Remove defined Variable-Word: " << s << std::endl;
				}
			}
		}
	}
} Runtime;

#endif
