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
void my_sort(linklist&list,int num){
	for(int i=0;i<num;i++){
	linknode*pre=list.head;
	linknode*curr=list.head->next;
		while(curr!=NULL&&curr->next!=NULL){
			if(curr->data>curr->next->data){
			linknode*temp1=curr->next->next;
			curr->next->next=curr;//这里已经更改了curr->next->next结点 ，因此前面的temp1有必要 
			pre->next=curr->next;
			curr->next=temp1;
			pre=pre->next;//交换之后curr去前面了，但是pre也要往前走
			}
			else{
				curr=curr->next;
				pre=pre->next;
			}
		}
	}
}
int main(){
	int n;
	cin>>n;//输入个数
	int arr[n]={};
	int i=0;
	while(cin>>arr[i]) {
		char c=cin.get();
		i++;
		if(c!=' '){
			break;
		}
	}
	linklist list;
	list.createlistr(arr,n);
	my_sort(list,n);
	list.print();
} 
