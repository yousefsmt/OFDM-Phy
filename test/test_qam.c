#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "qam.h"

typedef struct timeval timeval;

#define NUMBER_OF_DATA 1000000

int open_bin_file(uint8_t* buffer, uint64_t num_data)
{
    FILE     *read_file = fopen("data_1M.bin", "rb");
    uint64_t num_readed = 0l;
    int      is_correct = 0;

    if (read_file)
    {
        num_readed = fread(buffer, sizeof(uint8_t), num_data, read_file);
        if (num_readed != num_data)
        {
            fprintf(stderr, "cannot read all elements from BIN file\n");
            return -1;
        }
        printf("Open BIN file and read %ld bytes from file\n", num_readed);
        is_correct = fclose(read_file);
        if (is_correct == -1)
        {
            fprintf(stderr, "cannot close stream file\n");
            return -1;
        }
    }
    else
    {
        fprintf(stderr, "cannot open file maybe doesn't exist\n");
        return -1;
    }

    return 0;
}



int main()
{
    int        is_correct = 0;
    uint8_t*   input      = (uint8_t*)malloc(sizeof(uint8_t) * NUMBER_OF_DATA);
    complex_t* output     = (complex_t*)malloc(sizeof(complex_t) * SYMBOL_RATE);


    timeval start = {.tv_sec = 0, .tv_usec = 0};
    timeval stop  = {.tv_sec = 0, .tv_usec = 0};
    

    if (input && output)
    {
        is_correct = open_bin_file(input, NUMBER_OF_DATA);
        if (is_correct == -1)
        {
            fprintf(stderr, "open file error\n");
            return -1;
        }

        printf("\n\n***** Verify Read Corrected *****\n");
        printf("input[0]: %d\n", input[0]);
        printf("input[1]: %d\n", input[1]);
        printf("input[999998]: %d\n", input[NUMBER_OF_DATA-2]);
        printf("input[999999]: %d\n", input[NUMBER_OF_DATA-1]);
        printf("************************************\n\n");

        gettimeofday(&start, NULL);
        is_correct = map_bits_to_complex(input, output);
        if (is_correct == -1)
        {
            fprintf(stderr, "modulation error\n");
            return -1;
        }
        gettimeofday(&stop, NULL);
        double time_elapsed = (stop.tv_sec - start.tv_sec)*1000000.0 + (stop.tv_usec - start.tv_usec);
        printf("Modulation Runtime: %f\n", time_elapsed);
        printf("MODULATION: %d\n", is_correct);

        printf("\n\n***** Verify Complex 16-QAM Output *****\n");
        printf("output[0]: %f + j(%f)\n", output[0].i, output[0].q);
        printf("output[1]: %f + j(%f)\n", output[1].i, output[1].q);
        printf("output[1999998]: %f + j(%f)\n", output[SYMBOL_RATE-2].i, output[SYMBOL_RATE-2].q);
        printf("output[1999999]: %f + j(%f)\n", output[SYMBOL_RATE-1].i, output[SYMBOL_RATE-1].q);
        printf("************************************\n\n");

        free(input);
        free(output);
    }
    else
    {
        fprintf(stderr, "allocation error\n");
        return -1;
    }

    return 0;
}