//这里的链式栈是用带头结点的单链表建立的，因为不带头结点的循环单链表push,pop函数调用时间复杂度都是O（n）
 
#include<iostream>
using namespace std;
template<typename T>
class linknode{
	public:
		T data;
		linknode<T>*next;
		linknode(){
			next=NULL;
		}
		linknode(T d){
			data=d;
			next=NULL;
		}
};//创造结点，这个和之前没有区别
template<class T>
class linklist{
	public:
		linknode<T>* head;
	linklist(){
		head=new linknode<T>();
	}
	~linklist(){
		linknode<T>*pre=head;
		linknode<T>*p=head->next;
		while(p!=NULL){
			delete pre;
			pre=p;
			p=p->next;
		}
		delete pre;
	}
	bool empty(){
		return head->next==NULL;
	}//判断是否为空
	void push(T e){
		linknode<T>*p=new linknode<T>(e);
		p->next=head->next;
		head->next=p;
	} //类似头插法
	void pop(T &e){
		if(empty()){
			return;
		}
		linknode<T>*p=head->next;
		e=p->data;
		head->next=p->next;
		delete p;
	}//删除栈顶元素 
	void gettop(T &e){
		if(empty()){
			return;
		}
		linknode<T>*p=head->next;
		e=p->data;
	}//获取栈顶元素
	void print() 
	{
		linknode<T>*p=head->next;
		while(p!=NULL){
			cout<<p->data<<" ";
			p=p->next;
		}
	}
};
//下面是一些算法设计
//设计一个算法利用栈的基本运算将一个整数链栈中所有元素逆置。
//void reverse(linklist<int>&a){
//	linklist<int>b;
//	linknode<int>*p=a.head->next;
//	linknode<int>*m=b.head;
//	while(p!=NULL){
//	b.push(p->data);
//	linknode<int>*q=p->next;
//	delete p;
//	p=q;	
//	}
//	m=m->next;
//	while(m!=NULL){
//		a.push(m->data);
//		m=m->next;//这里无需delete，因为b是临时变量，会自动释放内存 
//	}	 
//} //我一开始想让它原地逆序发现不能这么干
void reverse(linklist<int>&a){
	int temp[100]={};
	linknode<int>*p=a.head->next;
	int i=0;
	while(!a.empty()){
	int e;
	a.pop(e);
	temp[i]=e;
	i++;
	}
	for(int j=0;j<i;j++){
		a.push(temp[j]);
	} 
}//知道必须用数组之后还是做出来了
//定义一个栈数据结构STACK，添加一个Getbottom()运算用于直接返回栈底元素（假设栈不空时）。
//要求采用链表实现并且函数Getbottom()、push以及pop的时间复杂度都是O(1)。
//我本人的想法，是只需要在插入第一个元素的时候记录一下就好，但是题目要求要使用尾结点的循环单链表
class stack{
	public:
		linknode<int>*rear;
	stack(){
		rear=NULL;//必须初始化rear; 
//		rear->next=rear;这里就不能要了 
	}
	void push(int e){
		linknode<int>*temp=new linknode<int>(e);
		if(empty()){
			rear=temp;
			rear->next=rear;
		}
		else{
		temp->next=rear->next;
		rear->next=temp;
		} 
	}
	void pop(int &e){
		if(empty()){
			return;
		}
		e=rear->next->data;
		linknode<int>*q=rear->next;
		rear->next=q->next;
		delete q;
	}//删除并返回栈顶元素 
	bool empty(){
		return rear==NULL;
	}
	void Getbottom(int &e){
		if(empty()){
			return;
		}
		e=rear->data;
	}//获取底部元素 
}; 
 

int main(){
	linklist<int> l1;
	int arr[3]={1,2,3};
	for(int i=0;i<3;i++){
		l1.push(arr[i]);
	} 
	l1.print();
	reverse(l1);
	l1.print();
	stack l2;
	for(int i=0;i<3;i++){
		l2.push(arr[i]);
	}
	int a;
	l2.Getbottom(a);
	cout<<a<<endl; 
} 
