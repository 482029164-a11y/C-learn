#include<iostream>
using namespace std;
#include<string>
#include<sstream>
//包含 N+1 行：

//第一行为一个正整数 N，对应于日志内所含操作的总数。

//接下来的 N 行，分别属于以下三种格式之一：

//格式 1：0 X，表示一次集装箱入库操作，正整数 X 表示该次入库的集装箱的重量。

//格式 2：1，表示一次集装箱出库操作，（就当时而言）最后入库的集装箱出库。

//格式 3：2，表示一次查询操作，要求分析程序输出当前仓库内最大集装箱的重量。

//当仓库为空时你应该忽略出库操作，当仓库为空查询时你应该输出 0。

//输出格式
//输出行数等于日志中查询操作的次数。每行为一个整数，表示查询结果。
//任务分析：由于是先进后出，符合栈的特点，因此用栈解决
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
class mystack{
	public:
		linknode*head;
		mystack(){
			head=new linknode();
		}
		void push(int x){
			linknode*s=new linknode(x);
			s->next=head->next;
			head->next=s;
		}
		bool empty(){
			return head->next==NULL;
		}
		bool pop(int &e){
			if(empty()){
				return false;	
			}
			linknode*p=head->next;
			e=p->data;
			head->next=p->next;
			delete p;
			return true;
		}
		bool gettop(int &e){
			if(empty()){
				return false;	
			}
			e=head->next->data;
			return true;
		}
};
int main() {
    int n;
    // 如果没有读到总数，直接结束
    if (!(cin >> n)) return 0; 
    
    int cmd;
    int x; 
    int e;
    mystack s1; // 仓库栈
    mystack s2; // 最大重量栈 
    
    for (int i = 1; i <= n; ++i) {
        cin >> cmd; // 读取操作码
        
        if (cmd == 1) { 
            // 出库操作
            if (s1.pop(e)) {
                s2.gettop(x);
                if (e == x) {
                    s2.pop(x); // 如果出库的刚好是最大值，辅助栈也要同步出库
                }
            }
        } 
        else if (cmd == 2) { 
            // 查询操作
            if (s2.gettop(x)) {
                cout << x << endl;
            } else {
                cout << 0 << endl; // 仓库为空时输出 0
            }
        } 
        else if (cmd == 0) { 
            // 入库操作
            cin >> x; // 核心：碰到 0 操作，立刻接着读取后面的重量 X
            
            s1.push(x); // 主仓库必然要入库
            
            // 维护辅助最大值栈
            if (s2.empty()) {
                s2.push(x);
            } else {
                s2.gettop(e);
                if (x >= e) {
                    s2.push(x); // 只有新来的重量大于等于当前最大值，才入最大重量栈
                }
            }
        }
    } 
    return 0;
}
