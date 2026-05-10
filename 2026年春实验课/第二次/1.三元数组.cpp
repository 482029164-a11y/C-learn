#include<iostream>
#include<string>
#include<sstream>
#include<vector> 
using namespace std; 
//先自行创建三元数组的元素类型 
struct node{
	int row;
	int clo;
	int val;
	node(int r,int c,int v){
		row=r;
		clo=c;
		val=v;
	}
	node(){}
};
void zhuanzhi(vector<node>&n1,vector<node>&n2,int n){
	//n1是源数据，n2是要修改后的数据,n为原矩阵的列数 
	vector<int>num(n,0);//用来存放每一列有几个非零元素,向量的大小就等于原本矩阵的列数,默认是0 
	int length_n1=(int)n1.size();
	node temp;
	for(int i=0;i<length_n1;i++){
		int clo1=n1[i].clo;
		num[clo1]++;//只要碰到 clo1就在原基础上+1 
	}
	vector<int>cpot(n);//用来记录原本矩阵某一列第一个非零元素在转置后矩阵的位置 
	cpot[0]=0;//第0列的第一个元素肯定在转置后矩阵的第一个位置 
	for(int i=1;i<n;i++){
		cpot[i]=cpot[i-1]+num[i-1];//本列第一个的位置等于上一列第一个加上一列非零的个数 
	} 
	for(int i=0;i<length_n1;i++){
		int clo1=n1[i].clo;//确认当前元素的列的位置
		int k=cpot[clo1];//k就是当前的排列位置，因为原矩阵是按行优先的，因此第一次遇到的天生就是某列的第一个元素 
		n2[k] = node(n1[i].clo, n1[i].row, n1[i].val);
		cpot[clo1]++;//这个已经排完了，再次碰到这一列的时候就需要往后排了 
	} 
}
int main(){
	freopen("in.txt","r",stdin);
	freopen("abc.out", "w", stdout);
	int m,n,l;//m为行数，n为列数，l为非零元素个数
	while(cin>>m>>n>>l){
		string line,trash;//trash用来吃掉垃圾字符
		getline(cin,trash);
		vector<node>san(l);//创建三元顺序表//数组大小就是非零个数的大小,//预分配l个空间 
		for(int i=0;i<l;i++){
			int r,c,v;
			getline(cin,line);
			stringstream ss(line);
			ss>>r>>c>>v;
			san[i]=node(r,c,v);
		}
		vector<node>san1(l);
		zhuanzhi(san,san1,n);
		cout<<n<<" "<<m<<" "<<l<<endl;
		for(int i=0;i<l;i++){
			node N=san1[i];
			cout<<N.row<<" "<<N.clo<<" "<<N.val<<endl;
		}	
	}
} 
