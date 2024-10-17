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
const int N=2e7+5;
const int M=4;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
char s[N];
map<char,int>a;
struct SAM{
	int lst=1,tot=1,root=1;
	int ch[N][M],fa[N],len[N];
	void Insert(int num){
		int x=lst,fx=++tot;len[fx]=len[x]+1;
		while(x&&!ch[x][num]){ch[x][num]=fx;x=fa[x];}
		if(!x)fa[fx]=root;
		else{
			int y=ch[x][num];
			if(len[y]==len[x]+1)fa[fx]=y;
			else{
				int fy=++tot;len[fy]=len[x]+1;
				fa[fy]=fa[y];fa[y]=fa[fx]=fy;
				memcpy(ch[fy],ch[y],sizeof(ch[fy]));
				while(x&&ch[x][num]==y){ch[x][num]=fy;x=fa[x];}
			}
		}
		lst=fx;
	}
	int Query(){
		int n=strlen(s+1);
		int p=root,ans=0;
		for(int i=1;i<=n;i++){
			int x=a[s[i]];
			if(ch[p][x]){p=ch[p][x];ans++;}
			else break;
		}
		return ans;
	}
}sam;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();scanf("%s",s+1);
	a['E']=0;a['S']=1;a['W']=2;a['N']=3;
	for(int i=1;i<=n;i++)sam.Insert(a[s[i]]);
	while(m--){scanf("%s",s+1);printf("%d\n",sam.Query());}
	return 0;
}