#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void func(double **matrix, double *vector, int n, char *vector_name){
        double *multiplied = (double *)malloc(n*sizeof(double));
        for(int i = 0; i < n; i++){
                multiplied[i] = 0;
                for(int j = 0; j < n; j++){
                        multiplied[i] += (matrix[i][j]*vector[j]);
                }
        }
        double lambda;
        for(int i = 0; i < n; i++){
                if(vector[i]!=0){
                        lambda = multiplied[i]/vector[i];
                        break;
                }
        }
        for(int i = 0; i < n; i++){
                if(vector[i] != 0 && abs((multiplied[i]/vector[i]) - lambda)>1e-2){
                        printf("%s: Not an eigenvector\n", vector_name);
                        return;
                }
        }

        printf("%s: Yes: %f\n",vector_name, lambda);
        char vectorname[1000];
        sprintf(vectorname, "inputfiles/%s", vector_name);
        FILE *file;
        file = fopen(vectorname, "a");
        fprintf(file, "Eigen Value for this corresponding Eigen Vector is %f\n", lambda);
        fclose(file);
        free(multiplied);
        return;
}


int main(){
        int n;
        printf("Given n: ");
        scanf("%d", &n);
        char matrixname[50], vectorname[50];
        snprintf(matrixname, sizeof(matrixname), "mat_%06d.in", n);
        double **matrix = (double **)malloc(n*sizeof(double *));
        double *vector = (double *)malloc(n*sizeof(double));

        for(int i = 0; i < n; i++){
                matrix[i] = (double *)malloc(n*sizeof(double));
        }
        char line[2056];
        int row = 0, col = 0;
        char matrix_name[1000];
        sprintf(matrix_name, "inputfiles/%s", matrixname);
        //printf("%s", matrix_name);
        //reading matrix from the input file
        FILE *file = fopen(matrix_name, "r");
        while (fgets(line, sizeof(line), file)) {
                char *token = strtok(line, ",");
                col = 0;

                while (token != NULL) {
                        matrix[row][col] = atof(token);
                        token = strtok(NULL, ",");
                        col++;
                        }
        row++;
        }
        fclose(file);
        /*
    // Print the matrix
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                         printf("%f ", matrix[i][j]);
                }
                printf("\n");
       }*/

        // reading the vectors from the vector file
        for(int i = 0; i < 4; i++){
                snprintf(vectorname, sizeof(vectorname), "vec_%06d_%06d.in", n, i + 1);
                char vector_name[1000];
                sprintf(vector_name, "inputfiles/%s", vectorname);
                file = fopen(vector_name, "r");
                fgets(line, sizeof(line), file);
                char *token = strtok(line, ",");
                col = 0;
                while(token != NULL){
                        vector[col] = atof(token);
                        token = strtok(NULL, ",");
                        col++;
                        //printf("%f", vector[col-1]);
                }
                //printf("%s\n", vector_name);
                func(matrix, vector, n, vectorname);
                fclose(file);
        }
        free(vector);
        for(int i = 0; i < n; i++){
                free(matrix[i]);
        }
        free(matrix);
        return 0;
}