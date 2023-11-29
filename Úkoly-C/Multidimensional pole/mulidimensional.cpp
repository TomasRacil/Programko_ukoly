#include <stdlib.h>    //random
#include <iostream>  //cout, cin
#include <string>   //string (text)
#include <time.h> 

using namespace std;

struct Matrix
{
    int** matrix;
    int rows;
    int cols;
};
void PrintMatrix(Matrix matrix);
void Dotaznik(int* rows1, int* cols1, int* rows2, int* cols2);
int** init2DArray(int rows, int cols);
int** init2DArray_random(int rows, int cols);
Matrix NewMatrix(int rows, int cols);
Matrix NewMatrix_random(int rows, int cols);
void DeletePole(Matrix* matrix);
Matrix AddMatrix(Matrix matrix1, Matrix matrix2);
Matrix MulMatrix(Matrix matrix1, Matrix matrix2);


int main()
{
srand (time(NULL));
Matrix matrix1, matrix2, matrix3, matrix4;
int  rows1, cols1, rows2, cols2;
Dotaznik(&rows1, &cols1, &rows2, &cols2);
matrix1 = NewMatrix_random(rows1, cols1);
PrintMatrix(matrix1);
matrix2 = NewMatrix_random(rows2, cols2);
PrintMatrix(matrix2);
matrix3 = AddMatrix(matrix1, matrix2);
PrintMatrix(matrix3);
matrix4 = MulMatrix(matrix1, matrix2);
PrintMatrix(matrix4);
DeletePole(&matrix1);
DeletePole(&matrix2);
DeletePole(&matrix3);
DeletePole(&matrix4);
    return 0;
}

void PrintMatrix(Matrix matrix)
{
    for (int i=0; i<matrix.rows; i++)
    {
        for (int j=0; j<matrix.cols; j++)
        {
            cout<<matrix.matrix[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;
}

int** init2DArray_random(int rows, int cols)
{
    int** array = new int* [rows];
    for(int i=0; i<rows; i++)
    {
        array[i] = new int[cols];
    }
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
        {
            array[i][j]=rand() % 10;
        }
    }
    return array;
}

Matrix NewMatrix_random(int rows, int cols)
{
    int** array = init2DArray_random(rows, cols);
    Matrix matrix;
    matrix.matrix = array;
    matrix.rows = rows;
    matrix.cols = cols;
    return matrix;
}

void DeletePole(Matrix* matrix)
{
    for (int i = 0; i < matrix->rows; i++) 
    {
            delete[]  matrix->matrix[i];
    }
    delete[] matrix->matrix;
    matrix->matrix = NULL;
}
int** init2DArray(int rows, int cols)
{
    int** array = new int* [rows];
    for(int i=0; i<rows; i++)
    {
        array[i] = new int[cols];
    }
    return array;
}

Matrix NewMatrix(int rows, int cols)
{
    int** array = init2DArray(rows, cols);
    Matrix matrix;
    matrix.matrix = array;
    matrix.rows = rows;
    matrix.cols = cols;
    return matrix;
}

Matrix AddMatrix(Matrix matrix1, Matrix matrix2)
{
    Matrix matrix3=NewMatrix(matrix1.rows, matrix1.cols);
    if(matrix1.rows == matrix2.rows && matrix1.cols == matrix2.cols)
    {
    for (int i=0; i<matrix1.rows; i++)
    {
        for (int j=0; j<matrix1.cols; j++)
        {
            matrix3.matrix[i][j] = matrix1.matrix[i][j] + matrix2.matrix[i][j];
        }
    }
    return matrix3;
    }
    else
    {
        cout<<"Matice nemají stejný počet sloupců a řádků!!"<<endl;
        return matrix3;
    }
}

Matrix MulMatrix(Matrix matrix1, Matrix matrix2)
{
   Matrix matrix3 = NewMatrix(matrix1.rows, matrix2.cols);
    if(matrix1.cols == matrix2.rows)
    {
        for(int i=0; i<matrix1.rows; i++)
        {
            for(int j=0; j<matrix2.cols; j++)
            {
                for(int k=0; k<matrix1.cols; k++)
                {
                    matrix3.matrix[i][j] += matrix1.matrix[i][k] * matrix2.matrix[k][j];
                }
            }
        }
        return matrix3;
    }
    else 
    {
        cout<<"Počet sloupců 1.matice není roven počtu řádků 2. matice!!"<<endl;
        return matrix3;
    }
}

void Dotaznik(int* rows1, int* cols1, int* rows2, int* cols2)
{
cout<<"1. Matrix rows: ";
cin>>*rows1;
cout<<"1. Matrix cols: ";
cin>>*cols1;
cout<<"2. Matrix rows: ";
cin>>*rows2;
cout<<"2. Matrix cols: ";
cin>>*cols2;
}

