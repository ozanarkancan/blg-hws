/***************************
Course : Bil105e
Term : 2010 Spring
Homework : #1
Student Name : Ozan Arkan Can
Student Number : 040090573
***************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.1415
int main()
{
 float A1,B1,C1,A2,B2,C2,slope, Alpha, xzero, yzero,distance,pow1,pow2;
 // Coefficients , intersection point , distance between two parallel lines and what need to calculate them // 

printf("Enter A1,B1,C1 and A2,B2,C2\n");

scanf("%f%f%f%f%f%f", &A1, &B1, &C1, &A2, &B2, &C2);

  if((A1/A2) != (B1/B2))
  // If the lines are intersection lines check are they perpendicular lines or not. //
 {
        if(((A1 * A2) + (B1 * B2)) == 0)
  // If they are perpendicular lines print it and calculate angle and intersection point //
       {
          printf(" \nThey are perpendicular lines. \n");
  
       } 
        else
       {
          printf(" \nThey are intersection lines. \n");
          
       }  
          slope = ((A1 * B2) - (A2 * B1)) / ((A1 * A2) + (B1 * B2));
  // Equation of slope //
          Alpha = ( atan(slope) * 180 ) / PI ;
  // Equation of angle between two lines //
          xzero = ((B1 * C2) - (B2 * C1)) / ((A1 * B2) - (A2 * B1));
          yzero = ((C1 * A2) - (C2 * A1)) / ((A1 * B2) - (A2 * B1));
  // Equation of intersection point //
          printf(" \nAlpha : %.2f \n" , Alpha);
          
          printf(" \nIntersection Point : (%.2f , %.2f)\n\n",xzero,yzero);
       
 }  
  else 
 {
       if((A1/A2) != (C1/C2))
  // If lines are parallel lines print it and calculate distance between them. //
      {          
          printf(" \nThey are parallel lines. \n");  
          
          pow1 = pow(A1,2);
          pow2 = pow(B1,2);
  // Equations that be used for calculating distance //       
          distance = fabs((C1 - C2)) / sqrt((pow1 + pow2));
  // Equation of   distance between two parallel lines //      
          printf(" \nDistance : %.2f\n\n",distance);
      }       
       else
      {       
          printf(" \nThey are coinside lines. \n\n");
      }
 }
  system("pause");
  
  return 0 ;
}          
