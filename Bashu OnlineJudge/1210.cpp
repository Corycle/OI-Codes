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
int n,c[1005][1005],m;
int lowbit(int x){
	return (x&(-x));
}
void Add(int x,int y,int z){
	for(int i=x;i<=n;i+=lowbit(i)){
		for(int j=y;j<=n;j+=lowbit(j)){
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
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();m=read();
		memset(c,0,sizeof(c));
		while(m--){
			char s[1];
			scanf("%s",s);
			if(s[0]=='Q'){
				int x=read(),y=read();
				printf("%d\n",Ask(x,y)%2);
			}
			if(s[0]=='C'){
				int x=read(),y=read(),a=read(),b=read();
				Add(x,y,1);Add(a+1,b+1,1);
				Add(x,b+1,-1);Add(a+1,y,-1);
			}
		}
		cout<<endl;
	}
	return 0;
}