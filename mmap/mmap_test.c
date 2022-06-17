#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/mman.h>

void mmapTest(int matrix_num)
{
    clock_t start1,start2, stop1,stop2;
    int *mmap_ptr[matrix_num];
    double running_time;
    
    for (int i = 0; i < matrix_num; i++)
    {
        mmap_ptr[i] = mmap(NULL, matrix_num * sizeof(int),
                      PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    }

    printf("mmap %dx%d행렬 곱 시작\n", matrix_num, matrix_num);
    start1 = clock();
    for (int i = 0; i < matrix_num; i++)
    {
        for (int j = 0; j < matrix_num; j++)
        {
            mmap_ptr[i][j] = 10;
        }
    }
    
    stop1 = clock();
    running_time = (double)(stop1 - start1) / CLOCKS_PER_SEC;
    printf("mmap %dx%d행렬 곱 수행시간:%f\n", matrix_num, matrix_num, running_time);
    
    for (int i = 0; i < matrix_num; i++)
    {
        int err = munmap(mmap_ptr[i], matrix_num * sizeof(int));
        if (err != 0)
        {
            printf("UnMapping Failed\n");
        }
    }
    

    if (mmap_ptr == MAP_FAILED)
    {
        printf("Mapping Failed\n");
    }

    int matrix[matrix_num][matrix_num];

    printf("일반 %dx%d행렬 곱셈 시작\n", matrix_num, matrix_num);
    start2 = clock();
    for (int i = 0; i < matrix_num; i++)
    {
        for (int j = 0; j < matrix_num; j++)
        {
            matrix[i][j] = 10;
        }
    }
    stop2 = clock();
    running_time = (double)(stop2 - start2) / CLOCKS_PER_SEC;
    printf("일반 %dx%d행렬 곱 수행시간:%f\n", matrix_num, matrix_num, running_time);

    printf("\n");
    
}

int main()
{
    for(int i=1; i<6; i++) {
        printf("%d회차:\n", i);
        mmapTest(100);
        mmapTest(500);
        mmapTest(1000);
    }

    return 0;
}
