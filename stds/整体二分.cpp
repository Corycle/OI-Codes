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
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,qnt;
int c[N],ans[N],a[N];
struct node{
	int x,y,type,id,k;
}q[N*3],q1[N*3],q2[N*3];
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
				Add(q[i].id,q[i].y);
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
	for(int i=1;i<=t1;i++)if(q1[i].type==1)Add(q1[i].id,-q1[i].y);
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
		a[i]=read();
		q[++tot]=(node){a[i],1,1,i,0};
	}
	for(int i=1;i<=m;i++){
		char op[3];
		scanf("%s",op);
		if(op[0]=='C'){
			int x=read(),y=read();
			q[++tot]=(node){a[x],-1,1,x,0};
			a[x]=y;
			q[++tot]=(node){a[x],1,1,x,0};
		}
		if(op[0]=='Q'){
			int x=read(),y=read(),k=read();
			q[++tot]=(node){x,y,2,++qnt,k};
		}
	}
	Divide(1,tot,0,inf);
	for(int i=1;i<=qnt;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
/*
　　给定一个长度为N的已知序列A[i](1<=i<=N)，要求维护这个序列，能够支持以下两种操作：
　　1、查询A[i],A[i+1],A[i+2],…,A[j](1<=i<=j<=N)中，升序排列后排名第k的数。
　　2、修改A[i]的值为j。
　　所谓排名第k，指一些数按照升序排列后，第k位的数。例如序列{6,1,9,6,6}，排名第3的数是6，排名第5的数是9。
*/
