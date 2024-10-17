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
const int N=525000;
const int G=3;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,len,L,R[N],a[N],t1[N],t2[N],Ans[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){
	int ans=1;
	while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}
	return ans;
}
void Prepare(int maxn){
	len=1;L=0;while(len<=maxn){len<<=1;L++;}
	for(int i=0;i<len;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
}
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
void Update(int a[]){
	a[1]++;
	for(int i=1;i<=a[0];i++){a[i+1]+=a[i]/10;a[i]%=10;}
	if(a[a[0]+1])a[0]++;
}
void Multi(int a[],int b[],int c[]){
	int n=a[0],m=b[0];Prepare(n+m);
	for(int i=0;i<n;i++)t1[i]=a[i+1];
	for(int i=0;i<m;i++)t2[i]=b[i+1];
	for(int i=n;i<len;i++)t1[i]=0;
	for(int i=m;i<len;i++)t2[i]=0;
	NTT(t1,len,1);NTT(t2,len,1);
	for(int i=0;i<len;i++)t1[i]=1ll*t1[i]*t2[i]%Mod;
	NTT(t1,len,-1);
	for(int i=1;i<=len;i++)c[i]=t1[i-1];
	for(int i=1;i<=len;i++){c[i+1]+=c[i]/10;c[i]%=10;}
	c[0]=len;while(!c[c[0]])c[0]--;
}
void Div(int a[],int b[],int v){
	for(int i=a[0];i>=1;i--){b[i]=a[i]/v;a[i-1]+=a[i]%v*10;}
	b[0]=a[0];while(!b[b[0]])b[0]--;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",s+1);n=a[0]=strlen(s+1);
	for(int i=1;i<=n;i++)a[i]=s[n-i+1]-'0';
	Ans[0]=Ans[1]=1;
	Update(a);Multi(Ans,a,Ans);
	Update(a);Multi(Ans,a,Ans);
	Update(a);Multi(Ans,a,Ans);
	Update(a);Multi(Ans,a,Ans);
	for(int i=0;i<=Ans[0];i++)a[i]=Ans[i];
	Div(a,Ans,24);
	for(int i=Ans[0];i>=1;i--)printf("%d",Ans[i]);
	return 0;
}