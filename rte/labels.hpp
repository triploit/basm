#ifndef LABELS_HPP
#define LABELS_HPP

#include <iostream>
#include <vector>

#include "objs/label.hpp"
#include "runtime.hpp"
#include "../tstring.hpp"
#include "objs/goto.hpp"

class Labels
{
private:
    std::vector<Label> b_labels;
    int i;
    std::stack<int> last_i;
    std::stack<std::string> last_label_name;
    std::string akt_label = "";
    std::vector<Goto> b_gotos;

public:
    int Index = 0;
    bool iChanged = false;

    void addGoto(Goto g)
    {
        b_gotos.push_back(g);
    }

    Goto getGoto(std::string name)
    {
        for (int i = 0; i < b_gotos.size(); i++)
        {
            if (b_gotos[i].getName() == name && akt_label == b_gotos[i].getScope())
            {
                return b_gotos[i];
            }
        }

        return Goto("", -1, "");
    }

    void setAktLabel(std::string name)
    {
        akt_label = name;
    }

    std::string getLastLabel()
    {
        if (last_label_name.size() > 0)
        {
            tri::string t = last_label_name.top();

            if (t.at(t.length()-1) == ':')
                return t.replaceAll(":", "").cxs();
        }
        else
            return "";
    }

    std::string getAktLabel()
    {
        return akt_label;
    }

    void setI(int _i)
    {
        i = _i;
    }

    int getI()
    {
        return i;
    }

    void addLabel(std::string name, int index)
    {
        // std::cout << "ADD LABEL \"" << name << "\"" << std::endl;
        b_labels.push_back(Label(name, index));
    }

    Label getLabel(std::string name)
    {
        for (int i = 0; i < b_labels.size(); i++)
        {
            if (b_labels[i].getName() == name)
            {
                return b_labels[i];
            }
        }

        return Label("NL", 0);
    }

    int labelCount()
    {
        return b_labels.size();
    }

    bool existsLabel(std::string name)
    {
        for (int i = 0; i < b_labels.size(); i++)
        {
            if (b_labels[i].getName() == name || b_labels[i].getName() == (name+":"))
            {
                return true;
            }
        }

        return false;
    }

    bool existsGoto(std::string name)
    {
        for (int i = 0; i < b_gotos.size(); i++)
        {
            if (b_gotos[i].getName() == name || b_gotos[i].getName() == (name+":"))
            {
                if (b_gotos[i].getScope() == getAktLabel())
                    return true;
            }
        }

        return false;
    }

    int returnI()
    {
        std::cout << "LAST_I.TOP=" << last_i.top() << " " << last_label_name.top() << std::endl;
        int g = last_i.top();
        last_i.pop();
        akt_label = last_label_name.top();
        last_label_name.pop();

        return g;
    }

    std::string returnLabel()
    {
        std::string label = last_label_name.top();
        last_label_name.pop();
        return label;
    }

    int labelArrayIndex(std::string name)
    {
        for (int i = 0; i < b_labels.size(); i++)
        {
            if (b_labels[i].getName() == name || b_labels[i].getName() == (name+":"))
            {
                return i;
            }
        }

        return -1;
    }

    bool gotoLabel(std::string name, int _i)
    {
        if (existsLabel(name))
        {
            last_i.push(i);
            tri::string t = getAktLabel();
            if (t.at(t.length()-1) == ':')
                last_label_name.push(t.replaceAll(":", "").cxs());
            std::cout << "PUSH " << getAktLabel() << " LAST_I=" << i << std::endl;

            i = getLabel(name).getIndex();
            setAktLabel(name);
            Index = i;
            return true;
        }
        else
        {
            std::cout << "ERROR: LABEL_NOT_FOUND:\n\tLabel \"" << name << "\" not found at line " << Runtime.LineNumber << std::endl;
            exit(0);
            return false;
        }
    }
} Labels;

#endif
