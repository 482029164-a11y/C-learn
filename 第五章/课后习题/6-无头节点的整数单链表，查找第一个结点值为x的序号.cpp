#include<iostream>
using namespace std;
#include<string>
#include<sstream> 
//这题如果允许加上Index为参数是很简单的，重点是不让带index参数，要学把距离转化为index 
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
			head=NULL;
		}
		void creat(int a[],int n){
			head=new linknode(a[0]);
			linknode*rear=head;
			linknode*p;
			for(int i=1;i<n;i++){
				p=new linknode(a[i]);
				rear->next=p;
				rear=p;
			}
		}
		void print(){
			linknode*p=head;
			while(p!=NULL){
				cout<<p->data<<" ";
				p=p->next;
			}
			cout<<endl;
		}
};
// 剥离了 index 参数的绝对纯净版递归
int getno(linknode* r, int x) {
    // 1. 绝对物理防线：如果当前节点为空（走到了链表尽头依然没找到）
    // 返回 -1 作为底层失败信号
    if (r == NULL) {
        return -1;
    }
    
    // 2. 命中目标：在当前内存锚点找到了 x
    // 相对于当前节点的偏移量绝对为 0
    if (r->data == x) {
        return 0;
    }
    
    // 3. 递归推进：询问后续的物理链路，x 在哪个位置
    int sub_index = getno(r->next, x);
    
    // 4. 信号拦截与回溯累加
    // 如果底层的物理链路返回了失败信号（-1），绝对不能加 1，必须将原生的 -1 继续向上抛出
    if (sub_index == -1) {
        return -1;
    } 
    // 如果底层找到了，那么相对于当前节点的真实物理距离，必然是底层的相对距离 + 1
    else {
        return sub_index + 1;
    }
}	
int main(){
	int arr[1000]={}; 
	string line;
	getline(cin,line);
	stringstream ss(line);
	int i=0;
	int x;
	while(ss>>x){
		arr[i]=x;
		i++;
	} 
	linklist l;
	l.creat(arr,i);
	l.print();
	int num=getno(l.head,2);
	cout<<num;
} 
