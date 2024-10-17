#include<iostream>  
#include<cstring>  
#include<cstdio>  
#include<algorithm>
using namespace std;  
int f[200010],a[200010],b[200010];  
int main()  
{  
    int i,j,n,k,maxf,ans=0;  
    int count=1;  
    cin>>n>>k;  
    for(i=1;i<=n;i++)cin>>a[i];  
    for(i=1;i<k;i++){//形成b，新数组   
        if(a[i]<a[k]){//比k小才入队，因为在前面，必须包含k 
            b[count++]=a[i];  
        } 
    }
    b[count++]=a[k];  //k入队 
    for(i=k+1;i<=n;i++){  
        if(a[i]>a[k]){  //上升就入队 
            b[count++]=a[i];  
        }  
    }
    count--;
    a[1]=b[1];//a[i]记录长度为l的子串末数字最小值，是个递增数组  
    f[1]=1;//以1结尾就一个 
    int left,right,len=1,mid,pos;  
    for(i=2;i<=count;i++){//多少个 
        left=1,right=len;  
        pos=0;  
        while(left<=right){//取最长的来二分 
            mid=(left+right)/2;//二分 
            if(a[mid]<b[i]){//小于 
                pos=mid;//可以上升 
                left=mid+1;//继续找 
            }  
            else{//大于等于 
                right=mid-1;  
            }  
        }  
        f[i]=pos+1;//上升+1 
        if(f[i]>len)len=f[i];
        a[f[i]]=b[i];//加入 
    }  
    cout<<len;  
    return 0;  
}  