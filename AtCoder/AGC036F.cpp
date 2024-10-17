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
int n,m,tot,Ans,Mod,l[N],r[N],f[N][N];
int mod(int x){return x>=Mod?x-Mod:x;}
struct Node{
	int x,y,id;
	friend bool operator<(Node A,Node B){
		return A.x!=B.x?A.x<B.x:(A.y!=B.y?A.y<B.y:A.id>B.id);
	}
}P[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Mod=read();
	for(int i=0;i<2*n;i++){
		r[i]=min((int)(floor(sqrt(4*n*n-i*i))),2*n-1);
		if(i<n){
			l[i]=(int)(ceil(sqrt(n*n-i*i)));
			P[++tot]=(Node){l[i]-1,r[i],i};
		}
		else P[++tot]=(Node){r[i],l[i]-1,i};
	}
	sort(P+1,P+tot+1);
	for(int k=0;k<=n;k++){
		int t=0;
		memset(f,0,sizeof(f));
		f[0][0]=1;
		for(int i=1;i<=tot;i++){
			int x=P[i].id;
			for(int j=0;j<=k;j++){
				if(x>=n){
					int c=r[x]+1-(i-1-(t-j));
					if(c>0)f[i][j]=1ll*f[i-1][j]*c%Mod;
				}
				else{
					int c=r[x]+1-(2*n-1-(x-(k-j)));
					if(c>0)f[i][j]=1ll*f[i-1][j]*c%Mod;
					if(j){
						c=l[x]-(i-1-(t-j+1));
						if(c>0)f[i][j]=mod(f[i][j]+1ll*f[i-1][j-1]*c%Mod);
					}
				}
			}
			t+=(x<n);
		}
		Ans=mod(Ans+1ll*(k&1?Mod-1:1)*f[tot][k]%Mod);
	}
	printf("%d",Ans);
	return 0;
}
