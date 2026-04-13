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
#include <math.h>
#include <string.h>

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
}

double generate_decimal()
{
    return ((double)rand()/(double)RAND_MAX) * 100;
}


double calculate_average(double* grades, int size)
{
    double average = 0.0;
    for(int i = 0; i < size; i++)
        average += grades[i];

    return average/size;
}

double calculate_standard_deviantion(double* values, double avg, int size)
{
    float sd = 0.0;

    for(int i = 0; i < size; i++)
        sd += pow(values[i] - avg, 2);

    sd = sqrt(sd / size);
    return sd;
}

int compare(const void* a, const void* b)
{
    return (*(double*)a - *(double*)b);
}

double**** generate_matrix(int r, int c, int a, int n)
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
                for(l = 0; l < n; l++)
                    matrix[i][j][k][l] = generate_decimal();
            }
        }
    }

    return matrix;
}


double*** generate_avg_matrix(int r, int c, int a, int n, double**** grade_matrix)
{

    int i, j, k, l = 0;
    double ***matrix = malloc(r * sizeof(double ***));

    for (i = 0; i < r; i++) 
    {
        matrix[i] = malloc(c * sizeof(double **));
        for (j = 0; j < c; j++) 
        {
            matrix[i][j] = malloc(a * sizeof(double *));
            for(k = 0; k < a; k++)
                matrix[i][j][k] = calculate_average(grade_matrix[i][j][k], n);
        }
    }
    return matrix;
}

double* city_statistics(double*** avg_matrix, int r, int c, int a)
{
    int i, j, k = 0;
    double median, avg, sd = 0.0;
    double* region_avg = malloc(r*sizeof(double));

    printf("============================== CITY STATISTICS MATRIX ==============================\n");
    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
            printf("R=%d | C=%d | ", i, j);
            avg = calculate_average(avg_matrix[i][j], a);
            sd = calculate_standard_deviantion(avg_matrix[i][j], avg, a);
            if(a % 2 == 0)
                median = (avg_matrix[i][j][a/2 - 1] + avg_matrix[i][j][a/2])/2; 
            else
                median = avg_matrix[i][j][a/2];

            printf("%.1lf | %.1lf | %.1lf | %.1lf | %.1lf |\n", avg_matrix[i][j][0], avg_matrix[i][j][a-1], median, avg, sd); 

            region_avg[i] += avg;
        }

        region_avg[i] /= c;
    }

    return region_avg;
}

double region_statistics(double** region_matrix, int r, int c, int a, double* region_avg)
{
    int i, j, k = 0;
    double median, avg, sd = 0.0;
    double country_avg = 0.0;

    printf("============================== REGION STATISTICS MATRIX ==============================\n");
    for(i = 0; i < r; i++)
    {
        printf("R=%d |", i);

        if(c*a % 2 == 0)
            median = (region_matrix[i][c*a/2 - 1] + region_matrix[i][c*a/2])/2;
        else
            median = region_matrix[i][c*a/2];

        sd = calculate_standard_deviantion(region_matrix[i], region_avg[i], c*a);        
        printf("%.1lf | %.1lf | %.1lf | %.1lf | %.1lf |\n", region_matrix[i][0], region_matrix[i][c*a-1], median, region_avg[i], sd);
    }

    return country_avg;
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
    int i, j = 0;
    get_input(&r, &c, &a, &n, &t, &seed);

    if (r <= 0 | c <= 0 | a <= 0 | n <= 0 | t<= 0)
    {
        printf("It seems there ocurred an error...\n Current values:");
        return -1;
    }
    
    srand(seed);

    double**** matrix = generate_matrix(r, c, a, n);
    double*** avg_matrix = generate_avg_matrix(r, c, a, n, matrix);

    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
            qsort(avg_matrix[i][j],a, sizeof(double), compare);
    }

    double* region_avg = city_statistics(avg_matrix, r, c, a); 
    double** region_matrix = malloc(r * sizeof(double**));

    for (i = 0; i < r; i++) 
    {
        region_matrix[i] = malloc(c * a * sizeof(double *));
        for (j = 0; j < c; j++) 
            memcpy(region_matrix[i] + j * a, avg_matrix[i][j], a * sizeof(double));
        
        qsort(region_matrix[i], a * c, sizeof(double), compare);
    }

    double country_avg = region_statistics(region_matrix, r, c, a, region_avg);

    free_matrix(matrix, r, c, a, n);
    return 0;
}
