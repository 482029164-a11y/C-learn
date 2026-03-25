#include<iostream>
using namespace std;
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
		void createsatckf(T a[],int n){
			for(int i=0;i<n;i++){
				linknode<T>*p=new linknode<T>(a[i]);
				p->next=head->next;
				head->next=p;
			}
		}
		bool empty(){
			return head->next==NULL;
		}
		void push(T x){
			linknode<T>*p=new linknode<T>(x);
			p->next=head->next;
			head->next=p;	
		}
		bool gettop(T &e){
			if(empty()){
				return false;
			}
			else{
				e=head->next->data;
				return true;
			}
		}
		bool pop(T &e){
			if(empty()){
				return false;
			}
			else{
				e=head->next->data;
				linknode<T>*p=head->next;
				head->next=p->next;
				delete p;
				return true;
			}
		}
};
struct box{
	int i;
	int j;
	int di;
	box(){
	}
	box(int a,int b,int c){
		i=a;
		j=b;
		di=c;
	}
};
void dispbox(stack<box> s){
	if(s.empty()){
		return;
	}
	linknode<box>*p=s.head->next;
	while(p!=NULL){
		cout<<'['<<p->data.i<<','<<p->data.j<<']'<<" ";
		p=p->next;
	}
	cout<<endl;
}
bool findmap(int xi,int yi,int xe,int ye){
int m=4,n=4;
int mg[4][4]={
  {0,1,0,0},
  {0,0,1,1},
  {0,1,0,0},
  {0,0,0,0}
};
int dx[]={-1,0,1,0};   	//x方向的偏移量
int dy[]={0,1,0,-1};   	//y方向的偏移量
stack<box> s;
bool find;
box b(xi,yi,-1);
box b1;
mg[xi][yi]=-1;
s.push(b);
while(!s.empty()){
	s.gettop(b);
	if(b.i==xe&&b.j==ye){
	dispbox(s);
	return true;	
	}
	else{
		find=false;
		int temi=b.di;
		while(temi<3&&find==false){
			temi++;
			int t1=b.i+dx[temi];
			int t2=b.j+dy[temi];
			if(t1<m&&t2<n&&t1>=0&&t2>=0&&mg[t1][t2]==0){
				// 1. 手里的复印件记下最新的试探方向
			    b.di=temi;//gettop返回的仅仅是栈顶元素的复印，不是栈顶元素本身 
			    
			    // 2. 【极其核心的物理替换】：狸猫换太子！
			    box temp_box;
			    s.pop(temp_box); // 把栈顶那个没更新的老古董弹出来扔掉
			    s.push(b); // 把手里更新了进度条的 b 重新压回去稳住阵脚！
			
			    // 3. 安心处理下一步的新路口
			    b1 = box(t1,t2,-1); 
			    mg[t1][t2]=-1;
			    s.push(b1);
			    find=true;
			}
		}
		if(find==false){
			s.pop(b);
			mg[b.i][b.j]=0;
		}
	}
}
return false;	
}
int main(){
	
    if(findmap(0,0,3,3)) {
        cout << "探索成功！" << endl;
    } else {
        cout << "这是一条死路！" << endl;
    }
    return 0;

} 
