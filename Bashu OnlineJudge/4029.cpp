#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int tot=1,lst=1,root=1,ans;
int ch[N][30],fa[N],len[N];
void SAM(int num){
	int x=lst,fx=++tot;
	len[fx]=len[x]+1;
	while(x&&!ch[x][num]){
		ch[x][num]=fx;
		x=fa[x];
	}
	if(!x)fa[fx]=root;
	else{
		int y=ch[x][num];
		if(len[y]==len[x]+1)fa[fx]=y;
		else{
			int fy=++tot;
			len[fy]=len[x]+1;
			for(int i=0;i<26;i++){
				ch[fy][i]=ch[y][i];
			}
			fa[fy]=fa[y];
			fa[y]=fa[fx]=fy;
			while(x&&ch[x][num]==y){
				ch[x][num]=fy;
				x=fa[x];
			}
		}
	}
	lst=fx;
}
void Match(){
	int sum=0,p=root;
	int n=strlen(s+1);
    for(int i=1;i<=n;i++){
		int x=s[i]-'a';
		if(ch[p][x]){
			sum++;
			p=ch[p][x];
		}
		else{
			while(p&&!ch[p][x])p=fa[p];
			if(!p){
				p=root;
				sum=0;
			}
			else{
				sum=len[p]+1;
				p=ch[p][x];
			}
		}
		ans=max(sum,ans);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(int i=1;i<=n;i++){
		SAM(s[i]-'a');
	}
	scanf("%s",s+1);
	Match();
	printf("%d",ans);
	return 0;
}