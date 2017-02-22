#ifndef PTR_HPP
#define PTR_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"
#include "../rte/variables.hpp"

class Ptr : public Command
{
private:
    std::regex name = std::regex("((P|p)(T|t)(R|r))");
    std::regex r_int = std::regex("[0-9]*");
    std::regex r_registers = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");
    std::regex r_variable = std::regex("([0-9a-zA-Z_]*)");
    std::regex r_hex = std::regex("0x([0-9a-fA-F]*)");
    std::smatch match;

public:
    void runFunction(std::vector<std::string> args)
    {
        std::string var_reg = args[0];
        std::string pointer = args[1];

        if (std::regex_match(pointer, match, r_int) || std::regex_match(pointer, match, r_hex))
        {
            int ptr = std::stoi(pointer);
            std::cout << "MEGA_SUPER_VIOLENT_WARNING:\n\tPointer to Hex-/Int-Adresses in Memory is not fully\n\tsupported!" << std::endl;

            if (std::regex_match(var_reg, match, r_registers))
            {
                Compiler.addLine(var_reg + " = " + std::to_string(ptr) + ";");
            }
            else
            {
                if (Variables.existsVariable(var_reg))
                {
                    Compiler.addLine(var_reg + " = " + std::to_string(ptr) + ";");
                }
                else
                {
                    std::cout << "VARIABLE_DOESNT_EXIST: LINE " << Runtime.LineNumber << ": PTR: \"ptr " << args[0] << ", " << args[1] << ";\"\n";
                    exit(1);
                }
            }
        }
        else if (std::regex_match(pointer, match, r_registers))
        {
            // std::cout << "POINTER 2: " << args[0] << " -> " << args[1] << std::endl;
            std::string ptr;
            ptr = Registers.getRegister(pointer).getRealName();

            if (std::regex_match(var_reg, match, r_registers))
            {
                Compiler.addLine(var_reg + " = &" + ptr + ";");
            }
            else
            {
                if (Variables.existsVariable(var_reg))
                {
                    Compiler.addLine(var_reg + " = &" + ptr + ";");
                }
                else
                {
                    std::cout << "VARIABLE_DOESNT_EXIST: LINE " << Runtime.LineNumber << ": PTR: \"ptr " << args[0] << ", " << args[1] << ";\"\n";
                    exit(1);
                }
            }
        }
        else if (std::regex_match(pointer, match, r_variable))
        {
            // std::cout << "POINTER 3: " << args[0] << " -> " << args[1] << std::endl;
            std::string ptr;
            if (Variables.existsVariable(pointer))
                ptr = Variables.getVariable(pointer).getRealName();

            if (std::regex_match(var_reg, match, r_registers))
            {
                Compiler.addLine(var_reg + " = &" + ptr + ";");
            }
            else
            {
                if (Variables.existsVariable(var_reg))
                {
                    Compiler.addLine(var_reg + " = &" + ptr + ";");
                }
                else
                {
                    std::cout << "VARIABLE_DOESNT_EXIST: LINE " << Runtime.LineNumber << ": PTR: \"ptr " << args[0] << ", " << args[1] << ";\"\n";
                    exit(1);
                }
            }
        }
        else
        {
            std::cout << "FATAL_COMPILER_ERROR: LINE " << Runtime.LineNumber << ": PTR_ERROR: \"ptr " << args[0] << ", " << args[1] << ";\"\n";
            exit(1);
        }
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
