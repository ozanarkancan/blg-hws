#include <stdio.h>

float yeni_ortalama(int *dizi, int baslangic, int boyut, int offset) {
  int i, toplam = 0;
  
  for (i = 0; i < boyut; i++)
    toplam += *(dizi + baslangic + i*offset);
  
  return (float)toplam / (float)boyut;
}

float ogrenci_ortalama(int notlar[][6], int j) {
	return (notlar[j][0]*0.1)+(notlar[j][1]*0.1)+(notlar[j][2]*0.1)+(notlar[j][3]*0.15)+(notlar[j][4]*0.2)+(notlar[j][5]*0.35);
}

void main()
{
  int i = 0, j = 0, notlar[10][6], *ptr;
  float toplam = 0.0;
  FILE *dosya = fopen("notlar.txt", "r");
  ptr = &notlar[0][0];
  while (!feof(dosya)) fscanf(dosya, "%d", ptr++ );

  printf("1.Her ogrencinin yilsonu ortalamasi\n2.Her odevin ortalamasi\n3.Odevlerin ogrenci ortalamalarinin sinif ortalamasi\n4.Sinifin yilsonu genel ortalamasi\nSeciminiz:");
  scanf("%d", &i);

  switch (i) {
	case 1: 
	for (j = 0; j < 10; j++) printf("%d. ogrencinin yilsonu ortalamasi = %.2f\n", j+1, ogrenci_ortalama(notlar, j));	
	break;
	
	case 2:
	for (j = 0; j < 3; j++)	printf("%d. odevin ortalamasi = %f\n", j+1, yeni_ortalama(&notlar[0][0], j, 10, 6));
	break;
	
	case 3:
	for ( j = 0; j < 3; j++) toplam += yeni_ortalama(&notlar[0][0], j, 10, 6);
	printf("Odevlerin ogrenci ortalamalarinin sinif ortalamasi = %.2f\n", toplam / 3);
	break;
	
	case 4:
	for (j = 0; j < 10; j++) toplam += ogrenci_ortalama(notlar, j);
	printf("Sinifin yilsonu genel ortalamasi = %.2f\n", toplam/10);
	break;
	
  } /* switch */
}
