#define AD_UZUNLUK 30
#define TELNO_UZUNLUK 15

struct Tel_dugum
{
	char ad[AD_UZUNLUK];	
	char telno[TELNO_UZUNLUK];
    Tel_dugum *sonraki;	
};
struct Liste_isaretci
{
    Tel_dugum *isaretci;
    Liste_isaretci *sonraki;
	int sira;
};
