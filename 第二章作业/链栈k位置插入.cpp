#include<bits/stdc++.h>
using namespace std;
//这个题目需要注意的就是：1. count要初始化2.cin.ignore(),要把上次剩下的回车符去掉3.小细节：输出error之后还要输出原始链表 
class linknode{
	public:
		int data;
		linknode*next;
		linknode(){
			next=NULL;
		}
		linknode(int d){
			data=d;
		}
};
class linkstack{
	public:
		linknode*head;
		int count;
		linkstack(){
			head=new linknode();
			count=0;
		}
		bool empty(){
			return head->next==NULL;
		}
		void push(int x){
			linknode*s=new linknode(x);
			s->next=head->next;
			head->next=s;
			count++;
		}
		bool pop(int &e){
			if(empty()){
				return false;
			}
			else{
				e=head->next->data;
				linknode*temp=head->next->next;
				delete head->next;
				head->next=temp;
				count--;
				return true;
			}
		}
		bool gettop(int &e){
			if(empty()){
				return false;
			}
			else{
				e=head->next->data;
				return true;
			}
		}
		bool delete_k(int &e,int k){
			int i=1;
			if(k<=0||empty()||k>count){
				return false;
			}
			else{
				linknode*p=head->next;
				linknode*pre=head;
				while(i!=k){
					++i;
					pre=p;
					p=p->next;
				}
					e=p->data;
					pre->next=p->next;
					delete p;
					return true;	
			}
		}
		void print(){
			linknode*p=head->next;
			while(p!=NULL){
				cout<<p->data<<" ";
				p=p->next;
			}
			cout<<endl;
		}	
}; 
int main(){ 
int num;
string line;
cin>>num;//输入栈中的元素的个数
int arr[num]={};
cin.ignore();//这里是为了防止留在缓冲区的回车符号使得下次输不进去 
getline(cin,line);
stringstream ss(line); 
int x;
int i=0;
while(ss>>x){
	arr[i]=x;
	i++;
}
int k;//出去第几个元素 
cin>>k;	
linkstack l1;
for(i=num-1;i>=0;--i){
	l1.push(arr[i]);
}//反向插入 
int elem;//去接受第k个元素；
if(l1.delete_k(elem,k)){
	cout<<elem<<endl;
	l1.print();
}
else{
	cout<<"error"<<endl;
	l1.print(); 
} 
} 
