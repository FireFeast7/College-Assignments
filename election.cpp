#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class process
{
public:
    int id;
    string pname;
    process()
    {
        id = 0;
        pname = "";
    }
    friend class election;
};
class election
{
    process *p;
    int num;
    int *flag;

public:
    void input()
    {
        cout << "Enter the number of processes: ";
        cin >> num;
        p = new process[num];
        flag = new int[num];
        for (int i = 0; i < num; i++)
        {
            cout << "Enter the process name: ";
            cin >> p[i].pname;
            cout << "Enter the process id: ";
            cin >> p[i].id;
        }
        int max = 0;
        int pos = 0;
        for (int i = 0; i < num; i++)
        {
            if (p[i].id > max)
            {
                max = p[i].id;
                pos = i;
            }
        }
        cout << "The initial coordinator: " << p[pos].pname << " has crashed" << endl;
    }
    int highest(process p[])
    {
        int max = 0;
        int pos = 0;
        for (int i = 0; i < num; i++)
        {
            if (p[i].id > max)
            {
                max = p[i].id;
                pos = i;
            }
        }
        return pos;
    }
    process bully(process coord)
    {
        for (int i = 0; i < num; i++)
        {
            flag[i] = 0;
        }
        int crashed = highest(p);
        flag[crashed] = 1; // the crashed process cannot be a coordinator

        for (int i = 0; i < num; i++)
        {
            if (p[i].id > coord.id)
            { // the initial coordinator will send election message to the other process
                cout << "Election message sent from " << coord.pname << " to " << p[i].pname << endl;
            }
            else
            {
                flag[i] = 1; // cannot be a coordinator as has lower id than initial coordinator
            }
        }
        for (int i = 0; i < num; i++)
        {
            if (flag[i] != 1 && p[i].id > coord.id)
            {
                cout << p[i].pname << " takes over from " << coord.pname << endl;
                flag[coord.id] = 1; // initial coordinator can no longer take part in the election
                coord = p[i];
            }
        }
        for (int i = 0; i < num; i++)
        {
            if (flag[i] == 0)
            {
                coord = bully(coord);
            }
        }
        return coord;
    }
    int find_pos(int id)
    { // to find position in the ring for cases where process_id!=process_no
        int pos = 0;
        for (int i = 0; i < num; i++)
        {
            if (p[i].id == id)
            {
                pos = i;
            }
        }
        return pos;
    }
    void ring(process coord)
    {
        vector<int> v;
        int crashed = highest(p);
        // v.push_back(coord.id);
        int pos = find_pos(coord.id);
        int cnt = 0;
        int i = pos;
        while (cnt < num)
        {
            if (i != crashed)
                v.push_back(p[i].id);
            // cout<<"hi";
            i = (i + 1) % num;
            cnt++;
        }

        vector<int>::iterator it;

        cout << "Message is: " << endl;
        cout << "[";
        for (it = v.begin(); it != v.end(); it++)
        {
            cout << *it << " ";
        }
        cout << "]" << endl;
        int coord_id = *max_element(v.begin(), v.end());
        int final_coord_pos = find_pos(coord_id);
        cout << "The final coordinator is: " << p[final_coord_pos].pname << endl;
    }
};
int main()
{
    election e;
    e.input();
    process coord;
    process final_coord;

    cout << "Enter the name process which detects that the coordinator has crashed: ";
    cin >> coord.pname;
    cout << "Enter the id process which detects that the coordinator has crashed: ";
    cin >> coord.id;
    int ch = 0;
    while (ch != 3)
    {
        cout << "MENU" << endl;
        cout << "1.Bully algorithm\n2.Ring algorithm\n3.Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            final_coord = e.bully(coord);
            cout << "The final coordinator is: " << final_coord.pname << endl;
            break;
        case 2:
            e.ring(coord);
        }
    }

    return 0;
}