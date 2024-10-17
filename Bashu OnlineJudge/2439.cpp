#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
long long n,m;
int a[2001];
int vis[2001];
long long ans[2001];
int flag=1;//表示无解 
void dfs(int x,int pos,long long sum)
//ans[x]表示所求子集中第x位置的值
//pos表示对给定数组a,进行搜索时的起点位置,防止重复找 
//sum表示解数组ans中1到x-1的和 
{
	if(sum==m)
	{
		for(int i=1;i<x;i++) cout<<ans[i]<<" ";
		flag=0;//此时有解,flag标记为0 
		return;
	}
	if(x==n+1)return; //超出总数,本次查找结束 
	for(int i=pos;i<=n;i++)
	//例举所有可能的下标,初始位置不断向前改变,结束位置不变 
	{
		if(flag==0)return;
		//有解且已输出一个,后续不再回溯查找新的解，直接return 
		if(!vis[i]&&(sum+a[i])<=m)
		//当第i个位置上的数未被使用,且相加后和不大于题目所给值才可能有解 
		{
			ans[x]=a[i];//解数组ans第x位置上的值为给定数组a中的第i个数 
			vis[i]=1;   //给定数组a中的第i个数已用 
			sum+=a[i]; 
			dfs(x+1,i+1,sum); //搜索解子集ans中下一个位置(x+1)的状态 
			ans[x]=0;   //恢复状态 
			sum-=a[i];
			vis[i]=0;   //恢复状态 
		}
	}
}
int main()
{
	cin>>n>>m;
	int s=0;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		s+=a[i];
	}
	if(s<m)//很重要的剪枝！！如果所有的数加起来都小于c，那么不可能有解。
    {
        cout<<"No Solution!";  
        return 0;  
    }
	dfs(1,1,0);
	if(flag) cout<<"No Solution!";
	return 0;
}