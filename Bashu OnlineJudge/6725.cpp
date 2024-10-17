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
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
int read(){
    int s=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
    return s*f;
}
int n,tot,root;
struct tree{
    int sum,fa,data,num;
    int ch[2];
}t[100005];
void Pushup(int x){
    t[x].sum=t[t[x].ch[0]].sum+t[t[x].ch[1]].sum+t[x].num;
}
void Rotate(int x){
    int y=t[x].fa;int z=t[y].fa;
    int l=(x!=t[y].ch[0]);int r=l^1;
    if(z!=0){
        if(t[z].ch[0]==y)t[z].ch[0]=x;
        else t[z].ch[1]=x;
    }
    t[x].fa=z;t[y].fa=x;
    t[t[x].ch[r]].fa=y;
    t[y].ch[l]=t[x].ch[r];
    t[x].ch[r]=y;
    Pushup(y);Pushup(x);
}
void Splay(int x){
    while(t[x].fa){
        int y=t[x].fa;int z=t[y].fa;
        if(z!=0){
            if(x==t[y].ch[0]^y==t[z].ch[0])Rotate(x);
            else Rotate(y);
        }
        Rotate(x);
    }
    root=x;
}
void Insert(int x){
    int p=root,f=0;
    while(p){
        f=p;
        t[p].sum++;
        if(x==t[p].data){
        	t[p].num++;
        	return;
        }
        if(x<=t[p].data)p=t[p].ch[0];
        else p=t[p].ch[1];
    }
    tot++;
    t[tot].data=x;
    t[tot].sum=1;
    t[tot].num=1;
    if(root==0){
        root=tot;
        return;
    }
    t[tot].fa=f;
    if(x<=t[f].data)t[f].ch[0]=tot;
    else t[f].ch[1]=tot;
    Splay(tot);
}
int FIND(int k){
    int p=root;
    if(t[p].sum<k)return -1;
    while(1){
        if(t[t[p].ch[0]].sum+t[p].num>=k&&t[t[p].ch[0]].sum+1<=k)return t[p].data;
        if(t[t[p].ch[0]].sum+t[p].num>=k)p=t[p].ch[0];
        else{
            k=k-t[t[p].ch[0]].sum-t[p].num;
            p=t[p].ch[1];
        }
    }
}
int Find(int x){
    int p=root;
    while(p){
        if(x==t[p].data){
            Splay(p);
            return 1;
        }
        if(x<=t[p].data)p=t[p].ch[0];
        else p=t[p].ch[1];
    }
    return 0;
}
void Delete(int x){
    Find(x);
    int p=root;
    t[p].num--;t[p].sum--;
    if(t[p].num)return;
    int ls=t[p].ch[0],rs=t[p].ch[1];
    if(!ls&&!rs){
        root=0;
        return;
    }
    if(!ls||!rs){
        root=max(ls,rs);
        t[root].fa=0;
        return;
    }
    p=ls;
    t[p].fa=0;
    while(t[p].ch[1])p=t[p].ch[1];
    Splay(p);
    t[p].ch[1]=rs;
    t[rs].fa=p;
    Pushup(rs);Pushup(p);
}
int Pred(int x){
    int ans=-inf,p=root;
    while(p){
        if(t[p].data<x)ans=max(ans,t[p].data);
        if(x<=t[p].data)p=t[p].ch[0];
        else p=t[p].ch[1];
    }
    return ans;
}
int Succ(int x){
    int ans=inf,p=root;
    while(p){
        if(t[p].data>x)ans=min(ans,t[p].data);
        if(x<t[p].data)p=t[p].ch[0];
        else p=t[p].ch[1];
    }
    return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
    n=read();
    while(n--){
        int p=read(),x=read();
        if(p==1)Insert(x);
        if(p==2)Delete(x);
        if(p==3){
            Find(x);
            int y=root;
            printf("%d\n",t[t[y].ch[0]].sum+1);
        }
        if(p==4)printf("%d\n",FIND(x));
        if(p==5)printf("%d\n",Pred(x));
        if(p==6)printf("%d\n",Succ(x));
    }
    return 0;
}