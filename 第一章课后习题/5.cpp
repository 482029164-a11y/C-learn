//题目要求：两个有序顺序表求并级，并存到另一个表中 
//注意时刻把物理长度要维护 
//时空复杂度都是m+n 
#include<iostream>
using namespace std;
const int initcap=5;
class sqlist{
	public:
		int*data;
		int length;
		int cap;
	sqlist(){
		data=new int[initcap];
		length=0;
		cap=initcap;
	}
	~sqlist(){
		delete[]data;
		length=0;
		cap=0;
	}
	void recap(int c){
		if(c<=cap){
			return;
		}
		int*olddata=data;
		data=new int[c];
		for(int i=0;i<length;i++){
			data[i]=olddata[i];
		}
		delete[]olddata;
		cap=c;
	}
	void createlist(int a[],int num){
		if(length!=0){
			return;
		}
		else{
			for(int i=0;i<num;i++){
				if(length==cap){
					recap(2*length);
				}
				data[i]=a[i];
				length++;
			}
		}
	}
	void print(){
		for(int i=0;i<length;i++){
			cout<<data[i]<<" ";
		}
		cout<<endl;
	}
};
void binji(sqlist&a,sqlist&b,sqlist&c){
	int k1=0;
	int k2=0;
	int i=0;
	while(k1<a.length&&k2<b.length){
		if(c.length==c.cap){
			c.recap(2*c.length);
		}
		if(a.data[k1]<b.data[k2]){
			c.data[i]=a.data[k1];
			k1++;
		}
		else if(a.data[k1]>b.data[k2]){
			c.data[i]=b.data[k2];
			k2++;
		}
		else if(a.data[k1]==b.data[k2]){
			c.data[i]=b.data[k2];
			k1++;
			k2++;
		}
		i++;
		c.length++;	
	}
	while(k1<a.length){
		if(c.length==c.cap){
			c.recap(2*c.length);}
		c.data[i]=a.data[k1];
		i++;k1++;
		c.length++;
	}
	while(k2<b.length){
		if(c.length==c.cap){
			c.recap(2*c.length);}
			c.data[i]=b.data[k2];
			i++;k2++;
			c.length++;	
	}
}
int main(){
	int arr1[3]={1,2,3};
	int arr2[3]={1,4,5};
	sqlist l1;
	sqlist l2;
	sqlist l3;
	l1.createlist(arr1,3);
	l2.createlist(arr2,3);
	binji(l1,l2,l3);
//	l1.print();
//	l2.print();
	l3.print();
} 
