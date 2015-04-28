#include<iostream>
using namespace std;
#define for if(false){}else for

//选择排序算法
void SelectSort(int list[],int n)
{
	int i,j,k;
	int x;
	for(i=0;i<n;i++)
	{
		k=i;
		for(j=i+1;j<n;j++)
			if(list[j]<list[k])  k=j;
		if(i!=k)
		{
			x=list[i];
			list[i]=list[k];
			list[k]=x;
			for (int j=0; j<n; j++)
			cout<<list[j]<<"  ";
		cout<<endl;
		}	
	}
}

//冒泡排序算法
void BubbleSort(int list[], int n)
{
	int m,i=0,j,flag=1; //当flag为0则停止排序
	int x;
	m=n-1;//m表示趟数
	while((m>0)&&(flag==1))
	{ 
		flag=0; //开始时元素未交换
		for(j=0; j<m; j++)
			if(list[j]>list[j+1])
			{ //发生逆序 
				flag=1;
				x=list[j];
				list[j]=list[j+1];
				list[j+1]=x;
				
				for (int j=0; j<n; j++)
					cout<<list[j]<<"  ";
				cout<<endl;
			} //交换，并标记发生了交换
		m--;
	}
}

//插入排序算法
void InsertSort(int list[], int n)
{
	int j;
    for(int i=1;i<n;i++)  //i表示插入次数，共进行n-1次插入
		if(list[i]<list[i-1])   //将list[i]插入到有序区list[0],…,list[i-1]中，
		//且a[i]<a[i-1]
		{
		int x=list[i];   //把待排序元素赋给 x
		//从a[i-2]开始比较
		for(int j=i-1; (x<list[j])&&(j>=0); j--)
			list[j+1]=list[j]; //从list[i-1]开始后移一位		
		list[j+1]=x;//直到找到一个元素，插入到正确位置 
		
		for (int k=0; k<n; k++)
			cout<<list[k]<<"  ";
		cout<<endl;
	}
}

//基数排序算法
//计算需要几次箱子排序
int maxBit(int list[],int size)
{
    int maxNum = 0;
    int counts = 0;
    for(int i = 1; i < size; i++)
    {
        if(list[maxNum] < list[i])
            maxNum = i;
    }
    int maxNumber = list[maxNum];
    while(maxNumber != 0)
    {
        counts++;
        maxNumber = maxNumber/10;
    }
    return counts;
}

void radixSort(int list[],int size)
{
    int maxB = maxBit(list,size);
    int *bin = new int[10];
    int *temp = new int[size];
    int radix = 1;

    //cout << "-----------------------" << endl;
	//最外层 进行多少次箱子排序
    for(int i = 0; i < maxB; i++)
    {
		//初始化
        for(int j = 0; j <10; j++)
            bin[j] = 0;
		//记录个数
	
        for(int k = 0; k < size; k++)
        {
            int x = list[k]/radix%10;
            bin[x]++;
        }
	
        for(int j = 1; j < 10; j++)
        {
            bin[j] = bin[j] + bin [j - 1];
        }
		
        for(int k = size-1; k >= 0; k--)
        {
            int x = list[k]/radix%10;
            temp[bin[x]-1] = list[k];
            bin[x]--;
        }
		
        for(int k = 0; k < size; k++)
            list[k] = temp[k];
        //cout << "第" << (i+1) << "次：";
		//输出过程
        for(int i = 0; i < size; i++)
			cout << list[i] << "  ";
		cout << endl;
        radix *= 10;
    }
    delete [] bin;
    delete [] temp; 
}

//快速排序算法
void qksort(int list[], int t, int w)
{
	int i, j;
	int x;
	if(t>=w)  
		return;
	i=t; j=w; x=list[i];
	while(i<j)
	{
		while((i<j)&&(list[j]>=x))  
			j--;
		if(i<j) 
		{ 
			list[i]=list[j]; 
			i++; 
		}
		while((i<j)&&(list[i]<=x))  
			i++;
		if(i<j) 
		{ 
			list[j]=list[i]; 
			j--; 
		}
	}
	list[i]=x;
	qksort(list,t,j-1);
	qksort(list,j+1,w);
}
//归并排序算法
//待完善

void main()
{
	int size;
	cout<<"请输入个数:"<<endl;
	cin>>size;
	int *list = new int[size];
	cout<<"请输入..."<<endl;
	for (int i=0; i<size; i++)
		cin>>list[i];
	cout<<"请选择排序方式：（输入1，2，3，4，5其中一种即可）"<<endl;
	cout<<"1.选择排序"<<endl;
	cout<<"2.冒泡排序"<<endl;
	cout<<"3.插入排序"<<endl;
	cout<<"4.基数排序"<<endl;
	cout<<"5.快速排序"<<endl;
	int n;
	cin>>n;
	if (n==1)
		SelectSort(list,size);
	else if(n==2)
		BubbleSort(list,size);
	else if(n==3)
		InsertSort(list,size);
	else if(n==4)
		radixSort(list,size);
	else if(n==5)
	{
		cout<<"过程暂无..."<<endl;
		qksort(list, 0, size-1);
	}
	else cout<<"输入无法识别，请重新尝试..."<<endl;
	cout<<"最终结果为："<<endl;
	for(int i = 0; i < size; i++)
			cout << list[i] << "  ";
		cout << endl;
}
