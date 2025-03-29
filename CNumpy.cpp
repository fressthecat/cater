// Finish this file
#include <iostream>
#include <fstream>
#include "CNumpy.h"
using namespace std;

CNumpy::CNumpy(string input_filename){ 
ifstream file(input_filename);  
file>>row>>col; 

matrix=new int* [row]; 
for(int i=0;i<row;++i)
  {matrix[i]=new int[col];}
for(int i=0;i<row;++i){
for(int h=0;h<col;++h)
  {file>>matrix[i][h];}
  } file.close();}

CNumpy::~CNumpy(){
for(int i=0;i<row;++i)
{delete[] matrix[i];}
 delete[] matrix;}

int** CNumpy::getMatrix()const
{return matrix;}
int CNumpy::getRow()const
{return row;}
int CNumpy::getCol()const
{return col;}

  int CNumpy::min()const{
    int mini=matrix[0][0];
    for(int i=0;i<row;i++){
    for(int h=0;h<col;h++){
        if(matrix[i][h]<mini){
          mini=matrix[i][h];}}} 
    return mini;}
  
  int CNumpy::max()const{
    int big=matrix[0][0];
    for(int i=0;i<row;i++){
    for(int h=0;h<col;h++){
        if(matrix[i][h]>big){
          big=matrix[i][h];}}} 
    return big;}
    
void CNumpy::argmin(int* idx1, int* idx2)
{
int mini=matrix[0][0];  *idx1=0;   *idx2=0;
for(int i=0;i<row;i++){
  for(int j=0;j<col;j++){
  if(matrix[i][j]<mini){
    mini=matrix[i][j];
                        *idx1=i;   *idx2=j;
}}}}
void CNumpy::argmax(int* idx1, int* idx2)
{
int big=matrix[0][0];   *idx1=0;   *idx2=0;
for(int i=0;i<row;i++){
  for(int j=0;j<col;j++){
  if(matrix[i][j]>big){
    big=matrix[i][j];
                        *idx1=i;   *idx2=j;
}}}
}
void CNumpy::quantize(int levels){
int big=max();
int mini=min();
if(big==mini) return;
float s=(float)(levels-1)/(big-mini);
for(int i=0;i<row;i++){
  for(int h=0;h<col;h++){
  matrix[i][h]=(int)(round((matrix[i][h]-mini)*s));
  }}}

void CNumpy::conv(int** kernel, int k_row, int k_col) {
    int pad_r = k_row / 2;
    int pad_c = k_col / 2;
    int rr = row;
    int cc = col;

    // Allocate new matrix for convolution result
    int** cMaxt = new int*[rr];
    for (int i = 0; i < rr; i++) {
        cMaxt[i] = new int[cc]();
    }

    // Perform convolution with zero-padding
    for (int i = 0; i < rr; i++) {
        for (int j = 0; j < cc; j++) {
            int s = 0;
            for (int h = 0; h < k_row; h++) {
                for (int k = 0; k < k_col; k++) {
                    int n1 = i + h - pad_r;
                    int n2 = j + k - pad_c;
                    // Apply zero-padding if out of bounds
                    if (n1 >= 0 && n1 < row && n2 >= 0 && n2 < col) {
                        s += matrix[n1][n2] * kernel[h][k];  // No flipping
                    }
                }
            }
            cMaxt[i][j] = s;
        }
    }

    // Free old matrix
    for (int i = 0; i < row; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    // Update matrix pointer
    matrix = cMaxt;
}




void CNumpy::render(ofstream &outfile){
for(int i=0;i<row;i++){
for(int j=0;j<col;j++){
outfile<<matrix[i][j]<<" ";}
outfile<<endl;}
}