//首先矩阵旋转90度，去除后效性。 
//f[i][j][k]表示截止到第i行，总共已经选j个砖块，其中第i行已经选了前k个砖块的最大值。
//f[i][j][k]=max(f[i][j-k][p]+sum[i][k]){0<=k<=j,0<=p<k} 
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int N=52;
int n,m,v[N][N],s[N],sum[N][N];
int ans,f[N][N*10][N];
int main(){
    //freopen("brike.in","r",stdin);
    //freopen("brike.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) for(int j=i;j<=n;j++) scanf("%d",&v[j][i]);
    for(int i=1;i<=n;i++) for(int j=1;j<=i;j++) sum[i][j]=sum[i][j-1]+v[i][j];
    for(int i=1;i<=n;i++) s[i]=s[i-1]+i;
    memset(f,-0x3f,sizeof f);
    f[0][0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=min(m,s[i]);j++){
            for(int k=0;k<=min(i,j);k++){
                for(int p=max(k-1,0);p<i&&s[p]<=j-k;p++){
                    f[i][j][k]=max(f[i][j][k],f[i-1][j-k][p]+sum[i][k]);
                }
                ans=max(ans,f[i][j][k]);
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}