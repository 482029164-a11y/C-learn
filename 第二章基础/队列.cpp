#include<bits/stdc++.h> 
using namespace std;
const int MaxSize=100;
//不循环的顺序队列太常规了，就省略了 
template <class T>
class CSqQueue	{			//循环队队列类模板
public:
   T* data;  				//存放队中元素
   int front, rear;			//队头和队尾指针
   //队列的基本运算算法
   CSqQueue() {			//构造函数
   data=new T[MaxSize];	//为data分配容量为MaxSize的空间
   front=rear=0;		//队头队尾指针置初值
	}

	~CSqQueue() {			//析构函数
   		delete [] data;
	}
	bool empty() {			//判队空运算 
   		return (front==rear); 
	}
	bool push(T e)	{			//进队列运算
   		if ((rear+1)%MaxSize==front)	//队满上溢出
      	return false;
   		rear=(rear+1)%MaxSize;
  		data[rear]=e;
   	return true;
	}
	bool pop(T& e)	{		//出队列运算
   		if (front==rear)		//队空下溢出
      	return false;
   		front=(front+1)%MaxSize;
   		e=data[front];
   		return true;
	}
bool gethead(T& e) {		//取队头运算
   if (front==rear)		//队空下溢出
      return false;
   int head=(front+1)%MaxSize;
   e=data[head];
   return true;
}
int getlength() {		//返回队中元素个数
   return (rear-front+MaxSize)%MaxSize;
}
};
//下面是一些算法设计
//1.在第k个位置插入元素 e 
bool push_k(CSqQueue<int>& a,int k,int e){
	int num=a.getlength();
	if(k<1||k>n+1){
		return false;
	}
	else if(k<=n){
		for(int i=1;i<=n;i++){
			if(i==k){
				a.push(e);
			}
			int x;
			a.pop(x);
			a.push(x);
		}
	}
	else{
		a.push(e);
	}
	return true;
} 
int main(){
	
} 
