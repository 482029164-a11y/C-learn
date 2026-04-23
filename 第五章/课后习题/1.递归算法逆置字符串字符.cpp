#include<iostream>
using namespace std;
#include<string> 
//弄清除逆置的本质，逆置就是对称元素交换，所以可以用双指针法进行交换 
void reverse_help(string&s,int left,int right){
	if(left>=right){
		return;//一直交换到左边到right或者left大于right 
	} 
	else{
		char temp=s[left];
		s[left]=s[right];
		s[right]=temp;//对称交换
		reverse_help(s,left+1,right-1);
	}
}
string reverse(string s){
	reverse_help(s,0,s.size()-1);
	return s;
}//其实我这里多此一举了，主要是为了防止改变原本的字符串 
int main(){
	string s;
	cin>>s;
	s=reverse(s);
	cout<<s; 
} 
