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
		void delete_chongfu(){
			linknode*q=head->next;//记录当前重复值 
			linknode*p=head->next->next;//从第二个结点开始 
			while(p!=NULL){
				if(p->data==q->data){
					linknode*temp=p->next;
					p->pre->next=p->next;
					if(p->next!=NULL){
					p->next->pre=p->pre;
					}
					delete p;
					p=temp;
				}
				else{
					q=p;
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
	l1.createlinkr(arr,n);
	l1.print();
	l1.delete_chongfu();
	l1.print();
} 
