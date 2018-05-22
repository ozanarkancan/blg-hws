#define AD_UZUNLUK 30
#define TELNO_UZUNLUK 15

struct Tel_dugum{
       char ad[AD_UZUNLUK];
       char telno[TELNO_UZUNLUK];
       Tel_dugum *sonraki;
       };

//Ýþaretçi listesi için düðüm 
struct isaretci_eleman{
       int kayitsirasi;//Aramada bulunan kayýtlarýn kayýt sýrasý
       Tel_dugum *aranan;//Ýþaretçi listesinde dugumun iþaret ettiði aramada bulunan kaydýn adresini tutan iþaretçi 
       isaretci_eleman *sonraki;//Ýþaretçi listesinde sýradaki düðümü iþaret eden iþaretçi
                      } ;
      
