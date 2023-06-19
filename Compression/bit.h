using namespace std;

class bit
{
public:
    char CurrentByte;
    short int BitCount;
    ofstream Out;

    bit(string Path){
        CurrentByte = 0;
        BitCount = 0;
        Out.open(Path, ios::binary);
    };
    
    // bit = 0 ou 1
    void WriteBit(int bit){
        CurrentByte = CurrentByte << 1 | bit;
        BitCount++;
        if(BitCount == 8){
            Out.write(&CurrentByte,1);
            CurrentByte = 0;
            BitCount = 0;
        }
    }

    void WriteByte(char c){
        Out.write(&c,1);
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