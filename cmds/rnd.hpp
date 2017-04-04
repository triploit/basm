// "rand()%21+10"
#ifndef RND_HPP
#define RND_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"
#include "../rte/variables.hpp"

class Rnd : public Command
{
private:
    std::regex name = std::regex("^((R|r)(N|n)(D|d))");
    std::regex r_regs = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");

    std::regex r_int = std::regex("[0-9]*");
    std::smatch match;
public:
    void runFunction(std::vector<std::string> args)
    {

        if ((Variables.existsVariable(args[0]) || Registers.existsRegister(args[0])) && (Variables.existsVariable(args[1]) || Registers.existsRegister(args[1])))
            Compiler.addLine("srand(time(NULL)); stack.push(rand() % ("+args[1]+" + 1 - "+args[0]+") + "+args[0]+");");
        else if (Variables.existsVariable(args[0]) || Registers.existsRegister(args[0]))
            Compiler.addLine("srand(time(NULL)); stack.push(rand() % ("+args[1]+" + 1 - "+args[0]+") + "+args[0]+");");
        else if (Variables.existsVariable(args[1]) || Registers.existsRegister(args[1]))
            Compiler.addLine("srand(time(NULL)); stack.push(rand() % ("+args[1]+" + 1 - "+args[0]+") + "+args[0]+");");
        else
            Compiler.addLine("srand(time(NULL)); stack.push(rand() % ("+args[1]+" + 1 - "+args[0]+") + "+args[0]+");");
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
