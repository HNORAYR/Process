#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t pid;
    int status;
    pid = fork();

    if(pid == -1){
        printf("Fork failed!\n");
        return 1;
    }
    else if(pid == 0){
        printf("I am a Child process! My PID is %d.\n", getpid());
        if(execlp("/bin/ls", "ls", (char*)NULL)== -1){
            printf("ExecLP faild!\n");
            return 1;
        }
    } else {
        if (wait(&status) == -1) {
            printf("wait failed");
            return 1;
        }
        if (WIFEXITED(status)) {
            printf("Parent process (PID: %d) reports: Child exited with status %d\n", getpid(), WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status)) {
            printf("Child killed by signal %d\n", WTERMSIG(status));
        }
    }

    return 0;
}

