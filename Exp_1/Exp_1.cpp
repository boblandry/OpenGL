#include<iostream>
using namespace std;

//交换两个数
void Swap(int &a, int &b)
{
	int i=b;
	b=a;
	a=i;
}

//利用递归全排列
void Perm(int list[], int k, int m)
{
	int i;
	if (k==m)
	{
		for (i=0; i<=m; i++)
			cout<<list[i]<<"    ";
		cout<<endl;
	}
	else
		for (i=k; i<=m; i++)
		{
			Swap(list[k], list[i]);
			Perm(list, k+1, m);
			Swap(list[k], list[i]);
		}
}



//主函数
void main()
{
	int size;
	cout<<"请输入个数:"<<endl;
	cin>>size;
	int *list = new int[size];
	cout<<"请输入..."<<endl;
	for (int i=0; i<size; i++)
		cin>>list[i];
	cout<<"全排列为:"<<endl;
	Perm(list,0,size-1);
	cout<<"子集为:"<<endl<<"{φ}"<<endl;
	for(i=1; i<=size; i++)
		cout<<"{"<<list[i-1]<<"} ";
	cout<<endl;

	int num=0;
	for(i=2; i<=size; i++)
	{
		int temp=1;
		while(temp+i-1<=size)
		{
			int s=temp+1;
			
			while(s+i-2<=size)
			{
				cout<<"{ ";
				cout<<list[temp-1]<<" ";
				for(int cur=s; cur<s+i-1; cur++)
					cout<<list[cur-1]<<" ";
				cout<<"}    ";
				s+=1;
			}
			temp++;
		}
		cout<<endl;
	}
}