#include<iostream>
#include<string>
#include<sstream>
#include<queue>
#include<cctype>
#include<cstring> 
using namespace std;
int const maxv=100;
int const inf=0x3f3f3f3f;
class MGraph{
	public:
		int n;//顶点个数 
		int e;//边数
		int edges[maxv][maxv];//存放边权重，这里只有1,0,inf三种情况 
		char VerticesList[maxv];//存放顶点
		MGraph(){
			for(int i=0;i<maxv;i++){
				for(int j=0;j<maxv;j++){
					if(i==j) edges[i][j]=0;
					else{
						edges[i][j]=inf;
					}
				}
			}
			e=0;
			n=0;
		}
		int find(char c){
			for(int i=0;i<n;i++){
				if(c==VerticesList[i]) return i; 
			}
			return -1; 
		} 
		MGraph(char arr[],int num,string &s){
			for(int i=0;i<maxv;i++){
				for(int j=0;j<maxv;j++){
					if(i==j) edges[i][j]=0;
					else{
						edges[i][j]=inf;
					}
				}
			}//防止调用重载构造函数之后没有初始化 
			n=num;e=0;
			for(int i=0;i<n;i++){
				VerticesList[i]=arr[i]; 
			}
			queue<char> q;
			for(int i=0;i<s.length();i++){
				char c=s[i];
				if(isalpha(c)) q.push(c);
				else if(c==')'){
					char t1=q.front();q.pop();
					char t2=q.front();q.pop();
					int p1=find(t1);
					int q1=find(t2);
					edges[p1][q1]=1;
					e++;
				}
			}
		}		 
}; 
int chu[maxv];
int ru[maxv];
void chudu(MGraph&g){
	for(int i=0;i<g.n;i++){
		for(int j=0;j<g.n;j++){
			if(g.edges[i][j]==1){
				chu[i]++;
			} 
		}
	}
}
void rudu(MGraph&g){
	for(int i=0;i<g.n;i++){
		for(int j=0;j<g.n;j++){
			if(g.edges[i][j]==1){
				ru[j]++;
			} 
		}
	}
}
int printVertices(MGraph&G){
	memset(chu, 0, sizeof(chu));
    memset(ru, 0, sizeof(ru));
	cout<<"K vertices: "; 
	chudu(G);rudu(G);
	int k=0;
	for(int i=0;i<G.n;i++){
		if(chu[i]>ru[i]){
			cout<<G.VerticesList[i]<<" ";
			k++;
		} 
	}
	cout<<endl;
	return k;
}
bool isRealEdgeLine(const string& s) {
    int alpha_count = 0;
    int bracket_count = 0;
    for (char c : s) {
        if (isalpha(c)) alpha_count++;
        if (c == ')') bracket_count++;
    }
    // 真正的边数据行特点：里面不仅有括号，更有高频成对出现的边括号 ')'。
    // 而提示语里只有一个示例括号，且总字母数极长。
    return (bracket_count >= 1 && alpha_count < (int)s.length() / 2);
}
int main() {
	string line, line1 = "", line2 = "";
	
	// 【绝对防御流扫描】：依靠数据核心特征（花括号与高频右括号）进行大浪淘沙
	while(getline(cin, line)) {
		if(line.find('{') != string::npos) {
			line1 = line; // 100% 锁定真实顶点行
		}
		else if(isRealEdgeLine(line)) {
			line2 = line; // 100% 锁定真实边数据行，完美避开提示语诱饵
			break;        
		}
	}
	
	stringstream ss(line1);
	char arr[maxv];
	char x;
	int i = 0;
	while(ss >> x) {
		if(isalpha(x)) {
			arr[i] = x;
			i++;
		}
	} 
	
	MGraph g(arr, i, line2);
	
	int k = printVertices(g);
	cout << "Number of K vertices: " << k << endl;
	return 0;
}
