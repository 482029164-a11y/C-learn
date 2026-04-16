#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int totalNQueens(int n) {
		int count=0;
		vector<bool> clo(n,false);
		vector<bool> dig1(2*n,false);
		vector<bool> dig2(2*n,false); 
		xunzhao(n,0,count,clo,dig1,dig2);
		return count;
    }
    void xunzhao(int n,int row,int&count,vector<bool> &clo,vector<bool> &dig1,vector<bool> &dig2){
    	if(row==n){
    		count++;
    		return;
		}
		else{
			for(int j=0;j<n;j++){
				int di1=row+j;//次对角线
				int di2=row-j+n;//主对角线
				if(clo[j]||dig1[di1]||dig2[di2]){
					continue;
				} 
				clo[j]=true;
				dig1[di1]=true;
				dig2[di2]=true;
				xunzhao(n,row+1,count,clo,dig1,dig2);
				clo[j]=false;
				dig1[di1]=false;
				dig2[di2]=false;
			}
		}
	}
};

int main() {
	int n;
	freopen("in.txt","r",stdin);
	cin>>n;
	Solution s1;
	int num=s1.totalNQueens(n);
	cout<<num;
    return 0;
}
