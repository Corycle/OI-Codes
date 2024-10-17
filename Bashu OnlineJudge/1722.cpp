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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot;
int c[N],ans[N];
struct node{
	int x,y,type,id,k;
}q[N*2],q1[N*2],q2[N*2];
int lowbit(int x){
	return x&(-x);
}
void Add(int x,int y){
	for(int i=x;i<=n;i+=lowbit(i)){
		c[i]+=y;
	}
}
int Ask(int x){
	int sum=0;
	for(int i=x;i>=1;i-=lowbit(i)){
		sum+=c[i];
	}
	return sum;
}
void Divide(int ql,int qr,int l,int r){
	if(ql>qr)return;
	if(l==r){
		for(int i=ql;i<=qr;i++){
			if(q[i].type==2)ans[q[i].id]=l;
		}
		return;
	}
	int mid=(l+r)>>1;
	int t1=0,t2=0;
	for(int i=ql;i<=qr;i++){
		if(q[i].type==1){
			if(q[i].x<=mid){
				Add(q[i].id,1);
				q1[++t1]=q[i];
			}
			else q2[++t2]=q[i];
		}
		if(q[i].type==2){
			int sum=Ask(q[i].y)-Ask(q[i].x-1);
			if(sum>=q[i].k)q1[++t1]=q[i];
			else{
				q[i].k-=sum;
				q2[++t2]=q[i];
			}
		}
	}
	int p=ql;
	for(int i=1;i<=t1;i++)if(q1[i].type==1)Add(q1[i].id,-1);
	for(int i=1;i<=t1;i++)q[p++]=q1[i];
	for(int i=1;i<=t2;i++)q[p++]=q2[i];
	Divide(ql,ql+t1-1,l,mid);
	Divide(ql+t1,qr,mid+1,r);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	//x,y,type,id,k;
	for(int i=1;i<=n;i++){
		int x=read();
		q[++tot]=(node){x,0,1,i,0};
	}
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),k=read();
		q[++tot]=(node){x,y,2,i,k};
	}
	Divide(1,tot,-inf,inf);
	for(int i=1;i<=m;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}