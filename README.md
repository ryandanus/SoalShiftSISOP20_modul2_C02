# SoalShiftSISOP20_modul2_C02

# SoalShift_modul2_A13
  - [Nomor 1](#nomor-1)
  - [Nomor 2](#nomor-2)
  - [Nomor 3](#nomor-3)

## Nomor 1
### Soal :
1. Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan
ketentuan sebagai berikut:
- a. Program menerima 4 argumen berupa:
    i. Detik: 0-59 atau * (any value)
    ii. Menit: 0-59 atau * (any value)
    iii. Jam: 0-23 atau * (any value)
    iv. Path file .sh
- b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak
  sesuai
- c. Program hanya menerima 1 config cron
- d. Program berjalan di background (daemon)
- e. Tidak boleh menggunakan fungsi system()

Contoh: ./program \* 34 7 /home/somi/test.sh
Program dengan argumen seperti contoh di atas akan menjalankan script test.sh setiap
detik pada jam 07:34.

### Jawaban :

```
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

//deklarasi main harus menggunakan argv untuk baca input detik,menit,waktu,path
int main(int argc, char *argv[]) {

  pid_t pid, sid;

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
  
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);


  while (1) {
    pid_t run;

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
```
Program dijalankan 

## Nomor 2
### Soal :
2. Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia
  merasa sudah jago materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat
  sebuah program.
- a. Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat
  sebuah program C yang per 30 detik membuat sebuah folder dengan nama
  timestamp [YYYY-mm-dd_HH:ii:ss].
- b. Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari
  https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap
  gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah

  detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-
  mm-dd_HH:ii:ss].

- c. Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan
  folder akan di delete(sehingga hanya menyisakan .zip).

- d. Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men-
  generate sebuah program "killer" yang siap di run(executable) untuk

  menterminasi semua operasi program tersebut. Setelah di run, program yang
  menterminasi ini lalu akan mendelete dirinya sendiri.

- e. Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu
  MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan
  dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen
  -b. Ketika dijalankan dalam MODE_A, program utama akan langsung
  menghentikan semua operasinya ketika program killer dijalankan. Untuk
  MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi
  membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua
  folder terisi gambar, terzip lalu di delete).

Kiwa lalu terbangun dan sedih karena menyadari programnya hanya sebuah mimpi.
Buatlah program dalam mimpi Kiwa jadi nyata!
Catatan:
- Tidak boleh memakai system().
- Program utama harus ter-detach dari terminal
Hint:
- Gunakan fitur picsum.photos untuk mendapatkan gambar dengan ukuran
tertentu
- Epoch Unix bisa didapatkan dari time()
### Jawaban :

```
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
```
penjelasan 

## Nomor 3
### Soal :
3. Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia
memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan
(multiprocessing).
- a. Program buatan jaya harus bisa membuat dua direktori di
  “/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu
  lima detik kemudian membuat direktori yang kedua bernama “sedaap”.
- b. Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori
  “/home/[USER]/modul2/”. Setelah tugas sebelumnya selesai, ternyata tidak
  hanya itu tugasnya.
- c. Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di
  dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan
  pengelompokan, semua file harus dipindahkan ke
  “/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke
  “/home/[USER]/modul2/indomie/”.
- d. Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/”
  harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu
  3 detik kemudian membuat file bernama “coba2.txt”.
  (contoh : “/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”).
  Karena Jaya terlalu banyak tugas dia jadi stress, jadi bantulah Jaya agar bisa membuat
  program tersebut.
Catatan :
- Tidak boleh memakai system().
- Tidak boleh memakai function C mkdir() ataupun rename().
- Gunakan exec dan fork
- Direktori “.” dan “..” tidak termasuk

### Jawaban :

```
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

  pid1 = fork();

  if(pid1 == 0){
    if(pid2 = fork() == 0){
      char *ar[] = {"mkdir","/home/danu/modul2/indomie",NULL};
      execv("/bin/mkdir",ar);
    }
    sleep(5);
    if(pid2 = fork() == 0){
      char *br[] = {"mkdir","/home/danu/modul2/sedap",NULL};
      execv("/bin/mkdir",br);
    }
    if(pid2 = fork() == 0){
      chdir("/home/danu/modul2");
      char *exc[] = {"unzip","jpg.zip",NULL};
      execv("/usr/bin/unzip",exc);
    }
    
  }
  
  sleep(2);

  struct dirent *der;
  DIR *dir = opendir("/home/danu/modul2/jpg");
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
      strcpy(filepath,"/home/danu/modul2/jpg/");
      strcat(filepath,der->d_name);

      if(stat(filepath,&typestat) == 0){
        if( typestat.st_mode & S_IFDIR ){
          if(pid1 = fork() == 0){
            char *movDir[]={"mv",filepath,"/home/danu/modul2/indomie",NULL};
            execv("/bin/mv",movDir);
          }
       }
       else if( typestat.st_mode & S_IFREG ){
         if(pid1 = fork() == 0){
           char *movReg[]={"mv",filepath,"/home/danu/modul2/sedap",NULL};
           execv("/bin/mv",movReg);
         }
       }
      }
    }
  }

  closedir(dir);

  struct dirent *mkfile;
  DIR *files = opendir("/home/danu/modul2/indomie");

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
      strcpy(locpath,"/home/danu/modul2/indomie/");
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
```

Untuk menjalankan perintah pada 3a digunakanlah fork dan exec untuk membuat direktori untuk memberikan jeda selama 5 detik sebelum membuat direktori sedaap digunakanlah sleep(5) 

```
char *ar[] = {"mkdir","/home/danu/modul2/indomie",NULL};
execv("/bin/mkdir",ar);

sleep(5);

char *br[] = {"mkdir","/home/danu/modul2/sedap",NULL};
execv("/bin/mkdir",br);
```

untuk mengekstrak file yang berbentuk zip pada file tersebut yaitu jpg.zip, mengggunakan exec dimana file itu sebelumnya telah diletakkan pada direktori "/home/danu/modul2" 

```
chdir("/home/danu/modul2");
char *exc[] = {"unzip","jpg.zip",NULL};
execv("/usr/bin/unzip",exc);
```
    
    
    
# Kendala
