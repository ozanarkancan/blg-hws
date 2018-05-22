/***************************
Ders : BLG221 (Veri Yapýlarý)
Dönem : 2010 Güz
Ödev : #2
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
    float toplam1 = 0, toplam2 = 0; // Sýnýf ortalamalarý hesaplanýrken kullanýlan deðiþkenler
    int notlar_d[6][10]; // notlar dizisinin tanýmý
    
    FILE *dosya; //dosya türünde pointer oluþturuluyor
    
    dosya = fopen( "notlar.txt" , "r" ); // "notlar.txt" text dosyasý açýlýyor
    
    //Dosyanýn açýlamamasý durumu 
    if(dosya == NULL){
             cout << "Dosya acilamadi." << endl;
             return -1;
                     }
    //Notlar dosyadan okunup notlar_d dizisine aktarýlýyor
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 6; j++)
                fscanf(dosya, "%d" , &notlar_d[j][i]);
                                }
    fclose(dosya); //Notlar diziye aktarýldýktan sonra dosya kapatýlýyor                             
    
    //Her öðrencinin yýl sonu ortalamasý                            
    for (int i = 0; i< 10; i++){
        //Ayný deðer toplam1 deðiþkeninde de kullanýlacaðý için kod kalabalýðýndan kurtulmak için x e atandý
        float x = (notlar_d[0][i] + notlar_d[1][i] + notlar_d[2][i]) * 0.1 + notlar_d[3][i] * 0.15 + notlar_d[4][i] * 0.2 + notlar_d[5][i] * 0.35;
        cout << i + 1 << ". ogrencinin yil sonu ortalamasi: " 
        << x
        << endl << endl;
        toplam1 += x;  //Sýnýfýn yýl sonu genel ortalamasýný bulmak için deðiþken        
                               }
   
   //Her ödevin ortalamasý
   for (int i = 0; i < 3; i++){
       cout << i + 1 << ". odevin ortalamasi: "
       << yeni_ortalama(&notlar_d[0][0], i * 10, 10, 1) << endl;
       //Ödevlerin öðrenci ortalamalarýnýn sýnýf ortalamasý için deðiþken
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
    
                                                           
                                    
    
                                                 
                      
    
                     
