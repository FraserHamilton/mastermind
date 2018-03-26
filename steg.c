#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int lines = 0;
struct PPM {
    char format[2];
    int width;
    int height;
    int max;
    int colors[9300000][3];
    struct node *head;
};

struct node {
    char text[260];
    struct node *next;
};

void insert(struct PPM * i, char comment[]) {
    struct node *new = (struct node*)malloc(sizeof(struct node));
    strcpy(new->text, comment);
    new->next = i->head;
    i->head = new;
}

struct PPM * decode(struct PPM * i1, struct PPM * i2) {
    for(int j = 0; j < lines; j++) {
        if((int) i1->colors[j][0] != (int) i2->colors[j][0]) {
            printf("%c", i2->colors[j][0]);
        }
        if((int) i1->colors[j][1] != (int) i2->colors[j][1]) {
            printf("%c", i2->colors[j][1]);
        }
        if((int) i1->colors[j][2] != (int) i2->colors[j][2]) {
            printf("%c", i2->colors[j][2]);
        }
    }
}

struct PPM * encode(char * text, struct PPM * i) {
    srand(time(NULL));
    int ran = rand() % 10;
    int cpos = 0;
    for(int j=0; j<(sizeof(text))-1; j++) {
        i->colors[ran+cpos][0] = text[j];
        cpos = ran+cpos;
    }
    return i;
}

void showPPM(struct PPM * i) {
    printf("%s", i->format);
    struct node * curr;
    curr = i->head;
    printf("%s", curr->text);
    while(curr->next != NULL) {
        curr = curr->next;
        printf("%s", curr->text);
    }
    printf("%d ", i->width);
    printf("%d \n", i->height);
    printf("%d \n", i->max);
    for(int j=0; j < lines; j++) {
        printf("%d %d %d \n", i->colors[j][0], i->colors[j][1], i->colors[j][2]);

    }
         
}

void printFile(FILE * fd) {
    int c;
    char buffer[260];
    if (fd) {
        // fgets(buffer, sizeof(buffer), fd);
        // printf(buffer);
        while ((c = getc(fd)) != 32) {
            putchar(c);
        }
    }
}

struct PPM * getPPM(FILE * fd) {
    char buffer[260];
    char buffer2[260];
    char buffer3[260];
    struct PPM * image;
    image = (struct PPM *)malloc(sizeof(struct PPM));
    image->head=NULL;
    if(fd) {
        fgets(buffer, sizeof(buffer), fd);
        strcpy(image->format, buffer);
        fgets(buffer, sizeof(buffer), fd);
        while(buffer[0] == 35) {
            insert(image, buffer);
            fgets(buffer, sizeof(buffer), fd);
        }
        sscanf(buffer, "%s %s", buffer2, buffer3);
        image->width = atoi(buffer2);
        image->height = atoi(buffer3);
        fgets(buffer, sizeof(buffer), fd);
        image->max = atoi(buffer);
        int row = 0;
        while(fscanf(fd, "%s %s %s", buffer2, buffer3, buffer) != EOF) {
            image->colors[row][0] = atoi(buffer2);
            image->colors[row][1] = atoi(buffer3);
            image->colors[row][2] = atoi(buffer);
            row++;
        }  
        
        fclose(fd);
        return image;
    }
}

void main(int argc, char ** argv)
{
    FILE * file;
    file = fopen(argv[2], "r");
        int ch=0;
        while(!feof(file))
        {
            ch = fgetc(file);
                if(ch == '\n')
                {
                    lines++;
                }
        }
    rewind(file);
    fclose(file);
    if(strcmp(argv[1],"e") == 0) {
        char string [256];
        printf ("Please enter a value to encode: ");
        gets (string);
        freopen("output.ppm","w",stdout);
        FILE * file;
        file = fopen(argv[2], "r");
        struct PPM * image;
        image = (struct PPM *)malloc(sizeof(struct PPM));
        image = getPPM(file);
        encode(string, image);
        showPPM(image);
        fclose(file);
    } else if(strcmp(argv[1],"d") == 0) {
        FILE * file1;
        file1 = fopen(argv[2], "r");
        FILE * file2;
        file2 = fopen(argv[3], "r");
        struct PPM * image1;
        struct PPM * image2;
        image1 = (struct PPM *)malloc(sizeof(struct PPM));
        image2 = (struct PPM *)malloc(sizeof(struct PPM));
        image1 = getPPM(file1);
        image2 = getPPM(file2);
        decode(image1, image2);
        fclose(file1);
        fclose(file2);

    }
}
