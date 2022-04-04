#include "functions.h"

FILE* dataIn(char* in, char* out)
{
    //input and output file
    FILE* input = fopen(in, "r");
    assert(input != NULL);
    FILE* output = fopen(out, "w");
    assert(output != NULL);
    
    //"header" info, row/col
    header_t* info = (header_t*)malloc(sizeof(header_t));
    if(fscanf(input, "%d %d", &(info)->row, &(info)->col));

    //matrix to store input data with call for mem allocation
    MATRIX matrix = NULL;
    matrix = allocate(matrix, info);

    int row = info->row;
    int col = info->col;

    //get input data for matrix
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if(fscanf(input, "%d ", &matrix[i][j]));
        }
    }
    
    //calculate new matrix using 3x3  or 5x5 filter
    matrix = calcNewMatrixThee(matrix, info);
    //matrix = calcNewMatrixFive(matrix, info);

    return output;
}

int** allocate(int** matrix, header_t* info)
{
    matrix = (int**)malloc(info->row * sizeof(int*));
    for (int i = 0; i < info->row; i++)
    {
        matrix[i] = (int*)malloc(info->col * sizeof(int));
    }

    return matrix;
}

int** calcNewMatrixThree(MATRIX matrix, header_t* info)
{
    header_t* three = (header_t*)malloc(sizeof(header_t));
    three->row = 3;
    three->col = 3;

    MATRIX threeFilter = NULL;
    threeFilter = allocate(threeFilter, three);
    threeFilter = threeX(threeFilter);

    MATRIX newMatrix = NULL;
    newMatrix = allocate(newMatrix, info);

    int rBound = (info->row);
    int cBound = (info->col);

    for (int r = 0; r < rBound; r++)
    {
        for (int c = 0; c < cBound; c++)
        {
            if (r == 0 || c == 0 || r == info->row - 1 || c == info->col - 1)
            {
                newMatrix[r][c] = matrix[r][c];
            }
            else 
            {
                int tempR = r - 1;
                int tempC = c - 1;

                int one = (matrix[tempR][tempC] * threeFilter[0][0]) + (matrix[tempR][tempC + 1] * threeFilter[0][1]) + (matrix[tempR][tempC + 2] * threeFilter[0][2]);
                int two = (matrix[tempR + 1][tempC] * threeFilter[1][0]) + (matrix[tempR + 1][tempC + 1] * threeFilter[1][1]) + (matrix[tempR + 1][tempC + 2] * threeFilter[1][2]);
                int three = (matrix[tempR + 2][tempC] * threeFilter[2][0]) + (matrix[tempR + 2][tempC + 1] * threeFilter[2][1]) + (matrix[tempR + 2][tempC + 2] * threeFilter[2][2]);
                int total = one + two + three;

                if (total > 255)
                    total = 255;
                if (total < 0)
                    total = 0;

                newMatrix[r][c] = total;
            }
        }
    }

    return newMatrix;
}

int** threeX(MATRIX t)
{
    t[0][0] = 0;
    t[0][1] = -1;
    t[0][2] = 0;

    t[1][0] = -1;
    t[1][1] = 5;
    t[1][2] = -1;

    t[2][0] = 0;
    t[2][1] = -1;
    t[2][2] = 0;

    return t;
}

int** fiveX(MATRIX t)
{
    t[0][0] = 0;
    t[0][1] = 0;
    t[0][2] = -1;
    t[0][3] = 0;
    t[0][4] = 0;

    t[1][0] = 0;
    t[1][1] = 0;
    t[1][2] = -1;
    t[1][3] = 0;
    t[1][4] = 0;

    t[2][0] = -1;
    t[2][1] = -1;
    t[2][2] = 5;
    t[2][3] = -1;
    t[2][4] = -1;

    t[3][0] = 0;
    t[3][1] = 0;
    t[3][2] = -1;
    t[3][3] = 0;
    t[3][4] = 0;

    t[4][0] = 0;
    t[4][1] = 0;
    t[4][2] = -1;
    t[4][3] = 0;
    t[4][4] = 0;

    return t;
}

FILE* printOut(MATRIX matrix, FILE* output, header_t* info)
{
    int row = (info->row);
    int col = (info->col);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (fprintf(output, "%d ", matrix[i][j]));
        }
        printf("\n");
    }
}