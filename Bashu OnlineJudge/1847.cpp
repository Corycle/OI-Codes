#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=500005;
const int M=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int q[N],Len[N];
char Map[M][M],ch[M];
int n,m,T,root=1,cnt=1;
int cx[8]={-1,-1,0,1,1,1,0,-1};
int cy[8]={0,1,1,1,0,-1,-1,-1};
struct node{int l,r,d;}ans[N];
struct Trie{
	int son[30],fail,count;
	void prepare(){
		memset(son,0,sizeof(son));
		fail=count=0;
	}
}t[N];
void Insert(int num){
	int p=root,len=strlen(ch);
	for(int i=0;i<len;i++){
		int y=ch[i]-'A';
		if(!t[p].son[y]){
			t[p].son[y]=++cnt;
			t[cnt].prepare();
		}
		p=t[p].son[y];
	}
	t[p].count=num;
}
void Build(){
	int l=1,r=1;q[l]=root;
	while(l<=r){
		int x=q[l++];
		for(int i=0;i<26;i++){
			int y=t[x].son[i];
			if(!y)continue;
			q[++r]=y;
			int p=t[x].fail;
			while(p&&!t[p].son[i])p=t[p].fail;
			if(p)t[y].fail=t[p].son[i];
			else t[y].fail=root;
		}
	}
}
int AC(int l,int r,int d){
	int p=root;
	while(l<=n-1&&l>=0&&r<=m-1&&r>=0){
		int y=Map[l][r]-'A';
		while(p&&!t[p].son[y])p=t[p].fail;
		if(p)p=t[p].son[y];else p=root;
		for(int j=p;j;t[j].count=0,j=t[j].fail){
			ans[t[j].count].l=l-cx[d]*(Len[t[j].count]-1);
			ans[t[j].count].r=r-cy[d]*(Len[t[j].count]-1);
			ans[t[j].count].d=d;
		}
		l+=cx[d];r+=cy[d];
	}
}
void Solve(){
	for(int i=0;i<m;i++){
		AC(0,i,4);AC(0,i,3);AC(0,i,5);
		AC(n-1,i,1);AC(n-1,i,0);AC(n-1,i,7);
	}
	for(int i=0;i<n;i++){
		AC(i,0,1);AC(i,0,2);AC(i,0,3);
		AC(i,m-1,5);AC(i,m-1,6);AC(i,m-1,7);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();T=read();
	for(int i=0;i<n;i++){
		scanf("%s",ch);
		for(int j=0;j<m;j++){
			Map[i][j]=ch[j];
		}
	}
	for(int i=1;i<=T;i++){
		scanf("%s",ch);
		Len[i]=strlen(ch);
		Insert(i);
	}
	Build();Solve();
	for(int i=1;i<=T;i++){
		printf("%d %d %c\n",ans[i].l,ans[i].r,ans[i].d+'A');
	}
	return 0;
}