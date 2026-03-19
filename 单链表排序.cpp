#include<iostream>
using namespace std;
struct linknode{
	int data;
	linknode*next;
	linknode(){
		next=NULL;
	}
	linknode(int d){
		data=d;
		next=NULL;
	}
};
class linklist{
	public:
		linknode*head;
		linklist(){
			head=new linknode();
		}
		void createlistr(int a[],int n){
			linknode*r=this->head;
			for(int i=0;i<n;i++){
				linknode*s=new linknode(a[i]);
				r->next=s;
				r=s;
			}
			r->next=NULL;
		}
		void print(){
			linknode*r=this->head->next;
			while(r!=NULL){
				cout<<r->data<<" ";
				r=r->next;
			}
		}
};
void mysort(linklist&a){
	linknode*q=a.head->next;
	if(q==NULL){
		return;
	}
	linknode*p=q->next;
	if(p==NULL){
		return;
	}
	q->next=NULL;
	while(p!=NULL){
			linknode*pre=a.head;
	q=p->next;
	while(pre->next!=NULL&&pre->next->data>p->data){
		pre=pre->next;
	}
	p->next=pre->next;
	pre->next=p;
	p=q;
	}
}//这里的一步要理解 
int main(){
	int a[5]={0,1,2,3,4};
	linklist l;
	l.createlistr(a,5);
	mysort(l);
	l.print();
} 
