//设计一个算法判断一个串是否是X@X的形式，x代表任意长度的字符串 
#include<iostream>
#include<string>
#include<sstream>
using namespace std;
class linknode{
	public:
		char data;
		linknode*next;
		linknode(){
			next=NULL;
		}
		linknode(char c){
			data=c;
			next=NULL;
		}
};
class mystring{
	public:
		linknode*head;
		linknode*r;
		int length;
		mystring(){
			head=new linknode();
			r=head;
			length=0;
		}
		void createstring(char a[],int num){
			linknode*s;
			for(int i=0;i<num;i++){
				s=new linknode(a[i]);
				r->next=s;
				r=s;
				length++;
			}
		}
		void print(){
			linknode*p=head->next;
			while(p!=NULL){
				cout<<p->data;
				p=p->next;
			}
			cout<<endl;
		}
		~mystring(){
			linknode*p=head;
			while(p!=NULL){
				linknode*t=p->next;
				delete p;
				p=t;
			}
			delete p;
		}
};
bool panduan(mystring& s) {
	if(s.length%2==0){
		return false;	
	}
   int i=0;
   linknode*p=s.head->next;
   while(i<s.length/2){
   	p=p->next;
   	++i;
   } 
   if(p->data!='@'){
   	return false;
   }
   ++i;
   p=p->next;
   linknode*m=s.head->next;
   while(p!=NULL){
   	if(p->data!=m->data){
   		return false;
	   }
	   p=p->next;
	   m=m->next;
   }
   return true;
}
int main(){
	char a[1000]={};
	int i=0;
	char x;
	string line;
	getline(cin,line);
	stringstream ss(line);
	while(ss>>x){
		a[i]=x;
		i++;
	}
	mystring s1;
	s1.createstring(a,i);
	s1.print();
cout<<panduan(s1);
} 
