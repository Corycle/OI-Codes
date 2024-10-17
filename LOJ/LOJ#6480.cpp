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
#define mp make_pair
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
const int M=11;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[M][N];
vector<int>P[N];
int n,m,b[N],nxt[N];
bool cmp(int x,int y){return mp(P[x],x)<mp(P[y],y);}
void KMP(int id,char s[]){
	int len=strlen(s+1);
	for(int i=2,j=0;i<=len;i++){
		while(j&&s[i]!=s[j+1])j=nxt[j];
		if(s[i]==s[j+1])j++;
		nxt[i]=j;
	}
	for(int i=len;i&&2*len-i<=n;i=nxt[i])P[id].push_back(i);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		scanf("%s",s[i]+1);
		KMP(i,s[i]);b[i]=i;
	}
	sort(b+1,b+m+1,cmp);
	for(int i=1;i<=m;i++)printf("%s\n",s[b[i]]+1);
	return 0;
}
