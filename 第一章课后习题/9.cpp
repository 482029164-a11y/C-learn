//整数单链表，删除所有值为x的结点，给出时空复杂度
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
	void delete_x(int x){
		linknode*p=head->next;
		linknode*pre=head;
		while(p!=NULL){
			if(p->data==x){
				pre->next=p->next;
				delete p;
				p=pre->next;
			}
			else{
				p=p->next;
				pre=pre->next;
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
	l1.delete_x(2);
	l1.print();
}
