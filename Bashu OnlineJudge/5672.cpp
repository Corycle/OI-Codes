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
const int Lim=1e3;
const int M=5e6+5;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll lst;
int n,m,len;
char s[M],tmp[M];
struct Node{
	int num,tag,fail,ch[2],son[2];
	void Init(){
		num=tag=fail=0;
		ch[0]=ch[1]=son[0]=son[1]=0;
	}
};
struct Tree{
	Node t[N];
	int tot,root;
	int New(){t[++tot].Init();return tot;}
	void Init(){tot=0;root=New();}
	void Build(){
		queue<int>q;
		t[root].fail=root;
		for(int i=0;i<2;i++){
			if(!t[root].ch[i])t[root].son[i]=root;
			else{
				t[root].son[i]=t[root].ch[i];
				t[t[root].ch[i]].fail=root;
				q.push(t[root].ch[i]);
			}
		}
		while(q.size()){
			int x=q.front();q.pop();
			t[x].num=t[t[x].fail].num+t[x].tag;
			for(int i=0;i<2;i++){
				int y=t[x].ch[i];
				if(y){
					q.push(y);
					t[x].son[i]=t[x].ch[i];
					t[y].fail=t[t[x].fail].son[i];
				}
				else t[x].son[i]=t[t[x].fail].son[i];
			}
		}
	}
	void Clear(){Init();Build();}
	bool Find(){
		int p=root;
		for(int i=1;i<=len;i++){
			int x=s[i]-'0';
			if(!t[p].ch[x])return false;
			p=t[p].ch[x];
		}
		return t[p].tag;
	}
	void Insert(){
		int p=root;
		for(int i=1;i<=len;i++){
			int x=s[i]-'0';
			if(!t[p].ch[x])t[p].ch[x]=New();
			p=t[p].ch[x];
		}
		t[p].tag=1;
	}
	ll Query(){
		int p=root;ll ans=0;
		for(int i=1;i<=len;i++){
			p=t[p].son[s[i]-'0'];
			ans+=t[p].num;
		}
		return ans;
	}
}S,B;//small,big
void Merge(int &x,int y){
	if(!x)x=B.New();
	if(S.t[y].tag)B.t[x].tag=1;
	for(int i=0;i<2;i++){
		if(S.t[y].ch[i]){
			Merge(B.t[x].ch[i],S.t[y].ch[i]);
		}
	}
}
void Prepare(){
	len=strlen(s+1);int p=lst%len;
	for(int i=1;i<=len;i++){int j=i+p;tmp[i]=s[j>len?j-len:j];}
	for(int i=1;i<=len;i++)s[i]=tmp[i];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	for(int Case=1;Case<=T;Case++){
		printf("Case #%d:\n",Case);
		S.Clear();B.Clear();
		m=read();lst=0;
		while(m--){
			scanf("%s",s);Prepare();
			if(s[0]=='+'){
				if(S.Find()||B.Find())continue;
				S.Insert();
				if(S.tot<=Lim)S.Build();
				else{Merge(B.root,S.root);B.Build();S.Clear();}
			}
			if(s[0]=='?')printf("%lld\n",lst=S.Query()+B.Query());
		}
	}
	return 0;
}