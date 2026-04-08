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
			next=NULL;
			data=d;
		}
}; 
class lstack{
	public:
		linknode*head;
		lstack(){
			head=new linknode();
		}
		bool empty(){
			return head->next==NULL;
		}
		void push(int x){
			linknode* s=new linknode(x);
			s->next=head->next;
			head->next=s;
		}
		void gettop(int &x){
			if(empty()){
				return;
			}
			linknode*p=head->next;
			x=p->data;
		}
		void pop(int&x){
			if(empty())
			{
				return;
			}
			linknode*p=head->next;
			x=p->data;
			head->next=p->next;
			delete p;
		}
		void chu_k(int& x, int k) {
		    // 物理拦截：k 不合法，或者栈为空，直接拒绝执行
			    if (k <= 0 || empty()) {
			        return; 
			    }
			
			    linknode* pre = head;        // pre 站在哨兵节点
			    linknode* p = head->next;    // p 站在第 1 个真实元素（栈顶）
			    int i = 1;
			
			    // 阶段 1：双探子同步推进，寻找第 k 个节点
			    while (p != NULL && i < k) {
			        pre = p;        // pre 紧跟 p
			        p = p->next;    // p 往前走
			        i++;
			    }
			
			    // 阶段 2：边界防御，如果 p 掉下悬崖了，说明 k 超出了栈的长度
			    if (p == NULL) {
			        return; 
			    }
			
			    // 阶段 3：执行精准物理切除
			    x = p->data;             // 1. 提取数据
			    pre->next = p->next;     // 2. 物理跨越：前一个节点直接连向后一个节点
			    delete p;                // 3. 彻底销毁目标节点，防止内存泄漏
		}
};
int main(){
	return 0;
} 
