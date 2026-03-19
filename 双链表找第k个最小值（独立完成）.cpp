#include<iostream>
using namespace std;
struct linknode{
	int data;
	linknode*next;
	linknode*prior;
	linknode(){
		next=NULL;
		prior=NULL;
	}
	linknode(int d){
		data=d;
		next=NULL;
		prior=NULL;
	}
};
class linklist{
	public:
		linknode*head;
		linklist(){
			head=new linknode();
		}
		void createlistr(int a[],int num){
			linknode*r=this->head;
			for(int i=0;i<num;i++){
				linknode*s=new linknode(a[i]);
				s->prior=r;
				r->next=s;
				r=s;
			}
			r->next=NULL;
		}
};
int my_select(linklist&a,linklist&b,int k){
	linknode*p=a.head->next;
	linknode*q=b.head->next;
	int i=1;
	while(p!=NULL&&q!=NULL){
		if(p->data<=q->data){
			if(i==k){
			return p->data;
			}
			p=p->next;
			i++;
		}
		else{
			if(i==k){
			return q->data;
			}
			q=q->next;
			i++;
		}
	}
	while(p!=NULL){
		if(i==k){
			return p->data;
		}
		p=p->next;
		i++;
	}
	while(q!=NULL){
		if(i==k){
			return q->data;
		}
		q=q->next;
		i++;
	} 
	return 0;
}
int main(){
	linklist l1;
	linklist l2;
	linklist l3;
	int m=0;
	int n=0;
	cin>>m>>n;
	int *arr1=new int[m];
	int *arr2=new int[n];
	int k;
	for(int i = 0; i < m; i++){
        cin >> arr1[i];
    }
	for(int j = 0; j < n; j++){
        cin >> arr2[j];
    }
	l1.createlistr(arr1,m);
	l2.createlistr(arr2,n);
	
	cin>>k;
	cout<<my_select(l1,l2,k);
}
