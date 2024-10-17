#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
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
const int M=20000005;
const int N=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,ans;
int a[N],P[N],f[M],v[M],pos[N];
int main(){
//	freopen("arg.in","r",stdin);
//	freopen("arg.out","w",stdout);
	n=read();m=read();
	P[0]=f[0]=v[0]=1;
	for(int i=1;i<=n;i++)P[i]=P[i-1]*3;
	for(int i=1;i<=m;i++){
		a[i]=read();
		pos[a[i]]=i;
	}
	/*
		S是一个三进制数: 
			0表示还没加入 
			1表示加入了且仍在当前的LIS中 
			2表示加入了且被别的数代替了。 
	*/
	for(int S=0;S<P[n]-1;S++){
		if(f[S]){
			int x=S,sum=0,tot=1;
			for(int i=n;i>=1;i--){
				v[i]=x/P[i-1];//第i位上的数 
				sum+=(v[i]==1);//更新LIS长度 
				tot*=v[i];
				x%=P[i-1];
			}
			if(sum>m)continue;
			int k=0;
			for(int i=n;i>=1;i--){
				if(!v[i]){//还没选 
					if(pos[i]&&!v[a[pos[i]-1]])continue;
					if(k)f[S+P[i-1]+P[k-1]]+=f[S];
					else f[S+P[i-1]]+=f[S];
				}
				if(v[i]==1)k=i;//i后面第一个1的位置 
			}
			if(tot&&sum==m)ans+=f[S];
			//如果全部取完(即全部为1或2) 
		}
	}
	printf("%d",ans);
	return 0;
}