#include <iostream>
#include <cassert>
using namespace std;

template <class T>
class Vector
{
private:
    T * arr = {};
    int size {};
    int capacity {};
    void expand_capacity();
public:
    Vector();
    Vector(int size);
    ~Vector();
    Vector(const Vector & v);
	int get_size();
	T get_front();
    void insert(int idx,T val);
	T get_back();
	T get(int idx);
	void set(int idx, T val);

	void print();
	int find(T value);
	void push_back(T value);

    T& operator[](int idx);
};

template <class T>
Vector<T>::Vector(int size) : size(size){
    if(size < 0) size=1;
    capacity=size+10;
    arr= new T[capacity] {};
}
template <class T>
Vector<T>::Vector(){
    size=0;
    capacity=10;
    arr= new T[capacity] {};
}

template <class T>
Vector<T>::~Vector(){
    delete arr;
    arr = nullptr;
}


template <class T>
T& Vector<T>::operator[](int idx){
    assert(idx>=0 && idx<size);
    return arr[idx];
}

template <class T>
int Vector<T>::get_size(){
    return size;
}

template <class T>
T Vector<T>::get_front(){
    return arr[0];
}

template <class T>
T Vector<T>::get_back(){
    return arr[size-1];
}

template <class T>
void Vector<T>::insert(int idx,T val){
    assert(idx>=0 && idx<size);
    if(size==capacity) expand_capacity();
    for(int i=size-1;i>=idx;i--){
        arr[i+1]=arr[i];
    }
    arr[idx]=val;
    size++;
}

template <class T>
void Vector<T>::expand_capacity(){
    capacity*=2;
    T *arr2= new T[capacity];
    for(int i=0;i<size;i++) arr2[i]=arr[i];
    swap(arr,arr2);
    delete arr2;
}

template <class T>
void Vector<T>::push_back(T val){
    if(capacity==size) expand_capacity();
    arr[size++]=val;
}

template <class T>
T Vector<T>::get(int idx){
    assert(idx>=0 && idx<size);
    return arr[idx];
}

template <class T>
void Vector<T>::set(int idx,T val){
    assert(idx>=0 && idx<size);
    arr[idx]=val;
}

template <class T>
int Vector<T>::find(T val){
    for(int i=0;i<size;i++){
        if(arr[i]==val) return i;
    }
    return -1;
}

template <class T>
void Vector<T>::print(){
    for(int i=0;i<size;i++) cout<<arr[i]<<" ";
    cout<<"\n";
}

template <class T>
Vector<T>::Vector(const Vector<T> & v){
    size=v.size;
    capacity=v.capacity;
    arr=new int[capacity];
    for(int i=0;i<size;i++) arr[i]=v.arr[i];
}


int main(){
    Vector<int> v;
    for(int i=0;i<20;i++) v.push_back(i);
    cout<<v[10]<<"\n";
    v[10]=1;
    v.print();
    Vector vv=v;
    vv[3]=100;
    vv.print();
    Vector<char>s;
    for(char ch='a';ch<='z';ch++){
        s.push_back(ch);
    }
    s.print();
}