//有序双链表（至少包含两个结点），删除重复值
//一定要注意最后一个元素删除的时候，不用再把下一个元素的pre改变了，因为下一个结点是空节点 
#include<iostream>
using namespace std;
class linknode{
	public:
		int data;
		linknode*next;
		linknode*pre;
		linknode(){
			next=NULL;
			pre=NULL;
		}
		linknode(int d){
			next=NULL;
			pre=NULL;
			data=d;
		}
};
class linklist{
	public:
		linknode*head;
		linklist(){
			head=new linknode();
		}
		void createlinkr(int a[],int n){
			linknode*r=head;
			for(int i=0;i<n;i++){
				linknode*s=new linknode(a[i]);
				r->next=s;
				s->pre=r;
				s->next=NULL;
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
int klist(linklist&a,linklist&b,int k){
	linknode*p=a.head->next;
	linknode*q=b.head->next;
	int e;//记录返回值
	int i=1;//记录循环次数 
	while(p!=NULL&&q!=NULL){
		if(p->data<=q->data){
			if(k==i){
				e=p->data;
				return e;
			}
			p=p->next;	
		}
		else{
			if(k==i){
				e=q->data;
				return e;
			}
			q=q->next;
		}
		i++;	
	}
	while(p!=NULL){
		if(k==i){
			e=p->data;
			return e;
		}
		p=p->next;
		i++;	
	}
	while(q!=NULL){
		if(k==i){
			e=q->data;
			return e;
		}
		q=q->next;
		i++;
	}
} 
int main(){
	int arr[100]={};
	int n=0;
	int arr1[100]={};
	int n1=0;
	int k;
	cin>>k;
	while(cin>>arr[n]){
		n++;
		char c=cin.get();
		if(c=='\n'||c=='\r'){
			break;
		}
	}
	while(cin>>arr1[n1]){
		n1++;
		char c=cin.get();
		if(c=='\n'||c=='\r'){
			break;
		}
	}
	linklist l1;
	l1.createlinkr(arr,n);
	linklist l2;
	l2.createlinkr(arr1,n1);
	l1.print();
	l2.print();
cout<<klist(l1,l2,k)<<endl;
} 
