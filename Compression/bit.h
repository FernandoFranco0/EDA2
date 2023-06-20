using namespace std;

class OutBit
{
public:
    char CurrentByte;
    char BitCount;
    ofstream Out;
    unsigned long long int TotalBitsRead;

    OutBit(string Path){
        CurrentByte = 0;
        BitCount = 0;
        Out.open(Path, ios::binary);
    };
    
    // bit = 0 ou 1
    void WriteBit(int bit){
        CurrentByte = CurrentByte << 1 | bit;
        BitCount++;
        TotalBitsRead++;

        if(BitCount == 8){
            Out.write(&CurrentByte,1);
            CurrentByte = 0;
            BitCount = 0;
        }
    }

    void WriteByte(char c){
        for(int i = 0 ; i < 8 ; i++){
            unsigned char a = c;
            unsigned char b = (a >> 7-i) & 1;
            WriteBit( b );
        }
    }

    void Fill(){  
        while(BitCount != 0){
            WriteBit(0);
        }
    }

    void Close(){
        Out.close();
    }
};

class InBit
{
public:
    unsigned char CurrentByte;
    unsigned char BitCount;
    unsigned long long int TotalBitsRead;
    ifstream In;

    InBit(string Path){
        CurrentByte = 0;
        BitCount = 0;
        In.open(Path, ios::binary);
        TotalBitsRead = 0;
    };

    char ReadBit(){
        if(BitCount == 0){
            char Byte;
            In.read(&Byte,1);    
            CurrentByte = Byte;
        }

        unsigned char ReturnByte = CurrentByte >> 7-BitCount & 1;
        BitCount++;
        TotalBitsRead++;

        if (BitCount == 8)
            BitCount = 0;
            
        return ReturnByte;
    }

    char ReadByte(){
        char Byte;
        In.read(&Byte,1);
        return Byte;
    }
    
    void Close(){
        In.close();
    }
};