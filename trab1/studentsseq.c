// ================== CODIGO SEQUENCIAL ==================
// Nome: Heloísa Pazeti
// =======================================================
// TODO
// - Get input
// - Generate 'random' grades
// - Put in a matrix.
// - Calculate things
// ========================================================

#include <stdio.h>
#include <stdlib.h>

// =========== Get Input ===========
// - Get the input from keyboard
// - returns by reference
// =================================
void get_input(int *r, int *c, int *a, int *n, int *t, int *seed)
{

    FILE *fptr;
    fptr = fopen("test.txt", "r"); 
    char output[50];
    fscanf(fptr, "%i", r);
    fscanf(fptr, "%i", c);
    fscanf(fptr, "%i", a);
    fscanf(fptr, "%i", n);
    fscanf(fptr, "%i", t);
    fscanf(fptr, "%i", seed);

    printf("r: %d\n", *r);
    printf("c: %d\n", *c);
    printf("a: %d\n", *a);
    printf("n: %d\n", *n);
    printf("t: %d\n", *t);
    printf("seed: %d\n", *seed);
}

double generate_decimal(int seed)
{
    return ((double)rand()/(double)RAND_MAX) * 100;
}

double**** generate_matrix(int r, int c, int a, int n, int seed)
{
    int i, j, k, l = 0;
    double ****matrix = malloc(r * sizeof(double ***));

    for (i = 0; i < r; i++) 
    {
        matrix[i] = malloc(c * sizeof(double **));
        for (j = 0; j < c; j++) 
        {
            matrix[i][j] = malloc(a * sizeof(double *));
            for (k = 0; k < a; k++) 
            {
                matrix[i][j][k] = malloc(n * sizeof(double));
            }
        }
    }

    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; c++)
        {
            for(k = 0; k < a; k++)
            {
                for(l = 0; l < n; l++)
                {
                    matrix[i][j][k][l] = generate_decimal(seed);
                    printf("r=%d, c=%d, a=%d, n=%d: %lf\n", i, j, k, l, matrix[i][j][k][l]);
                }
            }
        }
    }   

    return matrix;
}

void find_greatest_grade()
{

}

void find_minor_grade()
{

}

void calculate_median()
{

}

void calculate_simple_arithmetic_mean()
{

}

void calculate_standard_deviation()
{

}

void free_matrix(double**** matrix, int r, int c, int a, int n)
{
    int i, j, k = 0;
    if(matrix == NULL) return;

    
    for (i = 0; i < r; i++) 
    {
        matrix[i] = malloc(c * sizeof(double **));
        for (j = 0; j < c; j++) 
        {
            matrix[i][j] = malloc(a * sizeof(double *));
            for (k = 0; k < a; k++) 
            {
                matrix[i][j][k] = malloc(n * sizeof(double));
                free(matrix[i][j][k]);
            }

            free(matrix[i][j]);
        }

        free(matrix[i]);
    }
    
    free(matrix);
}

int main()
{
    int r, c, a, n, t, seed = 0;
    int i, j, k, l = 0;
    get_input(&r, &c, &a, &n, &t, &seed);

    if (r <= 0 | c <= 0 | a <= 0 | n <= 0 | t<= 0)
    {
        printf("It seems there ocurred an error...\n Current values:");
        return -1;
    }
    
    srand(seed);
    double**** matrix = generate_matrix(r, c, a, n,seed);

    free_matrix(matrix, r, c, a, n);
    return 0;
}
