#include<iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;
const int maxsize=1000;
template<class T>
struct datanode{
	T data[maxsize];
	datanode<T>*next;
	datanode(){
		next=NULL;
	} 
};
template<class T> 
struct hnode{
	int row,col;
	datanode<T>*next;
	hnode(){
		next=NULL;
		row=0;
		col=0;
	}
	hnode(int r,int c){
		row=r;
		col=c;
		next=NULL;
	}
};
template<class T>
class linklist{
	public:
		hnode<T>* head;
		linklist(int r,int c){
			head=new hnode<T>(r,c);//根据行数和列数初始化链表头节点 
		}
		linklist(){
			head=new hnode<T>();
		}
		void createlistr(vector<vector <T> > &v1,int r,int c){
			datanode<T>*s=new datanode<T>();
			for(int i=0;i<c;i++){
				s->data[i]=v1[0][i];
			}
			head->next=s;
			datanode<T>*rear=s;//由于head和datanode是不同的结构所以和普通链表不同，把第一个datanode单独拿出来 
			for(int i=1;i<r;i++){
				datanode<T>*s1=new datanode<T>();
				for(int j=0;j<c;j++){
					s1->data[j]=v1[i][j];
				}
				rear->next=s1;
				rear=s1;
			}
		}
		void print(){
			datanode<T>*p=head->next;
			int c=head->col;
			while(p!=NULL){
				for(int i=0;i<c;i++){
					cout<<p->data[i]<<" ";
				}
				cout<<endl;
				p=p->next;
			}
		}
		void lianjie(linklist<T>&l2,linklist<T>&l3,int cmi,int cmj){
			//l2是我们需要操作对比的对象，l3是用来存储结果的链表
			int c1=head->col;
			int c2=l2.head->col;
			int r3,c3;
			r3=0;//没运算之前不清楚具体有几行 
			c3=c1+c2;//没运算之前列数是固定的 
			datanode<T>*p=head->next;
			datanode<T>*q=l2.head->next;
			datanode<T>*rear=NULL;//用来对l3进行尾插法 
			while(p!=NULL){
				while(q!=NULL){
					if(p->data[cmi-1]>q->data[cmj-1]){
						datanode<T>*s=new datanode<T>();//用来给l3填充结点
						for(int i=0;i<c1;i++){
							s->data[i]=p->data[i];
						}
						for(int i=c1;i<c3;i++){
							s->data[i]=q->data[i-c1];
						}
						if(l3.head->next==NULL){
							l3.head->next=s;
							rear=s;
						}
						else{
							rear->next=s;
							rear=s;
						}
						//同样由于datanode和hnode结构不同，所以需要分类讨论rear情况 
						r3++;
					}
					q=q->next;
				}
				q=l2.head->next;
				p=p->next; 
			}
			l3.head->row=r3;
			l3.head->col=c3;//比较结束之后再修改l3的头节点的数据 
		}
};
int main(){
	string line;
	string trash;//用来接受'\n'等垃圾字符 
	cin>>line;
	int m1,n1;//m1表示第一个行数，n1表示第一个列数 
	cin>>m1>>n1;
	getline(cin,trash);
	if(line=="int"){
		vector<vector <int> > v1(m1);
		vector<int> v2(n1);
		for(int i=0;i<m1;i++){
			getline(cin,line);
			stringstream ss(line);
			for(int j=0;j<n1;j++){
				ss>>v2[j];
			}
			v1[i]=v2;
		}
		linklist<int>l1(m1,n1);
		l1.createlistr(v1,m1,n1);
		int m2,n2;
		cin>>m2>>n2;
		getline(cin,trash);
		vector<vector <int> > v3(m2);
		vector<int> v4(n2);
		for(int i=0;i<m2;i++){
			getline(cin,line);
			stringstream ss(line);
			for(int j=0;j<n2;j++){
				ss>>v4[j];
			}
			v3[i]=v4;
		}
		linklist<int> l2(m2,n2);
		l2.createlistr(v3,m2,n2);
		linklist<int> l3;
		int i,j;
		cin>>i>>j;
		l1.lianjie(l2,l3,i,j);
		l3.print();
	}
	else if(line=="char"){
		vector<vector <char> > v1(m1);
		vector<char> v2(n1);
		for(int i=0;i<m1;i++){
			getline(cin,line);
			stringstream ss(line);
			for(int j=0;j<n1;j++){
				ss>>v2[j];
			}
			v1[i]=v2;
		}
		linklist<char>l1(m1,n1);
		l1.createlistr(v1,m1,n1);
		int m2,n2;
		cin>>m2>>n2;
		getline(cin,trash);
		vector<vector <char> > v3(m2);
		vector<char> v4(n2);
		for(int i=0;i<m2;i++){
			getline(cin,line);
			stringstream ss(line);
			for(int j=0;j<n2;j++){
				ss>>v4[j];
			}
			v3[i]=v4;
		}
		linklist<char> l2(m2,n2);
		l2.createlistr(v3,m2,n2);
		linklist<char> l3;
		int i,j;
		cin>>i>>j;
		l1.lianjie(l2,l3,i,j);
		l3.print();
	}
} 
