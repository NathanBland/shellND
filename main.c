#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

void cd(char *nextData) {

}

/*
 *Clears away the screen
 */
void clr() {
    printf("\033[2J");
    printf("\033[1;1H");
}

/*
 *Lists the current directory contents
 */
void dir(char *nextData) {
    DIR *dir;
    struct dirent *file;
    nextData = strtok(NULL, " ");
    if (nextData == NULL){
        nextData = ".";
    }
    if ((dir = opendir(("%s", nextData))) == NULL)
        perror("opendir() error");
    while((file = readdir(dir)) != NULL)
        printf("  %s\t", file->d_name);
    printf("\n");
}

void env() {
    extern char **environ;
    int i = 0;
    while (environ[i]){
        printf("%s\n", environ[i++]);
    }
}


void echo(char *nextData) {
    if (nextData == NULL){
        printf("please enter a comment");
    }else{
        nextData = strtok(NULL, " ");
        while(nextData !=NULL){
            printf("%s ", nextData);
            nextData = strtok(NULL, " ");
        }
        printf("\n");
    }
}

void help() {
    printf("#################################### HELP ######################################\n");
    printf("#                          ===== List of Commands =====                        #\n");
    printf("# * cd      - navigates to a specified directory                               #\n");
    printf("# * clr     - clears the current text from the window.                         #\n");
    printf("# * dir     - lists the contents of the current directory.                     #\n");
    printf("# * environ - displays all the environmental variables.                        #\n");
    printf("# * echo    - prints whatever data is given to it.                             #\n");
    printf("# * help    - displays this help text.                                         #\n");
    printf("# * pause   - pauses the shell.                                                #\n");
    printf("# * quit    - terminates the shell. Same as: exit, and kill.                   #\n");
    printf("#################################### HELP ######################################\n");
}

void mypause() {

}

/* function to set environment values and set starting location.

*/
void setVariables() {
    char cwd[1024];
    char *pathname;
    char *name= "shell";
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        pathname = malloc(strlen(name)+strlen(cwd)+1);
        sprintf(pathname, "%s=%s", name, cwd);
        putenv(pathname);
    }
    else
        perror("getcwd() error");
    return 0;
}
/*
Function that listens for input.
*/
void inputloop() {
    char line[256];
    gets(line);
    char *nextData;
      nextData = strtok(line," ");
      while (nextData != NULL)
      {
        if (strcmp("cd", nextData) == 0){
            cd(nextData);
        }else if (strcmp("clr", nextData) == 0) {
            clr();
        }else if (strcmp("dir", nextData) == 0) {
            dir(nextData);
        }else if (strcmp("environ", nextData) == 0) {
            env();
        }else if (strcmp("echo", nextData) == 0) {
            echo(nextData);
        }else if (strcmp("help", nextData) == 0) {
            help();
        }else if (strcmp("pause", nextData) == 0) {
            printf("Press ENTER to continue.");
            char *a;
            gets(a);
        }else if ((strcmp("quit", nextData) == 0) || (strcmp("exit", nextData) == 0)  || (strcmp("kill", nextData) == 0)) {
            exit(EXIT_SUCCESS);
        }else{printf("not a command\n");}
        nextData = strtok(NULL, " ");
      }
}


int main(void)
{
    setVariables();
    while (1) {
        inputloop();
    }
    return 0;
}
