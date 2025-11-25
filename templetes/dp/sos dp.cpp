const int LOG = 20;
const int MX = (1<<LOG);
int dp1[MX]{};
int dp2[MX]{};
 
void SOS1(){ // sum over subsets
    for(int bit=0;bit<LOG;bit++){
        for(int i=0;i<MX;i++) if((i>>bit)&1){
            dp1[i] += dp1[i^(1<<bit)];
        }
    }
}
 
void REV1(){
    for(int bit=0;bit<LOG;bit++){
        for(int i=MX-1;i>=0;i--) if((i>>bit)&1){
            dp1[i] -= dp1[i^(1<<bit)];
        }
    }
}
 
void SOS2(){ // sum over supersets
    for(int bit=0;bit<LOG;bit++){
        for(int i=MX-1;i>=0;i--) if((i>>bit)&1){
            dp2[i^(1<<bit)] += dp2[i];
        }
    }
}
 
void REV2(){
    for(int bit=0;bit<LOG;bit++){
        for(int i=0;i<MX;i++) if((i>>bit)&1){
            dp2[i^(1<<bit)] -= dp2[i];
        }
    }
}

