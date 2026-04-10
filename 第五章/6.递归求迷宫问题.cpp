#include<iostream>
#include<vector>
using namespace std;
const int maxsize=4;
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};
int mg[][4]={{0,1,0,0},{0,0,1,1},{0,1,0,0},{0,0,0,0}};
int cnt=0;//记录可能的路径数；
class box{
	public:
	int i;
	int j;
	box(int l1,int l2):i(l1),j(l2){
	}
};
//这里我没有引用那个path是为了方便回溯，这样回溯的时候就不用麻烦地pop了,如果对于内存管控有要求，那么是需要用引用的 
void mgpath(int xi,int yi,int xe,int ye,vector<box>path){
	box b(xi,yi);
	path.push_back(b);
	mg[xi][yi]=-1;//避免来回走
	if(xi==xe&&yi==ye){
		cnt++;//路径数加一
		printf("迷宫路径%d:",cnt);
		for(int k=0;k<path.size();k++){
			printf("[%d,%d] ",path[k].i,path[k].j);
		} 
		cout<<endl;
		mg[xi][yi]=0;//回退，不然只能找到一条路径 
	} 
	else{
		int di=0;
		while(di<4){
			int i=xi+dx[di];
			int j=yi+dy[di];
			if(i>=0&&i<4&&j>=0&&j<4&&mg[i][j]==0){
				mgpath(i,j,xe,ye,path);
			}
			di++;
		}
		mg[xi][yi]=0;//在前方路径确定的情况下，已经找完这个点的所有情况了，退回去，但是为了防止之后新路径上面有它，所以要让它归为0 
	} 
	//这里其实 mg[xi][yi]=0;能一句话解决的，我写两遍是为了方便理解 
} 
int main(){
int xi=0,yi=0,xe=3,ye=3;
printf("(%d,%d)到(%d,%d)的所有路径:\n",xi,yi,xe,ye);
vector<box> path;
 mgpath(xi,yi,xe,ye,path);
 
} 
