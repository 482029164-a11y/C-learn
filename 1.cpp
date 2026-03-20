//题目要求:有一个递增有序的整数顺序表，设计一个算法将整数x插入后保持该表的有序性，并给出算法的时空复杂度
//时间复杂度是n,空间复杂度是1 
#include<iostream>
using namespace std;
const int inicap=5;
class sqlist{
	public:
		int* data;
		int capcity;
		int length;
	sqlist(){
		capcity=inicap;
		data=new int[capcity];
		length=0;
	}
	~sqlist(){
		if(data==NULL){
			return;
		}
		delete[]data;
		data=NULL;//不要有野指针 
		length=0;
	}
	void recap(int c){
		int *olddata=data;
		data=new int[c];
		for(int i=0;i<length;i++){
			data[i]=olddata[i];
		}
		delete[]olddata;
	} 
	void createlist(int a[],int num){
		for(int i=0;i<num;i++){
			if(length==capcity){
			recap(2*length);
			}
			data[i]=a[i];
			length++;
		}
	}
void push(int x) {
    // 只要满了，立刻扩容（注意：最好乘以 capcity，不要乘 length，防止起步为 0 的情况）
    if (length == capcity) {
        recap(2 * capcity); 
    }
    // 游标 j 站在最后一个有效数据上
    int j = length - 1; 
    
    // 只要 j 没越界，并且当前位置的数据比我要插入的 x 大
    while (j >= 0 && data[j] > x) {
        data[j + 1] = data[j]; // 把这个大的数字往后挪一格
        j--;                   // 游标继续往前看
    }
    
    // 循环停下来的那一刻，j 指向的数字一定 <= x
    // 那么 j + 1 就是 x 完美合法的插入坑位！
    data[j + 1] = x;
    
    // 【绝不遗漏的最后一步】
    length++; 
}
	void print(){
		for(int i=0;i<length;i++){
			cout<<data[i]<<" ";
		} 
		cout<<endl;
	}
};
int main(){
	int a[4]={1,2,3,4};
	sqlist l;
	l.createlist(a,4);
	l.print();
	l.push(6);
	l.print();
	
}
