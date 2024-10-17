/*====Corycle====*/

//SAM
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
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
map<char,int>id;
vector<int>G[N];
int n,m,Ans,tot,lst,root;
int ch[N][4],fa[N],len[N],sum[N];
void Prepare(){
	for(int i=0;i<=tot;i++){
		G[i].clear();
		fa[i]=len[i]=sum[i]=0;
		memset(ch[i],0,sizeof(ch[i]));
	}
	tot=lst=root=1;Ans=0;
}
void Insert(int num){
	int x=lst,fx=++tot;len[fx]=len[x]+1;sum[fx]=1;
	while(x&&!ch[x][num]){ch[x][num]=fx;x=fa[x];}
	if(!x)fa[fx]=root;
	else{
		int y=ch[x][num];
		if(len[y]==len[x]+1)fa[fx]=y;
		else{
			int fy=++tot;len[fy]=len[x]+1;
			memcpy(ch[fy],ch[y],sizeof(ch[fy]));
			fa[fy]=fa[y];fa[y]=fa[fx]=fy;
			while(x&&ch[x][num]==y){ch[x][num]=fy;x=fa[x];}
		}
	}
	lst=fx;
}
char s[N],t[N];
void DFS(int x){
	for(auto y:G[x]){
		DFS(y);
		sum[x]+=sum[y];
	}
}
void Solve(int p,int x,int num){
	if(num>3)return;
	if(x==m){Ans+=sum[p];return;}
	for(int i=0;i<4;i++){
		if(id[t[x]]==i&&ch[p][i])Solve(ch[p][i],x+1,num);
		if(id[t[x]]!=i&&ch[p][i])Solve(ch[p][i],x+1,num+1);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	id['A']=0;id['T']=1;
	id['G']=2;id['C']=3;
	while(T--){
		Prepare();
		scanf("%s%s",s,t);
		n=strlen(s);m=strlen(t);
		for(int i=0;i<n;i++)Insert(id[s[i]]);
		for(int i=1;i<=tot;i++)G[fa[i]].push_back(i);
		DFS(root);
		Solve(root,0,0);
		printf("%d\n",Ans);
	}
	return 0;
}

//FFT: 20(TLE)
/*
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
const double Pi=acos(-1);
const int N=300005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N],t[N];
complex<double>A[N],B[N];
int n,m,len,L,R[N],Ans[N];
void FFT(complex<double>a[],int n,int f){
	for(int i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
	for(int i=1;i<n;i<<=1){
		complex<double>Wn(cos(Pi/i),f*sin(Pi/i));
		for(int j=0;j<n;j+=(i<<1)){
			complex<double>W(1,0);
			for(int k=0;k<i;k++){
				complex<double>x=a[j+k],y=W*a[j+k+i];
				a[j+k]=x+y;a[j+k+i]=x-y;W*=Wn;
			}
		}
	}
	if(f==-1)for(int i=0;i<n;i++)a[i]/=n;
}
void Solve(char c){
	for(int i=0;i<n;i++)A[i]=(s[i]==c);
	for(int i=0;i<m;i++)B[i]=(t[m-i-1]==c);
	FFT(A,len,1);FFT(B,len,1);
	for(int i=0;i<len;i++)A[i]=A[i]*B[i];
	FFT(A,len,-1);
	for(int i=0;i<len;i++){
		Ans[i]+=(int)(A[i].real()+0.5);
		A[i]=B[i]=0;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		scanf("%s%s",s,t);
		n=strlen(s);m=strlen(t);
		len=1;L=0;
		while(len<n+n){len<<=1;L++;}
		for(int i=0;i<len;i++){
			R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
			Ans[i]=0;
		}
		int num=0;
		Solve('A');Solve('T');
		Solve('G');Solve('C');
		for(int i=m-1;i<n;i++)num+=(Ans[i]>=m-3);
		printf("%d\n",num);
	}
	return 0;
}
*/