#include <stdio.h>

int main(){
    int numOfProcess, choice;
    
    printf("Enter the number of processes: ");
    scanf("%d", &numOfProcess);
    
    int process[numOfProcess], burstTime[numOfProcess], priorityTable[numOfProcess];
    
    printf("Enter the burst time of each process:\n ");
    for(int i=0; i<numOfProcess; i++){
        printf("Burst Time of Process %d: ", i + 1);
        scanf("%d", &burstTime[i]);    
        process[i] = i + 1; 
    }
    
    printf("\n");

    printf("Enter the priority of each process (1 is highest priority): \n");
    for(int i=0; i<numOfProcess; i++){
        printf("Priority of Process %d: ", i + 1);
        scanf("%d", &priorityTable[i]);
    }
    
    printf("\n");

    int timeQuantum;
    printf("Enter the time quantum for Round Robin: ");
    scanf("%d", &timeQuantum);
    printf("\n");

    do{
        printf("\nEnter the scheduling algorithm to use:\n");
        printf("1. FCFS (First Come First Serve)\n");
        printf("2. SJF (Shortest Job First)\n");
        printf("3. Priority Scheduling\n");
        printf("4. Round Robin\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1: {
               fcfs(process, burstTime, numOfProcess);            
               break;
            }
            case 2: {
               sjf(process, burstTime, numOfProcess);
               break;
            }
            case 3: {
               priority(process, burstTime, priorityTable, numOfProcess);
               break;
            }
            case 4: {
               roundRobin(process, burstTime, numOfProcess, timeQuantum);
               break;
            }
            case 0: {
               printf("Exiting...\n");
               break;
            }
            default: {
               printf("Invalid choice. Please enter a valid option.\n");
               break;
            }
        }
        
    } while(choice != 0);
    
    return 0;
}

void fcfs(int process[], int burstTime[], int numOfProcess){
    int waitTime[numOfProcess], turnAroundTime[numOfProcess], totalTime=0;
    int totWaitTime=0, totTurnAroundTime=0;
    float avgWaitTime, avgTurnAroundTime;

    waitTime[0] = 0; 
    turnAroundTime[0]=burstTime[0];
    

    for(int i=1; i<numOfProcess; i++){
        waitTime[i] = waitTime[i-1] + burstTime[i-1];
        totWaitTime += waitTime[i];
        turnAroundTime[i] = waitTime[i] + burstTime[i];
        
    }

    for(int i=0; i<numOfProcess; i++){
        totTurnAroundTime+=turnAroundTime[i];
        }
    
    avgWaitTime = (float) totWaitTime / numOfProcess;
    avgTurnAroundTime = (float) totTurnAroundTime / numOfProcess;


    printf("FCFS Scheduling:\n");
    printf("Process\tBurst Time\tWait Time\tTurnaround Time\n");
    for(int i=0; i<numOfProcess; i++){
        printf("%d\t\t\t%d\t\t\t%d\t\t\t%d\n", process[i], burstTime[i], waitTime[i], turnAroundTime[i]);
    }
    printf("Average Waiting Time: %.2f\n", avgWaitTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnAroundTime);
printf("Total wait time: %d\n", totWaitTime);
printf("Total turn around Time: %d\n", totTurnAroundTime);
    

    //gantt 
 printf("Gantt chart\n");
    for(int i=0; i<numOfProcess; i++){
        printf("|P%d ", process[i]);
       
    }
    printf("|");
 printf("\n");
   for(int i=0; i<numOfProcess; i++){
        printf("  %d", waitTime[i]);
        
    }
    printf(" %d", turnAroundTime[numOfProcess-1]);
    printf("\n");
    
}

void sjf(int process[], int burstTime[], int numOfProcess){
    int waitTime[numOfProcess], turnAroundTime[numOfProcess], totalTime;
    int burstTimeCopy[numOfProcess], completionTime[numOfProcess];
    int totalWaitTime = 0, totalTurnAroundTime = 0;


    for(int i=0; i<numOfProcess; i++){
        burstTimeCopy[i] = burstTime[i];
    }

    for(int i=0; i<numOfProcess-1; i++){
        for(int j=0; j<numOfProcess-i-1; j++){
            if(burstTimeCopy[j] > burstTimeCopy[j+1]){
                int temp = burstTimeCopy[j];
                burstTimeCopy[j] = burstTimeCopy[j+1];
                burstTimeCopy[j+1] = temp;

                temp = process[j];
                process[j] = process[j+1];
                process[j+1] = temp;
            }
        }
    }


    for(int i=0; i<numOfProcess; i++){
        if(i == 0){
            completionTime[i] = burstTimeCopy[i];
            waitTime[i]=0;
        } else {
            completionTime[i] = completionTime[i-1] + burstTimeCopy[i];
        }
        turnAroundTime[i] = completionTime[i];
        waitTime[i] = turnAroundTime[i] - burstTimeCopy[i];
        
        totalWaitTime += waitTime[i];
        totalTurnAroundTime += turnAroundTime[i];
       
    }

    float avgWaitTime = totalWaitTime / numOfProcess;
    float avgTurnAroundTime = totalTurnAroundTime / numOfProcess;

    printf("SJF Scheduling:\n");
    printf("Process\tBurst Time\tWait Time\tTurnaround Time\n");
    for(int i=0; i<numOfProcess; i++){
        printf("%d\t\t%d\t\t\t%d\t\t%d\n", process[i], burstTimeCopy[i], waitTime[i], turnAroundTime[i]);
    }
    printf("Average Waiting Time: %.2f\n", avgWaitTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnAroundTime);
printf("Total wait time: %d\n", totalWaitTime);
printf("Total turn around Time: %d\n", totalTurnAroundTime);



         //gantt 
     printf("Gantt chart\n");
        for(int i=0; i<numOfProcess; i++){
            printf("|P%d ", process[i]);
           
        }
        printf("|");
     printf("\n");
       for(int i=0; i<numOfProcess; i++){
            printf("  %d", waitTime[i]);
            
        }
        printf(" %d", turnAroundTime[numOfProcess-1]);
        printf("\n");
        
    
    
   
}

void priority(int process[], int burstTime[], int priorityTable[], int numOfProcess){
    int waitTime[numOfProcess], turnAroundTime[numOfProcess], totalTime;
    int completionTime[numOfProcess];
    int totalWaitTime = 0, totalTurnAroundTime = 0;

  
    for(int i=0; i<numOfProcess-1; i++){
        for(int j=0; j<numOfProcess-i-1; j++){
            if(priorityTable[j] > priorityTable[j+1]){
                int temp = priorityTable[j];
                priorityTable[j] = priorityTable[j+1];
                priorityTable[j+1] = temp;

                temp = burstTime[j];
                burstTime[j] = burstTime[j+1];
                burstTime[j+1] = temp;

                temp = process[j];
                process[j] = process[j+1];
                process[j+1] = temp;
            }
        }
    }

    for(int i=0; i<numOfProcess; i++){
        if(i == 0){
            completionTime[i] = burstTime[i];
            waitTime[i]=0;
        } else {
            completionTime[i] = completionTime[i-1] + burstTime[i];
        }
        turnAroundTime[i] = completionTime[i];
        waitTime[i] = turnAroundTime[i] - burstTime[i];
        
        totalWaitTime += waitTime[i];
        totalTurnAroundTime += turnAroundTime[i];
      
    }

    float avgWaitTime = totalWaitTime / numOfProcess;
    float avgTurnAroundTime = totalTurnAroundTime / numOfProcess;

    printf("Priority Scheduling:\n");
    printf("Process\tBurst Time\tPriority\tWait Time\tTurnaround Time\n");
    for(int i=0; i<numOfProcess; i++){
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", process[i], burstTime[i], priorityTable[i], waitTime[i], turnAroundTime[i]);
    }
    printf("Average Waiting Time: %.2f\n", avgWaitTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnAroundTime);
    printf("Total wait time: %d\n", totalWaitTime);
    printf("Total turn around Time: %d\n", totalTurnAroundTime);
         //gantt 
     printf("Gantt chart\n");
        for(int i=0; i<numOfProcess; i++){
            printf("|P%d ", process[i]);
           
        }
        printf("|");
     printf("\n");
       for(int i=0; i<numOfProcess; i++){
            printf("  %d", waitTime[i]);
            
        }
        printf(" %d", turnAroundTime[numOfProcess-1]);
        printf("\n");

}

void roundRobin(int process[], int burstTime[], int numOfProcess, int timeQuantum) {
    int remainingBurstTime[numOfProcess], k=0;
    int completionTime[numOfProcess]; 
    int currentTime = 0;
    int totalWaitTime = 0, totalTurnAroundTime = 0;
    int waitTime[numOfProcess];
    int turnAroundTime[numOfProcess];

    int timeLog[30];
   

    // Initialize remaining burst time
    for(int i = 0; i < numOfProcess; i++) {
        remainingBurstTime[i] = burstTime[i];
    }

    printf("Gantt Chart\n");

    while(1) {
        int done = 1;

        for(int i = 0; i < numOfProcess; i++) {
            if(remainingBurstTime[i] > 0) {
                done = 0;

                if(remainingBurstTime[i] > timeQuantum) {
                    printf("| P%d\t", process[i]);
                    
                    currentTime += timeQuantum;
timeLog[k++]=currentTime;

                    
                    remainingBurstTime[i] -= timeQuantum;
                } else {
                   printf("| P%d\t", process[i]);
  
                     


               
                   
                  
                    currentTime += remainingBurstTime[i];
timeLog[k++]=currentTime;
                    completionTime[i] = currentTime;
                    remainingBurstTime[i] = 0;
                }
            }
        }

        if(done == 1) {
            break;
        }
    }


    for(int i = 0; i < numOfProcess; i++) {
        turnAroundTime[i] = completionTime[i];
        waitTime[i] = turnAroundTime[i] - burstTime[i];

        totalTurnAroundTime += turnAroundTime[i];
        totalWaitTime += waitTime[i];
    }

    
    float avgWaitTime = (float) totalWaitTime / numOfProcess;
    float avgTurnAroundTime = (float) totalTurnAroundTime / numOfProcess;
    
        printf("\n");
       printf("0");
      for(int i=0;i<k; i++){
             printf("\t%d ", timeLog[i]); 
    }
    
    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(int i = 0; i < numOfProcess; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", process[i], burstTime[i], waitTime[i], turnAroundTime[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avgWaitTime);
    printf("\nAverage Turnaround Time: %.2f\n", avgTurnAroundTime);
printf("Total wait time: %d\n", totalWaitTime);
    printf("Total turn around Time: %d\n", totalTurnAroundTime);


  
   
}

