#ifndef LABEL_HPP
#define LABEL_HPP

#include <iostream>

class Label
{
private:
    int index;
    std::string name;
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

    Label(std::string _name, int _index)
    {
        name = _name;
        index = _index;
    }
};

#endif
