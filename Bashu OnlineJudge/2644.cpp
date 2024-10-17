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
	int s=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s;
}
bool pr(int k){  //判断是否为素数，不予以注释 
	int m;
	for(m=2;m<=floor(sqrt(k));m++)
	if(k%m==0)return false;
	return true;
}
int n,m1,m2,ans=0x7fffffff/2,prime[30005],sum_prime,pipe_prime[30005];
int cell,cell_prime[30005],now;
bool here,flag;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m1=read();m2=read();
	for(i=2;i<=30000;i++)  //把30000以内的质因数枚举出来
	if(pr(i)){
		sum_prime++;
		prime[sum_prime]=i;
	}
	i=1;
	while(m1!=1){  //为m1质因数分解 
		if(m1%prime[i]==0)
		while(m1%prime[i]==0){  //除到没有为止
			pipe_prime[i]+=m2;
			m1/=prime[i];
		}
		i++;
	}
	for(i=1;i<=n;i++){
        cell=read();
		j=1;now=0;here=true;  //初始化
        memset(cell_prime,0,sizeof(cell_prime));
        while(j<=sum_prime){  //大于30000的质因子忽略，即在30000内质因数分解 
            if(cell%prime[j]==0)
            while(cell%prime[j]==0){
				cell_prime[j]++;
				cell/=prime[j];
			}
            j++;
        }
        for(j=1;j<=sum_prime;j++){
            if(pipe_prime[j]!=0&&cell_prime[j]==0)here=false; //细胞无试管所拥有质因子，不可用 
            if(pipe_prime[j]!=0&&cell_prime[j]!=0){  //如果试管没有该质因子，不用做 
                if(pipe_prime[j]%cell_prime[j]==0){
                	now=max(now,pipe_prime[j]/cell_prime[j]);
				}
                else now=max(now,pipe_prime[j]/cell_prime[j]+1);  //记得要+1，整除时不用加 
            }
            if(!here)break;
        }
        if(here){
			flag=true;
			if(now<ans)ans=now;
		}  //如果该细胞可行，做个标志，替换 
    }
	if(flag)printf("%d",ans);
	else printf("-1");
	return 0;
}