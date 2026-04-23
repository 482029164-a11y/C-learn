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

int getmax(linknode* r) {
	if(r==NULL){
		return 0;
	}
	if(r->next==NULL){
		return r->data;
	}
	int max=getmax(r->next);
    if(r->data>=max){
    	return r->data;
	}
	return max;
}
int getmin(linknode* r){
		if(r==NULL){
		return 0;
	}
		if(r->next==NULL){
		return r->data;
	}
	int min=getmin(r->next);
    if(r->data<=min){
    	return r->data;
	}
	return min;
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
