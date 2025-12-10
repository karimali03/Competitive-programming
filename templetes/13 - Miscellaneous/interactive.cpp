int ask(string s){
    cout<<"? "<<s<<endl;
    cout.flush();
    int ret; cin>>ret;
    return  ret;
}
void ans(int x,int y){
  cout<<"! ";
  if(x == -1) cout<<x;
  else cout<<x<<" "<<y;
  cout<<endl;
}
