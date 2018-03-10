//
// Created by dell on 07.03.2018.
//

#ifndef JIMP_EXERCISES_ARRAY2D_H
#define JIMP_EXERCISES_ARRAY2D_H

int **Array2D(int n_rows, int n_columns);
//void Fill(int n_rows, int **array, int n_columns);
void DeleteArray2D(int **array, int n_rows, int n_columns);
int **NewArray2D(int n_rows, int n_columns);

void Fill(int n_columns, int n_rows, int **array);

#endif //JIMP_EXERCISES_ARRAY2D_H
