# FCFS

```c
#include<stdio.h>
#include<stdlib.h>
#define Max 10


// Defining the structure for the process
struct process{

    int pid;    // process id
    int btime;  // burst time
    int atime;  // arrival time of the process
    int wtime;  // waiting time
    int tatime;  // turn around time
};

// Declaring a global array for storing the process
struct process p[Max];

// Main
void main(){

    int i;

    // reading total number of processes
    int n;
    printf("Enter the Total Number of Processes: ");
    scanf("%d",&n);

    // Reading the Processes
    for (int i = 0; i < n; i++){
        
        printf("%d\n",i+1);
        printf("Process Id: ");
        scanf("%d",&p[i].pid);

        printf("Burst Time: ");
        scanf("%d",&p[i].btime);

        printf("Arrival Time: ");
        scanf("%d",&p[i].atime);
    }
    
    // bubble sorting the process p[] based on arrival time

    for(int j=0;j<n-1;j++){
        int flag=0;
        for (int k = 0; k <n-1-j; k++){

            if(p[k].atime>p[k+1].atime){

                struct process temp=p[k];
                p[k]=p[k+1];
                p[k+1]=temp;
                flag=1;
            }
        }
        if(flag==0){
            break;
            // exiting the outer for loop if 
            // no swapping is performed
        }
  
    }

    //calculating the Waiting Time and Turn Around time
    
    // TAT= AT+WT
    // for the first process WT=0 and TAT=BT
    p[0].wtime=0;
    p[0].tatime=p[0].btime;

    for (int i = 1; i < n; i++){
        //calculating WT
        p[i].wtime=p[i-1].tatime+p[i-1].atime-p[i].atime;

        //used to handle cases where a process arrives after the completion of the previous process and has to 
        //wait for some time before it can start executing. In such cases, the waiting time can be negative.
        if(p[i].wtime<0){
            p[i].wtime=0;
        }

        //calculating the TAT
        p[i].tatime=p[i].wtime+p[i].btime;
    }
    
    // Calculating Average WT and Average TAT

    float awt=0;
    float atat=0;
    for(int i=0;i<n;i++){

        awt=awt+p[i].wtime;

        atat=atat+p[i].tatime;
    }
    
    awt=awt/n;
    atat=atat/n;

    //Displaying the Result

    for ( i = 0; i < n; i++){
        
        printf("%d\n",i+1);
        printf("Process Id: %d\n",p[i].pid);
        printf("Burst Time: %d\n",p[i].btime);
        printf("Arrival Time: %d\n",p[i].atime);
        printf("Waiting Time: %d\n",p[i].wtime);
        printf("Turn Around Time: %d\n",p[i].tatime);
        printf("\n");
    }

    printf("Average Waiting Time: %f\n",awt);
    printf("Average Turn Around Time: %f\n",atat);
    
}
```

### Output

```bash
Enter the Total Number of Processes: 3
1
Process Id: 1
Burst Time: 5
Arrival Time: 0
2
Process Id: 2
Burst Time: 3
Arrival Time: 2
3
Process Id: 3
Burst Time: 8
Arrival Time: 1


1
Process Id: 1
Burst Time: 5
Arrival Time: 0
Waiting Time: 0
Turn Around Time: 5

2
Process Id: 2
Burst Time: 3
Arrival Time: 2
Waiting Time: 3
Turn Around Time: 6

3
Process Id: 3
Burst Time: 8
Arrival Time: 1
Waiting Time: 5
Turn Around Time: 13

Average Waiting Time: 2.666667
Average Turn Around Time: 8.000000

```

### Testcase 2

```
Enter the Total Number of Processes: 2
1
Process Id: 1
Burst Time: 4
Arrival Time: 0
2
Process Id: 2
Burst Time: 2
Arrival Time: 1

1
Process Id: 1
Burst Time: 4
Arrival Time: 0
Waiting Time: 0
Turn Around Time: 4

2
Process Id: 2
Burst Time: 2
Arrival Time: 1
Waiting Time: 3
Turn Around Time: 5

Average Waiting Time: 1.500000
Average Turn Around Time: 4.500000

```

### Testcase 3

```
// Some codeEnter the Total Number of Processes: 1
1
Process Id: 1
Burst Time: 6
Arrival Time: 0

1
Process Id: 1
Burst Time: 6
Arrival Time: 0
Waiting Time: 0
Turn Around Time: 6

Average Waiting Time: 0.000000
Average Turn Around Time: 6.000000

```
