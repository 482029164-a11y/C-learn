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
};
linknode* delx(linknode*r,int x){
	if(r==NULL){
		return NULL;
	}
	if(r->data==x){
		linknode*p=r->next;
		delete r;
		return p;
	}
	else{
		r->next=delx(r->next,x);
		return r;
	}
}
linknode* delallx(linknode*r,int x){
	if(r==NULL){
		return NULL;
	}
	if(r->data==x){
		linknode*p=r->next;
		delete r;
		// 【绝对核心修改点】
        // 不要直接 return p; 
        // 必须让剩下的链路 p 继续接受递归引擎的洗礼！
        return delallx(p, x);
	}
	else{
		r->next=delallx(r->next,x);
		return r;
	}
}
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
	l.print();
	int max=getmax(l.head);
	int min=getmin(l.head);
	cout<<max<<min;
}  
