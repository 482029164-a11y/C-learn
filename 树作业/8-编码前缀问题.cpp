#include<iostream>
#include<vector>
#include<string>
using namespace std;
struct treenode{
	treenode* child[2];
	bool is_end;//用来判断该节点是否是某一行编码的结束
	treenode(){
		child[0]=NULL;
		child[1]=NULL;
		is_end=false;
	} 
};
bool qianzhui(treenode*r,string& s){
	treenode*curr=r;
	bool is_create_new=false;//判断是否创造分支//是否和现有的排序有所不同 
	for(int i=0;i<(int)s.size();i++){
		int bits=s[i]-'0';
		if(curr->child[bits]==NULL){
			curr->child[bits]=new treenode();
			is_create_new=true;
		} 
		if(curr->is_end){
			return false;
		}//现有线索已经结束了 ,并且没有创建新的分支避开它 
		curr=curr->child[bits];//继续往前推 
	}
	if(!is_create_new){
		return false;
	} //没创建新的，是别人的子集 
	curr->is_end=true;//前面情况都没有发生，最后一个结点刚好是自己的分支结束了 
	return true;
}
void delete_trie(treenode*r) {
    if (!r) return;
    delete_trie(r->child[0]);
    delete_trie(r->child[1]);
    delete r;
}

int main(){
	freopen("in.txt","r",stdin);
	string line;
	vector<string>counts;//用来记录有几行数据 
	while(getline(cin,line)){
		if(line=="9"){
			bool a=true;
			treenode*r=new treenode();
			for(int i=0;i<(int)counts.size();i++){
				if(!qianzhui(r,counts[i])){
					a=false;
					break;
				}
			} 
			if(!a){
				cout<<"N"<<endl;	
			}
			else{
				cout<<"Y"<<endl;
			}
			delete_trie(r);
			counts.clear();
		}
		counts.push_back(line);//没到最后一行的时候就把数据存入进counts 
	}
}
