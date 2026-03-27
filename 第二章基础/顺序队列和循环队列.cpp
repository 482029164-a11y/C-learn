#include<bits/stdc++.h> 
//求循环队列的长度那里太重要了！！ 
using namespace std;
const int maxsize=5;
template<class T>
class sqqueue{
	public:
		T *data;
		int front;
		int rear;
		sqqueue(){
			front=-1;
			rear=-1;
			data=new T[maxsize];
		}
		~sqqueue(){
			delete[]data;
		}
		bool push(T x){
			if(rear>=maxsize-1){
				return false;
			}
			else{
				rear++;
				data[rear]=x;
			}
		}
		bool empty(){
			return front==rear;
		}
		bool pop(T&e){
			if(empty()){
				return false;
			}
			else{
				front++;
				e=data[front];
			}
		}
		bool gettop(T&e){
			if(empty()){
				return false;
			}
			int head=front+1;
			e=data[head];
			return true;	
		}
};//顺序队列
template<class T>
class csqueue{
	public:
		T* data;
		int front;
		int rear;
		csqueue(){
			data=new T[maxsize];
			front=0;
			rear=0;
		}
		~csqueue(){
			delete[]data;
		}
		bool empty(){
			return rear==front;
		}
		bool push(T x){
			if((rear+1)%maxsize==front){
				return false;//队列满了返回 
			}
			else{
				rear=(rear+1)%maxsize;
				data[rear]=x;
				return true; 
			} 
		}
		bool pop(T &e){
			if(empty()){
				return false;//队列是空的返回 
			}
			else{
				front=(front+1)%maxsize;
				e=data[front];
				return true;
			} 
		}
		bool getfront(T &e){
			if(empty()){
				return false;
			}
			int head=(front+1)%maxsize;
			e=data[head];
			return true;
		}
		int getlength() {		//返回队中元素个数

   			return (rear-front+MaxSize)%MaxSize;

		}
		bool insert_k(T e, int k) {
		    int num = getlegth(); // 沿用你代码中的函数名（注意拼写可能是 getLength）
		    
		    // 1. 检查队列是否已满
		    if (num == maxsize - 1) {
		        return false;
		    }
		    
		    // 2. 检查插入位置 k 是否合法 (只能在现有元素中间或末尾追加)
		    if (k < 1 || k > num + 1) {
		        return false;
		    }
		
		    // 3. 计算目标插入位置的物理下标
		    int target_idx = (front + k) % maxsize;
		
		    // 4. 将第 k 个元素及其后面的元素整体向后移动一位
		    // 从队列尾部开始移动，防止数据被覆盖
		    for (int i = num; i >= k; i--) {
		        int curr = (front + i) % maxsize;         // 当前元素的位置
		        int next = (front + i + 1) % maxsize;     // 要移动到的下一个位置
		        data[next] = data[curr];
		    }
		
		    // 5. 在目标位置插入新元素
		    data[target_idx] = e;
		
		    // 6. 更新尾指针
		    rear = (rear + 1) % maxsize;
		
		    return true;
		}
};//循环队列

//下面是一些算法设计
//1.在CSqQueue循环队列类中增加一个求元素个数的算法getlength()。
//2.对于一个整数循环队列qu，利用队列基本运算和getlength()算法设计进队和出队第k（k≥1，队头元素的序号为1）个元素的算法。

int main(){
	
}
