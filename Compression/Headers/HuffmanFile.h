// #include <bits/stdc++.h>
using namespace std;

class HuffmanFile
{
    public:
        char Character;
        int Frequency;
        bool IsNode;
        HuffmanFile *LeftNode, *RightNode;

        HuffmanFile(char c, int f){
            Character = c;
            Frequency = f;
            LeftNode = RightNode = NULL;
            IsNode = false;
        }

        HuffmanFile(HuffmanFile *l, HuffmanFile *r){
            LeftNode = l;
            RightNode = r;
            Frequency = l->Frequency + r->Frequency;
            IsNode = true;
            Character = 0;
        }

        HuffmanFile(){
            LeftNode = RightNode = NULL;
            Character = 0;
        }

        bool operator() (HuffmanFile *a, HuffmanFile *b){
            return a->Frequency > b->Frequency;
        }

        static HuffmanFile* CreateTreeCompress(unordered_map<char, int> list){

            priority_queue< HuffmanFile*, vector<HuffmanFile*>, HuffmanFile > HuffmanNodes;

            for(auto p : list)
                HuffmanNodes.push(new HuffmanFile(p.first, p.second));
            
            
            while(HuffmanNodes.size() != 1){
                HuffmanFile *l = HuffmanNodes.top(); 
                HuffmanNodes.pop();
                HuffmanFile *r = HuffmanNodes.top(); 
                HuffmanNodes.pop(); 

                HuffmanNodes.push(new HuffmanFile(l,r));
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

        static void Compress(string Path){
            filesystem::path a = Path;
            unsigned long long int Lenght = filesystem::file_size(a);

            if(Lenght == 0){
                cout << "Escolha um arquivo com tamanho maior que 0 bytes";
                return;
            }
            unordered_map<char, int> FrequencyMap;
            try{
                FrequencyMap = HuffmanFile::CountFrequency(Path, Lenght);
            }
            catch(int e){
                if (e == 1){
                    cout << "Falha ao abrir arquivo de entrada";
                    return;
                }
            }
            auto Root = HuffmanFile::CreateTreeCompress(FrequencyMap);

            unordered_map<char,string> CodesMap;
            Root->Codes(CodesMap);

            cout << "Codigos:" << CodesMap.size() << endl;
            for(auto c : CodesMap){
                cout << (int)c.first << " " << c.second << endl;
            }

            OutBit b("Compressed.afc");
            
            if(b.e){
                cout << "Falha ao abrir arquivo comprimido. Tente novamente";
                return;
            }

            Root->CreateHeader(&b);

            try{
                Root->WriteCompressedMsg(&b, Path, Lenght, CodesMap);
            }
            catch(int e){
                if (e == 1){
                    cout << "Falha ao abrir arquivo comprimido. Tente novamente";
                    return;
                }
            }
            

            char BitCount = b.BitCount;
            
            b.Fill();
            BitCount = BitCount == 0 ? 8 : BitCount;
            b.WriteByte(BitCount);
            /*
            0 - > Ler 8
            1 -> Ler 1
            2 -> Ler 2
            
            */

            b.Close();

            Root->Free();
            delete Root;

        }
        
        void WriteCompressedMsg(OutBit *b, string InPath, unsigned long long int Lenght, unordered_map<char, string> CodesMap){
            ifstream in;
            in.open(InPath, ios::binary);

            if(in.fail()){
                throw(1);
            }

            char x;
            string Code;

            for(unsigned long long int i = 0 ; i < Lenght ; i++){
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

        void CreateHeader(OutBit *b){
            string OrderedAlphabet = "";

            CreateHeaderR(b, &OrderedAlphabet);
            b->WriteBit(1);
            cout << 1 << " ";

            for(auto Letter : OrderedAlphabet){
                b->WriteByte(Letter);
                cout << (int)Letter << " ";
            }

            cout << endl << endl << endl;

        }

        void CreateHeaderR(OutBit *b, string *OrderedAlphabet){
            if(!LeftNode && !RightNode){
                (*OrderedAlphabet) += Character;
                return;
            }
                
            b->WriteBit(0);
            cout << "0 ";
            LeftNode->CreateHeaderR(b, OrderedAlphabet);
            b->WriteBit(1);
            cout << "1 ";
            RightNode->CreateHeaderR(b, OrderedAlphabet);

            return;     
        }

        static unordered_map<char, int> CountFrequency(string Path, unsigned long long int Lenght){
            unordered_map<char, int> Frequency;

            ifstream in;
            in.open(Path, ios::binary);

            if(in.fail()){
                throw(1);
            }

            char x;

            for(unsigned long long int i = 0 ; i < Lenght ; i++){
                in.read(&x,1);
                Frequency[x]++;
            }
            
            in.close();
            return Frequency;
        }  

        static void Decompress(string Path){
            filesystem::path a = Path;
            unsigned long long int Lenght = filesystem::file_size(a);

            if(Lenght == 0){
                cout << "Escolha um arquivo com tamanho maior que 0 bytes";
                return;
            }

            InBit b(Path);

            if(b.e){
                cout << "Falha ao abrir arquivo comprimido. Tente novamente";
                return;
            }

            cout << "0 ";
            auto Root = CreateTreeDecompress(&b,b.ReadBit());

            Root->Fill(&b);

            Root->DecompressMsg(&b, 8*Lenght - b.TotalBitsRead);

            b.Close();
        }

        static HuffmanFile* CreateTreeDecompress(InBit *b, int bit, HuffmanFile* Root = NULL){
            if(Root == NULL)
                Root = new HuffmanFile();

            if(bit == 0){
                Root->LeftNode = new HuffmanFile();
                int a = b->ReadBit();
                cout << a << " ";
                CreateTreeDecompress(b,a, Root->LeftNode);
                Root->RightNode = new HuffmanFile();
                a = b->ReadBit();
                cout << a << " ";
                CreateTreeDecompress(b,a, Root->RightNode);
            }
            return Root;
        }
        
        void Fill(InBit *b){
            if(!LeftNode && !RightNode){
                for(int i = 0 ; i < 8 ; i++){
                    char c = b->ReadBit();
                    Character = Character << 1 | c;
                }
                return;
            }

            LeftNode->Fill(b);
            RightNode->Fill(b);

            return;
        }
        
        //Lenght in bits
        void DecompressMsg(InBit *b, unsigned long long int Lenght){
            auto Buffer = this;
            OutBit OutB("Arquivo Descomprimido.afc");

            if(OutB.e){
                cout << "Falha ao abrir o arquivo descomprimido";
                return;
            }

            for(unsigned long long int i = 0 ; i < Lenght - 16 ; i++){
                                
                if(!Buffer->LeftNode && !Buffer->RightNode){
                    OutB.WriteByte(Buffer->Character);
                    Buffer = this;
                    i--;
                }
                else{
                    if(b->ReadBit() == 0)
                        Buffer = Buffer->LeftNode;
                    else
                        Buffer = Buffer->RightNode;
                    
                }
                
            }

            char LastByte = b->ReadByte();
            int BitsToConsider = b->ReadByte();

            int a;

            for(unsigned long long int i = 0 ; i < BitsToConsider ; i++ ){
                                
                if(!Buffer->LeftNode && !Buffer->RightNode){
                    OutB.WriteByte(Buffer->Character);
                    Buffer = this;
                    i--;
                }
                else{
                    a = (LastByte >> 7 - i) & 1;
                    if( a == 0 )
                        Buffer = Buffer->LeftNode;
                    else
                        Buffer = Buffer->RightNode;
                }
            }

            if(!Buffer->LeftNode && !Buffer->RightNode){
                OutB.WriteByte(Buffer->Character);
                Buffer = this;
            }

            OutB.Close();
        }
};

// 0 0 0 1 1 1 0 1 0 1 1
// 0 0 0 1 3 7 14 29 0 1 3