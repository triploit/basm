#ifndef GOTO_HPP
#define GOTO_HPP

#include <iostream>

class Goto
{
private:
    int index;
    std::string name;
    std::string scope;

public:
    int getIndex()
    {
        return index;
    }

    std::string getScope()
    {
        return scope;
    }

    void setScope(std::string s)
    {
        scope = s;
    }

    std::string getName()
    {
        return name;
    }

    void setName(std::string s)
    {
        name = s;
    }

    Goto(std::string _name, int _index, std::string _scope)
    {
        name = _name;
        index = _index;
        scope = _scope;
    }
};

#endif
