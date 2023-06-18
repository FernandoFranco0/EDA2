// #include <fstream>
// #include <iomanip>
// #include <iostream>
// #include <math.h>
// #include <stdlib.h>
// #include <string>
// #include <vector>

#include <bits/stdc++.h>

using namespace std;

class Huffman
{
    public:
        char Character;
        int Frequency;
        bool IsNode;
        Huffman *LeftNode, *RightNode;

        Huffman(char c, int f){
            Character = c;
            Frequency = f;
            LeftNode = RightNode = NULL;
            IsNode = false;
        }

        Huffman(Huffman *l, Huffman *r){
            LeftNode = l;
            RightNode = r;
            Frequency = l->Frequency + r->Frequency;
            IsNode = true;
        }

        Huffman(){}

        bool operator() (Huffman *a, Huffman *b)
        {
            return a->Frequency > b->Frequency;
        }


        static Huffman* CreateTree(unordered_map<char, int> list){

            priority_queue< Huffman*, vector<Huffman*>, Huffman > HuffmanNodes;

            for(auto p : list)
                HuffmanNodes.push(new Huffman(p.first, p.second));
            
            
            while(HuffmanNodes.size() != 1){
                Huffman *l = HuffmanNodes.top(); 
                HuffmanNodes.pop();

                Huffman *r = HuffmanNodes.top(); 
                HuffmanNodes.pop(); 

                HuffmanNodes.push(new Huffman(l,r));
            }

            return HuffmanNodes.top();
        }

        unordered_map<char,int> Codes(){
            unordered_map<char, int> AllCodes;
            Codes(AllCodes);
            return AllCodes;
        }

        void Codes(unordered_map<char,int> &AllCodes, int Code = 0){      
            if (IsNode) {
                LeftNode->Codes(AllCodes,Code << 1);
                RightNode->Codes(AllCodes,Code << 1 | 1);   
                return;
            }

            AllCodes[Character] = Code;
            return;
        }

        
};


int main()
{

    unordered_map<char, int> a = {
        {'a',5},
        {'b',2},
        {'c',1},
        {'d',10},
        {'e',7},
    };
    
    auto root = Huffman::CreateTree(a);

    auto codes = root->Codes();

    for(auto c : codes){
        cout << c.first << " " << c.second << endl;
    }

    return 0;
}

