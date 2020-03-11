#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <wait.h>

int main(int argc, char *argv[]) {

  pid_t pid, sid;

  printf("%s\n%s\n%s\n%s\n",argv[1],argv[2],argv[3],argv[4]);

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }


  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  } 

  int error=0;

  int x = strlen(argv[1]);

  if(x > 2){
    error++;
  }
  else if(strcmp(argv[1],"*") != 0){
    if(atoi(argv[1]) > 60){
      error++;
    }
  }

  x= strlen(argv[2]);
  if(x > 2){
      error++;
    }
    else if(strcmp(argv[1],"*") != 0){
      if(atoi(argv[2]) > 60){
        error++;
      }
    }
  x=strlen(argv[3]);
  if(x > 2){
    error++;
  }
  else if(strcmp(argv[1],"*") != 0){
    if(atoi(argv[3]) > 24){
      error++;
    }
  }

  struct stat st = {0};
  if(error > 0){
    printf("DATA INPUT ERROR\n");
    exit(EXIT_FAILURE);
  }
  if(stat(argv[4],&st) != 0){
    printf("DATA PATH ERROR\n");
    exit(EXIT_FAILURE);
  }
  //
  // close(STDIN_FILENO);
  // close(STDOUT_FILENO);
  // close(STDERR_FILENO);


  while (1) {
    pid_t run;
    printf("Running\n");

    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    char *bashing[] = {"bash",argv[4],NULL};

    if(strcmp(argv[1],"*") == 0){
      if(strcmp(argv[2],"*") == 0){

        if(strcmp(argv[3],"*") == 0){
          while(1){
            if(run = fork() == 0){
              execvp("/bin/bash",bashing);
            }
            sleep(1);
            time(&rawtime);
            timeinfo = localtime ( &rawtime );
          }
        }

        else{
          while (1) {
            if(atoi(argv[3]) == timeinfo->tm_hour){
              if(run = fork() == 0){
                execvp("/bin/bash",bashing);
              }
            }
            sleep(1);
            time(&rawtime);
            timeinfo = localtime ( &rawtime );
          }
        }
      }


      else{
        if(strcmp(argv[3],"*") == 0){
          while (1) {
            if(atoi(argv[2]) == timeinfo->tm_min){
              if(run = fork() == 0){
                execvp("/bin/bash",bashing);
              }
            }
            sleep(1);
            time(&rawtime);
            timeinfo = localtime ( &rawtime );
          }
        }

        else{
          while (1) {
            if(atoi(argv[3]) == timeinfo->tm_hour && atoi(argv[2]) == timeinfo->tm_min){
              if(run = fork() == 0){
                execvp("/bin/bash",bashing);
              }
            }
            sleep(1);
            time(&rawtime);
            timeinfo = localtime ( &rawtime );
          }
        }
      }
    }



    else {


      if(strcmp(argv[2],"*") == 0){
        if(strcmp(argv[3],"*") == 0){
          while (1) {
            if(atoi(argv[1]) == timeinfo->tm_sec){
              if(run = fork() == 0){
                execvp("/bin/bash",bashing);
              }
            }
            sleep(1);
            time(&rawtime);
            timeinfo = localtime ( &rawtime );
          }
        }

        else{
          while (1) {
            if(atoi(argv[1]) == timeinfo->tm_sec && atoi(argv[3]) == timeinfo->tm_hour){
              if(run = fork() == 0){
                execvp("/bin/bash",bashing);
              }
            }
            sleep(1);
            time(&rawtime);
            timeinfo = localtime ( &rawtime );
          }
        }
      }


      else{

        if(strcmp(argv[3],"*") == 0){
          while(1){
            if(atoi(argv[2]) == timeinfo->tm_min && atoi(argv[1]) == timeinfo->tm_sec){
              if(run = fork() == 0){
                execvp("/bin/bash",bashing);
              }
            }
            sleep(1);
            time(&rawtime);
            timeinfo = localtime ( &rawtime );
          }
        }

        else{
          while (1) {
            if(atoi(argv[3]) == timeinfo->tm_hour && atoi(argv[2]) == timeinfo->tm_min && atoi(argv[1]) == timeinfo->tm_sec){
              if(run = fork() == 0){
                execvp("/bin/bash",bashing);
              }
            }
            sleep(1);
            time(&rawtime);
            timeinfo = localtime ( &rawtime );
          }
        }
      }
    }
    break;
  }
}
