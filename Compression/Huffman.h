// #include <bits/stdc++.h>
using namespace std;

#include "bit.h"

class Huffman
{
    public:
        char Character;
        int Frequency;
        bool IsNode;
        Huffman *LeftNode, *RightNode;
        string Code;

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

        Huffman(){
            LeftNode = RightNode = NULL;
        }

        bool operator() (Huffman *a, Huffman *b){
            return a->Frequency > b->Frequency;
        }

        static Huffman* CreateTreeEncoder(unordered_map<char, int> list){

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

        void Codes(unordered_map<char,string> &AllCodes, string Code = ""){      
            if (IsNode) {
                LeftNode->Codes(AllCodes,Code + "0");
                RightNode->Codes(AllCodes,Code + "1");   
                return;
            }

            AllCodes[Character] = Code;
            return;
        }

        static void EncodeFile(string Path){
            filesystem::path a = Path;
            unsigned long long int Lenght = filesystem::file_size(a);

            auto FrequencyMap = Huffman::CountFrequencyFile(Path, Lenght);
            auto Root = Huffman::CreateTreeEncoder(FrequencyMap);

            unordered_map<char,string> CodesMap;
            Root->Codes(CodesMap);

            bit b("Compressed.afc");
            Root->CreateHeaderFile(&b);

            // bla bla EncodeLenght()

            Root->WriteEncodedMsgFile(&b, Path, Lenght, CodesMap);

            b.Fill();

            b.Close();
        }
        
        void WriteEncodedMsgFile(bit *b, string InPath, int Lenght, unordered_map<char, string> CodesMap){
            ifstream in;
            in.open(InPath, ios::binary);

            if(in.fail()){
                cout << "Falha ao abrir o arquivo";
            }

            char x;
            string Code;

            for(int i = 0 ; i < Lenght ; i++){
                in.read(&x,1);
                Code = CodesMap[x];
                for(auto bit : Code){
                    if(bit == '0')
                        b->WriteBit(0);
                    else
                        b->WriteBit(1);
                }
            }
        }

        void CreateHeaderFile(bit *b){
            string OrderedAlphabet = "";

            CreateHeaderFileR(b, &OrderedAlphabet);

            for(auto Letter : OrderedAlphabet){
                b->WriteByte(Letter);
            }

        }

        void CreateHeaderFileR(bit *b, string *OrderedAlphabet){
            if(!LeftNode && !RightNode){
                (*OrderedAlphabet) += Character;
                return;
            }
                
            b->WriteBit(0);
            LeftNode->CreateHeaderFileR(b, OrderedAlphabet);
            b->WriteBit(1);
            RightNode->CreateHeaderFileR(b, OrderedAlphabet);

            return;     
        }

        static unordered_map<char, int> CountFrequencyFile(string Path, int Lenght){
            unordered_map<char, int> Frequency;

            ifstream in;
            in.open(Path, ios::binary);

            if(in.fail()){
                cout << "Falha ao abrir o arquivo";
            }

            char x;

            for(int i = 0 ; i < Lenght ; i++){
                in.read(&x,1);
                Frequency[x]++;
            }
            
            in.close();
            return Frequency;
        }  
        
        void Fill(string Header, int *Index){
            if(!LeftNode && !RightNode){
                Character = Header[*Index];
                (*Index)++;
                return;
            }

            LeftNode->Fill(Header, Index);
            RightNode->Fill(Header, Index);

            return;
        }
        
        static string EncodeString(string Str){
            auto FrequencyMap = Huffman::CountFrequencyString(Str);
            auto Root = Huffman::CreateTreeEncoder(FrequencyMap);
            
            unordered_map<char,string> CodesMap;
            Root->Codes(CodesMap);

            string EncodedString = "";

            for (auto c : Str){
                EncodedString += CodesMap[c];
            }

            EncodedString =  Root->CreateHeaderString()  + EncodedString;
            return EncodedString;
        }

        static unordered_map<char, int> CountFrequencyString(string text){
            unordered_map<char, int> Frequency;
            for (char ch: text) {
                Frequency[ch]++;
            }
            return Frequency;
        }

        string CreateHeaderString(){
            string Header = "";

            string OrderedAlphabet = "";

            CreateHeaderStringR(&Header, &OrderedAlphabet);
            
            return Header += OrderedAlphabet;    
        }

        void CreateHeaderStringR(string *Header, string *OrderedAlphabet){
            if(!LeftNode && !RightNode){
                (*OrderedAlphabet) += Character;
                return;
            }
                
            (*Header) += "0";
            LeftNode->CreateHeaderStringR(Header, OrderedAlphabet);
            (*Header) += "1";
            RightNode->CreateHeaderStringR(Header, OrderedAlphabet);
            return;
        }

        static string DecodeString(string EncodedString){
            int Index = 0;
            auto Root = CreateTreeDecoderString(EncodedString, &Index);
            Root->Fill(EncodedString,&(Index));

            return Root->DecodeMsgString(EncodedString, Index);
        }

        string DecodeMsgString(string Header, int Index){

            auto Buffer = this;
            string DString = "";

            while(Index <= Header.length()){
                if(!Buffer->LeftNode && !Buffer->RightNode){
                    DString += Buffer->Character;
                    Buffer = this;
                }
                else{
                    if(Header[Index] == '0')
                        Buffer = Buffer->LeftNode;
                    else
                        Buffer = Buffer->RightNode;
                    Index++;
                }
            }
            
            return DString;
        }

        static Huffman* CreateTreeDecoderString(string Header, int *Index, Huffman* Root = NULL, string C = ""){
            if(Root == NULL)
                Root = new Huffman();
            
            if(Header[*Index] == '0'){
                Root->LeftNode = new Huffman();
                (*Index)++;
                CreateTreeDecoderString(Header, Index, Root->LeftNode, C+"0");
                Root->RightNode = new Huffman();
                (*Index)++;
                CreateTreeDecoderString(Header, Index, Root->RightNode, C+"1");
            }
            
            return Root;
        }
};