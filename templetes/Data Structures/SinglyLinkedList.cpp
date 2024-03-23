#include <iostream>
using namespace std;



struct Node {
    int data {};
    Node* next;
    Node(int data):data(data){}
};



class LinkedList
{

private:
   Node* head;
   Node* tail;
   int length {};
public:

    LinkedList(){};
    ~LinkedList(){};

    void print(){
        for(auto cur = head ; cur ; cur=cur->next){
            cout<<cur->data<<" ";
        }
        cout<<"\n";
    }

    void insert_end(int val){
        Node* node=new Node(val);
        if(!head){
            head=tail=node;
        }
        else{
            tail->next=node;
            tail=node;
        }
         length++;
    }

    void insert_front(int val){
         Node* node=new Node(val);
        if(!head){
            head=tail=node;
        }
        else{
            node->next=head;
            head=node;
        }
        length++;
    }

    Node* get_Nth(int n){
        for(auto cur = head ; cur ; cur=cur->next){
            if(--n==0) return cur;
        }
        return {};
    }

    void delete_front(){
        if(!head) return;
        Node* del=head;
        if(head==tail){ 
            delete del;
            head=tail={};
        }
        else {
            head=head->next;
            delete del;
        }
        length--;
    }

   void delete_end(){
     if(!head) return;
     if(head==tail){
        delete head;
        head=tail={};
     }
     else{
        delete tail;
        tail=get_Nth(length-1);
        tail->next={};
     }
     length--;
   }

   void delete_Nth(int n){
    if(n<1 || n > length) return;
    if(n==1) delete_front();
    else{
        Node* prev=get_Nth(n-1);
        Node* del=prev->next;
        prev->next=prev->next->next;
        if(!prev->next) tail=prev;
        delete del;
        length--;
    }
   } 

   void reverse_LS(){
    if(!head || head==tail) return;
    swap(head,tail);
    auto cur=tail->next,prv=tail;

    while(cur){
        auto next=cur->next;
        cur->next=prv;
        prv=cur;
        cur=next;
    }
    tail->next=nullptr;
   }
   
  Node* AddBack(Node *prv,Node *cur){
        if(tail==cur) return cur;
        Node* nxt=cur->next;
        
        tail->next=cur;
        tail=tail->next;
        tail->next=nullptr;

        if(prv) prv->next=nxt;
        else head=nxt;
        return nxt;
    }

    // embed after
};
