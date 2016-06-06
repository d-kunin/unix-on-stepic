#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int get_path_for_pid(char * path, pid_t pid)
{
    return sprintf(path, "/proc/%d/status", pid);
}

pid_t get_parent_pid(pid_t pid)
{
    char path[256];
    if ( get_path_for_pid(path, pid) == -1) {
        return -1; // error here
    }
    FILE * proc_file = fopen(path, "r");
    if (!proc_file) {
        return -2; // error with file
    }
    // finding a line
    char * ppid_line = NULL;
    char line[512];
    while ( fgets(line, sizeof line, proc_file) != NULL) {
        if ( strstr(line, "PPid") ) {
            ppid_line = line;
            break; 
        }
    }
    if (!ppid_line) {
        return -3; // error line not found
    }
    int start = 0;
    while ( !isdigit(ppid_line[start]) || ppid_line[start] == '\0') {
        start++;
    }
    if ( ppid_line[start] ==  '\0') {
        return -4; // didn't find any numerics
    }
    char ppid_str[32];
    if ( !strcpy(ppid_str, ppid_line + start) ) {
        return -5;
    }
    return atoi(ppid_str);
}

int main(int arc, char ** argv)
{
    pid_t pid = getpid();

    int level = 0;
    printf("%d-level PID=%d\n",level++, pid);

    while ( 0 != (pid = get_parent_pid(pid)) ) {
        printf("%d-level PID=%d\n",level++, pid);
    } 

    return 0;
}

