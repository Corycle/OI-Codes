#include<stdio.h>  
#include<stdlib.h>   
int number[10005][205];  
int stairs[10005][205];//处理房间成圈形的楼梯计数    
int quan[10005],lm;//储存每楼层房间数
int main()  {  
    int n,m,ans=0,xx; 
    int lm;
    int i,ii; 
    int j,jj;    
    scanf("%d%d",&n,&m);       
    //输入每层楼是否有楼梯、牌子上的数字(房间的情况) 
    for(i=0;i<n;i++)  
    {  
        for(j=0;j<m;j++)  
        {  
            scanf("%d%d",&stairs[i][j],&number[i][j]);  
            quan[i]+=stairs[i][j];  
        }  
    }  
    scanf("%d",&jj);//小明从第几号开始爬楼        
    for(ii=0;ii<n;ii++)  
    {  
        ans=ans+number[ii][jj];
        lm=number[ii][jj];  
        lm=lm%quan[ii]+quan[ii];
        lm=lm-stairs[ii][jj];       
        while(lm>0)  
        {   
            jj++;  
            jj%=m;   
            lm=lm-stairs[ii][jj];   
        }  
    }  
    printf("%d\n",ans%20123);   
    return 0;   
}