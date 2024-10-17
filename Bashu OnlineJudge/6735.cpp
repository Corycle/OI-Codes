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
const int N=2000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot;
int top[N];
int lastans;
struct Stack{
	int data,next;
}st[N];
int Add(int x,int lst){
	tot++;
	st[tot].data=x;
	st[tot].next=lst;
	return tot;
}
int Pop(int x){
	if(x){
		printf("%d\n",st[x].data);
		lastans=st[x].data;
	}
	else lastans=0;
	return st[x].next;
}
int Ask(int x){
	if(x){
		printf("%d\n",st[x].data);
		lastans=st[x].data;
	}
	else lastans=0;
	return x;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		int op=(read()+lastans-1)%4+1,x=read();
//		cout<<"op:: "<<op<<endl;
		if(op==1)top[i]=Add(x^lastans,top[i-1]);
		if(op==2)top[i]=Pop(top[i-1]);
		if(op==3)top[i]=top[(x+lastans)%i];
		if(op==4)top[i]=Ask(top[i-1]);
	}
	return 0;
}