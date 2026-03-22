//题目要求：假设有一个带头节点的循环单链表A，不使用头节点删除该结点。
//绕一圈 
#include<iostream>
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
			next=NULL;
		}
};
class linklist{
	public:
		linknode*head;
		linklist(){
			head=new linknode();
			head->next=head;
		}
		void creater(int a[],int n){
			linknode*p=head;
			for(int i=0;i<n;i++){
				linknode*r=new linknode(a[i]);
				p->next=r;
				r->next=head;
				p=r;
			}
		}
		void print(){
			linknode*p=head->next;
			while(p!=head){
				cout<<p->data<<" ";
				p=p->next;
			}
			cout<<endl;
		}
		void delete_p(linknode* p){
    if(p == NULL) return; // 安全防线
    
    // 派出一个侦察兵，从 p 开始起跑
    linknode* pre = p;
    
    // 只要它的下一步不是 p，就一直跑
    // 当循环停下来时，pre 必定完美地站在了 p 的正身后！
    while(pre->next != p){
        pre = pre->next;
    }
    
    // 此时已经拿到了前驱节点 pre，执行标准的链表删除三步曲
    pre->next = p->next; // 1. 跨过 p
    delete p;            // 2. 物理销毁 p
}
};
int main(){
	int arr[3]={1,2,3};
	linklist l1;
	l1.creater(arr,3);
	l1.print();
} 
