#include<iostream>
using namespace std;
template<typename T>
struct linknode{
	T data;
	linknode<T>*next;//这种模板结构体指针也要先标出类型 
	linknode<T>*prior;
	linknode(){
		next=NULL;
		prior=NULL;
	} 
	linknode(T d){
		this->data=d;
		next=NULL;
		prior=NULL;
	} 
}; 
template<class T>
class linklist{
	public:
		linknode<T>*head;//定义头节点
		linklist(){
			head=new linknode<T>();//初始化头节点 
		} 
		bool my_insert(int i,T e){
			if(i<0){
				return false;
			}
			linknode<T>*s=new linknode<T>(e);
			linknode<T>*p=geti(i-1);
			s->next=p->next;
			s->prior=p;
			if(p->next!=NULL){
			p->next->prior=s;
			}
			p->next=s;
		} 
		bool my_delete(int i){
			if(i<0){
				return false;
			}
			linknode<T>*s=geti(i);
			if(s!=NULL){
							// 【动作 1：前驱节点断线重连】
			// 这一步是【无条件】的！不管 s 是不是最后一个，它前面的节点都得跨过它，指向它后面的东西
			s->prior->next = s->next; 

			// 【动作 2：后继节点断线重连】
			// 这一步才是【有条件】的！只有 s 后面有真实存在的节点时，才需要让后面的节点回头
			if (s->next != NULL) {
   				 s->next->prior = s->prior;
				}
				// 【动作 3：彻底销毁 s】
				delete s;
			}
						}
		void createlistf(T a[],int n){
			for(int i=0;i<n;i++){
				linknode<T>*s=new linknode<T>(a[i]);
				s->next=head->next;
				s->prior=head;
				if(head->next!=NULL){
					head->next->prior=s;//只有当后面不是空指针时它才需要回头 
				}
				head->next=s; 
			}
		}
		void createlistr(T a[],int n){
			linknode<T>*r=this->head;//将末尾结点初始为头节点 
			for(int i=0;i<n;i++){
				linknode<T>*s=new linknode<T>(a[i]);
				s->prior=r;
				r->next=s;
				r=s;
			}
			r->next=NULL; //为了安全着想 
		}
		linknode<T>* geti(int i){
			if(i<-1){
				return NULL;
			}
			if(i==-1){
				return this->head;
			}
			else{			
			linknode<T>*r=this->head;
			for(int j=0;j<=i;j++){
				r=r->next;
				if(r==NULL){
					return NULL;
				}
			}
			return r;
			}
		}  
};
//双链表算法设计
template<class T>
void delete_x(linklist<T>&list,T x){
	linknode<T>*r=list.head->next;//从首节点开始 
	while(r!=NULL){
		if(r->data==x){
			r->prior->next=r->next;
			if(r->next!=NULL){
				r->next->prior=r->prior;
			}
			delete r;
			break;
		}
		r=r->next;
	}
} 
//下面的题目为了方便我就设置成整型了 
void swap_x(linklist<int> &l,int x){
	linknode<int>*r=l.head->next;
	linknode<int>*q=NULL;
	while(r!=NULL){
		if(r->data==x){
			q=r;
		}
		r=r->next;
	}
	if(q==NULL||q==l.head->next){
		return;
	}
	else{
		linknode<int>*pre=q->prior;
		pre->prior->next=q;
		if(q->next!=NULL){
			q->next->prior=pre;
		}
		pre->next=q->next;
		q->prior=pre->prior;
		pre->prior=q;
		q->next=pre;
			}
}
int main(){
	
} 
