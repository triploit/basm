#ifndef INP_HPP
#define INP_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"

class Inp : public Command // get string
{
private:
    std::regex name = std::regex("^((I|i)(N|n)(P|p))");
    std::regex r_regs = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");

    std::regex r_int = std::regex("[0-9]*");
    std::smatch match;
public:
    void runFunction(std::vector<std::string> args)
    {
        Compiler.addLine("\n\t_str_sys_tmp_ = \"\";\n\t\tstd::getline(std::cin, _str_sys_tmp_);");
        Compiler.addLine("if (_sys_is_number_(_str_sys_tmp_))");
        Compiler.addLine("{");
        Compiler.addLine("\t*hx = 0;");
        Compiler.addLine("\t*gx = std::stoi(_str_sys_tmp_);");
        Compiler.addLine("}");
        Compiler.addLine("else");
        Compiler.addLine("{");
        Compiler.addLine("\tfor (int _int_sys_i_ = _str_sys_tmp_.size(); _int_sys_i_ >= 0; _int_sys_i_--)");
        Compiler.addLine("\t\tstack.push((int) _str_sys_tmp_[_int_sys_i_]);");
        Compiler.addLine("\t*hx = _str_sys_tmp_.size();\n");
        Compiler.addLine("}");
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
