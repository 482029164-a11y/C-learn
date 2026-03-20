//题目要求：有一个整数顺序表L，删除其中所有负整数，删除后不改变元素之间的相对次序
//双游标覆盖法
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
	void pop(int i){
		for(int j=i;j<length-1;j++){
			data[j]=data[j+1];
		}
		length--;
	}
//	void delete_none(){
//		for(int i=0;i<length;i++){
//			if(data[i]<0){
//				pop(i);
//				i--;
//			}
//		}
//	}//我写的时间复杂度为n平方
	void delete_none(){
		int k=0;
		for(int i=0;i<length;i++){
			if(data[i]>=0){
				data[k]=data[i];
				k++;
			}
		}
		length=k;
	} //时间复杂度O(N)、空间复杂度 O(1) 的“双游标覆盖法”。
	void print(){
		for(int i=0;i<length;i++){
			cout<<data[i]<<" ";
		} 
		cout<<endl;
	}
};
int main(){
	int arr[4]={-1,-1,1,2};
	sqlist l1;
	l1.createlist(arr,4);
	l1.print();
	l1.delete_none();
	l1.print();
}
