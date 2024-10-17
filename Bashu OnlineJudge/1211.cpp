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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int c[1500][1500],n,m;
int lowbit(int x){
	return (x&(-x));
}
void Add(int x,int y,int z){
	for(int i=x;i<=n;i+=lowbit(i)){
		for(int j=y;j<=m;j+=lowbit(j)){
			c[i][j]+=z;
		}
	}
}
int Ask(int x,int y){
	int ans=0;
	for(int i=x;i>=1;i-=lowbit(i)){
		for(int j=y;j>=1;j-=lowbit(j)){
			ans+=c[i][j];
		}
	}
	return ans;
}
int Sum(int a,int b,int x,int y){
	return Ask(x,y)-Ask(x,b-1)-Ask(a-1,y)+Ask(a-1,b-1);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(1){
		int p=read();
		if(p==0)n=m=read();
		if(p==1){
			int x=read()+1,y=read()+1,z=read();
			Add(x,y,z);
		}
		if(p==2){
			int a=read()+1,b=read()+1,x=read()+1,y=read()+1;
			printf("%d\n",Sum(a,b,x,y));
		}
		if(p==3)break;
	}
	return 0;
}