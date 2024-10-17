#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
struct node
{
    int x,y,next;
}a[110000];int len,last[110000];
void ins(int x,int y)
{
    len++;
    a[len].x=x;a[len].y=y;
    a[len].next=last[x];last[x]=len;
}
int fa[11000],son[11000];
int f[11000][2];
//f[i][j]：1表示这个人来，0表示不来
int v[110000];
void treedp(int x){
    f[x][1]=v[x];
    for(int k=last[x];k;k=a[k].next){
        treedp(a[k].y);
    }
    //讨论f[x][1]的情况
    for(int k=last[x];k;k=a[k].next){
        int y=a[k].y;
        f[x][1]+=f[y][0];
        //如果他来的话，那么他的儿子（下属）就不能来；
    }
    //讨论f[x][0]的情况
    f[x][0]=0;
    for(int k=last[x];k;k=a[k].next){
        int y=a[k].y;
        f[x][0]+=max(f[y][1],f[y][0]);
        //如果他不来，那么他的儿子来不来都可以
    }
}
int main(){
    int n;
    n=read();
    memset(f,-1,sizeof(f));
    memset(fa,0,sizeof(fa));
    for(int i=1;i<=n;i++)v[i]=read();
    int xx,yy;len=0;
    memset(last,0,sizeof(last));
    while(scanf("%d%d",&xx,&yy)!=EOF){
        if(xx==0 && yy==0)break;
        ins(yy,xx);fa[xx]=yy;son[yy]=xx;
    }
    int root;//根节点（Boss）
    for(int i=1;i<=n;i++)
        if(fa[i]==0){
			root=i;
			break;
		}
    for(int i=1;i<=n;i++){
        if(son[i]==0){
            f[i][0]=0;
        }
    }
    treedp(root);
    printf("%d\n",max(f[root][1],f[root][0]));
    return 0;
}