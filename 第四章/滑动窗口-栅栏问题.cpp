#include<iostream>
using namespace std;
int zuiduo(int a[], int num, int cm) {
    int maxlength = 0;
    int sum = 0;
    int y = 1; // 记录左边指针 
    
    for (int i = 1; i < num + 1; i++) {
        sum += a[i]; // 无脑吃入右侧新元素
        
        // 核心修复：用 while 循环逐步踢出左侧元素，直到总和合法
        while (sum > cm) {
            sum -= a[y];
            y++;
        }
        
        // 此时 sum 绝对 <= cm，安全计算最大长度
        if (maxlength <= i - y + 1) {
            maxlength = i - y + 1;
        }
    }
    
    return maxlength;
}
int main(){
	int n,p,c;
	cin>>n>>p>>c;
	int arr[p]={};
	arr[0]=0;
	for(int i=1;i<p;++i){
		arr[i]=0;
	}
	int x;
	for(int i=0;i<n;++i){
		cin>>x;
		if(x<1||x>p-1){
			cout<<"x范围出错"<<endl;
			break;
		} 
		arr[x]+=1;
	}
	cout<<zuiduo(arr,p-1,c);
} 
