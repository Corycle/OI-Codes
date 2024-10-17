#include<iomanip>  
#include<cstdio>  
#include<queue>  
#include<algorithm>  
using namespace std;  
int m,n;  
int gcd(int x,int y)  
{  
    if(y==0) return x;  
    else return gcd(y,x%y);  
}  
int main()  
{  
    scanf("%d%d",&m,&n);  
    int x=gcd(m,m+n);  
    printf("%d %d",m/x,(m+n)/x);  
}