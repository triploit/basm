#ifndef FILE_HPP
#define FILE_HPP

#include <vector>
#include <iostream>

class File
{
private:
	std::string name;
	std::vector<std::string> inc_files;

public:
	std::string getName()
	{
		return name;
	}

	void addFile(std::string _name)
	{
		inc_files.push_back(_name);
	}

	bool existsFile(std::string _name)
	{
		for (int i = 0; i < inc_files.size(); i++)
		{
			if (inc_files[i] == _name)
				return true;
		}

		return false;
	}

	void listFiles()
	{
		std::cout << "FILE ========== " << name << std::endl;
		for (int i = 0; i < inc_files.size(); i++)
		{
			std::cout << "\t[" << i << "] " <<  inc_files[i] << std::endl;
		}
	}

	File(std::string _name)
	{
		name = _name;
	}
};

#endif
