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
const int N=6005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
string S,F[N];
int n,m,id[N],PosA[N],PosB[N],nxt[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();cin>>S;S=" "+S;
	for(int i=1,n1=0,n2=0;i<=n*2;i++){
		if(S[i]=='a')PosA[id[i]=++n1]=i;
		if(S[i]=='b')PosB[id[i]=++n2]=i;
	}
	id[PosA[n+1]=PosB[n+1]=n*2+1]=n+1;
	for(int i=1,j=1;i<=n+1;i++)while(j<min(PosA[i],PosB[i])){nxt[j]=i;j++;}
	for(int i=n;i>=1;i--){
		if(PosA[i]<PosB[i])F[i]="ab"+F[nxt[PosB[i]]];
		else{
			int j=PosB[i],k=PosA[i];
			while(j<=k&&(id[j]<=i||PosB[id[j]]<=k)){
				if(id[j]>=i){F[i]+=S[j];k=max(k,PosA[id[j]]);}
				j++;
			}
			F[i]+=F[id[j]];
		}
		F[i]=max(F[i],F[i+1]);
	}
	cout<<F[1]<<'\n';
	return 0;
}
