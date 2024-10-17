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
const int N=100005;
const int M=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,blk,num;
int s[N],pos[N],sum[N],used[N];
int ed[M],st[M],dlt[M],ans[M*M];
struct ques{
	int l,r,a,b,id;
}q[M*M];
bool cmp(ques x,ques y){
	if(pos[x.l]==pos[y.l])return x.r<y.r;
	return pos[x.l]<pos[y.l];
}
void Ask(int k){
	int l=q[k].a,r=q[k].b;
	int x=pos[l],y=pos[r];
	if(x==y)for(int i=l;i<=r;i++)ans[q[k].id]+=sum[i];
	else{
		for(int i=l;i<=ed[x];i++)ans[q[k].id]+=sum[i];
		for(int i=st[y];i<=r;i++)ans[q[k].id]+=sum[i];
		for(int i=x+1;i<=y-1;i++)ans[q[k].id]+=dlt[i];
	}
}
void update(int p,int addv){
	used[s[p]]+=addv;
	if(addv==1&&used[s[p]]==1){
		sum[s[p]]++;
		dlt[pos[s[p]]]++;
	}
	if(addv==-1&&used[s[p]]==0){
		sum[s[p]]--;
		dlt[pos[s[p]]]--;
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	num=blk=sqrt(n);
	for(int i=1;i<=n;i++){
		s[i]=read();
		pos[i]=(i-1)/blk+1;
	}
	for(int i=1;i<=num;i++){
		st[i]=ed[i-1]+1;
		ed[i]=ed[i-1]+blk;
	}
	if(ed[num]!=n){
		num++;
		st[num]=ed[num-1]+1;
		ed[num]=n;
	}
	for(int i=1;i<=m;i++){
		q[i].id=i;
		q[i].l=read();q[i].r=read();
		q[i].a=read();q[i].b=read();
	}
	sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;i++){
		while(l<q[i].l)update(l++,-1);
		while(l>q[i].l)update(--l,1);
		while(r<q[i].r)update(++r,1);
		while(r>q[i].r)update(r--,-1);
		Ask(i);
	}
	for(int i=1;i<=m;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}