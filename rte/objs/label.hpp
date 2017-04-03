#ifndef LABEL_HPP
#define LABEL_HPP

#include <iostream>

class Label
{
private:
    int index;
    std::string name;
    int argc = 0;

public:
    int getIndex()
    {
        return index;
    }

    std::string getName()
    {
        return name;
    }

    void setName(std::string s)
    {
        name = s;
    }

    int getArgCount()
    {
        return argc;
    }

    Label(std::string _name, int _index, int _argc)
    {
        name = _name;
        index = _index;
        argc = _argc;
    }
};

#endif
