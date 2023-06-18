//#include<bits/stdc++.h>
//using namespace std;

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



class Linear
{

public:
    int AlphaMax, Marker = 0, ListLevel = 0, NumberOfKeys = 0, NumberOfPages;
    
    vector<vector<Page>> Lists ;

    Linear(int Alpha) 
    {   
        vector<Page> PqNaoFuncionaSemIsso(1);
        Lists = vector<vector<Page>>(2, PqNaoFuncionaSemIsso ); // c++ é podre
        NumberOfPages = Lists.size();
        AlphaMax = Alpha;
    }

    int Hash(int Key)
    {
        int Position = Key % ( (int) pow(2,ListLevel) * 2 );

        if (Position < Marker)
            Position = Key % ( (int) pow(2,ListLevel+1) * 2 );
        
        return Position;
    }

    void CreateExtraPages(vector<Page> *List)
    {
        NumberOfPages++;
        List->push_back({});
    }

    void CheckAlpha()
    {
        while( (double) NumberOfKeys/(2*NumberOfPages) > (double)AlphaMax/100 )
            Redistribute();
    }

   
    void Redistribute()
    {
        Lists.push_back(vector<Page>(1));
        NumberOfPages++;
        
        int PreviousMarker = Marker;

        if( ++Marker == pow(2,ListLevel) * 2)
        {
            Marker = 0;
            ListLevel += 1;
        }

        for(auto &p : Lists[PreviousMarker])
        {
            if(!p.SlotOne.Empty)
            {
                p.SlotOne.Empty = true;
                AddKey(p.SlotOne.Key,1);
            }
            if (!p.SlotTwo.Empty)
            {
                p.SlotTwo.Empty = true;
                AddKey(p.SlotTwo.Key,1);
            }         
        }

        Clean(PreviousMarker);

    }

    void Clean (int PageNumber)
    {
        int size = Lists[PageNumber].size();
        while(size > 1 && Lists[PageNumber][size-1].SlotOne.Empty && Lists[PageNumber][size-1].SlotTwo.Empty)
        {
            Lists[PageNumber].pop_back();
            size = Lists[PageNumber].size();
            NumberOfPages--;
        }
    } 

    // Remap = 0 -> nova chave. Remap = 1 -> chave ja esta na tabela, ira redistribuir ela
    void Insert(Slot *s, int Key, int Remap)
    {
        s->Key = Key;
        s->Empty = false;
        NumberOfKeys += !Remap;
        CheckAlpha();
    }

    // Remap = 0 -> nova chave. Remap = 1 -> chave ja esta na tabela, ira redistribuir ela
    void AddKey(int Key, int Remap = 0)
    {
        int Position = Hash(Key);

        bool In = false;

        while(!In)
        {
            for(auto &p : Lists[Position])
            {
                if(p.SlotOne.Empty)
                {
                    Insert(&p.SlotOne,Key, Remap);
                    In = true;
                    break;
                }
                else if (p.SlotTwo.Empty)
                {
                    Insert(&p.SlotTwo,Key, Remap);
                    In = true;
                    break;
                }         
            }

            if(!In)
            {
                CreateExtraPages(&Lists[Position]);
            }
        }
    }

    int* SearchKey(int Key)
    {
        int Position = Hash(Key);
        int AcessNumber = 1;
        int Found = 0;

        for (auto &p : Lists[Position])
        {
            if(p.SlotOne.Key == Key)
            {
                Found = 1;
                break;
            }
            AcessNumber++;
            if (p.SlotTwo.Key)
            {
                Found = 2;
                break;
            }    
            AcessNumber++;
        }
        int *Vetor_resposta = new int[2];
        Vetor_resposta[0] =  Found;
        Vetor_resposta[1] =  AcessNumber;
        return Vetor_resposta;
    }

    void PrintTable()
    {
        int i = 0;
        for(auto &l : Lists)
        {
            cout << "Pagina Numero " << i++ << ":    ";
            for(auto &p : l)
            {
                if(!p.SlotOne.Empty)
                    cout << "1: " << p.SlotOne.Key << "  ";
                else
                    cout << "1: ";
                
                if(!p.SlotTwo.Empty)
                    cout << "2: " << p.SlotTwo.Key << "  ";
                else
                    cout << "2: " ;
                
                cout << " --> ";
            }
            cout << endl;
        }
    }
};

