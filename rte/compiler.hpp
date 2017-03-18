// Der C Compiler, mit seinem Speicher für den C Code, der kompiliert wird
#ifndef COMPILER_HPP
#define COMPILER_HPP

#include <iostream>
#include <fstream>

class Compiler
{
private:
    std::string code = "";
public:
    bool COMPILE_STATIC;

    void addLine(std::string line)
    {
        code = code + "\t" + line + "\n";
    }

    void addLineT(std::string line)
    {
        code = code + line + "\n";
    }

    void addCode(std::string _code)
    {
        code = code + _code;
    }

    std::string getCode()
    {
        return code;
    }

    void compile(std::string file, std::string binary)
    {
        std::ofstream afile((file+".cpp"), std::ios::out);
        std::string _static = "";

        if (COMPILE_STATIC == true)
        {
            _static = "-static";
        }

        if (afile.is_open())
        {
            afile << code << std::endl;
            afile.close();
        }

        std::cout << "Compile: ";

        if (system(std::string("g++ -fpermissive -w "+_static+" -o "+binary+" "+(file+".cpp")).c_str()) == 0)
            std::cout << "OK.\n";
        else
            std::cout << "Compiling failed. Check this:\n - Is there a Syntax Error?\n - Is the GNU C++ Compiler (tested in V6.3.1) installed? (type in \"g++ -v\")\n\t- No? Check out this (Linux): https://gcc.gnu.org/wiki/InstallingGCC\n\t  or this (Windows): http://www.mingw.org/\n\t  or even this (Mac): https://www.mkyong.com/mac/how-to-install-gcc-compiler-on-mac-os-x/\n\n";
    }
} Compiler;

#endif
