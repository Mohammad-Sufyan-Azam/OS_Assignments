#include <stdio.h>
#include <sys/syscall.h>
#define kernel_2D_memcpy 450

int main() {
    float arr[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    float arr2[3][3];

    printf("arr1 is-\n");
    for(int i=0; i<3; i++)  {
        for(int j=0; j<3; j++)
            printf("%.2f ", arr[i][j]);
        printf("\n");
    }

    if (syscall(kernel_2D_memcpy, (float*)arr2, (float*)arr, 3, 3) == -1)
        printf("ERROR: Could not copy the matrix!\n");
    else {

        printf("Array copied succesfully!\narr2 is-\n");
        for(int i=0; i<3; i++) {
            for (int j = 0; j < 3; j++)
                printf("%.2f ", arr2[i][j]);
            printf("\n");
	}
    }
}
