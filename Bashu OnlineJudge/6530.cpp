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
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,a[N],b[N],Ans[N],f[N][2][2];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n*2;i++)a[i]=read();
	for(int i=1;i<=n*2;i++)b[i]=read();
	f[1][0][0]=f[1][1][1]=1;
	for(int i=1;i<2*n;i++){
		if(a[i]<=a[i+1]){f[i+1][0][0]=max(f[i+1][0][0],f[i][0][0]+1);f[i+1][1][0]=max(f[i+1][1][0],f[i][1][0]);}
		if(b[i]<=b[i+1]){f[i+1][1][1]=max(f[i+1][1][1],f[i][1][1]+1);f[i+1][0][1]=max(f[i+1][0][1],f[i][0][1]);}
		if(a[i]<=b[i+1]){f[i+1][1][1]=max(f[i+1][1][1],f[i][1][0]+1);f[i+1][0][1]=max(f[i+1][0][1],f[i][0][0]);}
		if(b[i]<=a[i+1]){f[i+1][0][0]=max(f[i+1][0][0],f[i][0][1]+1);f[i+1][1][0]=max(f[i+1][1][0],f[i][1][1]);}
	}
	if(max(f[2*n][1][1],f[2*n][1][0])<n||max(f[2*n][0][0],f[2*n][0][1])<n){puts("-1");return 0; }
	int A=0,B=0,Max=inf; 
	for(int i=2*n;i>=1;i--){
		if(A+f[i][0][0]>=n&&B+f[i][1][0]>=n&&a[i]<=Max){Ans[i]=0;A++;Max=a[i];continue;}
		if(A+f[i][0][1]>=n&&B+f[i][1][1]>=n&&b[i]<=Max){Ans[i]=1;B++;Max=b[i];continue;}
		puts("-1");return 0;
	}
	for(int i=1;i<=2*n;i++)printf("%c",Ans[i]?'B':'A');
	return 0;
}