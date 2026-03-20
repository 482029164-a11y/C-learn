//求并集 
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
	sqlist(const sqlist&l){
		data=new int[l.capcity];
		for(int i=0;i<l.length;i++){
			this->data[i]=l.data[i];
		}
		this->length=l.length;
		this->capcity=l.capcity;
	}
	void addlist(const sqlist&l)
	{
		for(int i=0;i<l.length;i++){
		if(length==capcity){
			recap(2*length);
		}
			data[length]=l.data[i];
			length++;
		}
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
		this->capcity=c;
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
	void print(){
		for(int i=0;i<length;i++){
			cout<<data[i]<<" ";
		} 
		cout<<endl;
	}
	void push(int x){
		if(length==capcity){
			recap(2*length);
		}
		data[length]=x;
		length++;
	}
};
void hebin(sqlist&a,sqlist&b,sqlist&c){
	if(a.length<=b.length){
		c.addlist(a);
		for(int i=0;i<b.length;i++){
			int num=0;
			for(int j=0;j<a.length;j++){
				if(b.data[i]==a.data[j]){
					break;
				}
				num++;
			}
			if(num==a.length){
				c.push(b.data[i]);
			}
		}
	}
	else{
		c.addlist(b);
		for(int i=0;i<a.length;i++){
				int num=0;
			for(int j=0;j<b.length;j++){
				if(a.data[i]==b.data[j]){
					break;
				}
				num++;
			}
			if(num==b.length){
				c.push(a.data[i]);
			}
		}
	}
}
int main(){
	int a[4]={1,2,3,4};
	int b[3]={3,5,6}; 
	sqlist l1;
	sqlist l2;
	sqlist l3;
	l1.createlist(a,4);
	l2.createlist(b,3);
	hebin(l1,l2,l3);
	l3.print();
}
