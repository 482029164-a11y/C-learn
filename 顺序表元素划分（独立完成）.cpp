#include<iostream>
using namespace std;
class sqlist{
	public:
		int*data;
		int capcity;
		int length;
	sqlist(){
		capcity=5;
		data=new int[capcity];
		length=0;
	}
	~sqlist(){
		delete[]data;
	}
	void recap(int c){
		int *olddata=data;
		data=new int[c];
		for(int i=0;i<this->length;i++){
			data[i]=olddata[i];
		}
		delete[]olddata;
		this->capcity=c;
	}
	void createlist(int a[],int n){
		for(int i=0;i<n;i++){
			if(length==this->capcity){
				recap(2*this->capcity);
			}
			data[i]=a[i];
			length++;
		}
		
	} 
	void print(){
		for(int i=0;i<length;i++){
			cout<<data[i]<<" ";
		}
	}
};
void my_sort(sqlist&a,int num,int& k1,int& k2){
		int*olddata=a.data;
		a.data=new int [a.capcity];
		int j=0;
		int p=0;
		for(int i=0;i<num;i++){
			if(olddata[i]<k1){
				a.data[p]=olddata[i];
				p++;
			}
			else if(olddata[i]>=k2){			
				a.data[num-1-j]=olddata[i];
				j++;
			}
		}
		k1=p-1;
		k2=num-j;
}
int main(){
	int k1;int k2;
	int num;
	cin>>k1>>k2;
	if(k1>k2){
		cout<<"false";
		return 0;
	}
	else{
	}
	cin>>num;
	int arr[num];
for(int i=0;i<num;i++){
	cin>>arr[i];
	}
	sqlist l;
	l.createlist(arr,num);
	my_sort(l,num,k1,k2);
	cout<<k1<<" "<<k2;
	return 0;
} 
