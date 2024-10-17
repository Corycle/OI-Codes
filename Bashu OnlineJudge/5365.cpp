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
const int M=60;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,Ans;
struct Tree{int ch[10],sum,Max;vector<int>ans;};
struct Trie{
	int tot=1;
	Tree t[N*M];
	void Update(int addv){
		int p=1,len=strlen(s+1);
		for(int i=1;i<=len;i++){
			int x=s[i]-'a';
			if(!t[p].ch[x]){
				t[p].ch[x]=++tot;
				t[tot].ans.push_back(0);
			}
			p=t[p].ch[x];t[p].sum+=addv;
			if(t[p].sum>t[p].Max){
				t[p].ans.push_back(m);
				t[p].Max=t[p].sum;
			}
		}
	}
	int Query(int num){
		int p=1,len=strlen(s+1);
		for(int i=1;i<=len;i++){
			int x=s[i]-'a';
			if(!t[p].ch[x])return -1;
			p=t[p].ch[x];
		}
		if(num>t[p].Max)return -1;
		return t[p].ans[num];
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(m=1;m<=n;m++){
		int op=read();
		if(op==1){scanf("%s",s+1);tree.Update(1);}
		if(op==2){scanf("%s",s+1);tree.Update(-1);}
		if(op==3){
			scanf("%s",s+1);
			ll a=read(),b=read(),c=read();
			Ans=tree.Query((a*abs(Ans)+b)%c+1);
			printf("%d\n",Ans);
		}
	}
	return 0;
}