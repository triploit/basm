#ifndef LISTS_HPP
#define LISTS_HPP

#include <iostream>
#include <vector>
#include "objs/list.hpp"

class Lists
{
private:
	std::vector<List> b_lists;

public:
	void addList(List l)
	{
		b_lists.push_back(l);
	}

	bool existsList(std::string _name)
	{
		for (int i = 0; i < b_lists.size(); i++)
		{
			if (b_lists[i].getName() == _name)
			{
				return true;
			}
		}

		return false;
	}

	List getList(std::string _name)
	{
		for (int i = 0; i < b_lists.size(); i++)
		{
			if (b_lists[i].getName() == _name)
			{
				return b_lists[i];
			}
		}

		return List("[NE:EN]");

	}

} Lists;

#endif
