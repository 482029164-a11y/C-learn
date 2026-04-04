//设计一个算法删除一个链串中所有非重叠的“abc"字串
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
		int length;
		mystring(){
			head=new linknode();
			length=0;
		}
		void createstring(char a[],int num){
			linknode*r=head,*s;
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
};
bool shanchu_mainstream(mystring& s) {
    if (s.length < 3) {
        return false; // 物理防御：长度不够直接退出
    }

    // 主流核心：永远只维护一个处于绝对安全区的前驱指针 p
    linknode* p = s.head; 

    // 只要 p 后面还有 3 个未知节点，就可以继续侦察
    while (p->next != NULL && p->next->next != NULL && p->next->next->next != NULL) {
        
        // 伸出三个探子获取前方的物理视野 (极其关键：这不会改变 p 的位置)
        linknode* n1 = p->next;
        linknode* n2 = n1->next;
        linknode* n3 = n2->next;

        // 一次性无脑匹配
        if (n1->data == 'a' && n2->data == 'b' && n3->data == 'c') {
            
            // 物理断链：p 直接跨过 n1, n2, n3，连上后面的链条
            p->next = n3->next;

            // 物理超度：销毁垃圾内存
            delete n1;
            delete n2;
            delete n3;
            
            s.length -= 3;
            
            // 【极致的物理静止】：
            // 注意！这里绝对没有 p = p->next;
            // 删完之后 p 必须留在原地！因为新接上来的链条，
            // 有可能和后面的节点再次拼出一个 "abc"。
            // 让 p 留在原地，下一轮 while 会自动重新侦察。
            
        } else {
            // 只有明确前方不是 "abc" 时，前哨兵 p 才能往前走一步
            p = p->next;
        }
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
	shanchu_mainstream(s1);
	s1.print();
} 
