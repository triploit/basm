#ifndef INP_HPP
#define INP_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"

class Inp : public Command
{
private:
    std::regex name = std::regex("^((I|i)(N|n)(P|p))");
    std::regex r_regs = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");

    std::regex r_int = std::regex("[0-9]*");
    std::smatch match;
public:
    void runFunction(std::vector<std::string> args)
    {
        Compiler.addLine("\n\t_str_sys_tmp_ = \"\";\n\tstd::getline(std::cin, _str_sys_tmp_);");
        Compiler.addLine("for (int _int_sys_i_ = _str_sys_tmp_.size(); _int_sys_i_ >= 0; _int_sys_i_--)");
        Compiler.addLine("\tstack.push((int) _str_sys_tmp_[_int_sys_i_]);");
        Compiler.addLine("*hx = _str_sys_tmp_.size();\n");
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
