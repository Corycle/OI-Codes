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
const int Maxn=1e6+5;
const int N=6e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,cnt,h[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
struct Tree{
	int root,tot;
	int ch[N][26],dep[N],fail[N];
	void Init(){root=tot=1;}
	int Insert(int id){
		int p=root,len=strlen(s+1);
		for(int i=1;i<=len;i++){
			int x=s[i]-'a';
			if(!ch[p][x])ch[p][x]=++tot;
			p=ch[p][x];dep[p]=i;
		}
		return p;
	}
	void Build(){
		queue<int>q;fail[1]=1;
		for(int i=0;i<26;i++){
			if(!ch[1][i])ch[1][i]=1;
			else {q.push(ch[1][i]);fail[ch[1][i]]=1;}
		}
		while(q.size()){
			int x=q.front();q.pop();
			for(int i=0;i<26;i++){
				if(ch[x][i]){
					q.push(ch[x][i]);
					fail[ch[x][i]]=ch[fail[x]][i];
				}
				else ch[x][i]=ch[fail[x]][i];
			}
		}
		for(int i=2;i<=tot;i++)Add(fail[i],i);
	}
}tree;
int main(){
//	freopen("string.in","r",stdin);
//	freopen("string.out","w",stdout);
	
	return 0;
}
