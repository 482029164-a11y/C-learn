//去看cin是怎么操作的，免得上机不会 
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
		}//构造函数，初始化头结点 
	void createlistr(int a[],int n){
		linknode*r=this->head;
		for(int i=0;i<n;i++){
			linknode*s=new linknode(a[i]);
			r->next=s;
			r=s;
		}
	}
	void print(){
		if(this->head->next==NULL){
			cout<<"error";
		}
		linknode*p=this->head->next;
		while(p!=NULL){
			cout<<p->data<<" ";
			p=p->next;
		}
	}//空格打印 
};
void merge(linklist&a,linklist&b,linklist&c){
	linknode*p=a.head->next;
	linknode*q=b.head->next;
	c.head->next=NULL;
	while(p!=NULL&&q!=NULL){
		if(p->data<q->data){
			p=p->next;
		}
		else if(p->data>q->data){
			q=q->next;
		}
		else if(p->data==q->data){
			linknode*temp= p->next;
			p->next=c.head->next;
			c.head->next=p;
			p=temp;
			q=q->next;
		}
	}//二路归并加上头插法 
	linknode*curr=c.head->next;
	linknode*pre=c.head;
	while(curr!=NULL&&curr->next!=NULL){
		if(curr->data==curr->next->data){
			pre->next=curr->next;
			delete curr;
			curr=pre->next;//pre已经前移动了 
		}//while的条件不要写反，否则会短路 
		else{
		pre=pre->next;
		curr=pre->next;
		}
	}//去重操作 
}
int main(){
	linklist list1;
	linklist list2;
	linklist list3;
	int arr1[1000]={};
	int arr2[1000]={};
	int na=0;
	int nb=0;
	while(cin>>arr1[na]){
		na++;
		char c=cin.get();
		if(c=='\n'||c=='\r'){
			break;
		}
	}
	list1.createlistr(arr1, na);
	while(cin>>arr2[nb]){
		nb++;
		char c=cin.get();
		if(c=='\n'||c=='\r'){
			break;
		}
	}
	list2.createlistr(arr2, nb);
	merge(list1,list2,list3);
	list3.print();
} 
