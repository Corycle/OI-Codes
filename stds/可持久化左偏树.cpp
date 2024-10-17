#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot;
int root[N*100];
struct tree{
	int l,r,dis,data;
}t[N*100];
void Add(){
	int x=read();
	root[++n]=++tot;
	t[tot].data=x;
}
int Merge(int x,int y){
	if(!x||!y)return x+y;
	if(t[x].data<t[y].data)swap(x,y);
	int k=++tot;
	t[k]=t[x];
	t[k].r=Merge(t[k].r,y);
	if(t[t[k].l].dis<t[t[k].r].dis)swap(t[k].l,t[k].r);
	if(!t[k].r)t[k].dis=0;
	else t[k].dis=t[t[k].r].dis+1;
	return k;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	m=read();
	while(m--){
		int k=read();
		if(k==1)Add();
		if(k==2){
			int x=read()%n+1,y=read()%n+1;
			root[++n]=Merge(root[x],root[y]);
		}
		if(k==3){
			int x=read()%n+1;
			printf("%d\n",t[root[x]].data);
		}
	}
	return 0;
}
/*
　　有m个操作，
　　如果k=1，输入一个x，新建一个集合只有元素x；
　　k=2，输入x和y，a=x%当前集合个数+1，b=y%当前集合个数+1，新建一个集合为第a个集合和第b个集合的并；
　　k=3，输入一个x，a=x%当前集合个数+1，查询第a个集合中最大的元素，保证第一个操作k=1，查询的时候总有集合存在而且集合都是可重集。
*/
