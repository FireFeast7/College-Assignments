#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

class Page
{
public:
    int frames;
    int num;
    int *pages;

    Page()
    {
        frames = 0;
        num = 0;
    }

public:
    void input()
    {
        cout << "Enter the frames: ";
        cin >> frames;
        cout << "Enter the string length : ";
        cin >> num;
        pages = new int[num];
        for (int i = 0; i < num; i++)
        {
            cin >> pages[i];
        }
    }

public:
    void FIFO()
    {
        int hit = 0;
        int miss = 0;
        unordered_set<int> currentSet;
        queue<int> q;
        for (int i = 0; i < num; i++)
        {
            if (currentSet.size() < frames)
            {
                if (currentSet.find(pages[i]) == currentSet.end())
                {
                    miss++;
                    currentSet.insert(pages[i]);
                    q.push(pages[i]);
                    cout << pages[i] << "\t";
                    for (auto f = currentSet.begin(); f != currentSet.end(); f++)
                    {
                        cout << "| " << *f << " ";
                    }
                    cout << " | " << endl;
                }
                else
                {
                    cout << pages[i] << endl;
                    hit++;
                }
            }
            else
            {
                if (currentSet.find(pages[i]) == currentSet.end())
                {
                    int page = q.front();
                    q.pop();
                    currentSet.erase(page);
                    currentSet.insert(pages[i]);
                    q.push(pages[i]);
                    miss++;
                    cout << pages[i] << "\t";
                    for (auto f = currentSet.begin(); f != currentSet.end(); f++)
                    {
                        cout << " | " << *f << " ";
                    }
                    cout << " | " << endl;
                }
                else
                {
                    hit++;
                    cout << pages[i] << endl;
                }
            }
        }
        cout << "\nNo. of hits = " << hit;
        cout << "\nNo. of page faults = " << miss;
        cout << endl;
    }

public:
    void LRU()
    {
        int hit = 0;
        int miss = 0;
        int currentSet[frames];
        for (int i = 0; i < frames; i++)
        {
            currentSet[i] = -1;
        }
        cout << "\nPage\tPage Frames";
        cout << "\n----------------------------\n";

        for (int i = 0; i < num; i++)
        {
            bool found = false;
            for (int j = 0; j < frames; j++)
            {
                if (currentSet[j] == pages[i])
                {

                    found = true;
                    hit++;
                    cout << pages[i] << "\n"
                         << endl;
                    break;
                }
            }
            if (!found)
            {
                bool freeFrame = false;
                for (int k = 0; k < frames; k++)
                {
                    if (currentSet[k] == -1)
                    {
                        currentSet[k] = pages[i];
                        freeFrame = true;
                        miss++;
                        cout << pages[i] << "\t";
                        for (int f = 0; f < frames; f++)
                        {
                            if (currentSet[f] != -1)
                                cout << "| " << currentSet[f] << "  ";
                        }
                        cout << "| " << endl;
                        break;
                    }
                }
                if (!freeFrame)
                {
                    int prevIndex[frames];
                    for (int m = 0; m < frames; m++)
                    {
                        for (int n = i; n >= 0; n--)
                        {
                            if (pages[n] == currentSet[m])
                            {
                                prevIndex[m] = n;
                                break;
                            }
                        }
                    }
                    int closest = 0;
                    for (int p = 0; p < frames; p++)
                    {
                        if (prevIndex[p] < prevIndex[closest])
                        {
                            closest = p;
                        }
                    }
                    currentSet[closest] = pages[i];
                    miss++;
                    cout << pages[i] << "\t";
                    for (int f = 0; f < frames; f++)
                    {
                        if (currentSet[f] != -1)
                            cout << "| " << currentSet[f] << "  ";
                    }
                    cout << "| " << endl;
                }
            }
        }
        cout << "\nNo. of hits = " << hit;
        cout << "\nNo. of page faults = " << miss;
        cout << endl;
    }

public:
    void ORPA()
    {
        int hit = 0;
        int miss = 0;
        int currentSet[frames];
        for (int i = 0; i < frames; i++)
        {
            currentSet[i] = -1;
        }
        for (int i = 0; i < num; i++)
        {
            bool found = false;
            for (int j = 0; j < frames; j++)
            {
                if (currentSet[j] == pages[i])
                {
                    hit++;
                    cout << pages[i] << "\t";
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                bool freeFrame = false;
                for (int j = 0; j < frames; j++)
                {
                    if (currentSet[j] == -1)
                    {
                        currentSet[j] = pages[i];
                        miss++;
                        freeFrame = true;
                        cout << pages[i] << "\t";
                        for (int m = 0; m < frames; m++)
                        {
                            if (currentSet[m] != -1)
                            {
                                cout << " | " << currentSet[m] << " ";
                            }
                        }
                        cout << " | " << endl;
                        break;
                    }
                }
                if (!freeFrame)
                {
                    int nextIndex[frames];
                    for (int h = 0; h < frames; h++)
                    {
                        nextIndex[h] = num + 1;
                    }
                    for (int m = 0; m < frames; m++)
                    {
                        for (int n = i; n < num; n++)
                        {
                            if (pages[n] == currentSet[m])
                            {
                                nextIndex[m] = n;
                                break;
                            }
                        }
                    }
                    int farthest = 0;
                    for (int p = 0; p < frames; p++)
                    {
                        if (nextIndex[p] > nextIndex[farthest])
                        {
                            farthest = p;
                        }
                    }
                    currentSet[farthest] = pages[i];
                    miss++;
                    cout << pages[i] << "\t";
                    for (int f = 0; f < frames; f++)
                    {
                        if (currentSet[f] != -1)
                            cout << "| " << currentSet[f] << "  ";
                    }
                    cout << "| " << endl;
                }
            }
        }
        cout << "\nNo. of hits = " << hit;
        cout << "\nNo. of page faults = " << miss;
        cout << endl;
    }
    void OPRAr()
    {
        int hit = 0;
        int miss = 0;

        // array containing current pages
        int currentSet[frames];
        for (int f = 0; f < frames; f++)
        {
            currentSet[f] = -1;
        }

        cout << "\nPage\tPage Frames";
        cout << "\n----------------------------\n";

        // for iteration over reference string
        for (int i = 0; i < num; i++)
        {
            bool found = false;
            for (int j = 0; j < frames; j++)
            {
                // if incoming page is present in set of current pages
                if (currentSet[j] == pages[i])
                {
                    found = true;
                    hit++;

                    // print only page number since it is a hit
                    cout << pages[i] << endl;
                    break;
                }
            }

            // if incoming page is absent from set of current pages
            if (!found)
            {
                // find an empty frame
                bool freeFrame = false;
                for (int k = 0; k < frames; k++)
                {
                    if (currentSet[k] == -1)
                    {
                        freeFrame = true;

                        // insert page into the empty frame
                        currentSet[k] = pages[i];
                        miss++;

                        // print the page number and the frames
                        cout << pages[i] << "\t";
                        for (int f = 0; f < frames; f++)
                        {
                            if (currentSet[f] != -1)
                                cout << "| " << currentSet[f] << "  ";
                        }
                        cout << "| " << endl;

                        break;
                    }
                }

                // if no empty frame is available
                if (!freeFrame)
                {
                    // initialize array to store next index of each page in current set
                    // default value is 1 + size of ref string
                    int nextIndex[frames];
                    for (int f = 0; f < frames; f++)
                    {
                        nextIndex[f] = num + 1;
                    }

                    // assign the next index
                    for (int m = 0; m < frames; m++)
                    {
                        for (int n = i; n < num; n++)
                        {
                            if (pages[n] == currentSet[m])
                            {
                                nextIndex[m] = n;
                                break;
                            }
                        }
                    }

                    // find the frame that occurs farthest from current page
                    int farthest = 0;
                    for (int p = 0; p < frames; p++)
                    {
                        if (nextIndex[p] > nextIndex[farthest])
                        {
                            farthest = p;
                        }
                    }

                    // replace the farthest occuring page with the incoming page
                    currentSet[farthest] = pages[i];
                    miss++;

                    // print the page number and the frames
                    cout << pages[i] << "\t";
                    for (int f = 0; f < frames; f++)
                    {
                        if (currentSet[f] != -1)
                            cout << "| " << currentSet[f] << "  ";
                    }
                    cout << "| " << endl;
                }
            }
        }

        // print the no. of hits and misses
        cout << "\nNo. of hits = " << hit;
        cout << "\nNo. of page faults = " << miss;
        cout << endl;
    }
};

int main()
{
    Page p;
    p.input();
    //    p.FIFO();
    //  p.LRU();
    p.ORPA();
    p.OPRAr();
}
