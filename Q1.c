#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void print_to_file(int **arr, int n, int format_flag){
        FILE *file;
        if(format_flag == 0){
                char filename[50] = "", str_int[6] = "", num[6] = "";
                sprintf(str_int, "%d", n);
                int len = strlen(str_int);
                memset(num, '0', 6 - len);
                strcat(num, str_int);
                strcat(filename, "array_");strcat(filename, num);strcat(filename, "_asc.out");

                file = fopen(filename, "w");
                for(int i = 0; i < n; i++){
                        for(int j = 0; j < n; j++){
                                fprintf(file, "%.15e",(double)arr[i][j]);
                                //printf("    ");
                        }
                        fprintf(file, "\n");
                }
        }
        if(format_flag == 1){
                char filename[50] = "", str_int[6] = "", num[6] = "";
                sprintf(str_int, "%d", n);
                int len = strlen(str_int);
                memset(num, '0', 6 - len);
                strcat(num, str_int);
                strcat(filename, "array_");strcat(filename, num);strcat(filename, "_bin.out");

                file = fopen(filename, "wb");
                for(int i = 0; i < n; i++){
                          fwrite(arr[i], sizeof(int), n, file);
                }
                fclose(file);
                /*file = fopen(filename, "rb");
                int read_row[n]; // Temporary buffer for each row
                printf("Contents of the binary file:\n");
                for (int i = 0; i < n; i++) {
                        fread(read_row, sizeof(int), n, file); // Read one row
                        for (int j = 0; j < n; j++) {
                                printf("%d ", read_row[j]); // Print each element
                        }
                printf("\n");
                }
                fclose(file);*/
        //file = fopen(filename, "rb");
        }

        return;

}

int main(){
        FILE *file;
        int n;
        file = fopen("input.in", "r");
        fscanf(file, "%d", &n);
        fclose(file);
        //printf("%d and %d\n", nx, ny);

        int **arr = (int **)malloc(n*sizeof(int*));
        for(int i = 0; i < n; i++){
                arr[i] = (int *)malloc(n*sizeof(int));
        }
        for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                        arr[i][j] = i + j;
                }
        }
        int format_flag;
        printf("select a format_flag: ");
        scanf("%d", &format_flag);
        print_to_file(arr, n, format_flag);

        for(int i = 0; i < n; i++)free(arr[i]);
        free(arr);
        return 0;
}