#define AD_UZUNLUK 30
#define TELNO_UZUNLUK 15

struct Tel_dugum{
       char ad[AD_UZUNLUK];
       char telno[TELNO_UZUNLUK];
       Tel_dugum *sonraki;
       };

//��aret�i listesi i�in d���m 
struct isaretci_eleman{
       int kayitsirasi;//Aramada bulunan kay�tlar�n kay�t s�ras�
       Tel_dugum *aranan;//��aret�i listesinde dugumun i�aret etti�i aramada bulunan kayd�n adresini tutan i�aret�i 
       isaretci_eleman *sonraki;//��aret�i listesinde s�radaki d���m� i�aret eden i�aret�i
                      } ;
      
