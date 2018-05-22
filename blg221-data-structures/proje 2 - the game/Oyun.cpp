#include "Oyun.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define SAG 1
#define SOL 2
#define YUKARI 3
#define ASAGI 4

using namespace std;

void Kuyruk::olustur(){
     Kuyruk_bas = NULL;
     Kuyruk_son = NULL;
}

void Kuyruk::kapat(){
     if(Kuyruk_bas == NULL)
         return;
     while(Kuyruk_bas != NULL){
                      dusman *gecici;
                      gecici = Kuyruk_bas;
                      Kuyruk_bas = Kuyruk_bas->sonraki;
                      delete gecici;
                              }
}

void Kuyruk::ekle(dusman *ceset){
     if(Kuyruk_bas == NULL){
                   Kuyruk_bas = ceset;
                   Kuyruk_son = ceset;
                   return;
                           }
     else{
     Kuyruk_son->sonraki = ceset;
     Kuyruk_son = ceset;
         }
}
void Kuyruk::yazdir(){
     dusman *tara = Kuyruk_bas;
     if(tara == NULL)
             cout << "Mezarlikta hic yaratik bulunmamaktadir..." << endl << endl;
             
     while(tara != NULL){
                      cout << tara->tur << ".tur Dusman: " << tara->irk << endl;
                      cout << "Strength: " << tara->strength << endl;
                      cout << "Intelligence: " << tara->intelligence << endl << endl;
                      tara = tara->sonraki;
                         }
}

void Yigin::olustur(){
     Yigin_bas == NULL;
}

void Yigin::kapat(){
     if(Yigin_bas == NULL)
         return;
     while(Yigin_bas != NULL){
                      hucre *gecici;
                      gecici = Yigin_bas;
                      Yigin_bas = Yigin_bas->sonraki;
                      delete gecici;
                              }         
}

void Yigin::push(hucre *ekle){
     if(Yigin_bas == NULL){
         Yigin_bas = ekle;
         return; 
                          }
     ekle->sonraki = Yigin_bas;
     Yigin_bas = ekle;
}

hucre *Yigin::pop(){
      if(Yigin_bas == NULL)
          return NULL;
      hucre *gecici;
      gecici = Yigin_bas;
      Yigin_bas = Yigin_bas->sonraki;
      return gecici;
}      

void Oyun::baslat(){
    player = oyuncu_olustur();
    mezarlik.olustur();
    yigin.olustur();
}

void Oyun::bitir(){
     mezarlik.yazdir();
     mezarlik.kapat();
     delete player;
} 
int Oyun::zarlab(){
    srand(time(NULL));
    return rand() % 4 + 1;
}

int Oyun::zar(int x){
    long long int kok_sayi = rand();
    kok_sayi *= rand();
    kok_sayi = kok_sayi % x + 1;
    return kok_sayi;
}

karakter *Oyun::oyuncu_olustur(){
     int tercih;
     karakter *oyuncu;
     oyuncu = new karakter;

     cout << "Karakter irklari: " << endl;
     cout << "1-) Barbarian \n2-)Sorceress" << endl;
     cout << "Seciminizi giriniz: "; cin >> tercih;
     cout << endl;
     if(tercih == 1){
               oyuncu->irk = "Barbarian";
               oyuncu->saldiri_tipi = "Fiziksel";
               oyuncu->strength = 10 + zar(20) + zar(20);
               oyuncu->intelligence = zar(12);
               oyuncu->hit_point = oyuncu->strength + zar(20) + zar(20);
               oyuncu->luck = oyuncu->intelligence + zar(12);
               //Ekipmanlar için zar atýþlarý
               (zar(12) + zar(12) > 18) ? oyuncu->ekipman[0] = true : oyuncu->ekipman[0] = false;
               (zar(12) + zar(12) > 20) ? oyuncu->ekipman[1] = true : oyuncu->ekipman[1] = false; 
               (zar(12) > 8) ? oyuncu->ekipman[2] = true : oyuncu->ekipman[2] = false;
               (zar(12) > 10) ? oyuncu->ekipman[3] = true : oyuncu->ekipman[3] = false;
                    }
     else{
               oyuncu->irk = "Sorceress";
               oyuncu->saldiri_tipi = "Buyu";
               oyuncu->strength = zar(12);
               oyuncu->intelligence = 10 + zar(20) + zar(20);
               oyuncu->hit_point = oyuncu->strength + zar(12);
               oyuncu->luck = oyuncu->intelligence + zar(20) + zar(20);
               //Ekipmanlar için zar atýþlarý
               (zar(12) + zar(12) > 18) ? oyuncu->ekipman[0] = true : oyuncu->ekipman[0] = false;
               (zar(12) + zar(12) > 20) ? oyuncu->ekipman[1] = true : oyuncu->ekipman[1] = false; 
               (zar(12) > 8) ? oyuncu->ekipman[2] = true : oyuncu->ekipman[2] = false;
               (zar(12) > 10) ? oyuncu->ekipman[3] = true : oyuncu->ekipman[3] = false;
          }
     
     cout << "Karakterin Ozellikleri: " << endl;
     cout << "Strength: " << oyuncu->strength << endl;
     cout << "Intelligence: " << oyuncu->intelligence << endl;
     cout << "Hit Point: " << oyuncu->hit_point << endl;
     cout << "Luck: " << oyuncu->luck << endl << endl;
     
     cout << "Ekipmanlar: " << endl;
     if(oyuncu->ekipman[0])
         cout << "Sarimsak" << endl;
     if(oyuncu->ekipman[1])
         cout << "Les Kani" << endl;     
     if(oyuncu->ekipman[2])
         cout << "Tohum" << endl;     
     if(oyuncu->ekipman[3])
         cout << "Gunes Yuzugu" << endl;
     if(!(oyuncu->ekipman[0] || oyuncu->ekipman[1] || oyuncu->ekipman[2] || oyuncu->ekipman[3]))
         cout << "Hic bir ekipman yoktur." << endl;
         
     cout << endl;
     oyuncu->elmas_cantasi = 0;
     
     return oyuncu;
}

dusman *Oyun::dusman_olustur(){

       int olus = zar(12) + zar(12);
       cout << "Atis: " << olus << endl << endl;
       if(olus < 18){
           cout <<"Dusman yok yola devam" << endl;
           return NULL;
                                 }
       else{
            dusman *yeni;
            yeni = new dusman;
            int zar_sonuc = zar(20);
            cout << "zar sonuc: " << zar_sonuc << endl;
            if(zar_sonuc < 6){          
                         cout << "Dusman: Malkavian" << endl;
                         yeni->irk = "Malkavian";
                         yeni->saldiri_tipi = "Fiziksel";
                         yeni->strength = 5 + zar(20);
                         yeni->intelligence = zar(12);
                         yeni->hit_point = yeni->strength + zar(12) + zar(12);
                             }
            else{    
                 if(zar_sonuc > 15){          
                             cout << "Dusman: Tremere" << endl;
                             yeni->irk = "Tremere";
                             yeni->saldiri_tipi = "Büyü";
                             yeni->strength = 10 + zar(12);
                             yeni->intelligence = zar(20) + zar(20);
                             yeni->hit_point = yeni->strength + zar(20);
                                   }                              
                 else{        
                             cout << "Dusman: Nosferatu" << endl;  
                             yeni->irk = "Nosferatu";
                             yeni->saldiri_tipi = "Fiziksel";
                             yeni->strength = zar(12);
                             yeni->intelligence = zar(12);
                             yeni->hit_point = yeni->strength + zar(12);
                     }
                 }
            yeni->sonraki = NULL;
            return yeni;
            }
}

int Oyun::dovus_sira(karakter *player, dusman *enemy){
    int x; 
    int y;
    
    cout << endl;
    
    if(stricmp(player->irk,"barbarian") == 0)
        x = zar(12) + zar (12);
    else
        x = zar(20) + zar(20);
    
    cout << "Karakter " << x << " atti." << endl;
    
    if(stricmp(player->irk,"Malkavian") == 0)
        y = zar(20);
    if(stricmp(player->irk,"Nosferatu") == 0)
        y = zar(12) + zar(12) + zar(12);
    if(stricmp(player->irk,"Tremere") == 0)
        y = zar(12) + zar(12);
       
    
    cout << "Dusman " << y << " atti." << endl;  
    
    if(x > y){
        cout << "Dovuse karakter basliyor..." << endl << endl;
        return 1;
             }
    else{
        cout << "Dovuse dusman basliyor..." << endl << endl; 
        return 2;
        }       
}     
    
void Oyun::dovus(karakter *player, dusman *enemy, int sira, int tur){
     int dusman_direnci = 0;
     int ekipman_destegi = 0;
     int engel_sansi;
     int p_saldiri_gucu;
     int e_saldiri_gucu;
     enemy->tur = tur;
     
     cout << "Strength: " << player->strength << endl;
     cout << "Intelligence: " << player->intelligence << endl;
     cout << "Luck: " << player->luck << endl << endl;
     
     cout << "Dusman Strength: " << enemy->strength << endl;
     cout << "Dusman Intelligence: " << enemy->intelligence << endl;
     
     if(sira == 1){
             while(true){
                 //oyuncunun vurusu
                 if(stricmp(player->irk,"barbarian") == 0)
                     p_saldiri_gucu = player->strength + zar(12);
                 else
                     p_saldiri_gucu = player->intelligence + zar(12);
                     
                 if(player->ekipman[0]){
                                        if(zar(12) > 8)
                                            ekipman_destegi += zar(12);
                                        }
                  if(player->ekipman[1]){
                                        if(zar(12) > 10)
                                             ekipman_destegi += zar(20);
                                         }
                  if( stricmp(player->saldiri_tipi, "fiziksel") == 0 ){
                       if( stricmp(enemy->irk, "malkavian") == 0)
                          dusman_direnci = zar(12);
                       if( stricmp(enemy->irk, "nosferatu") == 0)
                          dusman_direnci = zar(12) + zar(12) + zar(12);
                                                                       }
                  else{
                       if( stricmp(enemy->irk, "nosferatu") == 0)
                           dusman_direnci = zar(12) + zar(12);
                       if( stricmp(enemy->irk, "tremere") == 0)
                           dusman_direnci = zar(12) + zar(12);
                      }
                  
                  cout << "Dusman hp: " << enemy->hit_point << endl;
                  cout << "Karakter Saldiri Gucu " << p_saldiri_gucu << endl;
                  cout << "Ekipman destegi : " << ekipman_destegi << endl;
                  cout << "Dusman direnci : " << dusman_direnci << endl;
                  enemy->hit_point = enemy->hit_point - p_saldiri_gucu - ekipman_destegi + dusman_direnci;   
                  cout << "Vurus sonrasi Dusman Hp: " << enemy->hit_point << endl << endl;
                  if(enemy->hit_point <= 0){
                      cout << "Dusman Nakavt" << endl;
                      mezarlik.ekle(enemy);
                      break;
                                           }                                                                                  
                  //Dusman ýn vurusu
                  if(player->ekipman[2]){
                      if(zar(12) <= 10){
                                 if(player->ekipman[3]){
                                                        zar(12) > 8 ? ekipman_destegi = zar(12) : ekipman_destegi = 0 ;
                                                        }
                                 if(stricmp(player->irk, "barbarian") == 0){
                                                         if( stricmp(enemy->saldiri_tipi, "fiziksel") == 0 )
                                                             engel_sansi = player->luck / zar(12);
                                                         else
                                                             engel_sansi = player->luck / zar(20);
                                                                           }
                                 else{
                                      if( stricmp(enemy->saldiri_tipi, "fiziksel") == 0 )
                                          engel_sansi = player->luck / zar(20);
                                      else
                                          engel_sansi = player->luck / zar(12);
                                      }
                                if( stricmp(enemy->irk, "malkavian") == 0)
                                    e_saldiri_gucu = enemy->strength + zar(12) + zar(12);           
                                if( stricmp(enemy->irk, "nosferatu") == 0)
                                    e_saldiri_gucu = enemy->strength + zar(12);                                 
                                if( stricmp(enemy->irk, "tremere") == 0)
                                    e_saldiri_gucu = enemy->intelligence + zar(12);
                                cout << "Karakter hp: " << player->hit_point << endl;
                                cout << "Dusman Saldiri Gucu: " << e_saldiri_gucu << endl;
                                cout << "Ekipman Destegi: " << ekipman_destegi << endl;
                                cout << "Engen Sansi: " << engel_sansi;
                                player->hit_point = player->hit_point - e_saldiri_gucu + ekipman_destegi + engel_sansi;
                                cout << "Vurus Sonrasi Karakter Hp: " << player->hit_point << endl << endl;
                                if(player->hit_point <= 0){
                                                     cout << "Karakter Nakavt!!!!" << endl;
                                                     break;
                                                           }
                                       }
                        else
                             cout << "Tohum is yapti yirttin" << endl << endl;
                                         }
                  else{
                                 if(player->ekipman[3]){
                                                        zar(12) > 8 ? ekipman_destegi = zar(12) : ekipman_destegi = 0 ;
                                                        }
                                 if(stricmp(player->irk, "barbarian") == 0){
                                                         if( stricmp(enemy->saldiri_tipi, "fiziksel") == 0 )
                                                             engel_sansi = player->luck / zar(12);
                                                         else
                                                             engel_sansi = player->luck / zar(20);
                                                                           }
                                 else{
                                      if( stricmp(enemy->saldiri_tipi, "fiziksel") == 0 )
                                          engel_sansi = player->luck / zar(20);
                                      else
                                          engel_sansi = player->luck / zar(12);
                                      }
                                if( stricmp(enemy->irk, "malkavian") == 0)
                                    e_saldiri_gucu = enemy->strength + zar(12) + zar(12);           
                                if( stricmp(enemy->irk, "nosferatu") == 0)
                                    e_saldiri_gucu = enemy->strength + zar(12);                                 
                                if( stricmp(enemy->irk, "tremere") == 0)
                                    e_saldiri_gucu = enemy->intelligence + zar(12);
                                cout << "Karakter hp: " << player->hit_point << endl;
                                cout << "Dusman Saldiri Gucu: " << e_saldiri_gucu << endl;
                                cout << "Ekipman Destegi: " << ekipman_destegi << endl;
                                cout << "Engel Sansi: " << engel_sansi << endl;
                                player->hit_point = player->hit_point - e_saldiri_gucu + ekipman_destegi + engel_sansi;
                                cout << "Vurus Sonrasi Karakter Hp: " << player->hit_point << endl << endl;
                                if(player->hit_point <= 0){
                                                     cout << "Karakter Nakavt!!!!" << endl;
                                                     break;
                                                           }
                      }
                        }// while sonu
                  }  //if sonu                                                                               
     else{
          while(true){
                  
                  //Dusman ýn vurusu
                  if(player->ekipman[2]){
                      if(zar(12) <= 10){
                                 if(player->ekipman[3]){
                                                        zar(12) > 8 ? ekipman_destegi = zar(12) : ekipman_destegi = 0 ;
                                                        }
                                 if(stricmp(player->irk, "barbarian") == 0){
                                                         if( stricmp(enemy->saldiri_tipi, "fiziksel") == 0 )
                                                             engel_sansi = player->luck / zar(12);
                                                         else
                                                             engel_sansi = player->luck / zar(20);
                                                                           }
                                 else{
                                      if( stricmp(enemy->saldiri_tipi, "fiziksel") == 0 )
                                          engel_sansi = player->luck / zar(20);
                                      else
                                          engel_sansi = player->luck / zar(12);
                                      }
                                if( stricmp(enemy->irk, "malkavian") == 0)
                                    e_saldiri_gucu = enemy->strength + zar(12) + zar(12);           
                                if( stricmp(enemy->irk, "nosferatu") == 0)
                                    e_saldiri_gucu = enemy->strength + zar(12);                                 
                                if( stricmp(enemy->irk, "tremere") == 0)
                                    e_saldiri_gucu = enemy->intelligence + zar(12);
                                cout << "Karakter hp: " << player->hit_point << endl;
                                cout << "Dusman Saldiri Gucu: " << e_saldiri_gucu << endl;
                                cout << "Ekipman Destegi: " << ekipman_destegi << endl;
                                cout << "Engel Sansi: " << engel_sansi << endl;
                                player->hit_point = player->hit_point - e_saldiri_gucu + ekipman_destegi + engel_sansi;
                                cout << "Vurus Sonrasi Karakter Hp: " << player->hit_point << endl << endl;
                                if(player->hit_point <= 0){
                                                     cout << "Karakter Nakavt!!!!" << endl;
                                                     break;
                                                           }
                                       }
                        else
                             cout << "Tohum is yapti yirttin" << endl << endl;
                                         }
                  else{
                                 if(player->ekipman[3]){
                                                        zar(12) > 8 ? ekipman_destegi = zar(12) : ekipman_destegi = 0 ;
                                                        }
                                 if(stricmp(player->irk, "barbarian") == 0){
                                                         if( stricmp(enemy->saldiri_tipi, "fiziksel") == 0 )
                                                             engel_sansi = player->luck / zar(12);
                                                         else
                                                             engel_sansi = player->luck / zar(20);
                                                                           }
                                 else{
                                      if( stricmp(enemy->saldiri_tipi, "fiziksel") == 0 )
                                          engel_sansi = player->luck / zar(20);
                                      else
                                          engel_sansi = player->luck / zar(12);
                                      }
                                if( stricmp(enemy->irk, "malkavian") == 0)
                                    e_saldiri_gucu = enemy->strength + zar(12) + zar(12);           
                                if( stricmp(enemy->irk, "nosferatu") == 0)
                                    e_saldiri_gucu = enemy->strength + zar(12);                                 
                                if( stricmp(enemy->irk, "tremere") == 0)
                                    e_saldiri_gucu = enemy->intelligence + zar(12);
                                cout << "Karakter hp: " << player->hit_point << endl;
                                cout << "Dusman Saldiri Gucu: " << e_saldiri_gucu << endl;
                                cout << "Ekipman Destegi: " << ekipman_destegi << endl;
                                cout << "Engel Sansi: " << engel_sansi << endl;                                
                                player->hit_point = player->hit_point - e_saldiri_gucu + ekipman_destegi + engel_sansi;
                                cout << "Vurus Sonrasi Karakter Hp: " << player->hit_point << endl << endl;
                                if(player->hit_point <= 0){
                                                     cout << "Karakter Nakavt!!!!" << endl;
                                                     break;
                                                           }
                      }
                  //oyuncunun vurusu
                 if(stricmp(player->irk,"barbarian") == 0)
                     p_saldiri_gucu = player->strength + zar(12);
                 else
                     p_saldiri_gucu = player->intelligence + zar(12);
                     
                 if(player->ekipman[0]){
                                        if(zar(12) > 8)
                                            ekipman_destegi += zar(12);
                                        }
                  if(player->ekipman[1]){
                                        if(zar(12) > 10)
                                             ekipman_destegi += zar(20);
                                         }
                  if( stricmp(player->saldiri_tipi, "fiziksel") == 0 ){
                       if( stricmp(enemy->irk, "malkavian") == 0)
                          dusman_direnci = zar(12);
                       if( stricmp(enemy->irk, "nosferatu") == 0)
                          dusman_direnci = zar(12) + zar(12) + zar(12);
                                                                       }
                  else{
                       if( stricmp(enemy->irk, "nosferatu") == 0)
                           dusman_direnci = zar(12) + zar(12);
                       if( stricmp(enemy->irk, "tremere") == 0)
                           dusman_direnci = zar(12) + zar(12);
                      }
                  
                  cout << "Dusman hp: " << enemy->hit_point << endl;
                  cout << "Karakter Saldiri Gucu: " << p_saldiri_gucu << endl;
                  cout << "Ekipman destegi : " << ekipman_destegi << endl;
                  cout << "Dusman direnci : " << dusman_direnci << endl;
                  enemy->hit_point = enemy->hit_point - p_saldiri_gucu - ekipman_destegi + dusman_direnci;   
                  cout << "Vurus sonrasi Dusman hp: " << enemy->hit_point << endl << endl;
                  if(enemy->hit_point <= 0){
                      cout << "Dusman nakavt." << endl;
                      mezarlik.ekle(enemy);
                      break;
                                           }
                     }//while sonu
          }//else sonu                                            
}

void Oyun::maze(hucre *cell, int satir, int sutun){     
     cell->durum = true;
     if(komsu_varmi(cell, satir, sutun)){
                          bool secildi = false;
                          while(!secildi){
                                          int komsu_sec = zarlab();
                                          switch(komsu_sec){
                                                            case 1:
                                                                 if(cell->satir != 0 && cell->yukari == 1 ){
                                                                                yigin.push(cell);
                                                        		                cell->yukari = 0;
		                                                                        cell = cell - sutun;
		                                                                        cell->asagi = 0;
		                                                                        maze(cell, satir, sutun);
		                                                                        secildi = true;
                                                                                                            }
                                                                 break;
                                                            case 2:
                                                                 if(cell->satir != satir - 1 && cell->asagi == 1 ){
                                                                                yigin.push(cell);
                                                        		                cell->asagi = 0;
		                                                                        cell = cell + sutun;
		                                                                        cell->yukari = 0;
		                                                                        maze(cell, satir, sutun);
		                                                                        secildi = true;
                                                                                                                  }
                                                                 break;
                                                            case 3:
                                                                 if(cell->sutun != 0 && cell->sol == 1 ){          
	                                                                            yigin.push(cell);
		                                                                        cell->sol = 0;
                                                                                cell = cell - 1;
		                                                                        cell->sag = 0;
		                                                                        maze(cell, satir, sutun);
		                                                                        secildi = true;
		                                                                                                }
                                                                  break;
                                                            case 4:
                                                                 if(cell->sutun != sutun - 1 && cell->sag == 1 ){
                                                                                yigin.push(cell);
                                                                                cell->sag = 0;
                                                                                cell = cell + 1;
                                                                                cell->sol = 0;
                                                                                maze(cell, satir, sutun);
                                                                                secildi = true;
                                                                                                                 }
                                                                 break;
                                                          }//switch sonu
                                         }//while sonu
                                        }//if sonu                                                                                                                                                                                                                                                                
     else{     
          hucre *kontrol;
	      kontrol = yigin.pop();
	      if(kontrol)
              maze(kontrol, satir, sutun);
	      else //yýðýnda hücre kalmadý
              return;
         }  
}               

bool Oyun::komsu_varmi(hucre *cell, int satir, int sutun){
    if(cell->satir != 0 && (cell - sutun)->durum == false)
	    return true;
    if(cell->satir != satir - 1 && (cell + sutun)->durum == false)
	    return true;
    if(cell->sutun != 0 && (cell - 1)->durum == false)
	    return true;
    if(cell->sutun != sutun - 1 && (cell + 1)->durum == false)
	    return true;
    return false;
}

void Oyun::lab_yazdir(hucre *l, int satir, int sutun){
     cout << endl;
     for(int i = 0; i < satir; i++){
             for(int j = 0; j < sutun; j++){
                     if(l->karakter_burda == 1)
                         cout << l->karakter_burda;
                     else
                         cout << l->ozellik;
                     l++;
                                           }
             cout << endl;                      
                                   }            
     cout << endl;
}                                                   

void Oyun::labirent(){
     int satir, sutun, baslangicx, baslangicy;
     //ELMAS VE PORTAL KOORDÝNATLARI
     int rx = 0;
     int ry = 0;
     int bx = 0;
     int by = 0;
     int gx = 0;
     int gy = 0;
     int px = 0;
     int py = 0;
     
     cout << endl << "Labirentin satir ve sutun sayilarini giriniz." << endl;
     cout << "Satir: "; cin >> satir;
     cout << "Sutun: "; cin >> sutun;
     getchar();
     cout << endl << "Labirent olusturuluyor..." << endl << endl;
     
     hucre lab[satir][sutun];
     hucre yazdir[satir * 2 + 1][sutun * 2 + 1];
     
     for(int i = 0; i < satir; i++){
          for(int j = 0; j < sutun; j++){
	          lab[i][j].yukari = 1;
		      lab[i][j].asagi = 1;
		      lab[i][j].sol = 1;
		      lab[i][j].sag = 1;
		      lab[i][j].durum = false;
		      lab[i][j].sonraki = NULL;
              lab[i][j].satir = i;		
              lab[i][j].sutun = j;
		      lab[i][j].ozellik = ' ';
		      lab[i][j].karakter_burda = 0;
                                        }
							       }
     // Labirent oluþturmaya rastgele bir hücreden baþlanýyor
     baslangicx = zar(satir) - 1;							  
     baslangicy = zar(sutun) - 1;                               
     
     maze(&lab[baslangicx][baslangicy], satir, sutun);
     do{
     rx = zar(satir) - 1;
     ry = zar(sutun) - 1;  
     }while(rx == 0 && ry == 0);
     lab[rx][ry].ozellik = 'R';
     
     do{
        bx = zar(satir) - 1;
        by = zar(sutun) - 1;
        }
        while ((bx == rx && by == ry) || (bx == 0 && by == 0));    
     lab[bx][by].ozellik = 'B';
     
     do{
        gx = zar(satir) - 1;
        gy = zar(sutun) - 1;
        }while ((gx == rx && gy == ry) || (gx == bx && gy == by) || (gx == 0 && gy == 0));
     lab[gx][gy].ozellik = 'G';
             
     do{
        px = zar(satir) - 1;
        py = zar(sutun) - 1;
        }while((px == rx && py == ry) || (px == bx && py == by) || (px == gx && py == gy) || (px == 0 && py == 0));                                         
     lab[px][py].ozellik = 'P';
     
     for(int i = 0; i < satir * 2 + 1; i++){
              for(int j = 0; j < sutun * 2 + 1; j++){
                      if(i % 2 == 0 || j % 2 == 0){
                          yazdir[i][j].ozellik = 177;
                          yazdir[i][j].karakter_burda = 0;
                                                  }
                      else{
                          yazdir[i][j].ozellik = ' ';
                          yazdir[i][j].karakter_burda = 0;
                          }
                                                    }
                                           }
      
      for(int i = 1; i < satir * 2+ 1; i += 2){
        for(int j = 1; j < sutun * 2 + 1; j += 2){
                yazdir[i][j].ozellik = lab[(i - 1) / 2][(j - 1) / 2].ozellik;
                yazdir[i][j].karakter_burda = lab[(i - 1) / 2][(j - 1) / 2].karakter_burda;
                if(lab[(i - 1) / 2][(j - 1) / 2].yukari == 0)
                    yazdir[i - 1][j].ozellik = 0;    
                if(lab[(i - 1) / 2][(j - 1) / 2].asagi == 0)
                    yazdir[i + 1][j].ozellik = 0;
                if(lab[(i - 1) / 2][(j - 1) / 2].sol == 0)
                    yazdir[i ][j - 1].ozellik = 0;                                             
                if(lab[(i - 1) / 2][(j - 1) / 2].sag == 0)
                    yazdir[i][j + 1].ozellik = 0;
                                                 }
                                         }                                     
     
     //LABÝRENTTE YOL BULMA
     
     int tur = 0;
     bool geridonus = false;
     hucre konum;
     konum.gelinenyon = SOL;
     konum.satir = 0;
     konum.sutun = 0;
     bool hafiza = false;
     
     
     while(player->elmas_cantasi != 3 ){
           tur++;
           
           cout << endl << "Konum: " << konum.satir + 1 << " " << konum.sutun + 1 << endl;
           yazdir[konum.satir * 2 + 1][konum.sutun * 2 + 1].karakter_burda = 1;
           lab_yazdir(&yazdir[0][0], satir * 2 + 1, sutun * 2 + 1);
           yazdir[konum.satir * 2 + 1][konum.sutun * 2 + 1].karakter_burda = 0;

           dusman *enemy;
           enemy = dusman_olustur();
           if(enemy != NULL){
                    dovus(player, enemy, dovus_sira(player, enemy), tur);
                    if(player->hit_point <= 0){
                        cout << "Game Over..." << endl;
                        break;
                                               }
                            }                   
           if(lab[konum.satir][konum.sutun].ozellik == 'R'){
              cout << "Karakter kirmizi elmasi buldu." << endl;
              yazdir[konum.satir * 2 + 1][konum.sutun * 2 + 1].ozellik = ' ';
              player->elmas_cantasi++;
                                                          }
           
           if(lab[konum.satir][konum.sutun].ozellik == 'B'){
              cout << "Karakter mavi elmasi buldu." << endl;
              yazdir[konum.satir * 2 + 1][konum.sutun * 2 + 1].ozellik = ' ';
              player->elmas_cantasi++;
                                                          }
           
           if(lab[konum.satir][konum.sutun].ozellik == 'G'){
              cout << "Karakter yesil elmasi buldu." << endl;
              yazdir[konum.satir * 2 + 1][konum.sutun * 2 + 1].ozellik = ' ';
              player->elmas_cantasi++;
                                                          }                                                                                                                    
           
           if(player->elmas_cantasi == 3 && hafiza){
                                    cout << "Tum elmaslari topladik portala isinlaniyoruz =)" << endl;
                                    yazdir[px * 2 + 1][py * 2 + 1].karakter_burda = 1;
                                    lab_yazdir(&yazdir[0][0], satir * 2 + 1, sutun * 2 + 1);
                                    cout << "Gorev Basariyla Tamamlandi" << endl;
                                    break;
                                                   }
                                    
           
           
           if(lab[konum.satir][konum.sutun].ozellik == 'P'){
              cout << "Karakter portali buldu." << endl;
              if(player->elmas_cantasi == 3){
                  cout << "Görev basariyla tamamlandi..." << endl << endl;
                  break;
                                            }
              else{
                  hafiza = true;
                  cout << "Tum elmaslar toplanmadi aramaya devam..." << endl;
                  } 
                                                              }           
    
           cout << endl << "Devam etmek icin bir tusa basiniz" << endl << endl;
           getchar();           
           
           if(!geridonus){
                          konum.sag = 1; konum.sol = 1; konum.yukari = 1; konum.asagi = 1;
                          
                          if(konum.sutun < sutun - 1 && lab[konum.satir][konum.sutun].sag != 1)
                              konum.sag = 0;
                          if(konum.sutun > 0 && lab[konum.satir][konum.sutun].sol != 1)
                              konum.sol = 0;                          
                          if(konum.satir< satir - 1 && lab[konum.satir][konum.sutun].asagi != 1)
                              konum.asagi = 0;
                          if(konum.satir > 0 && lab[konum.satir][konum.sutun].yukari != 1)
                              konum.yukari = 0;           
                        }
           else geridonus = false;
           
           bool hareketetti = true;
           hucre gecmis = konum;
           
           if(konum.sol == 0 && konum.gelinenyon != SOL){
                          konum.sutun--; konum.gelinenyon = SAG; gecmis.sol = 1;}
           else if(konum.sag == 0 && konum.gelinenyon != SAG){
                konum.sutun++; konum.gelinenyon = SOL; gecmis.sag = 1;}
                else if(konum.yukari == 0 && konum.gelinenyon != YUKARI){
                      konum.satir--; konum.gelinenyon = ASAGI; gecmis.yukari = 1;}
                     else if(konum.asagi == 0 && konum.gelinenyon != ASAGI){
                              konum.satir++; konum.gelinenyon = YUKARI; gecmis.asagi = 1;}
                              else hareketetti = false;
                          
                                    if(konum.asagi + konum.yukari + konum.sol + konum.sag <= 2)
                                                   yigin.push(&gecmis);
                                                                                              
                                    if(!hareketetti){
                                                     if(yigin.Yigin_bas != NULL){
                                                                  hucre *tmp;
                                                                  tmp = yigin.pop();
                                                                  konum.satir = tmp->satir;
                                                                  konum.sutun = tmp->sutun;
                                                                  konum.asagi = tmp->asagi;
                                                                  konum.yukari = tmp->yukari;
                                                                  konum.sol = tmp->sol;
                                                                  konum.sag = tmp->sag;
                                                                  konum.gelinenyon = tmp->gelinenyon;
                                                                  geridonus = true;
                                                                          }
                                                     }
                                                                                    
                                                                                }//while sonu                                                                                              
}     
                                                                       
