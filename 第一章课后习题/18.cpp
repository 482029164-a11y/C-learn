//现在有一个带有头节点的循环双链表，某个结点的next指针是正常的，但是pre指针都指向NULL 
//修复所有结点的prior指针值 
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
			data=d;
			next=NULL;
			pre=NULL;
		}
};
class linklist{
	public:
		linknode*head;
		linklist(){
			head=new linknode();
			head->next=head;
			head->pre=head;
		}
void createlistr(int a[],int n){
    linknode*p=head;
    for(int i=0;i<n;i++){
        linknode*s=new linknode(a[i]);
        p->next=s;   // p 牵住新节点
        p=s;         // 【核心修正】：p 顺势走到最新的尾巴上
    }
    p->next=head;    // 【核心修正】：建完所有节点后，把最后的尾巴连回保安室，形成循环
}//人为制造困难 
		void xiufu(){
			linknode*p=head->next;
			linknode*prior=head;
			while(p!=head){
				p->pre=prior;
				p=p->next;
				prior=prior->next;
			}
			head->pre=prior;
		}
};
int main(){
	return 0; 
} 
