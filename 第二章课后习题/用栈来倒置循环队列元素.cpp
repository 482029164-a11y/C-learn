#include<iostream>
#include<string>
#include<sstream>
#include<stack>
using namespace std;
const int maxsize=1000;
//因为题目明确要求我用循环队列，所以我这里就不用STL版的了 
class cque{
public:
    int front;
    int rear;
    int max;
    int length;
    int* data;
    
    cque(){
        front=0;
        rear=0;
        length=0;
        max=maxsize;
        data=new int[max];
    }
    // 【物理修正 1】：绝对不可省略的内存回收
    ~cque(){
        delete[] data; 
    }
    
    bool empty(){
        return length==0;
    } 
    void push(int x){
        if(length==max){
            return;
        }
        data[rear]=x;
        rear=(rear+1)%max;
        length++;
    }
    void pop(){
        if(empty()){
            return;
        }
        front=(front+1)%max;
        length--;
    }
    // 【物理修正 2】：队列只有队首，没有栈顶
    void getfront(int &e){ 
        if(empty()){
            return;
        }
        e=data[front];
    }
    void createque(int a[],int n){
        for(int i=0;i<n;i++){
            push(a[i]);
        }
    }
    void print(){
        int i=front;
        while(i!=rear){
            cout<<data[i]<<" ";
            i=(i+1)%max;
        }
        cout<<endl;
    }   
}; 

int main(){
    int arr[1000]={};
    string line;
    getline(cin,line);
    stringstream ss(line);
    int x=0;
    int i=0;
    while(ss>>x){
        arr[i]=x;
        i++;
    }
    cque c1;
    c1.createque(arr,i);
    c1.print();
    
    stack<int>s1;
    int e;
    
    // 队列倾倒进栈
    while(!c1.empty()){
        c1.getfront(e); // 使用正确的物理命名
        c1.pop();
        s1.push(e);
    }
    
    // 栈倾倒回队列
    while(!s1.empty()){
        e=s1.top();
        s1.pop();
        c1.push(e);
    }
    c1.print();
    
    return 0;
}
