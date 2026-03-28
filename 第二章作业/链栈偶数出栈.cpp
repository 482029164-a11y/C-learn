#include<iostream>
#include<string>
#include<sstream>
using namespace std;
class linknode{
	public:
		int data;
		linknode*next;
		linknode(){
			next=NULL;
		}
		linknode(int d){
			data=d;
		}
};
class linkstack{
	public:
		linknode*head;
		int count;
		linkstack(){
			head=new linknode();
			count=0;
		}
		bool empty(){
			return head->next==NULL;
		}
		void push(int x){
			linknode*s=new linknode(x);
			s->next=head->next;
			head->next=s;
			count++;
		}
		bool pop(int &e){
			if(empty()){
				return false;
			}
			else{
				e=head->next->data;
				linknode*temp=head->next->next;
				delete head->next;
				head->next=temp;
				count--;
				return true;
			}
		}
		bool gettop(int &e){
			if(empty()){
				return false;
			}
			else{
				e=head->next->data;
				return true;
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
void oushu(linkstack&a,linkstack&b){
	linkstack l2;
	linknode*p=a.head->next;
	linknode*pre=a.head;
	while(p!=NULL){
		if(p->data%2==0){
			l2.push(p->data);
			pre->next=p->next;
			delete p;
			p=pre->next;
		}
		else{
			pre=p;
			p=p->next;
		}
	}
	int temp=0;
	while(!l2.empty()){
		l2.pop(temp);
		b.push(temp);
	}
} 
int main(){
	int num;//栈中的个数
	cin>>num;
	int arr[num]={};
	cin.ignore();
	string line;
	getline(cin,line);
	stringstream ss(line);
	int x;
	int i=0;
	while (ss>>x){
		arr[i]=x;
		i++;
	}
	linkstack l1;
	linkstack l2;
	for(i=num-1;i>=0;--i){
		l1.push(arr[i]);
	}
	oushu(l1,l2);
	l2.print();
	l1.print();
}
