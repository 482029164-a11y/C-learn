//两个递增单链表变成递减合并，原先的不变 
//空间复杂度是M+N
//时间复杂度是 M+N
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
void dijian(linklist&a,linklist&b,linklist&c){
	linknode*p=a.head->next;
	linknode*q=b.head->next;
	linknode*f=c.head;//因为要逆序所以采用头插法 
	while(p!=NULL&&q!=NULL){
		if(p->data<=q->data){
			linknode*temp=new linknode(p->data);
			temp->next=f->next;
			f->next=temp;
			p=p->next;
		}
		else if(p->data>q->data){
			linknode*temp=new linknode(q->data);
			temp->next=f->next;
			f->next=temp;
			q=q->next;	
		}
		
	}
	while(p!=NULL){
		linknode*temp=new linknode(p->data);
		temp->next=f->next;
		f->next=temp;
		p=p->next;
	}
	while(q!=NULL){
		linknode*temp=new linknode(q->data);
		temp->next=f->next;
		f->next=temp;
		q=q->next;	
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
dijian(l1,l2,l3);
	l3.print();
}
