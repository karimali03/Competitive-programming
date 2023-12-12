#include <iostream>
#include <cassert>
using namespace std;



template <class T>
class Stack
{
private:
    struct Node
    {
       T data {};
       Node* next {};
       Node(T data):data(data){};
    };
    Node *head {};
public:
    ~Stack(){
        while(!empty()) pop();
    }

    void print(){
        for(auto cur=head;cur;cur=cur->next)
        cout<<cur->data<<" ";
        cout<<"\n";
    }

    void push(T val){
        Node * add=new Node(val);
        add->next=head;
        head=add;
    }
    int pop(){
        assert(head);
        T val=head->data;
        Node* del = head;
        head=head->next;
        delete del; 
        return val;
    }

    int top(){
        assert(head);
        return head->data;
    }

    bool empty(){
        return !head;
    }
};




bool isDigit(char digit){
    return digit>='0' && digit<='9';
}

int precedence(char ch){
    if(ch=='+' || ch=='-') return 1;
    else if( ch=='*' || ch== '/' ) return 2;
    else if(ch == '^') return 3;
    return 0;
}

string convert(string  infix){
    Stack<char> st;
    string postfix;
    st.push('#');
    infix+='+';
    for(auto & x : infix){
        if(x == '(') st.push(x);
        else if(isdigit(x)) postfix+=x;
        else if(x == ')') {
            while(st.top()!='(') postfix+=st.pop();
            st.pop();
            }
        else {
            while ( precedence(st.top()) >= precedence(x)  )
            {
                if(x=='^') break;
                postfix+=st.pop();
            }
            st.push(x);
        }    
    }
    return postfix;
}


int main(){

    string s; cin>>s;
    cout<<convert(s)<<"\n";
	return 0;
}