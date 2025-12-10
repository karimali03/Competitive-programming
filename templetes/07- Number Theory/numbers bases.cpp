// to convert x in base A to base b 
// covert from A to 10 then from 10 to B
string letters = "0123456789ABCDEF";
int toDecimal(string in , int base){
            int res = 0;
            for(int i = 0 ; i < in.size() ; i++){
                res *= base;
                res += letters.find(in[i]);
            }
            return res;
}
string fromDecimal(int num , int base){
         if(!num) return "0";
         string res;
         while(num){
                res =  letters[num % base] + res;
                num /= base;
         }
         return res;
}
