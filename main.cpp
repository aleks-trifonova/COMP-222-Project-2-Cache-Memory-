#include <stdio.h>
#include <stdlib.h>

/* declare global var's */
int mainmemory_size, cache_size, block_size, numberlines;
/* define structure of dynamic cache and initialize var */
struct node {
    int tag;
    int *block;
}
        *cache = NULL;
typedef struct node line;
/* define dynamic array for main memory */
int *mainmemory = NULL;

/****************************************************************/
void OPTION1() {
/* declare local var's */
    int a, b;
/* Prompt for main memory size, cache size, block size */
    printf("Please enter main memory size: ");
    scanf("%d", &mainmemory_size);
    printf("Please enter cache size: ");
    scanf("%d", &cache_size);
    printf("Please enter block size: ");
    scanf("%d", &block_size);

/* allocate and initialize main memory--value at index i = size of main memory-i*/
    mainmemory = (int *) malloc(mainmemory_size * sizeof(int));
    for (int a = 0; a < mainmemory_size; a++) {
        mainmemory[a] = mainmemory_size - a;
    }
/* allocate memory for cache based on number of lines in cache*/
    numberlines = cache_size / block_size;
    cache = (line *) malloc(numberlines * sizeof(line));
/* initialize each tag to -1 and each block to NULL */
    for (int b = 0; b < numberlines; b++) {
        cache[b].tag = -1;
        cache[b].block = NULL;
    }

}


/****************************************************************/
void OPTION2() {
/* declare local var's */
    int read_write;
    int mainmemoryaddress;
    int data, tag, block, word, base;
    int k;


/* Prompt for read/write signal */
    printf("Please select 0 for read or 1 for write");
    scanf("%d", &read_write);

/* Prompt for main memory address to read/write */
    if (read_write == 0) { // this is the if statement for main memory read
        printf("Enter the main memory address to read from ");
        scanf("%d", &mainmemoryaddress);
    } else { // main memory write
        printf("Please enter the main memory address to write to ");
        scanf("%d", &mainmemoryaddress);
        printf("Please enter the value you wish to write ");
        scanf("%d", &data);
    }

/* Translate main mem addr to cache addr fields & create a base address */
    base = (mainmemoryaddress / block_size) * block_size;
    tag = (mainmemoryaddress / cache_size);
    word = (mainmemoryaddress % block_size);
    block = ((mainmemoryaddress % cache_size) / block_size);

/* Case 1: MISS--BLOCK NOT ALLOCATED */
    if (cache[block].tag == -1)

/* Allocate cache block based on block size */
        cache[block].block = (int *) malloc(block_size * sizeof(int));


/* Case 2: MISS--NON-MATCHING TAGS */
        if (cache[block].tag != tag)
/* Print message of Read/Write miss */
            if (read_write == 0)
                printf("Miss read: \n");
                else {
                    printf("Miss write. \n");
                }

/* Overwrite tag */
                cache[block].tag = tag;
/* Transfer equivalent block of main memory to cache--one word at a time */
                for (k = 0; k < block_size; k++) {
                    cache[block].block[k] = mainmemory[base + k];
                }



        }


/* Case 3:HIT DUE TO MATCHING TAGS */
    else if (cache[block].tag == tag) {



/* print message of Read/Write hit*/
        if (read_write == 0) {
            printf("Hit read. \n");
            else {
                printf("Hit write. \n");
            }
        }
    }


/* reference cache word, transfer data to/from cache depending on read/write signal*/
    if (read_write == 0) /* read */
{
    data = cache[block].block[word];
    else /* write */{
/* reverse above calculation */
    cache[block].block[word] =
    data;
/* update main memory if you are doing a write -- write through */
    mainmemory[mainmemoryaddress] = data;
}

/* Print message of word, block, tag, data value */
printf("***************************************************** \n");
printf("| Tag: %d | Block: %d |Word: %d | Data Value: %d | \n", tag, block, word, data);
printf("*************************************************************************************\n");

return;

}

/****************************************************************/
int main() {
/* declare local var's */
    int userschoice = 0;
    printf("This is the Cache Memory Allocator and Mapping Simulator \n");
/* until program exits, print menu, select choice via switch statement and call appropriate function*/
    while (userschoice != 3) {
        printf("\n***************************************************\n");
        printf("Options Menu \n ");
        printf("1. Enter the parameters \n");
        printf("\n");
        printf("2.Access the cache for read/write and data transfer \n");
        printf("\n");
        printf("3.Quit\n");
        printf("\n");
        printf("Enter Selection\n");
        printf("\n");
        scanf("%d", &userschoice);

        switch (userschoice) {
            case 1:
                OPTION1();
                break;

            case 2:
                OPTION2();
                break;

                case 3:
                    printf("Now quitting\n");
                break;

                default:
                    printf("Your input was invalid. Try again: \n");
            }

        }
        return 1;
    }
