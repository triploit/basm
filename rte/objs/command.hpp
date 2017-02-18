// Datentyp Command

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <regex>

class Command
{
private:
    std::regex name;
public:
    virtual std::regex getName() { return name; };
    virtual void runFunction(std::vector<std::string> args) {};
};

#endif
