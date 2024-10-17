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
const int Mod=998244353;
const int Phi=998244352;
const int N=8388610;
const int G=3;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int A[N],B[N],R[N];
int n,m,p,L,len,Ans;
int Minx,Miny,Maxx,Maxy;
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int id(int x,int y){return (x-1)*m+y;}
int mod(int x){return x>=Mod?x-Mod:x;}
void NTT(int a[],int n,int f){
	for(int i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
	for(int i=1;i<n;i<<=1){
		int Wn=Pow(G,Phi+f*Phi/(i<<1));
		for(int j=0;j<n;j+=(i<<1)){
			int W=1;
			for(int k=0;k<i;k++){
				int x=a[j+k],y=1ll*W*a[j+k+i]%Mod;
				a[j+k+i]=mod(x-y+Mod);
				a[j+k]=mod(x+y);
				W=1ll*W*Wn%Mod;
			}
		}
	}
	if(f==-1){
		int Inv=Pow(n,Mod-2);
		for(int i=0;i<n;i++)a[i]=1ll*a[i]*Inv%Mod;
	}
}
void Prepare(){
	scanf("%s",s+1);Minx=Miny=1;
	for(int i=1,x=1,y=1;i<=p;i++){
		x+=(s[i]=='s')-(s[i]=='w');
		y+=(s[i]=='d')-(s[i]=='a');
		Minx=min(Minx,x);
		Miny=min(Miny,y);
	}
	int sx=2-Minx,sy=2-Miny;
	B[n*m-id(sx,sy)+1]=1;
	Maxx=sx;Maxy=sy;
	for(int i=1,x=sx,y=sy;i<=p;i++){
		x+=(s[i]=='s')-(s[i]=='w');
		y+=(s[i]=='d')-(s[i]=='a');
		Maxx=max(Maxx,x);
		Maxy=max(Maxy,y);
		B[n*m-id(x,y)+1]=1;
	}
	len=1;L=0;while(len<=n*m*2){len<<=1;L++;}
	for(int i=0;i<len;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();p=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++){
			A[id(i,j)]=(s[j]=='1');
		}
	}
	Prepare();
//	cout<<Minx<<" "<<Miny<<" "<<Maxx<<" "<<Maxy<<endl;
//	for(int i=0;i<len;i++)cout<<A[i]<<" ";cout<<endl;
//	for(int i=0;i<len;i++)cout<<B[i]<<" ";cout<<endl;
	NTT(A,len,1);NTT(B,len,1);
	for(int i=0;i<len;i++)A[i]=1ll*A[i]*B[i]%Mod;
	NTT(A,len,-1);
//	for(int i=0;i<len;i++)cout<<A[i]<<" ";cout<<endl;
	for(int i=1;i<=n-Maxx+1;i++){
		for(int j=1;j<=m-Maxy+1;j++){
			Ans+=(A[id(i,j)+n*m]==0);
		}
	}
	printf("%d",Ans);
	return 0;
}