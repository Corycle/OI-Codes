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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,cnt,tot=1;
int step,cnt1,cnt2,root=1;
int pos[N],q[N],h1[N],h2[N];
int dfn[N],ed[N],ans[N],c[N];
struct Tree{
	int ch[26],fa,fail;
}t[N];
struct edge{
	int to,next,data;
}d[N],e[N];
void edge_add1(int x,int y){
	d[++cnt1]=(edge){y,h1[x],0};
	h1[x]=cnt1;
}
void edge_add2(int x,int y,int z){
	e[++cnt2]=(edge){y,h2[x],z};
	h2[x]=cnt2;
}
void Insert(){
	int p=root;
	for(int i=1;i<=n;i++){
		if(s[i]=='B')p=t[p].fa;
		if(s[i]=='P')pos[++cnt]=p;
		if('a'<=s[i]&&s[i]<='z'){
			int x=s[i]-'a';
			if(!t[p].ch[x]){
				t[p].ch[x]=++tot;
				t[tot].fa=p;
			}
			p=t[p].ch[x];
		}
	}
}
void Build(){
	int l=1,r=1;
	q[1]=root;
	while(l<=r){
		int x=q[l++];
		for(int i=0;i<26;i++){
			int y=t[x].ch[i];
			if(!y)continue;
			q[++r]=y;
			int p=t[x].fail;
			while(p&&!t[p].ch[i])p=t[p].fail;
			if(p)t[y].fail=t[p].ch[i];
			else t[y].fail=root;
		}
	}
}
void DFS(int x){
	dfn[x]=++step;
	for(int i=h1[x];i;i=d[i].next)DFS(d[i].to);
	ed[x]=step;
}
int lowbit(int x){
	return x&(-x);
}
void Add(int x,int y){
	for(int i=x;i<=n;i+=lowbit(i)){
		c[i]+=y;
	}
}
int Sum(int x){
	int tmp=0;
	for(int i=x;i>=1;i-=lowbit(i)){
		tmp+=c[i];
	}
	return tmp;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	scanf("%s",s+1);
	n=strlen(s+1);
	Insert();
	Build();
	for(int i=2;i<=tot;i++){//建立Fail树 
		edge_add1(t[i].fail,i);
	}
	DFS(1);
	m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		edge_add2(y,x,i);
	}
	int p=root,now=0;
	for(int i=1;i<=n;i++){
		if(s[i]=='B'){
			Add(dfn[p],-1);
			p=t[p].fa;
		}
		else if(s[i]=='P'){
			now++;
			for(int j=h2[now];j;j=e[j].next){
				int y=e[j].to;
				ans[e[j].data]=Sum(ed[pos[y]])-Sum(dfn[pos[y]]-1);
			}
		}
		else{
			int x=s[i]-'a';
			p=t[p].ch[x];
			Add(dfn[p],1);
		}
	}
	for(int i=1;i<=m;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
/*
2930 -- 【NOI2011】阿狸的打字机
Description
阿狸喜欢收藏各种稀奇古怪的东西，最近他淘到一台老式的打字机。打字机上只有28个按键，分别印有26个小写英文字母和'B'、'P'两个字母。
经阿狸研究发现，这个打字机是这样工作的：

l 输入小写字母，打字机的一个凹槽中会加入这个字母(这个字母加在凹槽的最后)。
l 按一下印有'B'的按键，打字机凹槽中最后一个字母会消失。
l 按一下印有'P'的按键，打字机会在纸上打印出凹槽中现有的所有字母并换行，但凹槽中的字母不会消失。

例如，阿狸输入aPaPBbP，纸上被打印的字符如下：

a
aa
ab

我们把纸上打印出来的字符串从1开始顺序编号，一直到n。打字机有一个非常有趣的功能，在打字机中暗藏一个带数字的小键盘，在小键盘上输入两个数(x,y)（其中1≤x,y≤n），打字机会显示第x个打印的字符串在第y个打印的字符串中出现了多少次。
阿狸发现了这个功能以后很兴奋，他想写个程序完成同样的功能，你能帮助他么？
*/
