// #include <bits/stdc++.h>
using namespace std;



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

        
        static string EncodeString(string str){
            auto FrequencyMap = Huffman::CountFrequencyString(str);
            auto Root = Huffman::CreateTreeEncoder(FrequencyMap);
            
            unordered_map<char,string> CodesMap;
            Root->Codes(CodesMap);
            cout << "Codigos:" << endl;
            for(auto c : CodesMap){
                cout << c.first << " " << c.second << endl;
            }

            string EncodedString = "";

            for (auto c : str){
                EncodedString += CodesMap[c];
            }


            EncodedString =  Root->CreateHeader(FrequencyMap)  + EncodedString;
            return EncodedString;
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

        static unordered_map<char, int> CountFrequencyString(string text){
            unordered_map<char, int> Frequency;
            for (char ch: text) {
                Frequency[ch]++;
            }
            return Frequency;
        }

        static unordered_map<char, int> CountFrequencyFile(string Path){
            unordered_map<char, int> Frequency;


            ifstream in;
            in.open(Path, ios::binary);

            if(in.fail()){
                cout << "Falha ao abrir o arquivo";
            }

            filesystem::path a = Path;
            int Lenght = filesystem::file_size(a);


            char x;
            ofstream out;
            out.open("out.txt",ios::binary);
            cout << Lenght << endl;
            for(int i = 0 ; i < Lenght ; i++){
                in.read(&x,1);
                Frequency[x]++;
                out.write(&x, 1);
            }
            in.close();
            out.close();
            return Frequency;
        }  

        string CreateHeader(unordered_map<char, int> list){
            string Header = "";

            string OrderedAlphabet = "";

            CreateHeaderR(&Header, &OrderedAlphabet);
            
            return Header += OrderedAlphabet;
                
        }

        void CreateHeaderR(string *Header, string *OrderedAlphabet){
            if(!LeftNode && !RightNode){
                (*OrderedAlphabet) += Character;
                return;
            }
                
            (*Header) += "0";
            LeftNode->CreateHeaderR(Header, OrderedAlphabet);
            (*Header) += "1";
            RightNode->CreateHeaderR(Header, OrderedAlphabet);
            return;
        }

        static string DecodeString(string Header){
            int Index = 0;
            auto Root = CreateTreeDecoder(Header, &Index);
            Root->Fill(Header,&(Index));

            return Root->DecodeMsg(Header, Index);
        }
        
        
        static Huffman* CreateTreeDecoder(string Header, int *Index, Huffman* Root = NULL, string C = ""){
            if(Root == NULL){
                Root = new Huffman();
                Root->Code = "";
            }
            else{
                Root->Code += C; 
            }
            if(Header[*Index] == '0'){
                Root->LeftNode = new Huffman();
                (*Index)++;
                CreateTreeDecoder(Header, Index, Root->LeftNode, C+"0");
                Root->RightNode = new Huffman();
                (*Index)++;
                CreateTreeDecoder(Header, Index, Root->RightNode, C+"1");
            }
            
            return Root;
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
        
        string DecodeMsg(string Header, int Index){

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
};
