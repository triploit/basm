#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <vector>

class List
{
private:
	std::vector<int> values;
	std::string name;
	std::string scope;

public:
	List(std::string _name, std::string _scope)
	{
		name = _name;
		scope = _scope;
	}

	std::string getScope()
	{
		return scope;
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
