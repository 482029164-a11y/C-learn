#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    vector<vector<int> > generateMatrix(int n) {
        // 1. 内存物理预分配：直接开辟 n x n 的二维空间，初始值为 0
        vector< vector<int> > matrix(n, vector<int>(n, 0));
    	int top=0;
    	int bottom=n-1;
    	int left=0;
    	int right=n-1;
    	int num=n*n;
    	int j=1;
    	while(j<=num){
    		for(int i=left;i<=right;i++){
    			matrix[top][i]=j;
    			j++;
			}
			top++;
			for(int i=top;i<=bottom;i++){
				matrix[i][right]=j;
				j++;
			}
			right--;
			for(int i=right;i>=left;i--){
				matrix[bottom][i]=j;
				j++;
			}
			bottom--;
			for(int i=bottom;i>=top;i--){
				matrix[i][left]=j;
				j++;
			}
			left++;
		}
        return matrix;
    }
};

int main() {
    // 根据题目要求，可以从 in.txt 重定向输入
//     freopen("in.txt", "r", stdin); 
    
    int n;
    if (cin >> n) {
        Solution sol;
        vector< vector<int> > res = sol.generateMatrix(n);
        // 4. 绝对格式化输出引擎 (严格匹配样例要求)
        cout << "[\n";
        for (int i = 0; i < n; i++) {
            cout << "[";
            for (int j = 0; j < n; j++) {
                cout << res[i][j];
                if (j < n - 1) cout << ",";
            }
            cout << "]";
            if (i < n - 1) cout << ",";
            cout << "\n";
        }
        cout << "]";
    }
    
    return 0;
}
