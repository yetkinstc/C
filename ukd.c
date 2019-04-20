#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct sporcular
{
    int lisans_no;
    char tc[12];
    char isim[31];
    int plaka;
    int ukd;
};

struct turnuvalar
{
    int no;
    char ad[41];
    char tarih[11];
    char sehir[16];
};

void turnuva_bilgisi_aktar(); //Biten turnuvaya iliskin bilgilerin sisteme aktarilmasi
void tcye_gore_goruntule(); //TC no ile oyuncu bilgilerinin listelenmesi
void oyuncu_bilgisi_goruntule(); //Oyuncunun bilgilerinin ve oynadigi maclarin listelenmesi
void ile_gore_goruntule(); //Illere gore oyuncu dagilimlarinin listelenmesi
void en_yuksek_on_ukd(); //UKD puani en yuksek on oyuncunun listelenmesi
void ile_gore_tum_oyuncular(); //Bir ildeki tum oyuncularin listelenmesi
void turnuvaya_gore_maclar(); //Turnuvanin bilgilerinin ve oynanan maclarin listelenmesi
void siyah_beyaz_karsilastirma(); //Siyah ve beyaz oynayan oyuncularin istatistiklerinin goruntulenmesi
void oyuncu_ekle(); //Yeni bir sporcunun eklenmesi
void oyuncu_il_guncelle(); //Oyuncunun ilinin guncellenmesi

int menu(); // Menunun goruntulenmesi
int sayi_al(int,int); //Iki deger arasinda bir sayinin alýnmasi
void lisansa_gore_goruntule(int,int *); //Lisans numarasina gore oyuncu bulup goruntulenmesi
void buyukten_kucuge_sirala(int ukd[], int lisans[], int eleman_say); //UKD puanina gore siralama yapilmasi
void yer_degistir(int *,int *); //Pointer yardimi ile yer degistirilmesi
void dosya_yarat_sporcu(); //sporcular.dat dosyasi olusturulmasi
void dosya_yarat_turnuva(); //turnuvalar.dat dosyasi olusturulmasi
int ilk_on(int ukd[]); //Onuncu ile ayni UKD'ye sahip oyuncu sayisinin belirlenmesi
void turn_bilgi(int); //Turnuvanin bilgilerinin yazdirilmasi
int turnuva_sayisi(); //Olusturulan turnuva sayisinin hesaplanmasi
void turnuva_ekle(FILE *); //Yeni bir turnuvanin eklenmesi
void ukd_guncelle(int,int,int); //UKD puaninin girilen degerlere gore guncellenmesi
void ukd_sifirla(); //Binin altindki UKD puanlarinin sifirlanmasi
void tum_maclar(int); //Bir oyuncunun oynadigi tum maclarin goruntulenmesi
void sporcu_al(struct sporcular *,int); //Lisans numarasina gore bir oyuncunun bilgilerinin aktarilmasi
void turnuva_bilgisi_al(int,int *); //Turnuva bilgilerinin goruntulenmesi ve bulundugunun aktarilmasi
void turnuvada_oynanan_maclar(int); //Bir turnuvada oynanan maclarin listelenmesi


int main()
{
    int secim;
    FILE *dosya;

    if((dosya=fopen("sporcular.dat","rb+"))==NULL)
        dosya_yarat_sporcu(); //sporcular.dat yoksa olustur
    fclose(dosya);

    if((dosya=fopen("turnuvalar.dat","rb+"))==NULL)
        dosya_yarat_turnuva(); //turnuvalar.dat yoksa olustur
    fclose(dosya);

    do
    {
        secim=menu();
        switch (secim)
        {
        case 1:
            turnuva_bilgisi_aktar();
            break;
        case 2:
            tcye_gore_goruntule();
            break;
        case 3:
            oyuncu_bilgisi_goruntule();
            break;
        case 4:
            ile_gore_goruntule();
            break;
        case 5:
            en_yuksek_on_ukd();
            break;
        case 6:
            ile_gore_tum_oyuncular();
            break;
        case 7:
            turnuvaya_gore_maclar();
            break;
        case 8:
            siyah_beyaz_karsilastirma();
            break;
        case 9:
            oyuncu_ekle();
            break;
        case 10:
            oyuncu_il_guncelle();
            break;
        default:
            break;
        }
        if (secim!=0)
        {
            printf("\n");
            system("PAUSE"); //Her islem sonrasinde bir tusa basilmasini iste
        }
    }
    while (secim!=0); //0 girildiginde program sonlanir
    return 0;
}


void turnuva_bilgisi_aktar()
{
    FILE *tgenel;
    FILE *tum_maclar;
    FILE *tmaclar;

    int ukd_ort;
    int lisans;
    int tur,blno,slno,sonuc;
    float bud,sud;

    if((tgenel=fopen("turnuva_genel.txt","r"))==NULL)
        printf("\nturnuva_genel.txt dosyasi acilamadi.\n");
    else
    {
        turnuva_ekle(tgenel); //turnuva_genel.txt'deki bilgilerle yeni bir turnuva olustur
        fscanf(tgenel,"%d",&ukd_ort);
        while(!feof(tgenel))
        {
            fscanf(tgenel,"%d",&lisans);
            ukd_guncelle(lisans,ukd_ort,0); //UKD'si 0 olan oyuncularin UKD'sini guncelle
        }
        fclose(tgenel);
    }
    if((tmaclar=fopen("turnuva_maclar.txt","r"))==NULL)
        printf("\nturnuva_maclar.txt dosyasi acilamadi.\n");
    else
    {
        if((tum_maclar=fopen("tum_maclar.txt","a"))==NULL)
            printf("\ntum_maclar.txt dosyasi acilamadi.\n");
        else
        {
            while(!feof(tmaclar))
            {
                fscanf(tmaclar,"%d %d %d %d %f %f",&tur,&blno,&slno,&sonuc,&bud,&sud);
                fprintf(tum_maclar,"%d %d %d %d %d %.1f %.1f\n",turnuva_sayisi(),tur,blno,slno,sonuc,bud,sud);
                ukd_guncelle(blno,0,bud); //UKD puanina ekleme yap
                ukd_guncelle(slno,0,sud);
            }
            fclose(tum_maclar);
            printf("\nIslem basarili.\n");
        }
        fclose(tmaclar);
    }
    ukd_sifirla(); //Binin altindaki puanlari sifirla
    return;
}

void tcye_gore_goruntule()
{
    FILE *dosya;
    struct sporcular sporcu;
    char tc[12];
    int i;
    int bulundu=0;

    if((dosya=fopen("sporcular.dat","rb+"))==NULL)
        printf("\nsporcular.dat dosyasi acilamadi.\n");
    else
    {
        printf("\nBilgilerini goruntulemek istediginiz oyununun TC numarasi: ");
        fflush(stdin);
        gets(tc);

        for(i=0; i<9999; i++)
        {
            fseek(dosya,i*sizeof(struct sporcular),SEEK_SET);
            fread(&sporcu,sizeof(struct sporcular),1,dosya);

            if(strcmp(tc,sporcu.tc)==0) //String karsilastirmasi yapip bulundugunu kontrol eder
            {
                bulundu=1;
                break;
            }
        }
        if(bulundu==1)
            printf("\nLisans No   TC Kimlik No   Ad Soyad                         Ili   UKD Puani\n"
                   "---------   ------------   ------------------------------   ---   ---------\n"
                   "%9d   %-12s   %-30s   %-3d   %9d\n",sporcu.lisans_no,sporcu.tc,sporcu.isim,sporcu.plaka,sporcu.ukd);
        else
            printf("\nBu TC'ye sahip bir oyuncu bulunamadi!\n");
        fclose(dosya);
    }
    return;
}

void oyuncu_bilgisi_goruntule()
{
    int lisans;
    int bulundu;

    printf("\nBilgilerini goruntulemek istediginiz oyununun lisans numarasi: ");
    lisans=sayi_al(1000,9999);
    printf("\n");
    lisansa_gore_goruntule(lisans,&bulundu); //Oyuncu bilgilerinin goruntulenmesi ve varliginin kontrolu
    if(bulundu==1) //Eger boyle bir oyuncu varsa
    {
        printf("\nKatildigi Turnuvalar ve Oynadigi Maclar: \n");
        tum_maclar(lisans); //Tum maclarini listele
    }
    return;
}

void ile_gore_goruntule()
{
    FILE *dosya;
    struct sporcular sporcu;
    int i;
    int plaka;
    int bulundu=0;

    if((dosya=fopen("sporcular.dat","rb+"))==NULL)
        printf("\nsporcular.dat dosyasi acilamadi.\n");
    else
    {
        printf("\nIl plaka kodunu giriniz: ");
        plaka=sayi_al(1,81);

        for(i=0; i<9999; i++) //Tek tek tum dosyayi arayan dongu
        {
            fseek(dosya,i*sizeof(struct sporcular),SEEK_SET);
            fread(&sporcu,sizeof(struct sporcular),1,dosya);

            if(plaka==sporcu.plaka && bulundu==0) //Eger eslesen deger bulursa ekrana yazdirilir ve bir daha yazdirilmaz
            {
                printf("\nLisans No   TC Kimlik No   Ad Soyad                         Ili   UKD Puani\n"
                       "---------   ------------   ------------------------------   ---   ---------\n");
                bulundu=1; //Bir daha yazirilmamasi icin
            }
            if(plaka==sporcu.plaka)
            {
                printf("%9d   %-12s   %-30s   %-3d   %9d\n",sporcu.lisans_no,sporcu.tc,sporcu.isim,sporcu.plaka,sporcu.ukd);
            }
        }
        if(bulundu==0)
            printf("\nBu ile ait bir oyuncu bulunmamaktadir.\n");
        fclose(dosya);
    }
    return;
}

void en_yuksek_on_ukd()
{
    FILE *dosya;
    struct sporcular sporcu;
    int lisans[9000]; //Tum oyuncularin lisans numarasini tutan dizi
    int ukd[9000]; //Tum oyuncularin UKD'sini tutan dizi
    int sayac,i,bos=1;

    if((dosya=fopen("sporcular.dat","rb"))==NULL)
        printf("\nsporcular.dat dosyasi acilamadi.\n");
    else
    {
        for(i=0; i<=8999; i++) //Tum sporculari okur
        {
            fseek(dosya,i*sizeof(struct sporcular),SEEK_SET);
            fread(&sporcu,sizeof(struct sporcular),1,dosya);
            lisans[i]=sporcu.lisans_no; //Diziye atama yapar
            ukd[i]=sporcu.ukd;
            if(ukd[i]!=-1) //UKD degeri olan bir oyuncu buldugunda
                bos=0;
        }
        if (bos==1) //Hic oyuncu bulamazsa
        {
            printf("\nSporcu bulunamadi!\n");
            return;
        }

        buyukten_kucuge_sirala(ukd,lisans,9000); //Tum oyunculari UKD'ye gore siralar

        if(lisans[9]!=0) //En az 10 oyuncu varsa
            sayac=ilk_on(ukd); //Onuncu ile esit puandaki oyunculari hesaplar
        else
        {
            for(i=0; i<9; i++) //Oyuncu sayisi 10'dan az ise sayisini tespit eder
                if(ukd[i]!=-1)
                    sayac=i+1;
        }

        printf("\nLisans No   TC Kimlik No   Ad Soyad                         Ili   UKD Puani\n"
               "---------   ------------   ------------------------------   ---   ---------\n");
        for(i=0; i<sayac; i++)
        {
            fseek(dosya,(lisans[i]-1000)*sizeof(struct sporcular),SEEK_SET);
            fread(&sporcu,sizeof(struct sporcular),1,dosya);
            printf("%9d   %-12s   %-30s   %3d   %9d\n",sporcu.lisans_no,sporcu.tc,sporcu.isim,sporcu.plaka,sporcu.ukd);
        }
        fclose(dosya);
    }
    return;
}

void ile_gore_tum_oyuncular()
{
    FILE *dosya;
    struct sporcular sporcu;
    int i;
    int iller[82]= {0};

    if((dosya=fopen("sporcular.dat","rb"))==NULL)
        printf("\nsporcular.dat dosyasi acilamadi.\n");
    else
    {
        for(i=0; i<9999; i++)
        {
            fseek(dosya,i*sizeof(struct sporcular),SEEK_SET);
            fread(&sporcu,sizeof(struct sporcular),1,dosya);

            if(sporcu.plaka!=0) //Plaka kodu bulursa
                iller[sporcu.plaka]++; //O ilin sayisini bir arttirir
        }

        printf("\nIl Plaka Kodu   Oyuncu sayisi\n"
               "-------------   -------------\n");

        for(i=1; i<=81; i++)
        {
            if(iller[i]!=0)
                printf("%13d   %13d\n",i,iller[i]);
        }
        fclose(dosya);
    }
    return;
}

void turnuvaya_gore_maclar()
{
    int no,bulundu;
    printf("\nBilgilerini goruntulemek istediginiz turnuvanin numarasini giriniz: ");
    scanf("%d",&no);
    while(no<1)
    {
        printf("Tekrar giriniz: ");
        fflush(stdin);
        scanf("%d",&no);
    }
    turnuva_bilgisi_al(no,&bulundu); //Turnuvanin varligini ogrenip ekrana yazdirir
    if(bulundu==1) //Turnuva varsa
    {
        turnuvada_oynanan_maclar(no); //Turnuvaya ait tum maclari listeler
    }
    return;
}

void siyah_beyaz_karsilastirma()
{
    FILE *dosya;
    int turn,tur,blno,slno,sonuc;
    float bud,sud;
    float b_toplam_mac_puani=0,b_toplam_ukd_degisimi=0;
    float s_toplam_mac_puani=0,s_toplam_ukd_degisimi=0;

    if((dosya=fopen("tum_maclar.txt","r"))==NULL)
        printf("\ntum_maclar.txt dosyasi acilamadi.\n");
    else
    {
        fscanf(dosya,"%d %d %d %d %d %f %f",&turn,&tur,&blno,&slno,&sonuc,&bud,&sud);
        while(!feof(dosya))
        {
            b_toplam_ukd_degisimi=b_toplam_ukd_degisimi+bud;
            s_toplam_ukd_degisimi=s_toplam_ukd_degisimi+sud;
            if(sonuc==1)
                b_toplam_mac_puani=b_toplam_mac_puani+1;
            else if(sonuc==2)
                s_toplam_mac_puani=s_toplam_mac_puani+1;
            else
            {
                b_toplam_mac_puani=b_toplam_mac_puani+0.5;
                s_toplam_mac_puani=s_toplam_mac_puani+0.5;
            }
            fscanf(dosya,"%d %d %d %d %d %f %f",&turn,&tur,&blno,&slno,&sonuc,&bud,&sud);
        }
        fclose(dosya);

        printf("\n                      Beyaz Oynayanlar   Siyah Oynayanlar\n"
               "                      ----------------   ----------------\n"
               "Toplam Mac Puani:     %16.1f   %16.1f\n"
               "Toplam UKD Degisimi:  %16.1f   %16.1f\n",
               b_toplam_mac_puani,s_toplam_mac_puani,b_toplam_ukd_degisimi,s_toplam_ukd_degisimi);
    }
    return;
}

void oyuncu_ekle()
{
    FILE *dosya;
    struct sporcular sporcu;
    int lisans;

    if((dosya=fopen("sporcular.dat","rb+"))==NULL)
        printf("\nsporcular.dat acilamadi.\n");
    else
    {
        printf("\nEklemek istediginiz sporcunun lisans numarasini giriniz: ");
        lisans=sayi_al(1000,9999);

        fseek(dosya,(lisans-1000)*sizeof(struct sporcular),SEEK_SET); //Imleci anahtar konuma getirir
        fread(&sporcu,sizeof(struct sporcular),1,dosya);

        while(sporcu.lisans_no==lisans)
        {
            printf("Zaten var olan bir lisans numarasi girdiniz: ");
            lisans=sayi_al(1000,9999);

            fseek(dosya,(lisans-1000)*sizeof(struct sporcular),SEEK_SET);
            fread(&sporcu,sizeof(struct sporcular),1,dosya);
        }

        sporcu.lisans_no=lisans;
        printf("Sporcunun TC kimlik numarasini giriniz: ");
        scanf("%s",sporcu.tc);
        printf("Sporcunun adini ve soyadini giriniz: ");
        fflush(stdin);
        gets(sporcu.isim);
        printf("Sporcunun il plaka kodunu giriniz: ");
        sporcu.plaka=sayi_al(1,81);
        printf("Sporcunun UKD puanini giriniz: ");
        scanf("%d",&sporcu.ukd);
        while(sporcu.ukd<1000 && sporcu.ukd!=0)
        {
            printf("\nUKD puani 0 haric 1000'den kucuk olamaz.\nTekrar giriniz: ");
            scanf("%d",&sporcu.ukd);
        }

        fseek(dosya,(lisans-1000)*sizeof(struct sporcular),SEEK_SET);
        fwrite(&sporcu,sizeof(struct sporcular),1,dosya);

        fclose(dosya);
    }
    return;
}

void oyuncu_il_guncelle()
{
    FILE *dosya;
    struct sporcular sporcu;
    int lisans;

    if((dosya=fopen("sporcular.dat","rb+"))==NULL)
        printf("\nsporcular.dat dosyasi acilamadi.\n");
    else
    {
        printf("\nIl plaka numarasini guncellemek istediginiz sporcunun lisans numarasi: ");
        lisans=sayi_al(1000,9999);
        fseek(dosya,(lisans-1000)*sizeof(struct sporcular),SEEK_SET);
        fread(&sporcu,sizeof(struct sporcular),1,dosya);

        while(sporcu.lisans_no==0)
        {
            printf("Bu lisans numarasina sahip oyuncu bulunamamistir.\nBastan giriniz: ");
            lisans=sayi_al(1000,9999);
            fseek(dosya,(lisans-1000)*sizeof(struct sporcular),SEEK_SET);
            fread(&sporcu,sizeof(struct sporcular),1,dosya);
        }

        printf("Yeni il plaka kodunu giriniz: ");
        sporcu.plaka=sayi_al(1,81);

        fseek(dosya,(lisans-1000)*sizeof(struct sporcular),SEEK_SET);
        fwrite(&sporcu,sizeof(struct sporcular),1,dosya);

        fclose(dosya);
    }
    return;
}


int menu()
{
    int secim;
    printf("\n------------------------------------------------------------------------------\n"
           " 1- Biten turnuvaya iliskin bilgilerin sisteme aktarilmasi\n"
           " 2- Bir oyuncunun bilgilerinin listelenmesi\n"
           " 3- Oyuncunun bilgilerinin ve katildigi turnuvalardaki maclarinin listelenmesi\n"
           " 4- Bir ildeki tum oyuncularin listelenmesi\n"
           " 5- UKD puani en yuksek 10 oyuncunun listelenmesi\n"
           " 6- Illerdeki oyuncu sayilarinin listelenmesi\n"
           " 7- Bir turnuvanin bilgilerinin ve turnuvada oynanan maclarin listelenmesi\n"
           " 8- Tum maclardaki beyaz-siyah karsilastirmasi\n"
           " 9- Yeni bir oyuncunun eklenmesi\n"
           "10- Bir oyuncunun ilinin guncellenmesi\n"
           "\n 0- Cikis\n"
           "\n------------------------------------------------------------------------------\n\n"
           "Seciminizi giriniz: ");
    secim=sayi_al(0,10);
    return secim;
}

int sayi_al(int sayi1,int sayi2)
{
    int sayi;
    scanf("%d",&sayi);
    while(sayi<sayi1 || sayi>sayi2)
    {
        printf("Tekrar giriniz: ");
        fflush(stdin);
        scanf("%d",&sayi);
    }
    return sayi;
}

void lisansa_gore_goruntule(int lisans,int *var)
{
    FILE *dosya;
    struct sporcular sporcu;
    int bulundu=0;
    *var=0;

    if((dosya=fopen("sporcular.dat","rb+"))==NULL)
        printf("\nsporcular.dat dosyasi acilamadi.\n");
    else
    {
        fseek(dosya,(lisans-1000)*sizeof(struct sporcular),SEEK_SET);
        fread(&sporcu,sizeof(struct sporcular),1,dosya);

        if(sporcu.ukd!=-1)
            bulundu=1;
        if(bulundu==1)
        {
            printf("\nLisans No   TC Kimlik No   Ad Soyad                         Ili   UKD Puani\n"
                   "---------   ------------   ------------------------------   ---   ---------\n"
                   "%9d   %-12s   %-30s   %-3d   %9d\n",sporcu.lisans_no,sporcu.tc,sporcu.isim,sporcu.plaka,sporcu.ukd);
            *var=1; //Bulundugunun bilgisini gonderir
        }
        else
            printf("Bu lisans numarasina sahip bir oyuncu bulunamadi!\n");
        fclose(dosya);
    }
    return;
}

void turnuvada_oynanan_maclar(int no)
{
    FILE *dosya;
    struct sporcular beyaz;
    struct sporcular siyah;
    int turn,tur,blno,slno,sonuc;
    float bud,sud,bmpuan,smpuan;

    if((dosya=fopen("tum_maclar.txt","r"))==NULL)
        printf("\ntum_maclar.txt dosyasi acilamadi.\n");
    else
    {
        printf("\n       Beyaz Oynayanlar\n       Siyah Oynayanlar\n"
               "\nTur No Ad Soyad                       UKD  Mac Puani\n"
               "------ ------------------------------ ---- ---------\n");
        fscanf(dosya,"%d %d %d %d %d %f %f",&turn,&tur,&blno,&slno,&sonuc,&bud,&sud);
        while(!feof(dosya))
        {
            if(turn==no)
            {
                sporcu_al(&beyaz,blno); //Oyuncularin bilgilerini alir
                sporcu_al(&siyah,slno);
                if(sonuc==1) //Mac puanini belirler
                {
                    bmpuan=1;
                    smpuan=0;
                }
                else if(sonuc==2)
                {
                    bmpuan=0;
                    smpuan=1;
                }
                else
                {
                    smpuan=0.5;
                    bmpuan=0.5;
                }
                printf("\n%6d %-30s %4d %9.1f\n       %-30s %4d %9.1f\n",tur,beyaz.isim,beyaz.ukd,bmpuan,siyah.isim,siyah.ukd,smpuan);
            }
            fscanf(dosya,"%d %d %d %d %d %f %f",&turn,&tur,&blno,&slno,&sonuc,&bud,&sud);
        }
        fclose(dosya);
    }
    return;
}

void turnuva_bilgisi_al(int no,int *bulundu)
{
    FILE *dosya;
    struct turnuvalar turnuva;

    if((dosya=fopen("turnuvalar.dat","rb"))==NULL)
        printf("\nturnuvalar.dat dosyasi acilamadi.\n");
    else
    {
        fseek(dosya,(no-1)*sizeof(struct turnuvalar),SEEK_SET);
        fread(&turnuva,sizeof(struct turnuvalar),1,dosya);
        if(turnuva.no==no)
        {
            printf("\nTurnuva No Turnuva Adi                              Tarih      Sehir\n"
                   "---------- ---------------------------------------- ---------- ---------------\n");
            printf("%10d %-40s %-10s %-15s\n",turnuva.no,turnuva.ad,turnuva.tarih,turnuva.sehir);
            *bulundu=1; //Bulundugunun bilgisini gonderir
        }
        else
        {
            printf("\nBu numaraya sahip bir turnuva bulunmamaktadir.\n");
            *bulundu=0; //Bulunamadiginin bilgisini gonderir
        }
        fclose(dosya);
    }
    return;
}

void turnuva_ekle(FILE *dosya)
{
    FILE *turnuva;
    struct turnuvalar turn;
    struct turnuvalar bos;

    if((turnuva=fopen("turnuvalar.dat","rb+"))==NULL)
        printf("\nturnuvalar.dat dosyasi acilamadi.\n");
    else
    {
        turn.no=turnuva_sayisi()+1; //Eski turnuva sayisini ogrenip yeni turnuva numarasini belirler
        printf("\nSistem tarafindan atanan turnuva numarasi: %d\n",turn.no);
        fscanf(dosya,"%s",turn.ad);
        fscanf(dosya,"%s",turn.tarih);
        fscanf(dosya,"%s",turn.sehir);

        fseek(turnuva,(turn.no-1)*sizeof(struct turnuvalar),SEEK_SET);
        fwrite(&turn,sizeof(struct turnuvalar),1,turnuva);
        bos.no=0;
        fwrite(&bos,sizeof(struct turnuvalar),1,turnuva); //Bir sonraki turnuva numarasini bosaltir
        fclose(turnuva);
    }
    return;
}

void ukd_guncelle(int lisans,int ort,int sayi)
{
    FILE *dosya;
    struct sporcular sporcu;

    if((dosya=fopen("sporcular.dat","rb+"))==NULL)
        printf("\nsporcular.dat dosyasi acilamadi.\n");
    else
    {
        fseek(dosya,(lisans-1000)*sizeof(struct sporcular),SEEK_SET);
        fread(&sporcu,sizeof(struct sporcular),1,dosya);
        if(sporcu.ukd==0)
            sporcu.ukd=ort; //UKD 0 ise yeni deger atar
        sporcu.ukd=sporcu.ukd+sayi; //Var olan degere ekleme yapar
        fseek(dosya,(lisans-1000)*sizeof(struct sporcular),SEEK_SET);
        fwrite(&sporcu,sizeof(struct sporcular),1,dosya);
    }
    fclose(dosya);
    return;
}

void ukd_sifirla()
{
    FILE *dosya;
    struct sporcular sporcu;
    int i;

    if((dosya=fopen("sporcular.dat","rb+"))==NULL)
        printf("\nsporcular.dat acilamadi.\n");
    else
    {
        for(i=0; i<=8999; i++)
        {
            fseek(dosya,i*sizeof(struct sporcular),SEEK_SET);
            fread(&sporcu,sizeof(struct sporcular),1,dosya);
            if (sporcu.ukd<1000 && sporcu.plaka!=0) //Plaka koduyla oyuncu var mi kontrol edip UKD'yi gunceller
            {
                sporcu.ukd=0;
                fseek(dosya,i*sizeof(struct sporcular),SEEK_SET);
                fwrite(&sporcu,sizeof(struct sporcular),1,dosya);
            }
        }
        fclose(dosya);
    }
    return;
}

void tum_maclar(int lisans)
{
    FILE *dosya;
    int turnuva,tur,blno,slno,sonuc;
    float bud,sud;
    int tsayac,yeni_t;
    float mac_puani,toplam_puan=0,toplam_degisim=0;
    struct sporcular rakip;
    int bulundu=0;
    int b=0;

    if((dosya=fopen("tum_maclar.txt","r"))==NULL)
        printf("\ntum_maclar.txt acilamadi.\n");
    else
    {
        tsayac=turnuva-1; //Sayac ile turnuva arasindaki esitligi bozar
        while(!feof(dosya))
        {
            fscanf(dosya,"%d %d %d %d %d %f %f\n",&turnuva,&tur,&blno,&slno,&sonuc,&bud,&sud);
            if(turnuva!=tsayac && tsayac>0) //Yeni bir turnuvaya gecildiginde
            {
                if(b!=0) //Art arda yazimini onler
                {
                    printf("\nToplam Mac Puani: %.1f\n",toplam_puan);
                    printf("Toplam UKD degisimi: %.1f\n",toplam_degisim);
                    toplam_puan=0; //Sifirla
                    toplam_degisim=0;
                }
                b=0;
            }
            if (blno==lisans)
            {
                if(turnuva!=tsayac) //Yeni bir turnuvada ise
                {
                    turn_bilgi(turnuva); //Turnuva bilgisi alinir
                    tsayac=turnuva; //Turnuva sayaci turnuva ile esitlenir
                    yeni_t=1; //Yeni bir turnuva oldugunu belirtir
                    b=1; //Onceki turnuva bilgilerinin yazilmasini saglar
                }
                if(yeni_t==1) //Yeni bir turnuvaya gectiyse
                {
                    bulundu=1;
                    printf("Tur No   Rakip Ad Soyad                   Rakip UKD   Mac Puani   UKD Degisimi\n"
                           "------   ------------------------------   ---------   ---------   ------------\n");
                    yeni_t=0; //Yeni bir turnuvada degil
                }
                if(sonuc==1)
                    mac_puani=1;
                else if(sonuc==0)
                    mac_puani=0.5;
                else
                    mac_puani=0;
                toplam_puan=toplam_puan+mac_puani;
                toplam_degisim=toplam_degisim+bud;
                sporcu_al(&rakip,slno); //Rakip bilgilerini alir
                printf("%6d   %-30s   %9d   %9.1f   %12.1f\n",tur,rakip.isim,rakip.ukd,mac_puani,bud);
            }
            else if (slno==lisans)
            {
                if(turnuva!=tsayac)
                {
                    turn_bilgi(turnuva);
                    tsayac=turnuva;
                    yeni_t=1;
                    b=1;
                }
                if(yeni_t==1)
                {
                    bulundu=1;
                    printf("Tur No   Rakip Ad Soyad                   Rakip UKD   Mac Puani   UKD Degisimi\n"
                           "------   ------------------------------   ---------   ---------   ------------\n");
                    yeni_t=0;
                }
                if(sonuc==1)
                    mac_puani=0;
                else if(sonuc==0)
                    mac_puani=0.5;
                else
                    mac_puani=1;
                toplam_puan=toplam_puan+mac_puani;
                toplam_degisim=toplam_degisim+sud;
                sporcu_al(&rakip,blno);
                printf("%6d   %-30s   %9d   %9.1f   %12.1f\n",tur,rakip.isim,rakip.ukd,mac_puani,sud);
            }
        }
        if(bulundu==1) //Son kez turnuva bilgilerini yazdirmak icin
        {
            printf("\nToplam Mac Puani: %.1f\n",toplam_puan);
            printf("Toplam UKD degisimi: %.1f\n",toplam_degisim);
        }
        else //Hic mac bulunamazsa
            printf("\nBu oyuncu mac oynamamistir.\n");
        fclose(dosya);
    }
    return;
}

void sporcu_al(struct sporcular *sporcu,int lisans)
{
    FILE *dosya;

    if((dosya=fopen("sporcular.dat","rb+"))==NULL)
        printf("\nsporcular.dat dosyasi acilamadi.\n");
    else
    {
        fseek(dosya,(lisans-1000)*sizeof(struct sporcular),SEEK_SET);
        fread(sporcu,sizeof(struct sporcular),1,dosya);
        fclose(dosya);
    }
    return;
}

int turnuva_sayisi()
{
    FILE *dosya;
    int i=1;
    struct turnuvalar turnuva;
    if((dosya=fopen("turnuvalar.dat","rb+"))==NULL)
        printf("\nturnuvalar.dat dosyasi acilamadi.");
    else
    {
        while(i!=0)
        {
            fseek(dosya,(i-1)*sizeof(struct turnuvalar),SEEK_SET);
            fread(&turnuva,sizeof(struct turnuvalar),1,dosya);
            if(turnuva.no==0) //Turnuva numarasi 0 olan turnuvayi bulana dek dongu devam eder
                break;
            i++;
        }
        fclose(dosya);
    }
    return i-1; //Var olan turnuva sayisini getirir
}

void turn_bilgi(int no)
{
    FILE *dosya;
    struct turnuvalar turnuva;

    if((dosya=fopen("turnuvalar.dat","rb"))==NULL)
        printf("\nturnuvalar.dat dosyasi acilamadi.\n");
    else
    {
        fseek(dosya,(no-1)*sizeof(struct turnuvalar),SEEK_SET);
        fread(&turnuva,sizeof(struct turnuvalar),1,dosya);
        printf("\nTurnuva Adi, Tarihi ve Sehri: %s, %s, %s\n\n",turnuva.ad,turnuva.tarih,turnuva.sehir);
        fclose(dosya);
    }
    return;
}

void buyukten_kucuge_sirala(int ukd[], int lisans[], int eleman_say)
{
    int i, gecis_say=0, yer_degisti;
    do
    {
        gecis_say++; //Her seferinde daha az yer degistirme yapmayi saglar
        yer_degisti=0;
        for(i=0; i<eleman_say-gecis_say; i++)
        {
            if(ukd[i]<ukd[i+1]) //Bir sonraki deger daha buyukse yer degistirir
            {
                yer_degistir(&ukd[i],&ukd[i+1]);
                yer_degistir(&lisans[i],&lisans[i+1]);
                yer_degisti=1;
            }
        }
    }
    while(yer_degisti==1);
    return;
}

void yer_degistir(int *sayi1, int *sayi2)
{
    int gecici_sayi;
    gecici_sayi=*sayi1;
    *sayi1=*sayi2;
    *sayi2=gecici_sayi;
    return;
}

int ilk_on(int ukd[])
{
    int sayi=10;
    while(ukd[sayi-1]==ukd[sayi]) //Ayni UKD'ye sahip oyuncu sayisini belirler
        sayi++;
    return sayi;
}

void dosya_yarat_turnuva()
{
    FILE *dosya;
    struct turnuvalar bos;

    if((dosya=fopen("turnuvalar.dat","wb"))==NULL)
        printf("turnuvalar.dat dosyasi yaratilamadi.\n");
    else
    {
        bos.no=0;
        fwrite(&bos,sizeof(struct turnuvalar),1,dosya); //Numarasi 0 olan bos bir turnuva yazar
        fclose(dosya);
    }
    return;
}

void dosya_yarat_sporcu()
{
    FILE *dosya;
    struct sporcular bos_sporcu;
    int i;
    bos_sporcu.lisans_no=0; //Lisans numarasina sahip degil
    bos_sporcu.ukd=-1; //UKD'ye sahip degil
    bos_sporcu.plaka=0; //Plakaya sahip degil

    if((dosya=fopen("sporcular.dat","wb"))==NULL)
        printf("sporcular.dat dosyasi yaratilamadi.\n");
    else
    {
        for(i=1000; i<=9999; i++)
            fwrite(&bos_sporcu,sizeof(struct sporcular),1,dosya); //9000 adet bos sporcu yazar
        fclose(dosya);
    }
    return;
}
