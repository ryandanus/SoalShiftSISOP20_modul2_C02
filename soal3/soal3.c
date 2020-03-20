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

int main(){
  pid_t pid1,pid2;

  int status;
  pid1 = fork();

  if(pid1 == 0){
    if(pid2 = fork() == 0){
      char *ar[] = {"mkdir","/home/feinard/modul2/indomie",NULL};
      execv("/bin/mkdir",ar);
    }
    sleep(5);
    if(pid2 = fork() == 0){
      char *br[] = {"mkdir","/home/feinard/modul2/sedap",NULL};
      execv("/bin/mkdir",br);
    }
    if(pid2 = fork() == 0){
      chdir("/home/feinard/modul2");
      char *exc[] = {"unzip","jpg.zip",NULL};
      execv("/usr/bin/unzip",exc);
    }
  }

  while(wait(&status) > 0);

  struct dirent *der;
  DIR *dir = opendir("/home/feinard/modul2/jpg");
  if(dir == NULL){
    return 0;
  }


  while ((der = readdir(dir)) != NULL) {
    char filepath[80];
    struct stat typestat;
    if(strcmp(der->d_name,".")==0 || strcmp(der->d_name,"..")==0){
      continue;
    }
    else{
      strcpy(filepath,"/home/feinard/modul2/jpg/");
      strcat(filepath,der->d_name);

      if(stat(filepath,&typestat) == 0){
        if( typestat.st_mode & S_IFDIR ){
          if(pid1 = fork() == 0){
            char *movDir[]={"mv",filepath,"/home/feinard/modul2/indomie",NULL};
            execv("/bin/mv",movDir);
          }
       }
       else if( typestat.st_mode & S_IFREG ){
         if(pid1 = fork() == 0){
           char *movReg[]={"mv",filepath,"/home/feinard/modul2/sedap",NULL};
           execv("/bin/mv",movReg);
         }
       }
      }
    }
  }

  closedir(dir);

  struct dirent *mkfile;
  DIR *files = opendir("/home/feinard/modul2/indomie");

  if(files == NULL){
    printf("directory error\n");
    return 0;
  }


  while ((mkfile = readdir(files)) != NULL) {

    if(strcmp(mkfile->d_name,".")==0 || strcmp(mkfile->d_name,"..")==0){
      continue;
    }
    else{
      char locpath[80];
      strcpy(locpath,"/home/feinard/modul2/indomie/");
      strcat(locpath,mkfile->d_name);

      if(pid1 = fork() == 0){
        chdir(locpath);
        char *temp[]={"touch","coba1.txt",NULL};
        execv("/bin/touch",temp);
      }
      sleep(3);
      if(pid1 = fork() == 0){
        chdir(locpath);
        char *temp[]={"touch","coba2.txt",NULL};
        execv("/bin/touch",temp);
      }
    }
  }
  closedir(files);
}
