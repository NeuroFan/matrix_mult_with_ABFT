#include <stdio.h>

// function to get matrix elements entered by the user
void getMatrixElements(int matrix[][10], int row, int column) {

   // Initializing elements of matrix mult to 0.
   for (int i = 0; i <= row; ++i) {
      for (int j = 0; j <= column; ++j) {
         matrix[i][j] = 0;
      }
   }

   for (int i = 0; i < row; ++i) {
      for (int j = 0; j < column; ++j) {
         matrix[i][j] = i+j ;
      }
   }
}

// function to multiply two matrices
void multiplyMatrices_abft(int first[][10],
                      int second[][10],
                      int result[][10],
                      int row_checksum[],  //accumulated checksum of C
                      int r1, int c1, int c2) { 
                          
    
    // Initializing elements of matrix mult to 0.
   for (int i = 0; i <= r1; ++i) {
      for (int j = 0; j <= c1; ++j) {
         result[i][j] = 0;
      }
   }             
   
    for (int i = 0; i <= c2; ++i) {
         row_checksum[i] = 0;
      
   }         

   for (int i = 0; i < r1+1; i++) {
      int chksm = 0;
      for (int j = 0; j < c2; j++) {
         for (int k = 0; k < c1; k++) {
            result[i][j] += first[i][k] * second[k][j];
            /*****ABFT stuff****/
            if (j==0 && i<r1) 
                first[r1][k] += first[i][k]; //checksum of first matrix is created here on the fly
         }
         if (i<r1)
            row_checksum[j] += result[i][j];  //the sum of all elements row-wise is computed to be comparted checksum vector in PS
      }
      
         /******************/
      //printf("%d \n", result[i][j]);
   }

}


 

// function to display the matrix
void display(int result[][10], int row, int column) {

   printf("\nOutput Matrix:\n");
   for (int i = 0; i < row; ++i) {
      for (int j = 0; j < column; ++j) {
         printf("%5d  ", result[i][j]);
         if (j == column - 1)
            printf("\n");
      }
   }
}

int main() {
   int first[10][10], second[10][10], result[10][10], row_checksum[10], r1, c1, r2, c2;
   printf("Enter rows and column for the first matrix: ");
   scanf("%d %d", &r1, &c1);
 
    r2 = r1;
    c2 = c1;

   // get elements of the first matrix
   getMatrixElements(first, r1, c1);

   // get elements of the second matrix
   getMatrixElements(second, r2, c2);

   // multiply two matrices.
   multiplyMatrices_abft(first, second, result, row_checksum, r1, c1,  c2);

   // display the result
   display(result, r1+1, c2);
   
    printf("\n");
   for (int i = 0; i<c2; ++i){
       printf("%5d  ", row_checksum[i]);
   }
   printf("\n");


   return 0;
}