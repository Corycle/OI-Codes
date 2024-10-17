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
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,num,blk,Ans;
int a[N],pos[N],sum[N],ans[N];
struct Ques{
	int l,r,id,ans;
}q[N];
bool cmp(Ques x,Ques y){
	if(pos[x.l]==pos[y.l])return x.r<y.r;
	return pos[x.l]<pos[y.l];
}
void Update(int x,int addv){
	sum[a[x]]+=addv;
	if(addv==1&&sum[a[x]]==1)Ans++;
	if(addv==-1&&sum[a[x]]==0)Ans--;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	num=blk=(int)(sqrt(n));
	for(int i=1;i<=n;i++){
		a[i]=read();
		pos[i]=(i-1)/blk+1;
	}
	m=read();
	for(int i=1;i<=m;i++){
		q[i].id=i;
		q[i].l=read();
		q[i].r=read();
	}
	sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;i++){
		while(l>q[i].l)Update(--l,1);
		while(r<q[i].r)Update(++r,1);
		while(l<q[i].l)Update(l++,-1);
		while(r>q[i].r)Update(r--,-1);
		ans[q[i].id]=Ans;
	}
	for(int i=1;i<=m;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
