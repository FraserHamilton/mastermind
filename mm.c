#include <stdio.h>  // input/output library
#include <stdlib.h> // general functions library
#include <sys/time.h>   // time library
#include <signal.h>

#define PEGS 3 // defines number of pegs
#define COLORS 3 // defines number of colours
#define TURNS 3 // defines numer of turns

struct SS {
    int pegs[PEGS];
};

struct SS * generateSecret() {
    struct SS * secret = (struct SS*)malloc(sizeof(struct SS));
    srand(time(NULL));
    for(int i = 0; i < PEGS; i++) {
        secret->pegs[i] = rand() % COLORS; 
    }
    
    return secret;
}

struct SS * customSecret(int a, int b, int c) {
    struct SS * secret = (struct SS*)malloc(sizeof(struct SS));
    secret->pegs[0] = a;
    secret->pegs[1] = b; 
    secret->pegs[2] = c;  
    
    return secret;
}


int * compareSecret(struct SS * s, struct SS * g) {
    // copy into fresh arrays
    // improve algo
    int * answer = (int*)malloc(2 * sizeof(int));
    answer[0] = 0;
    answer[1] = 0;
    for(int i = 0; i < PEGS; i++) {
        if(g->pegs[i] == s->pegs[i]) {
            answer[0]++;
            s->pegs[i] = -1;
            g->pegs[i] = -2;
        } 
    }

    for(int j = 0; j < PEGS; j++) {
        for(int k = 0; k < PEGS; k++) {
            if(g->pegs[j] == s->pegs[k]) {
                answer[1]++;
                s->pegs[j] = -1;
                g->pegs[k] = -2;
            } 
        }
    }
   
    printf("%d",answer[0]);
    printf("%d",answer[1]);

    return answer;
}

void printSecret(struct SS * s) {
    for(int i = 0; i < PEGS; i++) {
        printf("%d", s->pegs[i]);
    }
    printf("\n");
}

void newGame() {
    struct SS *secret = generateSecret();
    struct SS *secret2 = customSecret(1,2,1);
    printSecret(secret);
    printSecret(secret2);
    compareSecret(secret,secret2);
}

void main(int argc, char ** argv)
{
    newGame();
}
