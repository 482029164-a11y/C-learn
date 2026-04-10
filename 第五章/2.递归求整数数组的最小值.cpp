#include<iostream>
using namespace std;
#include <algorithm> // 引入 min 函数
//求数组中0到i中的最小值 
int zuixiao(int a[],int i){
	if(i==0){
		return a[0];
	}
	else{
		int mind=zuixiao(a,i-1);
		return min(a[i],mind); 
	}
} 
int main(){
	int arr[5]={10,25,7,4,90};
	int y=zuixiao(arr,4);
	cout<<y;
} 
