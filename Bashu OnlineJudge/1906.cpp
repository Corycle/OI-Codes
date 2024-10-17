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
const int N=100005;
const int M=26;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char a[N];
int n,nxt[N],f[N][M];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)nxt[i]=i-read();
//	for(int i=1;i<=n;i++)cout<<nxt[i]<<" ";cout<<endl;
	a[1]='a';
	for(int i=2,j=0;i<=n;i++){
		j=nxt[i-1];
		while(j>0&&j>=nxt[i]){//a[i]!=a[j+1];
			f[i][a[j+1]-'a']=1;
			j=nxt[j];
		}
		if(nxt[i]==0){
			for(int k=1;k<26;k++){
				if(!f[i][k]){a[i]='a'+k;break;}
			}
		}
		else a[i]=a[nxt[i]];
	}
	printf("%s",a+1);
	return 0;
}