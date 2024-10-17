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
const int N=4000005;
const int M=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[M];
string S[M];
int n,m,cnt,tot=1,lst=1,root=1;
int fa[N],sum[N],vis[N],len[N],ch[N][27];
void SAM(int num){
	int x=lst,fx=++tot;len[fx]=len[x]+1;
	while(x&&!ch[x][num]){ch[x][num]=fx;x=fa[x];}
	if(!x)fa[fx]=root;
	else{
		int y=ch[x][num];
		if(len[y]==len[x]+1)fa[fx]=y;
		else{
			int fy=++tot;len[fy]=len[x]+1;
			sum[fy]=sum[y];vis[fy]=vis[y];
			for(int i=1;i<=26;i++)ch[fy][i]=ch[y][i];
			fa[fy]=fa[y];fa[y]=fa[fx]=fy;
			while(x&&ch[x][num]==y){ch[x][num]=fy;x=fa[x];}
		}
	}
	x=fx;
	while(x&&vis[x]!=cnt){
		vis[x]=cnt;
		sum[x]++;
		x=fa[x];
	}
	lst=fx;
}
int Ask(int id){
	int p=root;
	int Len=S[id].length();
	for(int i=0;i<Len;i++){
		int num=S[id][i]-'a'+1;
		if(ch[p][num])p=ch[p][num];
		else return 0;
	}
	return sum[p];
}
int main(){
//	freopen("string.in","r",stdin);
//	freopen("string.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		S[i]=(string)(s);
	}
	m=read();
	while(m--){
		int op=read();
		if(op==1){
			lst=root;cnt++;
			scanf("%s",s+1);
			int Len=strlen(s+1);
			for(int i=1;i<=Len;i++){
				SAM(s[i]-'a'+1);
			}
		}
		if(op==2){
			int x=read();
			printf("%d\n",Ask(x));
		}
	}
	return 0;
}