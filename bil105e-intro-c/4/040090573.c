/***************************
Course : Bil105e
Term : 2010 Spring
Homework : #4
Student Name : Ozan Arkan Can
Student Number : 040090573
***************************/

#include <stdio.h>
#include <stdlib.h> 
  
  int main(){
      
      int pixel[263][651][3];//array for getting values of colour
      char *type[3];//pointer for file type
      char filename[12];//variable for getting file's name
      int maxcolour;//variable for value of max colour
      int row;//variable for row of matrix
      int column;//variable for column of matrix
      int i=0,j=0,k=0;//counter
      int Avg=0;//variable to calcýlate average of colour values
      int counterrow=0;//counter for small image
      int countercolumn=0;//counter for small image
      
      FILE *readPtr;//pointer for reading file
      FILE *writePtr;//pointer for writing file 
      
      //Getting file name from user
      printf("Enter name of input image file: ");
      scanf("%s",&filename);
      
      readPtr = fopen(filename,"r");//pointer assign to open file
      
      //If no memory available print message and close program
      if(readPtr == NULL){
              printf("File could not be opened\n");
              system("pause");
              return -1;
                         }
      //Getting file type,row and column values of matrix,value of max colour               
      fscanf(readPtr,"%s %d %d %d",type,&column,&row,&maxcolour);

      //Loop for getting pixel colour values
      for(i=0;i<row;i++){
             for(j=0;j<column;j++){
                      for(k=0;k<=2;k++)                     
                         fscanf(readPtr,"%d",&pixel[i][j][k]);
                      
                                  }
                        }
                      
      fclose(readPtr);//Close file 
      
      //Negative Image
      
      //If no memory available print message
      if(( writePtr = fopen("negative.ppm","w")) == NULL)
         printf("File could not be opened\n");
      else{
           //Printing file type,row and column values of matrix,value of max colour
           fprintf(writePtr,"%s\n",type);
           fprintf(writePtr,"%d %d\n",column,row);
           fprintf(writePtr,"%d\n",maxcolour);
           
           //Printing image matrix
           for(i=0;i<row;i++){
               for(j=0;j<column;j++){
                      for(k=0;k<=2;k++)
                             fprintf(writePtr,"%d ",maxcolour-pixel[i][j][k]);
                                    }
                     
                             } 
           }   
      
      fclose(writePtr);//Close file 
      
      //Gray Image
      
      //If no memory available print message
      if(( writePtr = fopen("gray.ppm","w")) == NULL)
         printf("File could not be opened\n");
      else{
           //Printing file type,row and column values of matrix,value of max colour
           fprintf(writePtr,"%s\n",type);
           fprintf(writePtr,"%d %d\n",column,row);
           fprintf(writePtr,"%d\n",maxcolour);
           
           //Printing image matrix
           for(i=0;i<row;i++){
               for(j=0;j<column;j++){
                      for(k=0;k<=2;k++)  
                      
                      //Calculating average of pixel values for every pixel  
                        Avg+=pixel[i][j][k];
                      Avg=Avg/3;  
                      
                      for(k=0;k<=2;k++)
                             fprintf(writePtr,"%d ",Avg);
                      Avg=0;//To calculate average of pixel values for every pixel average variable assign zero at end of loop
                                     }
                     
                              } 
           }   
      
      fclose(writePtr);//Close file                                                 
      
      //Mirror Image
      
      //If no memory available print message
      if((writePtr = fopen("mirror.ppm","w"))== NULL)
         printf("File could not be opened\n");
      else{
           //Printing file type,row and column values of matrix,value of max colour
           fprintf(writePtr,"%s\n",type);
           fprintf(writePtr,"%d %d\n",column,row);
           fprintf(writePtr,"%d\n",maxcolour);
           
           //Printing image matrix
           for(i=0;i<row;i++){
               for(j=0;j<column;j++){
                      for(k=0;k<=2;k++)
                           fprintf(writePtr,"%d ",pixel[i][column-1-j][k]);
                                    }
                             }
           }
           
     fclose(writePtr);//Close file 
     
     //Rotated Image
      
      //If no memory available print message
      if((writePtr = fopen("rotated.ppm","w"))== NULL)
         printf("File could not be opened\n");
      else{
           //Printing file type,row and column values of matrix,value of max colour
           fprintf(writePtr,"%s\n",type);
           fprintf(writePtr,"%d %d\n",row,column);
           fprintf(writePtr,"%d\n",maxcolour);
           
           //Printing image matrix
           for(j=0;j<column;j++){
               for(i=0;i<row;i++){
                      for(k=0;k<=2;k++)
                           fprintf(writePtr,"%d ",pixel[i][column-1-j][k]);
                                 }
                                }
           }
           
     fclose(writePtr);//Close file 
     
      //Big Image
      
      //If no memory available print message
      if((writePtr = fopen("big.ppm","w"))== NULL)
         printf("File could not be opened\n");
      else{
           //Printing file type,row and column values of matrix,value of max colour
           fprintf(writePtr,"%s\n",type);
           fprintf(writePtr,"%d %d\n",column*2,row*2);
           fprintf(writePtr,"%d\n",maxcolour);
           
           //Printing image matrix
           for(i=0;i<row;i++){               
               //Identical loops to generate copy column
               for(j=0;j<column;j++){
                      //Identical loops to generate copy column
                      for(k=0;k<=2;k++)
                           fprintf(writePtr,"%d ",pixel[i][j][k]);
                      for(k=0;k<=2;k++)
                           fprintf(writePtr,"%d ",pixel[i][j][k]);     
                           }
                           
               for(j=0;j<column;j++){
                      //Identical loops to generate copy column
                      for(k=0;k<=2;k++)
                           fprintf(writePtr,"%d ",pixel[i][j][k]);
                      for(k=0;k<=2;k++)
                           fprintf(writePtr,"%d ",pixel[i][j][k]);     
                                    }            
                           }
           }
     
     fclose(writePtr);//Close file                                                                   
      
     //Small Image
     
     //If no memory available print message
     if((writePtr = fopen("small.ppm","w"))== NULL)
         printf("File could not be opened\n");
      else{
           //Loops for calculating values of row and column for small image
           for(i=1;i<=row;i+=2)                    
             counterrow++;
           for(i=1;i<=column;i+=2)
             countercolumn++;
           
           //Printing file type,row and column values of matrix,value of max colour
           fprintf(writePtr,"%s\n",type);
           fprintf(writePtr,"%d %d\n",countercolumn,counterrow);
           fprintf(writePtr,"%d\n",maxcolour);    
           
           //Printing image matrix
           for(i=0;i<row;i=i+2){
               for(j=0;j<column;j=j+2){
                      for(k=0;k<=2;k++)
                           fprintf(writePtr,"%d ",pixel[i][j][k]);
                                      }
                                }
           }
      
      fclose(writePtr);//Close file 
      
      //Ending message
      printf("\n6 output image files have been generated.\nPROGRAM ENDED.\n\n");
                                      
      system("pause");
      return 0;
      }                                                          
                                                     
