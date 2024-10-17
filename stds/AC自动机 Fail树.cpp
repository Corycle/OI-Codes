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
	for(int i=2;i<=tot;i++){//����Fail�� 
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
2930 -- ��NOI2011������Ĵ��ֻ�
Description
����ϲ���ղظ���ϡ��ŹֵĶ�����������Ե�һ̨��ʽ�Ĵ��ֻ������ֻ���ֻ��28���������ֱ�ӡ��26��СдӢ����ĸ��'B'��'P'������ĸ��
�������о����֣�������ֻ������������ģ�

l ����Сд��ĸ�����ֻ���һ�������л���������ĸ(�����ĸ���ڰ��۵����)��
l ��һ��ӡ��'B'�İ��������ֻ����������һ����ĸ����ʧ��
l ��һ��ӡ��'P'�İ��������ֻ�����ֽ�ϴ�ӡ�����������е�������ĸ�����У��������е���ĸ������ʧ��

���磬��������aPaPBbP��ֽ�ϱ���ӡ���ַ����£�

a
aa
ab

���ǰ�ֽ�ϴ�ӡ�������ַ�����1��ʼ˳���ţ�һֱ��n�����ֻ���һ���ǳ���Ȥ�Ĺ��ܣ��ڴ��ֻ��а���һ�������ֵ�С���̣���С����������������(x,y)������1��x,y��n�������ֻ�����ʾ��x����ӡ���ַ����ڵ�y����ӡ���ַ����г����˶��ٴΡ�
���귢������������Ժ���˷ܣ�����д���������ͬ���Ĺ��ܣ����ܰ�����ô��
*/
