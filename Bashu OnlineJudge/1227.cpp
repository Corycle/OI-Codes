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
int n,c[100005];
int lowbit(int x){
	return (x&(-x));
}
void Add(int x,int y){
	for(int i=x;i<=100000;i+=lowbit(i)){
		c[i]+=y;
	}
}
int Ask(int x){
	int ans=0;
	for(int i=x;i>=1;i-=lowbit(i)){
		ans+=c[i];
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(1){
		n=read();
		if(n==0)break;
		memset(c,0,sizeof(c));
		for(int i=1;i<=n;i++){
			int x=read(),y=read();
			Add(x,1);Add(y+1,-1);
		}
		for(int i=1;i<=n;i++)printf("%d ",Ask(i));
		printf("\n");
	}
	return 0;
}