#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <vector>

class List
{
private:
	std::vector<int> values;
	std::string name;

public:
	List(std::string _name)
	{
		name = _name;
	}

	void addValue(int i)
	{
		values.push_back(i);
	}

	int getSize()
	{
		return values.size();
	}

	int getValue(int i=-1)
	{
		if (i == -1)
			return values[values.size()-1];
		else
			return values[i];
	}

	std::string getName()
	{
		return name;
	}

	void setName(std::string _name)
	{
		name = _name;
	}
};

#endif
