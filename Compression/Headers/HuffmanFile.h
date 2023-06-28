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
            unsigned long long int Lenght = 0;
            
            try{
                Lenght = filesystem::file_size(a);
            }
            catch(...){
                cout << "Passe o nome de um arquivo valido" << endl;
                return;
            }

            if(Lenght == 0){
                cout << "Escolha um arquivo com tamanho maior que 0 bytes" << endl;
                return;
            }

            string ReversedExtension = "";

            for(int i = Path.size()-1 ; i >= 0 ; i--){
                ReversedExtension += Path[i];
                if(Path[i] == '.')
                    break;
            }

            cout << "Contando frequencia" << endl;

            unordered_map<char, int> FrequencyMap;
            try{
                FrequencyMap = HuffmanFile::CountFrequency(Path, Lenght);
            }
            catch(int e){
                if (e == 1){
                    cout << "Falha ao abrir arquivo de entrada" << endl;
                    return;
                }
            }

            Entropy(FrequencyMap, Lenght);


            for(auto c : ReversedExtension){
                FrequencyMap[c]++;
            }

            cout << "Criando arvore" << endl << endl;
            auto Root = HuffmanFile::CreateTreeCompress(FrequencyMap);

            cout << "Preenchendo arvore" << endl << endl;
            unordered_map<char,string> CodesMap;
            Root->Codes(CodesMap);

            OutBit b("Compressed.afc");
            
            if(b.e){
                cout << "Falha ao abrir arquivo comprimido. Tente novamente" << endl;
                return;
            }

            cout << "Criando header" << endl << endl;
            Root->CreateHeader(&b);

            cout << "Escrevendo mensagem" << endl;
            try{

                Root->WriteCompressedMsg(&b, Path, Lenght, CodesMap, ReversedExtension);
            }
            catch(int e){
                if (e == 1){
                    cout << "Falha ao abrir arquivo comprimido. Tente novamente" << endl;
                    return;
                }
            }
            

            char BitCount = b.BitCount;
            
            b.Fill();
            BitCount = BitCount == 0 ? 8 : BitCount;
            b.WriteByte(BitCount);

            b.Close();

            Root->Free();
            delete Root;

        }
        
        void WriteCompressedMsg(OutBit *b, string InPath, unsigned long long int Lenght, 
                                unordered_map<char, string> CodesMap, string ReversedExtension){
            
            ifstream in;
            in.open(InPath, ios::binary);

            if(in.fail()){
                throw(1);
            }


            char x;
            string Code;

            
            for(auto c : ReversedExtension){
                Code = CodesMap[c];
                for(auto bit : Code){
                    if(bit == '0')
                        b->WriteBit(0);
                    else
                        b->WriteBit(1);
                }
            }

            int previous = 1;
            cout << "Bytes lidos: " << "0/" << Lenght << "\r" << flush;

            for(unsigned long long int i = 0 ; i < Lenght ; i++){
                in.read(&x,1);
                Code = CodesMap[x];
                for(auto bit : Code){
                    if(bit == '0')
                        b->WriteBit(0);
                    else
                        b->WriteBit(1);
                }

                if (i >= previous * (Lenght / 20)){
                    previous++;
                    cout << "Bytes comprimidos: " << i << "/" << Lenght << "\r" << flush;
                }
            }
            cout << endl <<  "Todos bytes lidos" << endl << endl;
        }

        void CreateHeader(OutBit *b){
            string OrderedAlphabet = "";

            CreateHeaderR(b, &OrderedAlphabet);
            b->WriteBit(1);

            for(auto Letter : OrderedAlphabet){
                b->WriteByte(Letter);
            }

        }

        void CreateHeaderR(OutBit *b, string *OrderedAlphabet){
            if(!LeftNode && !RightNode){
                (*OrderedAlphabet) += Character;
                return;
            }
                
            b->WriteBit(0);
            LeftNode->CreateHeaderR(b, OrderedAlphabet);
            b->WriteBit(1);
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

            int previous = 1;
            cout << "Bytes lidos: " << "0/" << Lenght << "\r" << flush;

            for(unsigned long long int i = 0 ; i < Lenght ; i++){
                in.read(&x,1);
                Frequency[x]++;
                if (i >= previous * (Lenght / 20)){
                    previous++;
                    cout << "Bytes lidos: " << i << "/" << Lenght << "\r" << flush;
                }
            }
            cout << endl <<  "Todos bytes lidos" << endl << endl;
            
            in.close();
            return Frequency;
        }  

        static void Decompress(string Path){
            filesystem::path a = Path;
            unsigned long long int Lenght = filesystem::file_size(a);

            if(Lenght == 0){
                cout << "Escolha um arquivo com tamanho maior que 0 bytes" << endl;
                return;
            }

            InBit b(Path);

            if(b.e){
                cout << "Falha ao abrir arquivo comprimido. Tente novamente" << endl;
                return;
            }
            
            cout << "Criando arvore para descompressao" << endl << endl;

            auto Root = CreateTreeDecompress(&b,b.ReadBit());

            cout << "Preenchendo arvore para descompressao" << endl << endl;

            Root->Fill(&b);

            cout << "Descomprimindo mensagem" << endl << endl;

            Root->DecompressMsg(&b, 8*Lenght - b.TotalBitsRead);

            b.Close();
        }

        static HuffmanFile* CreateTreeDecompress(InBit *b, int bit, HuffmanFile* Root = NULL){
            if(Root == NULL)
                Root = new HuffmanFile();

            if(bit == 0){
                Root->LeftNode = new HuffmanFile();
                int a = b->ReadBit();
                CreateTreeDecompress(b,a, Root->LeftNode);
                Root->RightNode = new HuffmanFile();
                a = b->ReadBit();
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
        void DecompressMsg(InBit *b, long double Lenght){
            auto Buffer = this;

            string Extension = "";

            while(Buffer->Character != '.'){
                if(!Buffer->LeftNode && !Buffer->RightNode){
                    Extension = Buffer->Character + Extension;
                    Buffer = this;
                }
                else{
                    if(b->ReadBit() == 0)
                        Buffer = Buffer->LeftNode;
                    else
                        Buffer = Buffer->RightNode;
                    Lenght--;
                }
            }

            if(!Buffer->LeftNode && !Buffer->RightNode){
                Extension = Buffer->Character + Extension;
                Buffer = this;
            }

            OutBit OutB("Arquivo Descomprimido" + Extension);

            if(OutB.e){
                cout << "Falha ao abrir o arquivo descomprimido" << endl;
                return;
            }

            int previous = 1;
            cout << "Bytes lidos: " << "0/" << (int)Lenght/8 << "\r" << flush;

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

                if (i >= previous * (Lenght / 20)){
                    previous++;
                    cout << "Bytes lidos: " << (int) i/8 << "/" << (int) Lenght/8 << "\r" << flush;
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

            cout << endl <<  "Todos bytes lidos" << endl << endl;

            OutB.Close();
        }

        static void Entropy(unordered_map<char, int> FrequencyMap, unsigned long long int Lenght){
            long double Sum = 0;

            for(auto c : FrequencyMap){
                Sum += c.second * ( log2((long double)c.second) - log2((long double)Lenght) );
            }

            Sum /= Lenght;
            Sum *= -1;

            cout << "Entropia = " << Sum << endl << endl;
        }
};