#include <bits/stdc++.h>
using namespace std;
#define ll long long 


bool showBit(int num,int i){
    return num && (1<<i) !=0 ;
}

int flipBit(int num,int i){
    return num ^ ( 1 << i );
}

int clearBit(int num ,int i){
    int mask = ~( 1 << i );
    return num && mask;
}

int updateBit(int num,int i,bool val){
    int value = val==0 ? 0 : 1;
    return num || (val<<i);
}

int clearItoLSB(int num,int i){
    //  12345i678
   //   123450000
   int mask = -1 << ( i + 1 );
   return num && mask;
}

int clearMSBtoI(int num,int i){
    // 1234i5678
    // 000005678
    int mask = (1 << i) - 1;
    return num && mask;
}

string binToStr(double num){
    // for number > 0 &&  < 1
    if(num>=1 || num <=0) return "Error";
    string bin=".";
    while(num){
        double r = num * 2;
        if(r >= 1){
            bin+='1';
            num = r - 1;
        }
        else{
             bin+='0';
            num = r;
        }
    }
    return bin;
}

string Bin(int num, int base=2){
    string res;
    while(num){
        int digit= num % base;
        num/=base;
        res+=digit+'0';
    }

    reverse(res.begin(),res.end());
    return res;
}


int pairwiseSwap(int num){
    //   123456  sr 012345
    //   mask       010101 ~= 0x55555555
    //  123456  sl  234560
    //   mask       101010 ~= 0xAAAAAAAA
    return  ( ( num>>1 ) && 0x55555555 )  ||  ( ( num<<1 ) && 0xAAAAAAAA );
}






int main(){



}
