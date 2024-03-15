#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/shm.h>



bool success(int mid,int final , int passG){ return((mid + final) > passG ? true : false);} // determine if student succeeded
int main(int argc, char **argv){
    int TACount=atoi((argv[2])),PassG=atoi(argv[3]),StudentNum,TACap,LastTACap,pid,mid ,final; // declare variables
    char * filename = argv[1];
    FILE* students =fopen(filename,"r");//start reading students from file
    fscanf(students,"%d",&StudentNum);
    TACap=StudentNum/TACount;
    LastTACap=(StudentNum%TACount) + TACap;
    int **grades = (int **)malloc(StudentNum * sizeof(int *));
    int shmid = shmget(IPC_PRIVATE, TACount * sizeof(int), IPC_CREAT | 0666);//create shared memory between child and parent processes 
    int *TAPassedCount = shmat(shmid, NULL, 0);
    for(int i = 0; i < TACount; i++) {
        TAPassedCount[i] = 0;
    }
    if (grades == NULL) {
        perror("Memory allocation failed");
        return 1;
    }
    for (int i = 0; i < StudentNum; i++) {
        grades[i] = (int *)malloc(2 * sizeof(int));
        if (grades[i] == NULL) {
            perror("Memory allocation failed");
            return 1;
        }
        fscanf(students, "%d %d", &grades[i][0], &grades[i][1]);
    }
    fclose(students);//close file 
    for(int i = 0; i < TACount; i++) {
        pid = fork();
        if(i == TACount - 1) {
            TACap = LastTACap;//if last TA that TA should handle any remaining students if students wasn't evenly distributed 
        }
        if(pid ==0){
            for(int j = 0; j <TACap; j++) {
                mid = grades[i*TACap + j][0];
                final = grades[i*TACap + j][1];
                if(success(mid,final,PassG)){
                    TAPassedCount[i]++;//increase the count of succeeded students for the TA i pointing to its index
                }
            }
            exit(0);
        }
        else if (pid < 0){
        perror("Fork Failed");
        }
    }
    for(int i = 0; i < TACount; i++){
        wait(NULL);
    }
    for(int i = 0; i < TACount; i++){
        i == TACount -1 ? printf("%d\n",TAPassedCount[i]) : printf("%d ",TAPassedCount[i]);
    }
    for (int i = 0; i < StudentNum; i++) {
        free(grades[i]);
    }
    free(grades);
    shmdt(TAPassedCount);
    shmctl(shmid, IPC_RMID, NULL);
}