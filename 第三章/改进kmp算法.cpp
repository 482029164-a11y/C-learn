#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 获取改进后的 nextval 数组
vector<int> getNextval(const string& pattern) {
    int m = pattern.length();
    vector<int> nextval(m, 0);
    
    // 初始化第一个位置（客观规律：第 0 个位置失配，只能让主串前进，标记为 -1）
    nextval[0] = -1; 
    
    int j = 0; // 遍历模式串的指针
    int k = -1; // 记录前缀末尾位置（也即要跳往的下标）
    
    while (j < m - 1) {
        // 如果 k 退回了起点，或者当前字符与前缀字符匹配上了
        if (k == -1 || pattern[j] == pattern[k]) {
            j++;
            k++;
            
            // 【核心改进逻辑就在这一个 if-else 里】
            // 如果我 (j) 和我要跳过去的人 (k) 长得一样：
            if (pattern[j] == pattern[k]) {
                // 我就不存 k 了，我直接继承他的逃跑路线！
                nextval[j] = nextval[k]; 
            } else {
                // 如果长得不一样，那这就是一个有效的新比对点，老老实实存下来
                nextval[j] = k;
            }
            
        } else {
            // 如果没匹配上，k 指针按照之前的逃跑路线回退
            k = nextval[k]; 
        }
    }
    
    return nextval;
}
void getnextval(string s,int*nextval){
	int k=-1;
	nextval[0]=-1;
	int i=0;
	while(i<s.length()-1){
		if(k==-1||s[i]==s[k]){
			i++;
			k++;
			if(s[i]==s[k]){
				nextval[i]=nextval[k];
			}
			else{
				nextval[i]=k;
			}
		}
		else{
			k=nextval[k];
		}
	}
} //自己写的改进算法 
int main() {
    string pattern = "ababaa";
    vector<int> nextval = getNextval(pattern);
    
    cout << "模式串: " << pattern << endl;
    cout << "nextval: ";
    for (int val : nextval) {
        cout << val << " ";
    }
    cout << endl;
    
    return 0;
}
