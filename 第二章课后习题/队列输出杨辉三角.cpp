//对于给定的正整数 n,利用队列输出n阶杨辉三角
//利用队列中滑动窗口的思想 
#include<iostream>
#include<string>
#include<sstream>
using namespace std;
const int maxsize=1000;
class cque{
    // ... (你的 cque 类保持完全不动，物理结构是正确的)
public:
    int front;
    int rear;
    int max;
    int length;
    int* data;
    
    cque(){
        front=0; rear=0; length=0; max=maxsize;
        data=new int[max];
    }
    ~cque(){ delete[] data; }
    
    bool empty(){ return length==0; } 
    void push(int x){
        if(length==max) return;
        data[rear]=x;
        rear=(rear+1)%max;
        length++;
    }
    void pop(){
        if(empty()) return;
        front=(front+1)%max;
        length--;
    }
    void getfront(int &e){ 
        if(empty()) return;
        e=data[front];
    }
};

// 【核心物理修正】：真正的利用队列特性生成杨辉三角
void yanghui_by_queue(cque& q, int n) {
    // 放入第一行的基础元素 1，以及每一行的物理分隔符 0
    q.push(1);
    q.push(0);
	int left;//左肩
	int right;//右肩 
    for(int i=1;i<=n;i++){
    	left=0;//窗口的左肩默认为0
		q.getfront(right);//获取当前右肩，一开始的右肩是1，符合杨辉三角的结构 
		for(int j=0;j<n-i;j++){
			cout<<" ";
		} //杨辉三角结构存在空格 
		while(right!=0){
			cout<<right<<" ";
			q.push(right+left);//下一行第一个元素 
			left=right;//向右边滑动一格
			q.pop();//打印之后把这个元素踢掉,注意我们一直打印的是右边的元素 
			q.getfront(right); 
		}
		cout<<endl;//这次循环完之后记得换行 
		//循环结束之后，right到了分隔符0，此时进行当前大循环最后一次操作
		q.pop();//把这个分割符号去掉，以免影响下一次right的初始化 
		q.push(right+left);//在下一行补充了一个1
		q.push(0);//下一行末尾还有一个0 
	}
}

int main(){
    int n;
    // 增加防御，防范不合法的行数
    if(cin >> n && n > 0) {
        cque c1;
        yanghui_by_queue(c1, n);
    }
    return 0;
}
