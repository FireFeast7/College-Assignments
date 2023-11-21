#include <bits/stdc++.h>
using namespace std;

class Assembler
{
    vector<pair<string, string>> SYMTAB;
    vector<pair<string, string>> LITTAB;
    fstream intermediatecode;
    fstream symboltable;
    fstream literaltable;
    fstream file;
    fstream output1;

public:
    Assembler()
    {
        intermediatecode.open("intermediate_code.txt", ios::in);
        if (!intermediatecode.is_open())
        {
            cout << "Error" << endl;
        }
        symboltable.open("symbol_table.txt", ios::in);
        if (!symboltable.is_open())
        {
            cout << "Error" << endl;
        }
        else
        {
            string line;
            while (!symboltable.eof())
            {
                getline(symboltable, line);
                string w = "";
                string key = "";
                string value = "";
                for (int i = 0; i < line.size(); i++)
                {
                    if (line[i] != ' ')
                    {
                        w += line[i];
                    }
                    else
                    {
                        key.assign(w);
                        w = "";
                    }
                }
                value = w;
                SYMTAB.push_back(pair<string, string>(key, value));
            }
        }
        literaltable.open("literal_table.txt", ios::in);
        if (!literaltable.is_open())
        {
            cout << "Error" << endl;
        }
        else
        {
            string line = "";
            while (!literaltable.eof())
            {
                string line = "";
                getline(literaltable, line);
                string w = "";
                string key = "";
                string value = "";
                for (int i = 0; i < line.size(); i++)
                {
                    if (line[i] != ' ')
                    {
                        w += line[i];
                    }
                    else
                    {
                        key.assign(w);
                        w = "";
                    }
                }
                value = w;
                LITTAB.push_back(pair<string, string>(key, value));
            }
        }
        output1.open("output1.txt", ios::out);
        if (!output1.is_open())
        {
            cout << "Error opening output1 file" << endl;
        }
    }
    void passTwo()
    {
        string line = "";
        vector<string> words;
        if (intermediatecode.is_open())
        {
            while (!intermediatecode.eof())
            {
                getline(intermediatecode, line);
                string w = "";
                for (int i = 0; i < line.size(); i++)
                {
                    if (line[i] != ' ')
                    {
                        w += line[i];
                    }
                    else
                    {
                        words.push_back(w);
                        w = "";
                    }
                }
                words.push_back(w);

                if (words[1].at(1) == 'I' && words[1].at(2) == 'S')
                {
                    if (words.size() == 2)
                    {
                        output1 << words[0] << " " << words[1].at(4) << endl;
                    }
                    else if (words.size() == 3)
                    {
                        int index = int(words[2].at(3) - '0');
                        output1 << words[0] << " " << words[1].at(4) << " " << SYMTAB[index - 1].second << endl;
                    }
                    else
                    {
                        if (words[3].at(1) == 'S')
                        {
                            int index = int(words[3].at(3) - '0');
                            output1 << words[0] << " " << words[1].at(4) << " " << words[2].at(1) << " " << SYMTAB[index - 1].second << endl;
                        }
                        else if (words[3].at(1) == 'L')
                        {
                            int index = int(words[3].at(3) - '0');
                            output1 << words[0] << " " << words[1].at(4) << " " << words[2].at(1) << " " << LITTAB[index - 1].second << endl;
                        }
                        else
                        {
                            output1 << words[0] << " " << words[1].at(4) << " " << words[2].at(1) << " " << words[3].at(1);
                        }
                    }
                }
                words.clear();
            }
        }
    }
}

;
int main()
{
    Assembler a;
    a.passTwo();
    return 0;
}