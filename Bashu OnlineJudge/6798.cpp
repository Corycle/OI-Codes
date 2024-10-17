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
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,E,Ans,a[N][N],S[N],T[N],px[N],py[N],wx[N],wy[N],pre[N],slack[N];
void KM(){
	for(int i=1;i<=n;i++){wx[i]=inf;wy[i]=0;px[i]=0;py[i]=0;}
	for(int Step=1;Step<=n;Step++){
		for(int i=1;i<=n;i++){slack[i]=inf;S[i]=T[i]=pre[i]=0;}
		for(int i=1;i<=n;i++){
			if(px[i])continue;S[i]=1;
			for(int j=1;j<=n;j++){
				int tmp=wx[i]+wy[j]-a[i][j];
				if(tmp<slack[j]){slack[j]=tmp;pre[j]=i;}
			}
		}
		bool flag=true;
		while(flag){
			int dlt=inf;
			for(int i=1;i<=n;i++)if(!T[i])dlt=min(dlt,slack[i]);
			for(int i=1;i<=n;i++){
				if(S[i])wx[i]-=dlt;
				if(T[i])wy[i]+=dlt;
				else slack[i]-=dlt;
			}
			for(int i=1;i<=n;i++){
				if(!T[i]&&!slack[i]){
					T[i]=1;
					if(py[i]){
						int x=py[i];S[x]=1;
						for(int y=1;y<=n;y++){
							if(T[y])continue;
							int tmp=wx[x]+wy[y]-a[x][y];
							if(tmp<slack[y]){slack[y]=tmp;pre[y]=x;}
						}
					}
					else{
						int x=pre[i],y=i;
						while(x){int tmp=px[x];px[py[y]=x]=y;y=tmp;x=pre[y];}
						flag=false;break;
					}
				}
			}
		}
	}
	for(int i=1;i<=n;i++)Ans+=a[i][px[i]];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();E=read();
	for(int i=1;i<=E;i++){
		int x=read(),y=read();
		if(n<=m)a[x][y]=max(a[x][y],read());
		else a[y][x]=max(a[y][x],read());
	}
	if(n>m)swap(n,m);
	KM();
	printf("%d",Ans);
	return 0;
}