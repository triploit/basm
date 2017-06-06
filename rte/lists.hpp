#ifndef LISTS_HPP
#define LISTS_HPP

#include <iostream>
#include <vector>
#include "objs/list.hpp"
#include "variables.hpp"
#include "registers.hpp"

class Lists
{
private:
	std::vector<List> b_lists;

public:
	void addList(List l)
	{
		if (Runtime.nameDefined(l.getName()))
		{
			std::cout << "ERROR: LINE " << Runtime.LineNumber << ": LIST_CREATE: NAME_ALREADY_DEFINED: Name is already defined: " << l.getName() << std::endl;
			exit(1);
		}

		b_lists.push_back(l);
		Runtime.defineName(l.getName());
	}

	void clearAll()
	{
		for (int i = 0; i < b_lists.size(); i++)
		{
			if (b_lists[i].getName() != "list_ax" &&
				b_lists[i].getName() != "list_bx" &&
				b_lists[i].getName() != "list_cx")
			{
				if (Runtime.Verbose)
					std::cout << "[RTE] Erase List: " << b_lists[i].getName() << std::endl;
				b_lists.erase(b_lists.begin()+i);
			}
		}
	}

	std::vector<List> getLists()
	{
		return b_lists;
	}

	bool existsList(std::string _name)
	{
		for (int i = 0; i < b_lists.size(); i++)
		{
			if ((b_lists[i].getScope() == Runtime.M__M ||
				b_lists[i].getScope() == "_sys_public__SCOPE_") &&
				b_lists[i].getName() == _name)
			{
				return true;
			}
			else
			{
				// std::cout << "[RTE] " << b_lists[i].getName() << " != " << _name << std::endl;
				// std::cout << "[RTE] " << b_lists[i].getScope() << " != " << Runtime.M__M << std::endl;
				// std::cout << "[RTE] " << b_lists[i].getScope() << " != " << "_sys_public__SCOPE_" << std::endl;
			}
		}

		return false;
	}

	List getList(std::string _name)
	{
		for (int i = 0; i < b_lists.size(); i++)
		{
			if ((b_lists[i].getScope() == Runtime.M__M ||
				b_lists[i].getScope() == "_sys_public__SCOPE_") &&
				b_lists[i].getName() == _name)
			{
				return b_lists[i];
			}
		}

		return List("[NE:EN]", "[NE:EN]");

	}

} Lists;

#endif
