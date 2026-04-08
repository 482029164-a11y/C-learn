//偶数位置元素移动到奇数位置之前，相对位置不要改变 
#include<iostream>
#include<sstream>
#include<string>
using namespace std;
template<class T>
class linknode{
public:
    T data;
    linknode<T>* next;
    linknode(){
        next = NULL;
    }
    linknode(T x){
        data = x;
        next = NULL;
    }
};

template<class T> 
class linkqueue{
public:
    linknode<T>* front;
    linknode<T>* rear;
    int count;

    linkqueue(){
        front = NULL;
        rear = NULL;
        count = 0; // 修复A：必须初始化
    }
    
    ~linkqueue(){
        linknode<T>* p = front;
        while(p != NULL){
            linknode<T>* temp = p->next;
            delete p;
            p = temp; 
        } 
    }
    
    void push(T x){
        linknode<T>* s = new linknode<T>(x);
        if(front == NULL){ // 修复B：正确的判空逻辑
            front = s;
            rear = s;
        }
        else{
            rear->next = s;
            rear = s;
        }
        count++;
    }
    
    bool empty(){
        return front == NULL; // 修复C配套：统一用 front 判空更安全
    }
    
    bool pop(T& x){
        if(empty()){
            return false;
        }
        else{
            x = front->data;
            linknode<T>* temp = front->next;
            delete front;
            front = temp;
            if(front == NULL) {
                rear = NULL; // 修复C：队列为空时同步置空 rear
            }
            count--;
            return true;
        } 
    }
    
    int getlength() {
        return count; 
    }
    
    bool gethead(T& e) {
        if (empty())
            return false;
        e = front->data; 
        return true;
    }
    
    void print(){
        linknode<T>* p = front;
        while(p != NULL){
            cout << p->data << " ";
            p = p->next; // 修复D：防止死循环
        }
        cout << endl;
    }
};
void change(linkqueue<int>& q) {
    int e;
    int l = q.getlength();
    linkqueue<int> q1; // 辅助队列：用来暂存奇数位置的元素

    for (int i = 0; i < l; i++) {
        q.pop(e); // 统一先出队
        
        // 【物理修正】：用索引 i 来判断物理位置，而不是用元素值 e
        // i=0 是第1个元素(奇数位)，i=1 是第2个元素(偶数位)
        if ((i + 1) % 2 == 0) { 
            q.push(e); // 偶数位置元素：留在主通道，排入队尾
        } else {
            q1.push(e); // 奇数位置元素：流入辅助通道 q1
        }
    } 
    
    // 阶段 2：通道合并（把辅助通道的奇数位元素，全部接在主通道后面）
    l = q1.getlength();
    for (int i = 0; i < l; i++) {
        q1.pop(e);
        q.push(e);
    }
}
int main(){
	 string line;
	 getline(cin,line);
	 stringstream ss(line);
	 int x;
	 linkqueue<int>q1;
	 while(ss>>x){
	 	q1.push(x);
	 }
	 q1.print();
	 change(q1);
	 q1.print();
} 
