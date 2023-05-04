#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include<sys/wait.h>

void display_regular_file_info(char *filename) {
    struct stat filestat;
    if (lstat(filename, &filestat) == -1) {
        perror("Failed to get file info");
        return;
    }

    printf("File name: %s\n", filename);
    printf("File type: Regular File\n");
    printf("Size: %ld bytes\n", filestat.st_size);
    printf("Hard link count: %ld\n", filestat.st_nlink);
    printf("Time of last modification: %s", ctime(&filestat.st_mtime));
    printf("Access rights:\n");
    printf("User:\n");
    printf("Read - %s\n", (filestat.st_mode & S_IRUSR) ? "yes" : "no");
    printf("Write - %s\n", (filestat.st_mode & S_IWUSR) ? "yes" : "no");
    printf("Exec - %s\n", (filestat.st_mode & S_IXUSR) ? "yes" : "no");
    printf("Group:\n");
    printf("Read - %s\n", (filestat.st_mode & S_IRGRP) ? "yes" : "no");
    printf("Write - %s\n", (filestat.st_mode & S_IWGRP) ? "yes" : "no");
    printf("Exec - %s\n", (filestat.st_mode & S_IXGRP) ? "yes" : "no");
    printf("Others:\n");
    printf("Read - %s\n", (filestat.st_mode & S_IROTH) ? "yes" : "no");
    printf("Write - %s\n", (filestat.st_mode & S_IWOTH) ? "yes" : "no");
    printf("Exec - %s\n", (filestat.st_mode & S_IXOTH) ? "yes" : "no");

    char options[256];
    printf("Enter options: ");
    scanf("%s", options);

    for (int i = 0; i < strlen(options); i++) {
        switch (options[i]) {
            case 'n':
                printf("File name: %s\n", filename);
                break;
            case 'd':
                printf("Size: %ld bytes\n", filestat.st_size);
                break;
            case 'h':
                printf("Hard link count: %ld\n", filestat.st_nlink);
                break;
            case 'm':
                printf("Time of last modification: %s", ctime(&filestat.st_mtime));
                break;
            case 'a':
                printf("Access rights:\n");
                printf("User:\n");
                printf("Read - %s\n", (filestat.st_mode & S_IRUSR) ? "yes" : "no");
                printf("Write - %s\n", (filestat.st_mode & S_IWUSR) ? "yes" : "no");
                printf("Exec - %s\n", (filestat.st_mode & S_IXUSR) ? "yes" : "no");
                printf("Group:\n");
                printf("Read - %s\n", (filestat.st_mode & S_IRGRP) ? "yes" : "no");
                printf("Write - %s\n", (filestat.st_mode & S_IWGRP) ? "yes" : "no");
                printf("Exec - %s\n");
                printf("Read - %s\n", (filestat.st_mode & S_IXGRP) ? "yes" : "no");
                printf("Others:\n");
                printf("Read - %s\n", (filestat.st_mode & S_IROTH) ? "yes" : "no");
                printf("Write - %s\n", (filestat.st_mode & S_IWOTH) ? "yes" : "no");
                printf("Exec - %s\n", (filestat.st_mode & S_IXOTH) ? "yes" : "no");
                break;
            case '1':
                printf("Enter name of symbolic link: ");
                char linkname[256];
                scanf("%s", linkname);
                if (symlink(filename, linkname) == -1) {
                    perror("Failed to create symbolic link");
                } else {
                    printf("Symbolic link '%s' created successfully.\n", linkname);
                }
                break;
            default:
                printf("Invalid option: %c\n", options[i]);
        }
    }
}

void display_symlink_info(char *filename) {
    struct stat filestat;
    if (lstat(filename, &filestat) == -1) {
        perror("Failed to get file info");
        return;
    }

    printf("File name: %s\n", filename);
    printf("File type: Symbolic Link\n");
    printf("Size of symbolic link: %ld bytes\n", filestat.st_size);
    printf("Size of target file: %ld bytes\n", filestat.st_blocks * 512);
    printf("Access rights:\n");
    printf("User:\n");
    printf("Read - %s\n", (filestat.st_mode & S_IRUSR) ? "yes" : "no");
    printf("Write - %s\n", (filestat.st_mode & S_IWUSR) ? "yes" : "no");
    printf("Exec - %s\n", (filestat.st_mode & S_IXUSR) ? "yes" : "no");
    printf("Group:\n");
    printf("Read - %s\n", (filestat.st_mode & S_IRGRP) ? "yes" : "no");
    printf("Write - %s\n", (filestat.st_mode & S_IWGRP) ? "yes" : "no");
    printf("Exec - %s\n", (filestat.st_mode & S_IXGRP) ? "yes" : "no");
    printf("Others:\n");
    printf("Read - %s\n", (filestat.st_mode & S_IROTH) ? "yes" : "no");
    printf("Write - %s\n", (filestat.st_mode & S_IWOTH) ? "yes" : "no");
    printf("Exec - %s\n", (filestat.st_mode & S_IXOTH) ? "yes" : "no");

    char options[256];
    printf("Enter options: ");
    scanf("%s", options);

    for (int i = 0; i < strlen(options); i++) {
        switch (options[i]) {
            case 'n':
                printf("File name: %s\n", filename);
                break;
            case '1':
                printf("Enter name of symbolic link to delete: ");
                char linkname[256];
                scanf("%s", linkname);
                if (unlink(linkname) == -1) {
                    perror("Failed to delete symbolic link");
                } else {
                    printf("Symbolic link '%s' deleted successfully.\n", linkname);
                }
                break;
            case 'd':
                printf("Size of symbolic link: %ld                bytes\n", filestat.st_size);
                break;
            case 't': {
                char target[256];
                ssize_t size = readlink(filename, target, sizeof(target));
                if (size == -1) {
                    perror("Failed to read target of symbolic link");
                } else {
                    target[size] = '\0';
                    printf("Size of target file: %ld bytes\n", filestat.st_blocks * 512);
                    printf("Target file: %s\n", target);
                }
                break;
            }
            case 'a':
                printf("Access rights:\n");
                printf("User:\n");
                printf("Read - %s\n", (filestat.st_mode & S_IRUSR) ? "yes" : "no");
                printf("Write - %s\n", (filestat.st_mode & S_IWUSR) ? "yes" : "no");
                printf("Exec - %s\n", (filestat.st_mode & S_IXUSR) ? "yes" : "no");
                printf("Group:\n");
                printf("Read - %s\n", (filestat.st_mode & S_IRGRP) ? "yes" : "no");
                printf("Write - %s\n", (filestat.st_mode & S_IWGRP) ? "yes" : "no");
                printf("Exec - %s\n", (filestat.st_mode & S_IXGRP) ? "yes" : "no");
                printf("Others:\n");
                printf("Read - %s\n", (filestat.st_mode & S_IROTH) ? "yes" : "no");
                printf("Write - %s\n", (filestat.st_mode & S_IWOTH) ? "yes" : "no");
                printf("Exec - %s\n", (filestat.st_mode & S_IXOTH) ? "yes" : "no");
                break;
            case 'I':
                return;
            default:
                printf("Invalid option: %c\n", options[i]);
        }
    }
    int argc;
    //char *argv[];
    int opt;
    while((opt=getopt(argc, argv,"nl:d:t:a:")) !=-1){
        switch (opt) {
            case 'n':
                printf("Name of symbolic link: %s\n", argv[optind]);
                break;
            case 'l':
                if(unlink(argv[optind])== -1){
                    perror("unlink");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'd':
               {
                 struct stat sb;
                 if (lstat(argv[optind], &sb)==-1){
                    perror("lstat");
                    exit(EXIT_FAILURE);
                 }
                 printf("Size of symbolic link: %ld bytes\n", sb.st_size);
               }    
               break;
            case 't':
                {
                    struct stat sb;
                    if (stat(argv[optind], &sb) ==-1){
                        perror("stat");
                        exit(EXIT_FAILURE);
                    }
                    printf("Size of target file: %ld bytes\n", sb.st_size);
                }   
             case 'a':
                {
                    struct stat sb;
                    if (stat(argv[optind], &sb) ==-1){
                        perror("stat");
                        exit(EXIT_FAILURE);
                    }
                    printf("Access rights:%o\n", sb.st_mode);
                }

        }
    }
}



int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename1> <filename2> ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        char *filename = argv[i];
        struct stat filestat;

        if (lstat(filename, &filestat) == -1) {
            perror("Failed to get file info");
            continue;
        }

        printf("File name: %s\n", filename);

        if (S_ISREG(filestat.st_mode)) {
            printf("File type: Regular File\n");
            display_regular_file_info(filename);
        } else if (S_ISLNK(filestat.st_mode)) {
            printf("File type: Symbolic Link\n");
            display_symlink_info(filename);
        } else if (S_ISDIR(filestat.st_mode)) {
            printf("File type: Directory\n");
            //display_directory_info(filename);
        } else {
            printf("File type: Unknown\n");
        }

        printf("\n");
    }

    return 0;
}

/*int parentp() {
    pid_t pid, w;
    pid = fork();
    int wstatus;

    if(pid<0) {
        printf("error fork()");
        exit(1);
    }
    
    if(pid==0) {
        printf("this is the child process with pid %d \n", getpid());
        
        //execlp("ls", "ls", "-l", NULL);
        exit(5);
    }
    else {
        if(pid>0) {
            printf("this is the parent process\n");
            w = wait(&wstatus);
            if(WIFEXITED(wstatus)) {
                printf("process with pid %d, exited, status = %d\n", w, WEXITSTATUS(wstatus));
            }
        }
    }
}
*/