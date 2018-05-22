/***************************
Course : Bil105e
Term : 2010 Spring
Homework : #2
Student Name : Ozan Arkan Can
Student Number : 040090573
***************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100

int main()
{
    float radius[MAX], apsis[MAX], ordinate[MAX];//arrays of circles' center coordinates and radius//
    int containment[MAX]={0};//counter of containment for every circle//
    int intersection[MAX]={0};//counter of intersection for every circle//
    int n;//number of circles//
    int i, j, k, countera, counterb, a, b;//counter//
    int maxcontainment, maxintersection;//variables for defining which circle is with most containments and which circle is with most intersection//
    
    printf("Enter number of circles.\n");
    scanf("%d",&n);
        //loop for getting information about circles//
        for(i=0,j=0,k=0;i<n;i++,j++,k++){
            printf("Enter center coordinates and radius of circle#%d ( x y r ):\n",i+1);
            scanf("%f %f %f",&apsis[i],&ordinate[j],&radius[k]);
                                        }
       //loop for printing all circles and their informations// 
        for(i=1,j=0,k=0;i<=n;i++,j++,k++){
            printf("Circle#%d (x y r): (%.2f %.2f %.2f)\n\n",i,apsis[i-1],ordinate[j],radius[k]);
                                         }
       //loop for comparing circles
        for(countera=0;countera<n;countera++){      
            for(counterb=0;counterb<n;counterb++){
              //loop for determining any two or more circles are same //   
              for(a=0;a<=counterb;a++){
                  for(b=0;b<=a;b++){
                     if(a!=b){
                       if((apsis[a]==apsis[b])&&(ordinate[a]==ordinate[b])&&(radius[a]==radius[b])){
                          counterb++;}
                             }
                                   }
                                      }
                 
                 //if two circle are same don't compare them//
                 if((apsis[countera]==apsis[counterb])&&(ordinate[countera]==ordinate[counterb])&&(radius[countera]==radius[counterb]))
                              continue ;
                  
                 else{ 
                          //if second circle is internally tangent to first circle first circle's containment counter and intersection counter are incremented by 1//
                          if( ( sqrt( (((apsis[countera]-apsis[counterb])*(apsis[countera]-apsis[counterb]))) + (((ordinate[countera]-ordinate[counterb])*(ordinate[countera]-ordinate[counterb]))) ) ) == (fabs(radius[countera]-radius[counterb])) ){
                              if(radius[countera]>radius[counterb]){
                                 containment[countera]+=1;
                                 intersection[countera]+=1;}
                          
                              else
                                continue;
                                }
                          else{
                               //If containment condition ensure containment counter is incremented by 1//
                               if( ( sqrt( (((apsis[countera]-apsis[counterb])*(apsis[countera]-apsis[counterb]))) + (((ordinate[countera]-ordinate[counterb])*(ordinate[countera]-ordinate[counterb]))) ) ) < (fabs(radius[countera]-radius[counterb])) ){
                                if(radius[countera]>radius[counterb]){
                                containment[countera]+=1;}
                                                                               }
                               else{
                               //If 1st circle is little circle despite of fact that it ensure the containment condition , do nothing//
                                    if( ( sqrt( (((apsis[counterb]-apsis[countera])*(apsis[counterb]-apsis[countera]))) + (((ordinate[counterb]-ordinate[countera])*(ordinate[counterb]-ordinate[countera]))) ) ) <= (fabs(radius[counterb]-radius[countera])) ){
                                    continue;}
                                    else{
                              //If  intersection condition ensure intersection counter is incremented by 1//                                  
                                      if( ( sqrt( (((apsis[countera]-apsis[counterb])*(apsis[countera]-apsis[counterb]))) + (((ordinate[countera]-ordinate[counterb])*(ordinate[countera]-ordinate[counterb]))) ) ) <= (radius[countera]+radius[counterb]) ) {
                                         intersection[countera]+=1;}
                                        }
                                   }
                               }    
                      }
                                                   }
                                               }           
        //print containments and intersection numbers of circles//
        printf("\t  %s%16s\n","Intersection","Containment");
        for(i=0;i<n;i++){
           printf("Circle#%d: %8d %10d\n\n",i+1,intersection[i],containment[i]);}
        
        
        maxintersection=0;//assign zero for first value of max intersection//
        
        //Find which circle is with most intersections//  
        for(i=0,j=0;i<n;i++){
            if(maxintersection<intersection[i]){
                maxintersection=intersection[i];
                j=i;}
                             }
        //print circle with most intersection ,the circle info and the number of circles that it intersects.If there is no intersection print it.//                     
        if(maxintersection==0)                     
           printf("There is no intersection.\n\n");        
        else
           printf("Circle with most intersections is (x y r) : (%.2f %.2f %.2f) Circle#%d\nCount of Intersections : %d\n\n",apsis[j],ordinate[j],radius[j],j+1,maxintersection);       
        
        maxcontainment=0;//assign zero for first value of max containment.//
        
        //Find which circle is with most containment// 
        for(i=0,j=0;i<n;i++){
            if(maxcontainment<containment[i]){
                maxcontainment=containment[i];
                j=i;}
                            }
        //print circle with most containments ,the circle info and the number of circles that it contains.If there is no containment print it.//                     
        if(maxcontainment==0)                     
           printf("There is no containment.\n\n");
        else
           printf("Circle with most containments is (x y r) : (%.2f %.2f %.2f) Circle#%d\nCount of Containments : %d\n\n",apsis[j],ordinate[j],radius[j],j+1,maxcontainment);
        

    system("pause");
    return 0;
}        
    
