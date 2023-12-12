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



int main(){
   
	Stack<int> stk;
	stk.push(10);
	stk.push(20);
	stk.push(30);
	stk.print();	// 30 20 10
    Stack<char>st;
    st.push('a');
    st.push('b');
    st.push('c');
    st.print();
	
	return 0;
}