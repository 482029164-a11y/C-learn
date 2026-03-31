//不要运行，看得懂就可以了 
#include<iostream>
using namespace std;
#include <sstream> 
#include<string>// 一行一行去读必须包含这个头文件
int main(){
	//第一种情况，直接告诉我数组的长度；
	int n;
	cin>>n;
	int arr1[n]={};
	for(int i=0;i<n;i++){
		cin>>arr1[i];
	} 
	//**********
	//第二种情况，只告诉读到文件结束
	int x;
	int n1 = 0;
	// 只要能成功读到一个整数，就存起来。读到文件末尾自动结束。
	while(cin >> x) {
    	arr[n1] = x;
    	n1++;
	}
	//*********** 
	//第三种情况，一行一行地去读
	string line;
    // 1. 极其霸道地把这一整行直接抽出来，OJ 里的换行符会自动被吃掉
    getline(cin, line); 
    int arr[100]={};
    // 2. 把这一行变成一个“迷你的 cin”
    stringstream ss(line); 
    
    int n = 0;
    int x;
    // 3. 在这个干净的、只有这一行的流里面，安全地读取
    while(ss >> x) {
        arr[n] = x;
        n++;
    }
} 
//明确有几行
 #include <iostream>
#include <sstream>
#include <string>
using namespace std;

// 【极其清爽的工具函数】：专门用来读取一行不定长的数字
void readOneLine(int arr[], int& n) {
    string line;
    getline(cin, line); 
    stringstream ss(line); 
    
    n = 0;
    int x;
    while(ss >> x) {
        arr[n] = x;
        n++;
    }
}

int main() {
    int arr1[100] = {};
    int n1 = 0;
    int arr2[100] = {};
    int n2 = 0;

    // 极其优雅的调用，要读几行就喊它几次
    readOneLine(arr1, n1); // 第一行乖乖存进 arr1
    readOneLine(arr2, n2); // 第二行乖乖存进 arr2

    // 接下来就可以去建你的链表啦...
    return 0;
}
//不定行数
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    string line;
    
    while (getline(cin, line)) {
        if (line.empty()) continue; 
        
        // 【物理过滤防线】：在交给 stringstream 之前，清洗这行字符串
        for (int i = 0; i < (int)line.length(); ++i) {
            // 如果遇到逗号，或者其他你认为是“脏”的符号
            if (line[i] == ',') {
                line[i] = ' '; // 直接把它变成空格
            }
        }
        
        // 清洗完毕，现在 line 里面只剩下数字和空格了（比如 "12  34"）
        stringstream ss(line);
        int arr[100] = {};
        int n = 0;
        int x;
        
        // 此时提取将畅通无阻
        while (ss >> x) {
            arr[n] = x;
            n++;
        }
        
        // ... 后续处理 ...
    }
    return 0;
}
