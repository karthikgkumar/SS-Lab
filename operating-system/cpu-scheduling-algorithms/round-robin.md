# Round Robin

```c
#include<stdio.h>
void main()
{ int n,i,at[100],bt[100],rt[100],ts,remain,time,flag=0,wt[100],tt[100],totwt=0,tottt=0;
  printf("\nenter number of processes ");
  scanf("%d",&n);
 remain=n;
  for(i=0;i<n;i++)
 { printf("\nenter arrival time and burst time ");
   scanf("%d",&at[i]);
   scanf("%d",&bt[i]);
   rt[i]=bt[i];
 }
 
 printf("\nenter time slice ");
 scanf("%d",&ts);
 
for(time=0,i=0;remain!=0;)
{ if(rt[i]<=ts && rt[i]>0)
    { time=time+rt[i];
      rt[i]=0;
      flag=1;
    }
  else if(rt[i]>0)	
    { time=time+ts;
      rt[i]=rt[i]-ts;
    }
  if(rt[i]==0 && flag==1)
    { remain--;
      
     
      wt[i]=time-at[i]-bt[i];
      tt[i]=time-at[i];
      totwt=totwt+wt[i];
      tottt=tottt+tt[i];
      flag=0;
    }

  if(i==n-1)
   i=0;
  else if(at[i+1]<=time)
   i++;
  else 
   i=0;
 
}
 
printf("\nprocess\tat\tbt\twt\ttt\n");
 for(i=0;i<n;i++)
{ printf("%d\t\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],wt[i],tt[i]);
 }

printf("\ntotal waiting time %d",totwt);
printf("\navg waiting time %f",(float)totwt/n);
printf("\ntotal turnaround time %d",tottt);
printf("\navg turnaround time %f",(float)tottt/n);

}
```
