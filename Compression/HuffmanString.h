using namespace std;

class HuffmanString
{
    public:
        char Character;
        int Frequency;
        bool IsNode;
        HuffmanString *LeftNode, *RightNode;

        HuffmanString(char c, int f){
            Character = c;
            Frequency = f;
            LeftNode = RightNode = NULL;
            IsNode = false;
        }

        HuffmanString(HuffmanString *l, HuffmanString *r){
            LeftNode = l;
            RightNode = r;
            Frequency = l->Frequency + r->Frequency;
            IsNode = true;
            Character = 0;
        }

        HuffmanString(){
            LeftNode = RightNode = NULL;
            Character = 0;
        }

        bool operator() (HuffmanString *a, HuffmanString *b){
            return a->Frequency > b->Frequency;
        }

        static HuffmanString* CreateTreeCompress(unordered_map<char, int> list){

            priority_queue< HuffmanString*, vector<HuffmanString*>, HuffmanString > HuffmanNodes;

            for(auto p : list)
                HuffmanNodes.push(new HuffmanString(p.first, p.second));
            
            
            while(HuffmanNodes.size() != 1){
                HuffmanString *l = HuffmanNodes.top(); 
                HuffmanNodes.pop();
                HuffmanString *r = HuffmanNodes.top(); 
                HuffmanNodes.pop(); 

                HuffmanNodes.push(new HuffmanString(l,r));
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

        void Free(){
            if(!LeftNode && !RightNode)
                return;

            LeftNode->Free();
            delete LeftNode;
            
            RightNode->Free();
            delete RightNode;
            
        }

        static string Compress(string Str){
            auto FrequencyMap = HuffmanString::CountFrequency(Str);
            auto Root = HuffmanString::CreateTreeCompress(FrequencyMap);
            
            unordered_map<char,string> CodesMap;
            Root->Codes(CodesMap);

            string CompressedString = "";

            for (auto c : Str){
                CompressedString += CodesMap[c];
            }

            CompressedString =  Root->CreateHeader()  + CompressedString;

            Root->Free();
            delete Root;

            return CompressedString;
        }

        static unordered_map<char, int> CountFrequency(string text){
            unordered_map<char, int> Frequency;
            for (char ch: text) {
                Frequency[ch]++;
            }
            return Frequency;
        }

        string CreateHeader(){
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

        static string Decompress(string EncodedString){
            int Index = 0;
            auto Root = CreateTreeDecompress(EncodedString, &Index);
            Root->Fill(EncodedString,&(Index));

            return Root->DecompressMsg(EncodedString, Index);
        }

        string DecompressMsg(string Header, int Index){

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

        static HuffmanString* CreateTreeDecompress(string Header, int *Index, HuffmanString* Root = NULL){
            if(Root == NULL)
                Root = new HuffmanString();
            
            if(Header[*Index] == '0'){
                Root->LeftNode = new HuffmanString();
                (*Index)++;
                CreateTreeDecompress(Header, Index, Root->LeftNode);
                Root->RightNode = new HuffmanString();
                (*Index)++;
                CreateTreeDecompress(Header, Index, Root->RightNode);
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
};