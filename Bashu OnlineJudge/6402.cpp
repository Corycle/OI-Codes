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
const int N=50005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,S,num;
int a[N],vis[N],sta[N];
int main(){
//	freopen("aorder.in","r",stdin);
//	freopen("aorder.out","w",stdout);
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=1;i<=n;i++)vis[a[i]=s[i]-'a']=1;
	for(int i=n;i>=1;i--)sta[i]=sta[i+1]|(1<<a[i]);
	for(int i=0;i<26;i++)if(vis[i]){num++;S|=(1<<i);}
	for(int i=1,lst=0;i<=num;i++){
		int pos=0;
		for(int j=lst+1;j<=n;j++){
			if(vis[a[j]]&&(sta[j]&S)==S){
				if(!pos||a[j]<a[pos])pos=j;
			}
		}
		lst=pos;
		vis[a[pos]]=0;
		S^=(1<<a[pos]);
		printf("%c",s[pos]);
	}
	return 0;
}