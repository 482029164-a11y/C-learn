#include<iostream>
using namespace std;
const int initcap=5;//初始化顺序表的容量
template<class T>//模板化列表，因为我们不知道列表中的具体元素是什么
class sqlist{
	public:
		T *data;//存放元素的地址，首地址 
		int length;//表中元素的个数
		int cap;//表的容量
		sqlist(){
			data=new T[initcap];
			this->length=0; 
			cap=initcap;
		}//构造函数初始化
		sqlist(const sqlist<T>&list){
			this->cap=list.cap;
			this->length=list.length;
			data=new T[this->cap];
			for(int i=0;i<list.length;i++){
				this->data[i]=list.data[i];
			}
		}//拷贝构造，注意 <T>&两者的位置关系 
		~sqlist() {
    		if (this->data != NULL) {
        	delete[] this->data;
        	this->data = NULL;
    		}
		}//析构函数； 
		void recap(int cap){
			if(cap<0){
				cout<<"请输入正确的容量"<<endl;
					} 
			T*olddata=this->data;//用一个临时指针存放我们的旧指针
			this->data=new T[cap];//开辟新空间 
			for(int i=0;i<length;i++){
				data[i]=olddata[i];//把旧表的元素放入新的表中 
			}
			delete[]olddata;//释放旧表的地址  
			this->cap=cap; 
		} //改变顺序表的容量
		void createlist(T list[],int n){
			for(int i=0;i<n;i++){
			if(length==cap){
				recap(2*length);
				}
			data[i]=list[i];
			length++;	
			}
		} //传入一个任意类型的数组去创造我们的表
		void add(T a){
			if(length==cap){
				recap(2*length);
			}
			data[length]=a;
			length++;
		} //添加元素 
		int getlength(){
			return this->length;
		}//获取顺序表的元素个数
		bool getelem(int i,T&e){
			if(i<0||i>=this->length){
				cout<<"请输入正确的下标："<<endl;
				return false;
			}
			e=data[i];//这里用引用就是为了这一步可以把值带出来 
			return true; 
		} 
		int getno(T e){
		for(int i=0;i<this->length;i++){
			if(data[i]==e) {
				return i;
			}//等号重载的问题暂时不考虑 
		} 
		return -1;
		}//查找值为e的元素的下标 
		void print(){
			for(int i=0;i<this->length;i++){
				cout<<data[i]<<" "; 
			}
			cout<<endl;
		} //打印所有元素
		bool insert(T e,int j){
			if(j<0||j>length){
				cout<<"请输入正确的索引"<<endl;
				return false; 
			} 
			if(this->length==this->cap){
				recap(2*this->length);
			}
			for(int i=this->length-1;i>=j;i--){
				data[i+1]=data[i];
			}
			data[j]=e;
			this->length++;
			return true;
		} //插到对应索引元素的前面
		bool my_delte(int i){
			if(i<0||i>length-1){
				cout<<"请输入正确的索引"<<endl;
				return false; 
			} 
			for(int j=i+1;j<this->length;j++){
				data[j-1]=data[j];
			}//直接覆盖就行了
			this->length--; 
			return true; 
		} //删除元素 
		
//下面就是一些经典的算法函数设计了
void reverse(){
	for(int i=0;i<(length/2);i++){
		T temp=data[i];
		data[i]=data[length-1-i];
		data[length-1-i]=temp;
	}
} //我觉得这个函数定义在类内比较好 
}; 
template<class T>
bool deletek(sqlist<T>&list,int i,int k){
	if(i<0||i>list.length-1||k<1||i+k>list.length){
		return false;
	}
	for(int j=i+k;j<=list.length-1;j++){
		list.data[j-k]=list.data[j];
	}
	list.length=list.length-k;
	return true;
}//删除i后的k个元素 

//下面开始是基于整体建立顺序表的算法设计
template<class T>
void deletex1(sqlist<T>&list,T x){
	int j=0; 
	T* olddata=list.data;//存储旧数据 
	list.data=new T[list.cap];//开辟新表
	for(int i=0;i<list.length;i++){
		if(olddata[i]!=x){
			list.data[i-j]=olddata[i];//把不等于x的元素加入新表 
		}
		if(olddata[i]==x){
			j++;
		}
	} 
	delete[]olddata;//删除原有数据堆内存 
	list.length-=j;//修改长度 
} //删除重复元素x ,这个是自己写的，内存效率不高，逻辑没问题
template<class T>
void deletex2(sqlist<T>&list,T x){
	int k=0;
	for(int i=0;i<list.length;i++){
		if(list.data[i]!=x){
			list.data[k]=list.data[i];
			k++;
		}
	} 
	list.length=k;
}//删除重复元素x ,这个是把x的内存直接覆盖了；类似于建立新表
template<class T>
void deletex3(sqlist<T>&list,T x){
	int k=0;//累计等于x的元素个数
	for(int i=0;i<list.length;i++){
		if(list.data[i]!=x){
			list.data[i-k]=list.data[i];
		}
		else{
			k++;
		}
	} 
	list.length-=k;
}//删除重复元素x ,这个和我的想法一样，只是没新划分内存
template<class T>
void deletex4(sqlist<T>&list,T x){
	int j=-1;//记录一下要保存的元素的区间的最后一个元素的下标
	for (int i=0;i<list.length;i++)
	{
		if(list.data[i]!=x){
			list.data[j+1]=list.data[i];
			j++;
		}
	}
	list.length=j+1;
}//除重复元素x，自己写的区间法，课本上是进行的一个swap不是简单的覆盖，但我觉得，后面length都改变了，保存后面的x值没有意义啊 

//下面是有序顺序表的算法设计：
//二路归并
template<class T>
void merge(sqlist<T>&a,sqlist<T>&b,sqlist<T>&c)
{
	int na=a.length;
	int nb=b.length;
	int i=0;int j=0;
	while(i<na&&j<nb){
		if(a.data[i]<=b.data[j]){
			c.add(a.data[i]);
			i++;
		}
		else{
			c.add(b.data[j]);
			j++;	
		}
	}
	while(i<na){
		c.add(a.data[i]);
		i++;
	}
	while(j<nb){
		c.add(b.data[j]);
		j++;
	}
 }//时间复杂度为m+n(max{n,m});空间复杂度是m+n(其实也是max{n,m}) 

//两个等长有序数组求合并后的中位数,同样采用二路归并但是不需要存放进入新表 
template<class T>
T midle(sqlist<T>&a,sqlist<T>&b){
	int i=0;int j=0;
	int n=a.length;//等长所以只需设置一个值 
	int k=1;//用k记录是第几次，第n次时小的那个就是中位数 
	while(i<n&&j<n){
		if(a.data[i]<=b.data[j]){
			if(k==n){
				return a.data[i];
			}
			i++;
		} 
		else{
			if(k==n){
				return b.data[j];
			}
			j++;
		}
		k++;	
	} 
}
int main(){
	int arr1[3]={4,77,95};
	sqlist<int> list1;
	list1.createlist(arr1,3);//不要传进去arr[]； 
	int arr2[3]={15,44,28} ;
	sqlist<int> list2;
	list2.createlist(arr2,3);
	int arr3[0]={};
	sqlist<int> list3;
	list3.createlist(arr3,0);
	merge(list1,list2,list3);
	list3.print();
	cout<<midle(list1,list2)<<endl;
} 
class Solution {
public:
    int removeDuplicates(int* nums, int size) {
        if (size == 0) return 0; // 空表保护

        // j 是“占座指针”，记录最后一个唯一元素的位置
        int j = 0; 

        // i 是“跑腿指针”，从第二个元素开始扫
        for (int i = 1; i < size; i++) {
            // 只要发现 i 指向的值和 j 不一样，说明发现了一个“新数字”
            if (nums[i] != nums[j]) {
                j++;             // 给新数字腾出一个位置
                nums[j] = nums[i]; // 把新数字填进去（覆盖掉旧的重复值）
            }
        }

        // 因为下标从 0 开始，所以个数是 j + 1
        return j + 1;
    }
};//书上要求做的leetcode 26，有序的数组删除重复元素 
