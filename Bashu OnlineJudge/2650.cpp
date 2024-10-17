#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
#define MAXN 10000
using namespace std;
int n,c;
struct kkksc03{
	int l,r;
	int mark;
	int sum;
	int lc,rc;
}lin_toto[800001];//200000*4 
inline long long read()
{
	long long res=0,bj=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')bj=-1;c=getchar();}
	while(c>='0'&&c<='9'){res=res*10+c-48;c=getchar();}
	return res*bj;
}
void Himself65(int v)
{
	if(lin_toto[v].mark==-1)return;
	lin_toto[2*v].mark=lin_toto[2*v+1].mark=lin_toto[v].mark;
	lin_toto[2*v].lc=lin_toto[2*v].rc=lin_toto[2*v+1].lc=lin_toto[2*v+1].rc=lin_toto[v].mark;
	lin_toto[2*v].sum=lin_toto[2*v+1].sum=1;//以上两行是下传标记时容易忽略的部分。本题需要在更新mark同时更新sum与lc,rc 
	lin_toto[v].mark=-1;
}
void chen_zhe(int v,int l,int r,int x)
{
	if(l<=lin_toto[v].l&&r>=lin_toto[v].r)
	{
		lin_toto[v].mark=x;lin_toto[v].sum=1;
		lin_toto[v].lc=lin_toto[v].rc=x;
		return;
	}
	Himself65(v);
	int mid=lin_toto[v].l+lin_toto[v].r>>1;
	if(l<=mid)chen_zhe(2*v,l,r,x);
	if(r>mid)chen_zhe(2*v+1,l,r,x);
	lin_toto[v].sum=lin_toto[2*v].sum+lin_toto[2*v+1].sum;
	if(lin_toto[2*v].rc==lin_toto[2*v+1].lc)lin_toto[v].sum--;//记得要判断颜色相同 
	lin_toto[v].lc=lin_toto[2*v].lc;lin_toto[v].rc=lin_toto[2*v+1].rc;//更新sum 
}
void darkflames(int v,int l,int r)
{
	lin_toto[v].l=l,lin_toto[v].r=r;
	lin_toto[v].lc=c,lin_toto[v].rc=c;
	lin_toto[v].sum=1;lin_toto[v].mark=-1;
	if(l==r)return;
	int mid=l+r>>1;
	darkflames(2*v,l,mid);
	darkflames(2*v+1,mid+1,r);
}
int main()
{
	int x,y;
	c=read();n=read();
	darkflames(1,0,199999);//左开右闭区间 
	for(int i=1;i<=n;i++)
	{
		x=read();y=read();c=read();
		x+=100000;y+=100000;//偏移 
		if(y<x)continue;
		chen_zhe(1,x,y-1,c);
	}
	printf("%d",lin_toto[1].sum);
	return 0;
}
