#include <unistd.h>

int main(){

    int i;
    pid_t pid = 1;

    for(i = 0; i < 10; i++){
        if(pid != 0){
            pid = fork();
        }
    }

    if(pid == 0){
        int x = 0;
        int y = 1;
        int z = 0;
        for(;;){
            z = x;
            x = y;
            y = z;
        }
    }

    return 0;
}

