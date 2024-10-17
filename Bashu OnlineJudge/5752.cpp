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
const int M=1005;
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,f[M][N][1<<6];
int mod(int x){return x>=Mod?x-Mod:x;}
struct Tree{int fail,ch[2],tag[2];};
struct AC_Tree{
	Tree t[M];
	int tot,root;
	void Prepare(){tot=root=1;}
	void Insert(int len,int id,int x){
		int p=root;
		for(int i=1;i<=len;i++){
			int c=s[i]-'0';
			if(!t[p].ch[c])t[p].ch[c]=++tot;
			p=t[p].ch[c];
		}
		t[p].tag[x]|=(1<<(id-1));
	}
	void Build(){
		queue<int>q;q.push(root);
		while(q.size()){
			int x=q.front();q.pop();
			for(int i=0;i<2;i++){
				int y=t[x].ch[i];
				if(!y)continue;
				int p=t[x].fail;q.push(y);
				while(p&&!t[p].ch[i])p=t[p].fail;
				t[y].fail=(p?t[p].ch[i]:root);
				t[y].tag[0]|=t[t[y].fail].tag[0];
				t[y].tag[1]|=t[t[y].fail].tag[1];
			}
		}
	}
	int Next(int p,int x){
		while(p&&!t[p].ch[x])p=t[p].fail;
		return (p?t[p].ch[x]:root);
	}
	int Solve(){
		int Sta=(1<<n)-1;
		for(int i=1;i<=tot;i++)f[i][m][Sta]=1;
		for(int len=m-1;len>=0;len--){
			for(int i=tot;i>=1;i--){
				for(int S=0;S<=Sta;S++){
					S|=t[i].tag[0];
					int t0=Next(i,0),T0=S|t[t0].tag[0];
					int t1=Next(i,1),T1=S|t[t1].tag[0];
					if(len+1==m){
						T0|=t[t0].tag[1];
						T1|=t[t1].tag[1];
					}
					f[i][len][S]=mod(f[i][len][S]+f[t0][len+1][T0]);
					f[i][len][S]=mod(f[i][len][S]+f[t1][len+1][T1]);
				}
			}
		}
		return f[1][0][0];
	}
}tree;
bool Check(int len,int p){
	for(int i=len;i>p;i--){
		if(s[i]==s[p*2-i+1])return false;
	}
	return true;
}
void Prepare(int id,int len){
	tree.Insert(len,id,0);
	for(int i=len;i>len/2;i--){
		if(Check(len,i))tree.Insert(i,id,1);
	}
	reverse(s+1,s+len+1);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	tree.Prepare();
	n=read();m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		int len=strlen(s+1);
		Prepare(i,len);
		for(int i=1;i<=len;i++){
			s[i]=((s[i]-'0')^1)+'0';
		}
		Prepare(i,len);
	}
	tree.Build();
	printf("%d",tree.Solve());
	return 0;
}