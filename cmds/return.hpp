#ifndef RETURN_HPP
#define RETURN_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"
#include "../rte/labels.hpp"

class Return : public Command
{
private:
    std::regex name = std::regex("^((R|r)(E|e)(T|t)(U|u)(R|r)(N|n))");
    std::regex r_regs = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");

    std::regex r_int = std::regex("[0-9]*");
    std::smatch match;
public:
    void runFunction(std::vector<std::string> args)
    {
        if (!Runtime.Compile)
        {
            int i = Labels.returnI();
            std::cout << "From "<< Labels.getI() <<" return to " << i << std::endl;

            if (!Runtime.Compile)
                Labels.setI(i);
        }

        Compiler.addLine("\n\treturn gx;");
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
