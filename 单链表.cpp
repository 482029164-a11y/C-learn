//单链表
#include<iostream>
using namespace std;
template<typename T>
struct linknode{
	T data;//因为数据的具体类型不知道，所以用模板来写
	linknode<T>* next;//创建后继结点
	linknode():next(NULL){
	}//为了方便后面创造头节点，头结点无需创造数据 
	linknode(T d):data(d),next(NULL){
	}//重载构造函数 
};//这种构造函数的形式必须会看 
template<class T>
class linklist{
	public:
		linknode<T>* head;
		linklist(){
			head=new linknode<T>(); 
		}//构造函数创造一个新的空链表
		~linklist(){
			linknode<T>* pre,* p;
			pre=head;p=pre->next;
			while(p!=NULL){
				delete pre;
				pre=p;
				p=p->next;
			}//判断条件的意思就是当pre为最后一个结点
			delete pre; 
		} //析构函数 
		void add(T e){
			linknode<T>* E=new linknode<T>(e);
			linknode<T>* p=this->head;
			while(p->next!=NULL){
				p=p->next;
			}
			p->next=E;//在末尾节点插入 
		}//添加元素
		int getlength(){
			int i=0;
			linknode<T>* p=this->head;
			while(p->next!=NULL){
				p=p->next;
				i++;
			}
			return i;
		} //获取链表的长度（我的做法居然和书上一样） 
		bool getelem(int i,T&e){
			if(i>=this->getlength()||i<0){
				return false;
			}
			linknode<T>* p=this->head;
			int cnn=-1;//记录此时链表的下标 
			while(p->next!=NULL){
				if(cnn==i){
					e=p->data;
					return true;
				}
				p=p->next;
				cnn++; 
			}
			
		}//求链表中序号为i的节点值
		linknode<T>* geti(int i) {
    		if (i < -1) return NULL; // 客观保护：索引不能为负数

   			 linknode<T>* p = this->head;
    		int j = -1; // 当前 p 指向的结点的序号

    		// 条件：p 不为空，且还没走到我们要的序号 i
    		while (p != NULL && j < i) {
        		p = p->next; // 【核心修正】：让指针跳向下一个结点
        		j++;         // 计数器同步增加
    		}

    		// 循环结束有两种可能：
    		// 1. 找到了（j == i），返回 p
    		// 2. 没找到（p 提前变空了，说明 i 超出了链表长度），返回 nullptr
    		return p; 
			} //求链表序号为i的结点 
		void createlistf(T a[],int n){
			for(int i=0;i<n;i++){
				linknode<T>* s=new linknode<T>(a[i]);
				s->next=this->head->next;
				this->head->next=s;	
			}
		}//头插法，创建链表 
		void createlistr(T a[],int n){
			linknode<T>* r=this->head;//因为一开始末尾结点就是头结点，所以这样初始化 
			for(int i=0;i<n;i++){
				linknode<T>* s=new linknode<T>(a[i]);
				r->next=s; 
				r=s;//把末尾结点换成s 	 
			}
		}//尾插法 
		void insert(int i,T e){
			linknode<T>* r=geti(i-1);
			linknode<T>* s=new linknode<T>(e);
			s->next=r->next;
			r->next=s;
		}//插入新元素,删除元素同理，我就不写了 
		void print(){
			int n=this->getlength();
			for(int i=0;i<n;i++){
				linknode<T>* temp=this->geti(i);
				cout<<temp->data<<" ";
			}
			cout<<endl; 
		} //打印所有元素 
};
//下面是一些算法设计
//1.有一个长度大于2整数单链表，设计一个算法查找L中的中位数，有两种解法，计数法和快慢指针法
int middle1(linklist<int>l){
	int n=l.getlength();//获取链表的长度
	int e;
	if(l.getelem(n/2,e)){
		return e;
	}
	return -1;
} //计数法
int middle2(linklist<int>l)
{
	if(l.head->next==NULL){
		return -1;
	}
	linknode<int>* p1=l.head;//快指针 
	linknode<int>* p2=l.head;//慢指针 
	while(p1!=NULL&&p1->next!=NULL){
		p1=p1->next->next;
		p2=p2->next; 
	}
	return p2->next->data;
 } //快慢指针 
//2.寻找整数列表中的最大值的个数 
int selectmax(linklist<int>l){
	linknode<int>*p=l.head->next;//创造首结点 
	int cnn=1;//记录最大数的个数
	while(p->next!=NULL){
		if(p->data==p->next->data){
			cnn++;
		}
		if(p->data<p->next->data){
			cnn=1;
		}
		p=p->next;
	} 
	return cnn;
}//这里是书上的想法，只需要遍历一次链表
 
//3.整数单链表，删除链表中的所有的最大值的结点 
void deletemax(linklist<int>& l) {
    // 1. 客观保护：空表直接退场
    if (l.head->next == NULL) return;

    linknode<int>* p = l.head->next;
    int maxVal = p->data; 

    // 第一趟：寻找最大值
    while (p != NULL) {
        if (p->data > maxVal) {
            maxVal = p->data;
        }
        p = p->next;
    }//应该和max比较 

    // 2. 【核心修正】：重新复位指针，准备第二次扫描
    p = l.head->next;
    linknode<int>* pre = l.head;

    // 第二趟：删除所有等于 maxVal 的结点
    while (p != NULL) {
        if (p->data == maxVal) {
            pre->next = p->next;
            delete p;
            p = pre->next; // 删完后，p 指向新的后继，pre 保持不动
        } else {
            pre = p;       // 没删，两个指针一起同步后移
            p = p->next;
        }
    }
} //书上的想法和我一样 


//基于整体建立单链表的算法设计
//头插法逆置
void reverse(linklist<int>&l){
	linknode<int>*p=l.head->next;//p变成首结点 
	l.head->next=NULL;//将L变成空表 
	while(p!=NULL){
	 linknode<int>*q=p->next;//这里不存储的话，后面就会发生改变 
	 p->next=l.head->next;
	 l.head->next=p;	
	 p=q;	
	}
}  
//有序单链表的算法设计
//两个整数单链表归并到C去
void merge(linklist<int>&A, linklist<int>&B, linklist<int>& C) {
    linknode<int>* p1 = A.head->next;
    linknode<int>* p2 = B.head->next;
    linknode<int>* r = C.head;

    // 1. 修正语法 &&
    while (p1 != NULL && p2 != NULL) {
        // 2. 修正逻辑漏洞：使用 <= 处理相等情况，避免丢节点；使用 else 互斥
        if (p1->data <= p2->data) {
            r->next = p1;
            r = p1;
            p1 = p1->next;
        } else {
            r->next = p2;
            r = p2;
            p2 = p2->next;
        }
    }

    // 3. 终极优化：不需要用 while 一个个挪！
    // 既然剩下的那条链表本身就是连好的，直接把头挂上去就行了
    if (p1 != NULL) {
        r->next = p1;
    }
    if (p2 != NULL) {
        r->next = p2;
    }
}
int main(){
	int arr[12]={1,2,3,4,5,6,7,8,8,8,8,8};
	int arr1[3]={1,18,33};
	linklist<int> list1;
	linklist<int> list2;
	linklist<int> list3;
	list1.createlistr(arr,12);
	list2.createlistr(arr1,3);
	merge(list1,list2,list3);
//	cout<<middle2(list1);
//cout<<selectmax(list1);
//deletemax(list1);
//list1.print();
//reverse(list1);这里运行的话，会影响下面的操作 
list3.print();
} 
//leetcode 题目：给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。 
//class Solution {
//public:
//    ListNode* swapPairs(ListNode* head) {
//        // 1. 创建一个虚拟头结点，指向真实的 head
//        // 这样所有的结点（包括第一个）就都有了“前驱结点”
//        ListNode* dummy = new ListNode(0);
//        dummy->next = head;
//        
//        // prev 始终指向准备交换的两个结点的前一个结点
//        ListNode* prev = dummy;
//        
//        // 客观条件：必须保证后面确实有两个结点可以交换
//        while (prev->next != nullptr && prev->next->next != nullptr) {
//            // 锁定要交换的两个结点
//            ListNode* node1 = prev->next;
//            ListNode* node2 = prev->next->next;
//            
//            // --- 核心交换逻辑（必须按顺序连线，防止断链） ---
//            prev->next = node2;       // 步骤 1：让前面的结点指向第二个
//            node1->next = node2->next; // 步骤 2：让第一个结点指向第三个
//            node2->next = node1;       // 步骤 3：让第二个结点反身指向第一个
//            // ----------------------------------------------
//            
//            // 步进：把 prev 挪到下一对要交换的结点的前面（即现在的 node1）
//            prev = node1;
//        }
//        
//        // 记录新的真实头结点
//        ListNode* newHead = dummy->next;
//        
//        // 客观操守：自己 new 出来的虚拟结点，用完必须 delete，防止内存泄漏
//        delete dummy; 
//        
//        return newHead;
//    }
//};
