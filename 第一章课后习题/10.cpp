//整数单链表，负整数移到前面去
//注意特殊情况，紧跟着的时候不要换位置 
//时间复杂度n,空间复杂度1 
#include<iostream>
using namespace std;
class linknode{
	public:
		int data;
		linknode*next;
		linknode(){
			next=NULL;
		}
		linknode(int d){
			next=NULL;
			data=d;
		}
}; 
class linklist{
	public:
	linknode*head;
	linklist(){
		head=new linknode();
	} 
	void createlistr(int a[],int n){
		linknode*r=head;
		for(int i=0;i<n;i++){
			linknode*s=new linknode(a[i]);
			s->next=r->next;
			r->next=s;
			r=s;
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
	void my_sort(){
		linknode*p=head->next;
		linknode*pre=head;
		linknode*q=head;//q用来记录最后一个负数的位置 
		while(p!=NULL){
			if(p->data<0){
				if(pre==q){
					pre=p;
					q=p;
					p=p->next;
				} 
				else{
					pre->next=p->next;
					p->next=q->next;
					q->next=p;
					q=p;
					p=pre->next;
				}//这里要加else	
			}
			else{
			pre=pre->next;
			p=p->next;	
			}
		}
	} 
};
int main(){
	int arr[100]={};
	int n=0;
	while(cin>>arr[n]){
		n++;
		char c=cin.get();
		if(c=='\n'||c=='\r'){
			break;
		}
	}
	linklist l1;
	l1.createlistr(arr,n);
	l1.print();
	l1.my_sort();
	l1.print();
}
