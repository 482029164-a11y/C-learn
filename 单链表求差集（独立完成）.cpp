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
		void createlistr(int a[],int num){
			linknode*r=head;
			for(int i=0;i<num;i++){
				linknode*s=new linknode(a[i]);
				r->next=s;
				r=s;
			}
			r->next=NULL;
		}
		void print(){
			linknode*r=head->next;
			while(r!=NULL){
				cout<<r->data<<" ";
				r=r->next;
			}
		}
};
void getDiff(linklist&a,linklist&b,linklist&c){
	linknode*p=a.head->next;
	linknode*q=b.head->next;
	linknode*r=c.head;
	while(p!=NULL&&q!=NULL){
		if(p->data==q->data){
			p=p->next;
			q=q->next;
		}//如果两个相同都往前走一步 
		else{
			if(q->next!=NULL){
				linknode*temp=q;
				q=q->next;
				while(q!=NULL){
					if(p->data==q->data){
						break;
					}
					q=q->next;
				}
				if(q==NULL){
				q=temp;
				r->next=p;
				r=p;
				p=p->next;
				}
			}//如果不同，且当前q不是最后一个元素就要往后遍历，只要找到相同的就结束，否则将p存进c，p往前走一步 
			else{
			r->next=p;
			r=p;
            p=p->next;	
			}//如果不同，但是q是最后一个元素了，就不需要遍历了，直接存入c就行了 
		}
	}
	while(p!=NULL){
		r->next=p;
		r=p;
		p=p->next;
	}
	r->next=NULL;
}
int main(){
int na=0;
int nb=0;
int arr1[1000]={};
int arr2[1000]={};
linklist l1;
linklist l2;
linklist l3;
int i=0;
while(cin>>arr1[i]){
	char c=cin.get();
	if(c=='\n'||c=='\r'){
		break;
	}
	i++;
}
na=i+1;	
int j=0;
while(cin>>arr2[j]){
	char c=cin.get();
	if(c=='\n'||c=='\r'){
		break;
	}
	j++;
}
nb=j+1;	
l1.createlistr(arr1,na);
l2.createlistr(arr2,nb);
getDiff(l1,l2,l3); 
l3.print();
} 
