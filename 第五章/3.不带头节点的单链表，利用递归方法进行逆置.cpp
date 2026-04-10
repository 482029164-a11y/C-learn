#include<iostream>
using namespace std;
#include<string>
#include<sstream> 
class linknode{
	public:
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
			head=NULL;
		}
		void creat(int a[],int n){
			head=new linknode(a[0]);
			linknode*rear=head;
			linknode*p;
			for(int i=1;i<n;i++){
				p=new linknode(a[i]);
				rear->next=p;
				rear=p;
			}
		}
		void print(){
			linknode*p=head;
			while(p!=NULL){
				cout<<p->data<<" ";
				p=p->next;
			}
			cout<<endl;
		}
		linknode* r(linknode* p){
			if(p==NULL||p->next==NULL){
				return p;
			}
			else{
				linknode*s=r(p->next);
				p->next->next=p;
				p->next=NULL;
				return s;
			}
		}//永远返回的是逆置之后的头节点，逆置之后的头节点实际上是通过f(n-1)得来的； 
		void reverse(){
			head=r(head);
		}
};
int main(){
	int arr[1000]={}; 
	string line;
	getline(cin,line);
	stringstream ss(line);
	int i=0;
	int x;
	while(ss>>x){
		arr[i]=x;
		i++;
	} 
	linklist l;
	l.creat(arr,i);
	linknode*s=l.head;
	l.print();
	l.reverse();
	l.print();
} 
