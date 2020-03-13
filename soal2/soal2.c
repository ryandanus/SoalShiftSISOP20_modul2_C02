#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <wait.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char const *argv[]) {
pid_t pid,sid;

pid = fork();
if(pid < 0){
    exit(EXIT_FAILURE);
}
else if(pid > 0){
    exit(EXIT_SUCCESS);
}

umask(0);
sid = setsid();
if(sid < 0){
    exit(EXIT_FAILURE);
}

if((chdir("/")) < 0){
    exit(EXIT_FAILURE);
}

close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);

time_t rawtime;
struct tm * timeinfo;
time(&rawtime);
timeinfo = localtime ( &rawtime );

char timefolder[80];
char temp[20];

while (1) {
    pid_t run;
    run = fork();
    int stat;
    if(run == 0 ){
        time(&rawtime);
        timeinfo = localtime ( &rawtime );
        strcpy(timefolder,"/home/feinard/modul2/");
        strftime(temp,20,"%Y-%m-%d_%T",timeinfo);
        strcat(timefolder,temp);

        run = fork();

        if(run == 0){
            char *makedir[] = {"mkdir",timefolder,NULL};
            execv("/bin/mkdir",makedir);
        }

        else if(run != 0){
            while(wait(&stat) > 0);
            int temp=0;
            while(temp < 20){
                temp++;
                chdir(timefolder);

                int x = ((int)time(NULL)%1000)+100;

                time(&rawtime);
                timeinfo = localtime ( &rawtime );

                char tempdown[80];
                char snum[10];

                sprintf(tempdown,"https://picsum.photos/%d",x);

                char filename[20];
                strftime(filename,20,"%Y-%m-%d_%T",timeinfo);

                char *wget[]={"wget",tempdown,"-O",filename,NULL};
                if(run = fork() == 0){
                    execv("/usr/bin/wget",wget);
                }
                sleep(5);
            }
            if(run = fork() == 0){
                char zipname[100];
                sprintf(zipname,"%s.zip",timefolder);
                char *zip[]={"zip",zipname,NULL};
                execv("/usr/bin/zip",zip);
            }
        }
    }
    else{
        sleep(30);
    }
}
return 0;
}
