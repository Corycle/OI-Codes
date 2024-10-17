/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
const int M=350;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,num;
struct Ques{int l,r,a,b,id;}P[N*10];
int a[N],st[N],ed[N],pos[N],num1[N],num2[N],sum1[N],sum2[N],Ans1[N*10],Ans2[N*10];
bool cmp(Ques A,Ques B){return pos[A.l]!=pos[B.l]?pos[A.l]<pos[B.l]:A.r<B.r;}
void Prepare(){
	while(ed[num]!=n){num++;st[num]=ed[num-1]+1;ed[num]=min(ed[num-1]+M,n);}
	for(int i=1;i<=num;i++)for(int j=st[i];j<=ed[i];j++)pos[j]=i;
}
void Update(int x,int addv){
	num1[a[x]]+=addv;sum1[pos[a[x]]]+=addv;
	if(num1[a[x]]==1&&addv==1){num2[a[x]]++;sum2[pos[a[x]]]++;}
	if(num1[a[x]]==0&&addv==-1){num2[a[x]]--;sum2[pos[a[x]]]--;}
}
void Query(int l,int r,int id){
	int x=pos[l],y=pos[r];
	if(x==y)for(int i=l;i<=r;i++){Ans1[id]+=num1[i];Ans2[id]+=num2[i];}
	else{
		for(int i=l;i<=ed[x];i++){Ans1[id]+=num1[i];Ans2[id]+=num2[i];}
		for(int i=st[y];i<=r;i++){Ans1[id]+=num1[i];Ans2[id]+=num2[i];}
		for(int i=x+1;i<=y-1;i++){Ans1[id]+=sum1[i];Ans2[id]+=sum2[i];}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Prepare();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++){
		int l=read(),r=read(),a=read(),b=read();
		P[i]=(Ques){l,r,a,b,i};
	}
	sort(P+1,P+m+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;i++){
		while(l>P[i].l)Update(--l,1);
		while(r<P[i].r)Update(++r,1);
		while(l<P[i].l)Update(l++,-1);
		while(r>P[i].r)Update(r--,-1);
		Query(P[i].a,P[i].b,P[i].id);
	}
	for(int i=1;i<=m;i++)printf("%d %d\n",Ans1[i],Ans2[i]);
	return 0;
}