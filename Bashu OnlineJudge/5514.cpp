#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p,num,blk,Ans;
int a[N],sum[N],ans[N],pos[N];
struct Ques{int l,r,id;}q[N];
bool cmp(Ques x,Ques y){
	if(pos[x.l]==pos[y.l])return x.r<y.r;
	return pos[x.l]<pos[y.l];
}
void Update(int x,int addv){
	if(addv==1){
		Ans+=sum[p^a[x]];
		sum[a[x]]++;
	}
	if(addv==-1){
		sum[a[x]]--;
		Ans-=sum[p^a[x]];
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();p=read();
	num=blk=sqrt(n);
	for(int i=1;i<=n;i++){
		a[i]=a[i-1]^read();
		pos[i]=(i-1)/blk+1;
	}
	for(int i=1;i<=m;i++){
		q[i].id=i;
		q[i].l=read()-1;
		q[i].r=read();
	}
	int l=1,r=0;
	sort(q+1,q+m+1,cmp);
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