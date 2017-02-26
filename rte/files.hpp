#ifndef FILES_HPP
#define FILES_HPP

#include <vector>
#include <iostream>
#include "objs/file.hpp"

class Files
{
private:
	std::vector<File> files;

public:
	std::string CURRENT_FILE;

	void addFile(File f)
	{
		files.push_back(f);
	}

	bool existsFile(std::string f)
	{
		for (int i = 0; i < files.size(); i++)
		{
			if (files[i].getName() == f)
				return true;
		}

		return false;
	}

	File getFile(std::string f)
	{
		for (int i = 0; i < files.size(); i++)
		{
			if (files[i].getName() == f)
				return files[i];
		}

		return File("[NE:EN]");
	}

	void addIncludeFile(std::string file, std::string inc_file)
	{
		for (int i = 0; i < files.size(); i++)
		{
			if (files[i].getName() == file)
				files[i].addFile(inc_file);
		}
	}

	void listIncludeFiles(std::string file)
	{
		for (int i = 0; i < files.size(); i++)
		{
			if (files[i].getName() == file)
			{
				files[i].listFiles();
			}
		}
	}

} Files;

#endif
