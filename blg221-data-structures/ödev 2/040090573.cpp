/***************************
Ders : BLG221 (Veri Yap�lar�)
D�nem : 2010 G�z
�dev : #2
Ad Soyad : Ozan Arkan Can
Numara : 040090573
***************************/

#include <iostream>
#include <stdlib.h>

using namespace std;

float yeni_ortalama(int *dizi, int baslangic, int boyut, int offset){
      int toplam = 0;
      for(int i = 0; i < boyut; i++)
          toplam += *(dizi + baslangic + i * offset);
      return (float)toplam / (float)boyut;
      }

int main(){
    float toplam1 = 0, toplam2 = 0; // S�n�f ortalamalar� hesaplan�rken kullan�lan de�i�kenler
    int notlar_d[6][10]; // notlar dizisinin tan�m�
    
    FILE *dosya; //dosya t�r�nde pointer olu�turuluyor
    
    dosya = fopen( "notlar.txt" , "r" ); // "notlar.txt" text dosyas� a��l�yor
    
    //Dosyan�n a��lamamas� durumu 
    if(dosya == NULL){
             cout << "Dosya acilamadi." << endl;
             return -1;
                     }
    //Notlar dosyadan okunup notlar_d dizisine aktar�l�yor
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 6; j++)
                fscanf(dosya, "%d" , &notlar_d[j][i]);
                                }
    fclose(dosya); //Notlar diziye aktar�ld�ktan sonra dosya kapat�l�yor                             
    
    //Her ��rencinin y�l sonu ortalamas�                            
    for (int i = 0; i< 10; i++){
        //Ayn� de�er toplam1 de�i�keninde de kullan�laca�� i�in kod kalabal���ndan kurtulmak i�in x e atand�
        float x = (notlar_d[0][i] + notlar_d[1][i] + notlar_d[2][i]) * 0.1 + notlar_d[3][i] * 0.15 + notlar_d[4][i] * 0.2 + notlar_d[5][i] * 0.35;
        cout << i + 1 << ". ogrencinin yil sonu ortalamasi: " 
        << x
        << endl << endl;
        toplam1 += x;  //S�n�f�n y�l sonu genel ortalamas�n� bulmak i�in de�i�ken        
                               }
   
   //Her �devin ortalamas�
   for (int i = 0; i < 3; i++){
       cout << i + 1 << ". odevin ortalamasi: "
       << yeni_ortalama(&notlar_d[0][0], i * 10, 10, 1) << endl;
       //�devlerin ��renci ortalamalar�n�n s�n�f ortalamas� i�in de�i�ken
       toplam2 += yeni_ortalama(&notlar_d[0][0], i * 10, 10, 1);
                               }
   cout << endl;
   cout << "Odevlerin ogrenci ortalamasinin sinif ortalamasi: "
   << toplam2 / 3 << endl << endl;
   
   cout << "Sinifin yil sonu genel ortalamasi: " 
   << toplam1 / 10 << endl;
   getchar();
   return EXIT_SUCCESS;
}
    
                                                           
                                    
    
                                                 
                      
    
                     
