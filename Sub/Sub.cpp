#include <iostream>
using namespace std;

int main(void)
{
 cout<<"please input the number:\t";
 int n;
 cin>>n;
 int* integer = new int[n+1];
 cout<<"\nplease input each number : \n";
 for(int i=1; i<=n; i++){
  cout<<i<<" : ";
  cin>>integer[i];
 }
 
 cout<<"the result : \n";
 cout<<" null\n";
 for(i=1; i<=n; i++)
  cout<<integer[i]<<" ";
 cout<<endl;

 int num=0;
 for(i=2; i<=n; i++){
  int temp=1;
  while(temp+i-1<=n){
   int s=temp+1;
   while(s+i-2<=n){
    cout<<integer[temp]<<"  ";
    for(int cur=s; cur<s+i-1; cur++)
     cout<<integer[cur]<<"  ";
    cout<<"    ";
    s+=1;
   }
   temp++;
  }
  cout<<endl;
 }

 return 0;
}
