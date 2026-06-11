#include<iostream>
#include<string>
#include<sstream>
#include<vector>
using namespace std;
bool search(vector<int>& v,vector<int>& path,int k){
	int high=(int)v.size()-1;
	int low=0;
	while(low<=high){
		int mid=(low+high)/2;
		path.push_back(v[mid]);
		if(v[mid]==k){
			return true;
		}
		else{
			if(v[mid]<k){
				low=mid+1;
			}
			else{
				high=mid-1;
			}
		}
	}
	return false;
}
int main(){
	int dest;//查找目标数据
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout); 
	cin>>dest;
	string trash,line;
	getline(cin,trash);
	getline(cin,line);
	vector<int>v;
	int x;
	stringstream ss(line);
	while(ss>>x){
		v.push_back(x);
	}
	vector<int>path;
	bool is=search(v,path,dest);
	if(is){
		cout<<"True"<<endl;
	}
	else{
		cout<<"False"<<endl;
	}
	for(int i=0;i<(int)path.size();i++){
		cout<<path[i]<<" ";
	}
}
