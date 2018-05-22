/***************************
Course : Bil105e
Term : 2010 Spring
Homework : #3
Student Name : Ozan Arkan Can
Student Number : 040090573
***************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
  //Student struct to get information a student
  typedef struct student{
        int number;
        char name[20];
        char surname[20];
        float midterm,final,hw1,hw2;
        float grade;}Student;


    int main(){
        //Variables,counters and array for getting student's information
        Student TMP;
        int i=0;
        int j;
        char c;
        int counter=0;
        Student list[100];
    
        int n=0;//Countr of number of students whose all exam and homeworks notes are different zero
        
        // Counter,temporary variables and arrays for sorting
        int pass;
        int holdgrade;
        int holdnumber;
        char holdname[20];
        char holdsurname[20];
        // average of grades and sum of grades   
        float mean;
        float total1=0.0;
        //standart deviation
        float deviation;
        float total2=0.0;
        //average of midterm results and sum of midterm results    
        float mtavg;
        float total3=0.0;
        //average of final results and sum of final results
        float favg;
        float total4=0.0;
        //average of homework1 results and sum of homework1 results
        float hw1avg;
        float total5=0.0;
        //average of homework2 results and sum of homework2 results
        float hw2avg;
        float total6=0.0;
        
        //Counters for letter grades
        int aa=0;
        int ba=0;
        int bb=0;
        int cb=0;
        int cc=0;
        int dc=0;
        int dd=0;
        int ff=0;
        int vf=0;
    
        printf("Enter information of students and enter this order:\n");
        printf("Number Name Surname midterm final homework1 homework2\n\n");
        printf("To finish enter student number -1\n");
    
        //Getting information about every student such as number,name,surname,midterm result,final result ,homework1 result,homework2 result
        for(counter=0; counter < 100 && TMP.number!=-1; counter ++){
                  scanf("%d",&TMP.number);
                  if(TMP.number!=-1){
                       c=getchar();
                       c=getchar();
                       for(i=0;i<20;i++){
                       TMP.name[i]=0;
                       TMP.surname[i]=0;
                                        }
                       for(i=0; i<20 && c!=32; i++){
                               TMP.name[i]=c;
                               c=getchar();
                                                   }
                       c=getchar();
                       for(i=0; i<20 && c!=32; i++){
                                TMP.surname[i]=c;
                                c=getchar();
                                                   }
                       scanf("%f",&TMP.midterm);
                       scanf("%f",&TMP.final);
                       scanf("%f",&TMP.hw1);
                       scanf("%f",&TMP.hw2);
                       TMP.grade=(TMP.final*40.0/100+TMP.midterm*25.0/100+TMP.hw1*15/100+TMP.hw2*20/100);//Calcýlating grade
                       list[counter]=TMP;
                                    }
                                                                     }
         //Calculating average of grades           
         for(i=0;i<counter-1;i++){
             if(list[i].grade!=0){
                total1+=list[i].grade;
                n++;             }
                                 }                   
         mean=total1/n;
         //Calculating standart deviation           
         for(i=0;i<counter-1;i++){
             if(list[i].grade!=0){
                total2+=pow((list[i].grade-mean),2);
                                 }
                                 }
         deviation=sqrt(total2/n);
         //Calculating average of midterm results              
         for(i=0;i<counter-1;i++)
             total3+=list[i].midterm;
         mtavg=total3/n;
         //Calculating average of final results           
         for(i=0;i<counter-1;i++)
             total4+=list[i].final;
         favg=total4/n;
         //Calculating average of homework1 results           
         for(i=0;i<counter-1;i++)
             total5+=list[i].hw1;
         hw1avg=total5/n;
         //Calculating average of homework2 results           
         for(i=0;i<counter-1;i++)
             total6+=list[i].hw2;
         hw2avg=total6/n;
                    
                    //Sorting by Grades in decending order by bubble sort method
                    for(pass=1;pass<counter;pass++){
                        for(i=0;i<counter-2;i++){
                          
                          if(list[i].grade<list[i+1].grade){
                             holdgrade=list[i].grade;                      
                             holdnumber=list[i].number;
                             strncpy(holdname,list[i].name,20);
                             strncpy(holdsurname,list[i].surname,20);
                             list[i].grade=list[i+1].grade;
                             list[i].number=list[i+1].number;
                             strncpy(list[i].name,list[i+1].name,20);
                             strncpy(list[i].surname,list[i+1].surname,20);
                             list[i+1].grade=holdgrade;
                             list[i+1].number=holdnumber;
                             strncpy(list[i+1].name,holdname,20);
                             strncpy(list[i+1].surname,holdsurname,20);
                                                           }
                                                 }
                                                    }
       
       //PART1                   
       printf("RESULTS SORTED BY GRADE IN DESCENDING ORDER\n\n");
       printf("%-16s %-25s %-8s %-6s\n","Student Number","Student Name","Grade","Letter");
       printf("%-16s %-25s %-8s %-6s\n","==============","=====================","=====","======");

       for(j=0;j<counter-1;j++){
       printf("%-16d %-10s %-10s",list[j].number,list[j].name,list[j].surname);
       printf("%-5s   %.f"," ",list[j].grade);
       
          if(list[j].grade>=(mean+1.5*deviation)){
          printf("%-6sAA");
          aa++;}
       
          if( (list[j].grade>=(mean+1.0*deviation))&&(list[j].grade<(mean+1.5*deviation)) ){
          printf("%-6sBA");
          ba++;}
          
          if( (list[j].grade>=(mean+0.5*deviation))&&(list[j].grade<(mean+1.0*deviation)) ){
          printf("%-6sBB");
          bb++;}
          
          if( (list[j].grade>=mean)&&(list[j].grade<(mean+0.5*deviation)) ){
          printf("%-6sCB");
          cb++;}
          
          if( (list[j].grade>=(mean-0.5*deviation))&&(list[j].grade<mean) ){
          printf("%-6sCC");
          cc++;}
          
          if( (list[j].grade>=(mean-1.0*deviation))&&(list[j].grade<(mean-0.5*deviation)) ){
          printf("%-6sDC");
          dc++;}
          
          if( (list[j].grade>=(mean-1.5*deviation))&&(list[j].grade<(mean-1.0*deviation)) ){
          printf("%-6sDD");
          dd++;}
          
          if(list[j].grade<(mean-1.5*deviation)&&(list[j].grade!=0)){
          printf("%-6sFF");
          ff++;}
          
          if(list[j].grade==0){
          printf("%-6sVF");
          vf++;}
 
          printf("\n");}
          
          printf("\n\n");
          
             //PART2
             printf("CLASS AVERAGES\n\n");
             printf("Number of student records = %d\n",counter-1);
             printf("N = %d\n\n",n);
             printf("Midterm Average = %.2f\n",mtavg);
             printf("Final Average   = %.2f\n",favg);
             printf("HW1 Average     = %.2f\n",hw1avg);
             printf("HW2 Average     = %.2f\n\n",hw2avg);
             printf("Mean (Grade Average) = %.2f\n",mean);
             printf("Standard deviation   = %.2f\n\n\n",deviation);
          
          //PART3
          printf("LETTER COUNTS AND HISTOGRAM\n\n\n");
          printf("AA Count = %3d ",aa);
          for(i=0;i<aa;i++)
            printf("*");
          printf("\n");
          
          printf("BA Count = %3d ",ba);
          for(i=0;i<ba;i++)
            printf("*");
          printf("\n");
    
          printf("BB Count = %3d ",bb);
          for(i=0;i<bb;i++)
            printf("*");
          printf("\n");
          
          printf("CB Count = %3d ",cb);
          for(i=0;i<cb;i++)
            printf("*");
          printf("\n");
          
          printf("CC Count = %3d ",cc);
          for(i=0;i<cc;i++)
            printf("*");
          printf("\n");
          
          printf("DC Count = %3d ",dc);
          for(i=0;i<dc;i++)
            printf("*");
          printf("\n");
          
          printf("DD Count = %3d ",dd);
          for(i=0;i<dd;i++)
            printf("*");
          printf("\n");
          
          printf("FF Count = %3d ",ff);
          for(i=0;i<ff;i++)
            printf("*");
          printf("\n");
          
          printf("VF Count = %3d ",vf);
          for(i=0;i<vf;i++)
            printf("*");
          printf("\n\n");
    
          
    system("pause");
 
    return 0;
}
