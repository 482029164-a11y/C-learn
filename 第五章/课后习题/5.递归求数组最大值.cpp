#include <iostream>
#include <string>
#include<sstream>
using namespace std;
int my_max(int a[],int num){
	if(num==1){
		return a[0];
	}
	if(num<=0){
		return -1;
	}
	else {
        // 3. 内存的完美对半劈裂 (分治)
        // 前半部分的物理长度恒为 num / 2
        int max1 = my_max(a, num / 2);
        
        // 后半部分的物理长度：利用总长度减去前半部分，自适应奇偶数，省去复杂的 if 判断
        int max2 = my_max(a + num / 2, num - num / 2); 
        
        // 4. 物理数值角力，返回胜者
        return (max1 >= max2) ? max1 : max2;
    }
}
int main(){
	int arr[1000]={};
	string line;
	getline(cin,line);
	stringstream ss(line);
	int i=0;
	while(ss>>arr[i]){
		i++;
	}
	int max=my_max(arr,i);
	cout<<max;
}
