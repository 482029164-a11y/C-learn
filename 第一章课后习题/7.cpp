//½»¼¯
#include<iostream>
using namespace std;
const int initcap=5;
class sqlist{
	public:
		int *data;
		int length;
		int cap;
	sqlist(){
		data=new int[initcap];
		length=0;
		cap=initcap;
	}
	~sqlist(){
		delete []data;
		length=0;
		cap=0;
	}
	void recap(int c){
		int *olddata=data;
		data=new int[c];
		for(int i=0;i<length;i++){
			data[i]=olddata[i];
		}
		delete[]olddata;
		cap=c;
	}
	void creatlist(int a[],int n){
		if(length!=0){
			return;
		} 
		for(int i=0;i<n;i++){
			if(length==cap){
				recap(2*length);
			}
			data[i]=a[i];
			length++;
		}
	}
	void print(){
		for(int i=0;i<length;i++){
			cout<<data[i]<<" ";
		}
		cout<<endl;
	}	
};
void jiaoji(sqlist&a,sqlist&b,sqlist&c){
	int k1=0;
	int k2=0;
	while(k1<a.length&&k2<b.length){
		if(a.data[k1]<b.data[k2]){
			k1++;
		}
		else if(a.data[k1]>b.data[k2]){
			k2++;
		}
		else{
			if(c.length==c.cap){
				c.recap(2*c.length);
			}
			c.data[c.length]=a.data[k1];
			k1++;k2++;c.length++;
		}
	}
}
int main(){
	int arr1[100]={};
	int arr2[100]={};
	int n1=0;
	int n2=0;
	while(cin>>arr1[n1]){
		n1++;
		char c=cin.get();
		if(c=='\n'||c=='\r'){
			break;
		}
	}
	while(cin>>arr2[n2]){
		n2++;
		char c=cin.get();
		if(c=='\n'||c=='\r'){
			break;
		}
	}
	sqlist l1;
	sqlist l2;
	sqlist l3;
	l1.creatlist(arr1,n1);
	l2.creatlist(arr2,n2);
	jiaoji(l1,l2,l3);
	l1.print();
	l2.print();
	l3.print();
} 
