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
#include<set>
#define ll long long
#define set_it set<int>::iterator
using namespace std;
const int inf=0x3f3f3f3f;
const int N=5e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
char s[N];
struct Trie{
	int tot=1,root=1,ch[N][3],Max[N],pos[N];
	void Insert(int id){
		int p=root,len=strlen(s+1);
		for(int i=1;i<=len;i++){
			int c=s[i]-'a';
			if(!ch[p][c])ch[p][c]=++tot;
			p=ch[p][c];
			Max[p]=max(Max[p],id-pos[p]-1);
			pos[p]=id;
		}
	}
	int Query(){
		int p=root,len=strlen(s+1);
		for(int i=1;i<=len;i++)p=ch[p][s[i]-'a'];
		return (!p?n:Max[p]);
	}
}trie;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){scanf("%s",s+1);trie.Insert(i);}
	for(int i=1;i<=trie.tot;i++)trie.Max[i]=max(trie.Max[i],n-trie.pos[i]);
	for(int i=1;i<=m;i++){scanf("%s",s+1);printf("%d\n",trie.Query());}
	return 0;
}