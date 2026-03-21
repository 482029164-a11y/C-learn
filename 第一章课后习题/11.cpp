//两个单链表求并集 
//空间复杂度是1
//时间复杂度是m+n 
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
};
void binji(linklist&a,linklist&b,linklist&c){
	linknode*p=a.head->next;
	linknode*q=b.head->next;
	linknode*r=c.head;
	while(p!=NULL&&q!=NULL){
		if(p->data<q->data){
			linknode*temp=p->next;
			p->next=r->next;
			r->next=p;
			r=p;
			p=temp;
		}
		else if(p->data>q->data){
			linknode*temp=q->next;
			q->next=r->next;
			r->next=q;
			r=q;
			q=temp;	
		}
		else{
			linknode*temp=p->next;
			p->next=r->next;
			r->next=p;
			r=p;
			p=temp;
			q=q->next;
		}
	}
	if(p!=NULL){
		r->next=p;
	}
	else if(q!=NULL){
		r->next=q;
	}
} 
int main(){
	int arr[100]={};
	int n=0;
	int brr[100]={};
	int n1=0;
	while(cin>>arr[n]){
		n++;
		char c=cin.get();
		if(c=='\n'||c=='\r'){
			break;
		}
	}
	while(cin>>brr[n1]){
		n1++;
		char c=cin.get();
		if(c=='\n'||c=='\r'){
			break;
		}
	}
	linklist l1;
	l1.createlistr(arr,n);
	linklist l2;
	l2.createlistr(brr,n1);
	linklist l3;
	l1.print();
	l2.print();
binji(l1,l2,l3);
	l3.print();
}
