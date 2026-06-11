#include<iostream>
#include<string>
#include<sstream>
#include<vector>
using namespace std;
int low_bound(vector<int>&v,int k){
	vector<int>counts;//用来存储发现k的下标 
	int low=0;
	int high=(int)v.size()-1;
	while(low<=high){
		int mid=(low+high)/2;
		if(v[mid]<k){
			low=mid+1;
		} 
		else{
			if(v[mid]==k){
				counts.push_back(mid);
			}
			high=mid-1;
		}
	} 
	if(counts.empty()){
		return -1;
	}
	return counts[(int)counts.size()-1]+1;
} 
int high_bound(vector<int>&v,int k){
	vector<int>counts;//用来存储发现k的下标 
	int low=0;
	int high=(int)v.size()-1;
	while(low<=high){
		int mid=(low+high)/2;
		if(v[mid]>k){
			high=mid-1;
		} 
		else{
			if(v[mid]==k){
				counts.push_back(mid);
			}
			low=mid+1;
		}
	}
	if(counts.empty()){
		return -1;
	}
	return counts[(int)counts.size()-1]+1;
}
int main(){
	int n,target;//元素个数,目标元素 
	cin>>n;
	string line,trash;
	getline(cin,trash);
	getline(cin,line);
	int x;
	stringstream ss(line);
	vector<int>v;
	v.resize(n);
	int i=0;
	while(ss>>x){
		v[i]=x;
		i++;
	} 
	cin>>target;
	int be=low_bound(v,target);
	int ed=high_bound(v,target);
	cout<<be<<" "<<ed;
} 
