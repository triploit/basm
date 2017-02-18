#ifndef PTC_HPP
#define PTC_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"

class Ptc : public Command
{
private:
    std::regex name = std::regex("((P|p)(T|t)(C|c))");

    std::regex r_int = std::regex("[0-9]*");
    std::smatch match;
public:
    void runFunction(std::vector<std::string> args)
    {
        if (!Runtime.Compile)
            std::cout << (char) Runtime.peekStack();

        Compiler.addLine("std::cout << (char) stack.top();");
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
