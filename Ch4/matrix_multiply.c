
#include <stdio.h>
#include <stdlib.h>

static void print_matrix(size_t n, int c[][n]);

static void matrix_add_to(size_t n, 
    int c1[][n], int c2[][n], size_t row, size_t col, int c[][n * 2])
{
    int i = 0;
    for (; i < n; i++)
    {
        int j = 0;
        for (; j < n; j++)
        {
            c[row + i][col + j] = c1[i][j] + c2[i][j];
        }
    }
}

static void matrix_multiply_2(
    size_t start_row, size_t start_col, size_t n, 
    int a[][n], int b[][n], int c[][n])
{
    int i = 0;
    for (; i < n; i ++)
    {
        int j = 0;
        for (; j < n; j ++)
        {
            int k = 0;
            for (; k < n; k ++)
                c[start_row + i][start_col + j] += 
                    a[start_row + i][start_col + k] * b[start_row + k][start_col + j];
        }
    }   
}

static matrix_copy_to(size_t n, int target[][n],
    size_t dimenstion, size_t s_row, size_t s_col, int source[][dimenstion])
{
    int i = 0;
    for (; i < n; i ++)
    {
        int j = 0; 
        for (; j < n; j ++)
        {
            source[s_row + i][s_col + j] = target[i][j] ;
        }
    }
}

static matrix_copy_back(size_t dimenstion, int source[][dimenstion], size_t s_row, size_t s_col,
    size_t n, int target[][n])
{
    int i = 0;
    for (; i < n; i ++)
    {
        int j = 0; 
        for (; j < n; j ++)
        {
            target[i][j] = source[s_row + i][s_col + j];
        }
    }
}

void matrix_multiply_recursive(size_t dimenstion, 
    size_t start_row_a, size_t start_col_a, int a[][dimenstion], 
    size_t start_row_b, size_t start_col_b, int b[][dimenstion], 
    size_t start_row_c, size_t start_col_c, int c[][dimenstion],
    size_t n, int c_n[][n])
{
    if (n <= 1)
    {
        c_n[0][0] = a[start_row_a][start_col_a] * b[start_row_b][start_col_b];
    }
    else
    {
        if (n % 2 != 0)
        {
            printf("Cannot handle matrix where dimenstion is not powers of 2\n");
            return;
        }
        int center = n / 2;
        int i = 0, j = 0;

        int c1[center][center], c2[center][center], c_temp[center][center];
        matrix_multiply_recursive(dimenstion, 
            start_row_a, start_col_a, a, 
            start_row_b, start_col_b, b, 
            start_row_c, start_col_c, c, center, c1);
        matrix_multiply_recursive(dimenstion, 
            start_row_a, start_col_a + center, a, 
            start_row_b + center, start_col_b, b, 
            start_row_c, start_col_c, c, center, c2);

        if (n == dimenstion)
            matrix_add_to(center, c1, c2, start_row_c, start_col_c, c);
        else
            matrix_add_to(center, c1, c2, 0, 0, c_n);

        matrix_multiply_recursive(dimenstion, 
            start_row_a, start_col_a, a, 
            start_row_b, start_col_b + center, b, 
            start_row_c, start_col_c, c, center, c1);
        matrix_multiply_recursive(dimenstion, 
            start_row_a, start_col_a + center, a, 
            start_row_b + center, start_col_b + center, b, 
            start_row_c, start_col_c, c, center, c2);
        
        if (n == dimenstion)
            matrix_add_to(center, c1, c2, start_row_c, start_col_c + center, c);
        else
            matrix_add_to(center, c1, c2, 0, center, c_n);

        matrix_multiply_recursive(dimenstion, 
            start_row_a + center, start_col_a, a, 
            start_row_b, start_col_b, b, 
            start_row_c, start_col_c, c, center, c1);
        matrix_multiply_recursive(dimenstion, 
            start_row_a + center, start_col_a + center, a, 
            start_row_b + center, start_col_b, b, 
            start_row_c, start_col_c, c, center, c2);

        if (n == dimenstion)
            matrix_add_to(center, c1, c2, start_row_c + center, start_col_c, c);
        else
            matrix_add_to(center, c1, c2, center, 0, c_n);

        matrix_multiply_recursive(dimenstion, 
            start_row_a + center, start_col_a, a, 
            start_row_b, start_col_b + center, b, 
            start_row_c, start_col_c, c, center, c1);
        matrix_multiply_recursive(dimenstion, 
            start_row_a + center, start_col_a + center, a, 
            start_row_b + center, start_col_b + center, b,
            start_row_c, start_col_c, c, center, c2);
        
        if (n == dimenstion)
            matrix_add_to(center, c1, c2, start_row_c + center, start_col_c + center, c);
        else
            matrix_add_to(center, c1, c2, center, center, c_n);
    }
}

void matrix_multiply(size_t n, int a[][n], int b[][n], int c[][n])
{
    int i = 0;
    for (; i < n; i ++)
    {
        int j = 0;
        for (; j < n; j ++)
        {
            c[i][j] = 0;
            int k = 0;
            for (; k < n; k ++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }   
}

static void print_matrix(size_t n, int c[][n])
{
    int i = 0;
    for (; i < n; i ++)
    {
        int j = 0;
        for (; j < n; j ++)
        {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
}

int compare_matrices(size_t n, int a[][n], int b[][n])
{
    int i = 0;
    for (; i < n; i ++)
    {
        int j = 0;
        for (; j < n; j ++)
        {
            if (a[i][j] != b[i][j])
                return 0;
        }
    }

    return 1;
}

int main()
{
    int a[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int b[3][3] = {{2,3,4},{5,6,7},{8,9,1}};

    int c[3][3];
    int expected[3][3] = {{36,42,21},{81,96,57},{126,150,93}};
    matrix_multiply(3, a, b, c);

    if (c[0][0] != 36 || c[0][1] != 42 || c[0][2] != 21 || 
        c[1][0] != 81 || c[1][1] != 96 || c[1][2] != 57 || 
        c[2][0] != 126 || c[2][1] != 150 || c[2][2] != 93)
    {
        printf("Fails, expected:\n");
        print_matrix(3, expected);
        printf("Actual:");
        print_matrix(3, c);
    }
    else
    {
        printf("matrix_multiply() succeed \n");
    }

    int a2[4][4] = {{1,2,3,4},{2,3,4,5},{3,4,5,6},{4,5,6,7}};
    int b2[4][4] = {{1,2,3,4},{2,3,4,5},{3,4,5,6},{4,5,6,7}};

    int c2[4][4] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    // int c2[4][4]
    int expected2[4][4] = {{30,40,50,60},{40,54,68,82},{50,68,86,104},{60,82,104,126}};
    matrix_multiply_recursive(4, 0, 0, a2, 0, 0, b2, 0, 0, c2, 4, c2);

    if (!compare_matrices(4, c2, expected2))
    {
        printf("matrix_multiply_recursive() case 1# Fails, expected:\n");
        print_matrix(4, expected2);
        printf("Actual:");
        print_matrix(4, c2);
    }
    else
    {
        printf("matrix_multiply_recursive() succeed\n");
    }

    int a3[2][2] = {{1,2},{3,4}};
    int b3[2][2] = {{1,2},{3,4}};

    int c3[2][2];
    int expected3[2][2] = {{7,10},{15,22}};
    matrix_multiply_recursive(2, 0, 0, a3, 0, 0, b3, 0, 0, c3, 2, c3);

    if (!compare_matrices(2, c3, expected3))
    {
        printf("matrix_multiply_recursive() case 2# Fails, expected:\n");
        print_matrix(2, expected3);
        printf("Actual:");
        print_matrix(2, c3);
    }
    else
    {
        printf("matrix_multiply_recursive() case 2# succeed\n");
    }
    
    return 0;
}