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

    void compile(std::string file, std::string binary)
    {
        std::ofstream afile((file+".cpp"), std::ios::out);

        if (afile.is_open())
        {
            afile << code << std::endl;
            afile.close();
        }

        std::cout << "Compile: ";
        system(std::string("g++ -o "+binary+" "+(file+".cpp")).c_str());
        std::cout << "OK.\n";
    }
} Compiler;

#endif
