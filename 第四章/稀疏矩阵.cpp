#include <iostream>
using namespace std;
const int maxsize=100;
struct elem{
	int i;
	int j;
	int x;
	elem(){
		
	} 
	elem(int a,int b,int c){
		i=a;
		j=b;
		x=c;
	} 
};
class tup{
	public:
		int num;//包含的稀疏矩阵的非零元素
		int row;//稀疏矩阵的行数
		int clos;//稀疏矩阵的列数
		elem *data;
		tup(){
			data=new elem[maxsize];
		}
	void creattup(int a[][maxsize],int b,int c){
		row=b;
		clos=c;
		int k=0;
		for(int i=0;i<b;i++){
			for(int j=0;j<c;j++){
				if(a[i][j]!=0){
					data[k].x=a[i][j];
					data[k].i=i;
					data[k].j=j;
					k++;
				}
			}
		}
		num=k;
	bool setva(int i, int j, int x) {
	    if (i < 0 || i > row - 1 || j < 0 || j > clos - 1) {
	        return false;
	    }
	    
	    int k = 0;
	    while (k < num && data[k].i < i) {
	        k++;
	    }
	    while (k < num && data[k].i == i && data[k].j < j) {
	        k++;
	    }
	    
	    // 【核心变换】：强行注入 k < num 防止访问垃圾内存
	    if (k < num && data[k].i == i && data[k].j == j) {
	        data[k].x = x;
	        return true;
	    } else {
	        elem t1(i, j, x);
	        for (int m = num - 1; m >= k; m--) {
	            data[m + 1] = data[m];
	        }
	        data[k] = t1;
	        num++; 
	        return true;
	    }
	}
}; //默认容量没有问题，recap函数懒得写了 
int main(){
	
}
