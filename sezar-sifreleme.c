#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool sezarSifreleme(char* metin, int key, FILE* dosya);     //Sifreleme yapan metot
void sezarSifreCozucu(char* metin, int key, FILE* dosya);   //Sifre cozucu metot
int asalBulma(int no);                                      //Asal carpan bulan metot

char input[500], metin[500];
int main(void)
{
    printf("\t###SEZAR SIFRELEME UYGULAMASI###\n\n");
    FILE* dosya; //Dosyalama islemleri icin degiskenimiz
    int key = 9; //Sifreleme icin gerekli integer -> 212802090
    int ogr_no, parola, value;

    //Dosyamızı *yoksa olusturuyoruz ve aciyoruz
    dosya = fopen("sifrelimetin.txt", "w+");

    printf("Ad soyad-> ");
    fgets(input, sizeof(input), stdin);

    printf("Ogrenci numaraniz nedir? -> ");
    scanf("%d", &ogr_no);

    printf("Ogrenci numaranizin en buyuk asal carpani nedir?(PAROLA) -> ");
    scanf("%d", &parola);

    if((sezarSifreleme(input, key, dosya)) == true)
    {
        printf("\n\t///SIFRELEME BASARILI///\n");
    }
    
    //Cozumleme icin parola bilgileri aliniyor
    islem:
    printf("\nSifreli metini cozmek icin 1 yaziniz-> ");
    scanf("%d", &value);

    if(value == 1)
    {   
        printf("PAROLA-> ");
        scanf("%d", &value);
        if(value == asalBulma(ogr_no))//Kullanicidan alinan deger metot ciktisina esit ise
        {
            sezarSifreCozucu(input, key, dosya);//Sifre cozumleme metotu calisiyor

            fclose(dosya);//Acik dosya kapatiliyor
            remove("sifrelimetin.txt");//Dosya bilgisayardan siliniyor
        }
        else
        {
            printf("\n**Hatali parola girdiniz!");
            goto islem;
        }
    }
    else
    {
        printf("HATALI KODLAMA, program sonlandiriliyor...");

        fclose(dosya);
        remove("sifrelimetin.txt");
        exit(1);
    }
}

//Sezar sifreleme islemi yapiliyor
bool sezarSifreleme(char* metin, int key, FILE* dosya)
{
    bool durum = false;
    char *ptr = metin;
    while(*ptr != '\0')
    {
        if (isupper(*ptr))//Gelen karakter buyuk harf ise;
        {
            *ptr = ((*ptr - 65 + key) % 26) + 65;//ASCII karakter tablosuna gore degisim oluyor
        }
        else if (islower(*ptr))//Gelen karakter kucuk harf ise;
        {
            *ptr = ((*ptr - 97 + key) % 26) + 97;
        }
        ptr++;
    }
    fputs(metin, dosya);//Sifrelenmis metin dosyaya yaziliyor
    rewind(dosya);
    durum = true;
    return durum;
}

//Sifrelenmis metin cozuluyor
void sezarSifreCozucu(char* metin, int key, FILE* dosya)
{
    char *ptr = metin;
    while(*ptr != '\0')
    {
        if (isupper(*ptr))
        {
            *ptr = ((*ptr - 65 + (26 - key)) % 26) + 65;
        }
        else if (islower(*ptr))
        {
            *ptr = ((*ptr - 97 + (26 - key)) % 26) + 97;
        }
        ptr++;
    }
    printf("\nCozulmus metin: %s", metin);//Sifresi cozulmus metin ekrana yaziliyor
}

//Girilen integer degerin en büyük asal çarpanı bulunuyor
int asalBulma(int ogr_no)
{
	int x = 0;
	for(int i = 2; 1 < ogr_no; i++)
 	{
  		while(ogr_no % i == 0)
  		{	
			if(i > x)//Gelen asal çarpan öncekinden büyük ise değeri ata
				x = i;
   			ogr_no = ogr_no / i;
  		}
 	}
	return x;//En büyük asal çarpan
}