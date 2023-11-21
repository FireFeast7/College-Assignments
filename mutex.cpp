#include <iostream>
#include <mutex>
using namespace std;

struct semaphore
{
    int rcount;
    int rwait;
    int mutex;
    bool wrt;
};
void addR(struct semaphore *s)
{
    if (s->rcount == 0 && s->mutex == 0)
    {
        cout << "\n The File is open in write mode.\nReaders added in queue\n";
        s->rwait++;
    }
    else
    {
        s->mutex--;
        s->rcount++;
        cout << "\nReader Process Added\n";
    }
}
void addW(struct semaphore *s)
{
    if (s->mutex == 1)
    {
        s->mutex--;
        s->wrt = 1;
        cout << "\nWriter Process Added\n";
    }
    else if (s->wrt)
    {
        cout << "\nFile already in write mode\n";
    }
    else
    {
        cout << "\nFile in read mode\n";
    }
}
void remR(struct semaphore *s)
{
    if (s->rcount == 0)
    {
        cout << "\nNo readers to be removed\n";
    }
    else
    {
        s->mutex++;
        s->rcount--;
        cout << "\nReader removed\n";
    }
}
void remW(struct semaphore *s)
{
    if (s->wrt == 0)
    {
        cout << "\nNo Writers for removing\n";
    }
    else
    {
        s->mutex++;
        s->wrt = 0;
        cout << "\nWriter Removed\n";
        if (s->rwait != 0)
        {
            s->mutex -= s->rwait;
            s->rcount = s->rwait;
            s->rwait = 0;
            cout << "waiting Readers Added:" << s->rcount << endl;
        }
    }
}
int main()
{
    struct semaphore s1 = {1, 0, 0};
    while (1)
    {
        cout << "Options :-\n1.Add Reader.\n2.Add Writer.\n3.Remove Reader.\n4.Remove Writer.\n5.Exit.\n\n\tChoice : ";
        int ch;
        cin >> ch;
        switch (ch)
        {
        case 1:
            addR(&s1);
            break;

        case 2:
            addW(&s1);
            break;

        case 3:
            remR(&s1);
            break;

        case 4:
            remW(&s1);
            break;

        case 5:
            cout << "\n\tGoodBye!";
            exit(0);

        default:
            cout << "\nInvalid Entry!";
        }
    }
    return 0;
}