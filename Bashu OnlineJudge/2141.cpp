#include<bits/stdc++.h>
using namespace std;
const int inf=0x7fffffff;
struct _{int x,y;}a[27][2];//记录每个矩形的四个角 横纵坐标的最大最小值 
bool map1[27][27],used[27],v[27];//map1为图与图之间的关系 used记录该字母是否出现 
int in[27],h,w,s[35][35],ans[27],tot;//in为入度，s记录图 
void init()
{
	int i,t,j;
	char ch;
	for(i=1;i<=26;i++)
	{
		a[i][1].x=a[i][1].y=inf;
		a[i][2].x=a[i][2].y=-inf;
	}
	cin>>h>>w;
	for(i=1;i<=h;i++)
	{
		for(j=1;j<=w;j++)
		{
			cin>>ch;
			if(ch=='.')t=0;
			else 
			{
				t=ch-'A'+1;
				if(a[t][1].x>i)a[t][1].x=i;
				if(a[t][1].y>j)a[t][1].y=j;
				if(a[t][2].x<i)a[t][2].x=i;
				if(a[t][2].y<j)a[t][2].y=j;
				used[t]=1;
			}
			s[i][j]=t;
		}
	}
}
void pre_top()
{
	int i,j,t1,t2;
	for(i=1;i<=26;i++)
	{
		if(used[i])
		{
			t1=a[i][1].y;t2=a[i][2].y;
			for(j=a[i][1].x;j<=a[i][2].x;j++)
			{
					if(s[j][t1]!=i&&!map1[i][s[j][t1]])map1[i][s[j][t1]]=1,in[s[j][t1]]++;
					if(s[j][t2]!=i&&!map1[i][s[j][t2]])map1[i][s[j][t2]]=1,in[s[j][t2]]++;
			}
			t1=a[i][1].x;t2=a[i][2].x;
			for(j=a[i][1].y;j<=a[i][2].y;j++)
			{
					if(s[t1][j]!=i&&!map1[i][s[t1][j]])map1[i][s[t1][j]]=1,in[s[t1][j]]++;
					if(s[t2][j]!=i&&!map1[i][s[t2][j]])map1[i][s[t2][j]]=1,in[s[t2][j]]++;
			}
			tot++;
		}
	}
}
void out(int x)
{
	int i,j,k;
	bool xx[27]={0};
	ans[0]++;
	ans[ans[0]]=x;
	v[x]=1;
	if(ans[0]!=tot)
	{
		for(k=1;k<=26;k++)if(map1[x][k]){in[k]--;xx[k]=1;}
		for(j=1;j<=26;j++)if(!in[j]&&!v[j]&&used[j])out(j);
		for(k=1;k<=26;k++)if(xx[k])in[k]++;
	}
	else 
	{
		for(i=1;i<=ans[0];i++)cout<<char(ans[i]+'A'-1);
		cout<<endl;
	}
	ans[0]--;
	v[x]=0;
}
int main()
{
	init();
	pre_top();
	for(int i=1;i<=26;i++)if(in[i]==0&&used[i])out(i);
	return 0;
}