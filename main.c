#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define KILO 1024

int I, N;

typedef char B;
typedef struct {
    B data[KILO];
} KB;

typedef struct {
    KB data[KILO];
} MB;

typedef struct {
    MB data[KILO];
} GB;

void progress(int i, int n) {
    printf("Init (%d/%d) [", I, N);
    for (int j = 0; j < i; j++) printf("=");
    for (int j = 0; j < n - i; j++) printf(" ");
    printf("]\r");
}

void init_kb(KB* kb) { memset(kb->data, 0, KILO); }

void init_mb(MB* mb) {
    for (int i = 0; i < KILO; i++) init_kb(&mb->data[i]);
}

void init_gb(GB* gb) {
    for (int i = 0; i < KILO; i++) {
        progress(i / 50, KILO / 50);
        init_mb(&gb->data[i]);
    }
}

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]);

    for (int i = 1; i < n; i++) {
        GB* data = (GB*)malloc(sizeof(GB) * i);
        printf("Allocate %dGB at %p\n", i, data);

        if (data == NULL) continue;

        for (int j = 0; j < i; j++) {
            I = j + 1;
            N = i;
            init_gb(&data[j]);
        }
        printf("\n");

        free(data);
        data = NULL;
    }
    return 0;
}
