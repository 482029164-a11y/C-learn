//用栈求简单算数表达式
#include<iostream>
using namespace std;
#include<string>
template<class T>
class linknode{
	public:
		T data;
		linknode<T>*next;
		linknode(){
			next=NULL;
		}
		linknode(T d){
			data=d;
			next=NULL;
		}
};
template<class T>
class stack{
	public:
		linknode<T>*head;
		stack(){
			head=new linknode<T>();
		}
		void createstackf(T a[],int n){
			for(int i=0;i<n;i++){
				linknode<T>*s=new linknode<T>(a[i]);
				s->next=head->next;
				head->next=s; 
			}
		}
		void push(T x){
			linknode<T>*s=new linknode<T>(x);
			s->next=head->next;
			head->next=s;
		}
		bool empty(){
			return head->next==NULL;
		}
		bool pop(T &e){
			if(empty()){
				return false;
			}
			e=head->next->data;
			linknode<T>*temp=head->next;
			head->next=head->next->next;
			delete temp;
			return true;
		}
		bool gettop(T &e){
			if(empty()){
				return false;
			}
			e=head->next->data;
			return true;
		}
}; 
class Express{
	public:
		stack<char>opor;
		stack<double>opran; 
		string exp;
		string postexp;
		Express(string ch){
			exp=ch;
			postexp="";
		}
		string getpost(){
			return postexp;
		}
		void Trans(){
			char ch;
			int i=0;
			while(i<exp.length()){
				ch=exp[i];
				if(ch=='('){
					opor.push(ch);
				}
				else if(ch==')'){
					char temp;
					opor.pop(temp);
					while(temp!='('){
						postexp+=temp;
						opor.pop(temp);
					}
				}
				else if (ch == '+' || ch == '-') {
    			char temp;
   				 // 只要栈不空，且栈顶不是左括号结界
    			while (opor.gettop(temp) && temp != '(') {//这里智只能看，不能去pop 
        		// 因为 + - 优先级最低，所以只要栈顶是个正常的运算符，都得弹出来让位
        			postexp += temp;
       				opor.pop(temp); // 真正弹出
    			}
    			opor.push(ch); // 别人全让位了，自己安稳坐进去
				}
				else if (ch == '*' || ch == '/') {
				    char temp;
				    // 只要栈顶是高优先级的 * 或 /，才需要弹出来让位
				    while (opor.gettop(temp) && (temp == '*' || temp == '/')) {
				        postexp += temp;
				        opor.pop(temp);
				    }
				    opor.push(ch); // 坐进去
				}
			else{
					string d;
					d="";
					while(ch>='0'&&ch<='9'){
						d+=ch;
						i++;
						if(i>=exp.length()){
							break;
						}
						ch=exp[i];
					}
					i--;//如果循环结束之后的exp[i]不在 ch>='0'&&ch<='9'这个范围了就-1，不然等下再加1就重复了 
					postexp+=d;
					postexp+="#";	
				}
				
				i++;
				}
				while(!opor.empty()){
				char temp;
				opor.pop(temp);
				postexp+=temp;
			} 
			}
		double getvalue(){
			char ch;
			int i=0;
			while(i<postexp.length()){
				ch=postexp[i];
				if(ch=='+'){
					double temp1;
					opran.pop(temp1);
					double temp2;
					opran.pop(temp2);
					double t=temp1+temp2;
					opran.push(t);
				}
				else if(ch=='*'){
					double temp1;
					opran.pop(temp1);
					double temp2;
					opran.pop(temp2);
					double t=temp1*temp2;
					opran.push(t);
				}
				else if(ch=='/'){
					double temp1;
					opran.pop(temp1);
					double temp2;
					opran.pop(temp2);
					double t=temp2/temp1;
					opran.push(t);
				}
				else if(ch=='-'){
					double temp1;
					opran.pop(temp1);
					double temp2;
					opran.pop(temp2);
					double t=temp2-temp1;
					opran.push(t);
				}
				else{
					double d;
					d=0;
					while(ch!='#'){
						d=10*d+(ch-'0');
						i++;
						if(i<postexp.length()){
							ch=postexp[i];
						}
						else{
							break;
						}
					}
					opran.push(d);
				}
				i++;
			}
			double e;
			opran.gettop(e);
			return e;
		}
};
int main(){
	string str="(56-20)/(4+2)";
	Express obj(str);
	cout<<"中缀表达式为："<<str<<endl;
	cout<<"中缀表达式转化为后缀表达式中···"<<endl; 
	obj.Trans();
	cout<<"后缀表达式为："<<obj.getpost()<<endl;
	cout<<"结果为："<<obj.getvalue()<<endl; 
} 
