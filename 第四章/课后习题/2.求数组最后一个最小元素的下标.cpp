#include<iostream>
#include<vector>
using namespace std;
int min_index(int v[],int num){
	int min=0;//³õÊ¼»¯Îª0
	int min_e=v[0];
	for(int i=0;i<num;i++){
		if(min_e>=v[i]){
			min_e=v[i];
			min=i;
		}
	} 
	return min;
} 
int main(){
	int arr[1000]={7,7,1,0,2,3};
	cout<<min_index(arr,5);
} 
