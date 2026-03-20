//题目要求：把负整数移动到其他元素前面去，同样要求相对位置不变，最后给出时空复杂度 
#include<iostream>
using namespace std;
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
	void pop(int i){
		for(int j=i;j<length-1;j++){
			data[j]=data[j+1];
		}
		length--;
	}
void sort_none() {
    int k = 0; // k 永远指向下一个负数应该安放的正确坑位
    
    for (int i = 0; i < length; i++) {
        // 如果侦察兵 i 找到了一个负数
        if (data[i] < 0) {
            
            // 1. 先把这个负数暂存在口袋里，避免在平移时被踩踏覆盖
            int temp = data[i]; 
            
            // 2. 从 i 开始往回倒退，把 k 到 i-1 之间的所有正数，整体往右挪一格
            // 刚好把 k 这个坑位给腾出来
            for (int j = i; j > k; j--) {
                data[j] = data[j - 1];
            }
            
            // 3. 把口袋里的负数，安放到腾出来的 k 坑位上
            data[k] = temp;
            
            // 4. 负数队伍壮大了一名，分界线 k 往前推进一格
            k++; 
        }
        // 客观事实：如果 data[i] >= 0，侦察兵 i 直接往前走，什么都不用管。
    }
}
	void print(){
		for(int i=0;i<length;i++){
			cout<<data[i]<<" ";
		} 
		cout<<endl;
	}
};
int main(){
	
}
