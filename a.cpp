#include<bits/stdc++.h>
using namespace std;

typedef struct 
{
    int Key;
    bool Empty = true;
}Slot;

typedef struct 
{
    Slot SlotOne;
    Slot SlotTwo;
}Page;



void Insert(Slot *s, int Key)
{
        s->Key = Key;

}

void CreateExtraPages(vector<Page> *List)
    {
        Page p;
        List.push_back(p);
    }

int main()
{

    vector<vector<Page>> Lists (2,vector<Page>(1)) ;


    Insert(&Lists[1][0].SlotOne,69);
    CreateExtraPages(&Lists[1]);

    cout << Lists[1][0].SlotOne.Key;

    return 0;
}