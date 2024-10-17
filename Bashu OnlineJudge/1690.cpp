#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<algorithm>
using namespace std;
int t,n,m,rd[1005],g[1005];
inline int read(){
	int s=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s;
}
int f(int x){
	int fa;
	if(x==g[x])return x;
	fa=f(g[x]);
	g[x]=fa;
	return fa;
}
int main(){
	int i,j,k;
	t=read();
	while(t--){
		n=read();
		m=read();
		memset(rd,0,sizeof(rd));
		memset(g,0,sizeof(g));
		int x,y;
		for(i=1;i<=n;i++)g[i]=i;
		for(i=1;i<=m;i++){
			x=read();y=read();
			rd[x]++;rd[y]++;
			int fx=f(x),fy=f(y);
			if(fx!=fy)g[fx]=fy;
		}
		int num1=0,num2=0;
		for(i=1;i<=n;i++){
			if(i==g[i])num1++;
			if(rd[i]&1)num2++;
		}
		if((num2==0||num2==2)&&num1==1)printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}