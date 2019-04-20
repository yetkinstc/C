#include <stdio.h>
#include <stdlib.h>

int kategori_al() //Kullanicidan kategoriyi girmesini saglar ve kontrol eder.
{
    char kategori;
    scanf(" %c",&kategori);
    while (kategori!='a' && kategori!='A' && kategori!='G' && kategori!='g' && kategori!='Y' && kategori!='y' && kategori!='K' && kategori!='k' && kategori!='M' && kategori!='m')
    {
        printf("Yanlis karakter girdiniz. Tekrar giriniz: ");
        scanf(" %c",&kategori);
    }
    return kategori;
}

int sayi_al(int alt_sinir) //Kullanicidan, sonradan belirlenen bir alt sinirin ustunde sayi girmesini saglar ve kontrol eder.
{
    int sayi;
    scanf("%d",&sayi);
    while (sayi<alt_sinir)
    {
        printf("Sayi 1000'den kucuk olamaz. Tekrar giriniz: ");
        scanf("%d",&sayi);
    }
    return sayi;
}

int katsayi_hesabi(int ukd_puani) //Katsayi hesabini sonradan belirlenen bir degere gore karsilasirarak belirler.
{
    int k;
    if (ukd_puani>=2400) k=10;
    else
    {
        if (ukd_puani>=2000) k=15;
        else
        {
            if (ukd_puani>=1600) k=20;
            else
            {
                if (ukd_puani>=1300) k=25;
                else
                {
                    if (ukd_puani>=1000) k=30;
                }
            }
        }
    }
    return k;
}

int main()
{
    int tur_sayisi,lisans_no,ukd_puani,ukd_rakip,mac_sonucu,i,ukd_fark,k,buyuk_mu,sayac=0,son_ukd,ukd_top=0,
    ukd_ort,ukd2400=0,ukd2000=0,ukd1600=0,ukd1300=0,ukd1000=0,sifirlanan=0,acik=0,gencler=0,yildizlar=0,kucukler=0,minikler=0,
    acik_ukd=0,gencler_ukd=0,yildizlar_ukd=0,kucukler_ukd=0,minikler_ukd=0,acik_ort,gencler_ort,yildizlar_ort,kucukler_ort,
    minikler_ort,max_ukd=-1,max_lisans,max_minikler_ukd=0,max_minikler_lisans=0,max_degisim=0,max_degisim_lisans,max_degisim_ukd,
    min_degisim=0,min_degisim_ukd,min_degisim_lisans,tek_max_degisim=0,tek_min_degisim=0,tek_max_lisans=0,tek_min_lisans=0,
    tek_max_ukd,tek_min_ukd,puansiz_galibiyet=0,puansiz_maclar=0,min=0,max=0,tek_min=0,tek_max=0;
    float x,degisim,degisim_toplam,mac_puani,puansiz_galibiyet_yuzde;
    char kategori,max_kategori;
    printf("Tur sayisini giriniz: ");
    scanf("%d",&tur_sayisi);
    printf("\nLisans numarasini giriniz: ");
    scanf("%d",&lisans_no);

    while (lisans_no>0)
    {
        degisim_toplam=0;
        sayac++;
        mac_puani=0;
        printf("Yas kategorisini giriniz(Acik:A,Gencler:G,Yildizlar:Y,Kucukler:K,Minikler:M): ");
        kategori=kategori_al(); //Hazir fonksiyon kullanir.
        printf("UKD puanini giriniz: ");
        ukd_puani=sayi_al(1000); //Kullanicidan hazir fonksiyon yardimiyla 1000 ve uzeri bir deger girmesini saglar.

        mac_puani=0;

        k=katsayi_hesabi(ukd_puani); //Hazir fonksiyon yardimiyla katsayiyi belirler.

        for (i=1; i<=tur_sayisi; i++) //Daha onceden girilen tur sayisi kadar alttaki kodlarý tekrarlar.
        {
            printf("\n%d. rakibin UKD puanini giriniz: ",i);
            scanf("%d",&ukd_rakip);
            if ((ukd_rakip>0 && ukd_rakip<1000) || ukd_rakip<0)
            {
                printf("UKD puani 1-999 arasi ve 0'dan kucuk olamaz. Tekrar giriniz: ");
                scanf("%d",&ukd_rakip);
            }
            printf("%d. macin sonucu (1=galibiyet,0=berabelik,-1=maglubiyet): ",i);
            scanf("%d",&mac_sonucu);
            while (mac_sonucu!=1 && mac_sonucu!=-1 && mac_sonucu!=0)
            {
                printf("Mac sonucunu tekrar giriniz (1,0,-1): ");
                scanf("%d",&mac_sonucu);
            }

            if (ukd_rakip==0)
            {
                if (mac_sonucu==-1)
                {
                    puansiz_galibiyet++;
                    degisim=k*-0,1;
                }
                puansiz_maclar++;
            }

            if (mac_sonucu==0)
            {
                degisim=0;
                mac_puani=mac_puani+0.5;
            }
            else
            {
                if (mac_sonucu==1 && ukd_rakip==0)
                {
                    degisim=k*0.1;
                    mac_puani++;
                }
                else
                {
                    if(mac_sonucu==-1 && ukd_rakip==0)
                    {
                        degisim=k*-0.1;
                    }
                    else {
                        ukd_fark=ukd_puani-ukd_rakip;

                        if (ukd_fark<0) //Mutlak degerini almak icin kullanilir.
                        {
                            buyuk_mu=-1;
                            ukd_fark=0-ukd_fark;
                        }
                        else buyuk_mu=1;

                        if (ukd_fark>350) ukd_fark=350;

                        if (ukd_fark<=3) x=0.5;
                        else
                        {
                            if (ukd_fark<=10) x=0.51;
                            else
                            {
                                if (ukd_fark<=17) x=0.52;
                                else
                                {
                                    if (ukd_fark<=25) x=0.53;
                                    else
                                    {
                                        if (ukd_fark<=32) x=0.54;
                                        else
                                        {
                                            if (ukd_fark<=39) x=0.55;
                                            else
                                            {
                                                if (ukd_fark<=46) x=0.56;
                                                else
                                                {
                                                    if (ukd_fark<=53) x=0.57;
                                                    else
                                                    {
                                                        if (ukd_fark<=61) x=0.58;
                                                        else
                                                        {
                                                            if (ukd_fark<=68) x=0.59;
                                                            else
                                                            {
                                                                if (ukd_fark<=76) x=0.6;
                                                                else
                                                                {
                                                                    if (ukd_fark<=83) x=0.61;
                                                                    else
                                                                    {
                                                                        if (ukd_fark<=91) x=0.62;
                                                                        else
                                                                        {
                                                                            if (ukd_fark<=98) x=0.63;
                                                                            else
                                                                            {
                                                                                if (ukd_fark<=106) x=0.64;
                                                                                else
                                                                                {
                                                                                    if (ukd_fark<=113) x=0.65;
                                                                                    else
                                                                                    {
                                                                                        if (ukd_fark<=121) x=0.66;
                                                                                        else
                                                                                        {
                                                                                            if (ukd_fark<=129) x=0.67;
                                                                                            else
                                                                                            {
                                                                                                if (ukd_fark<=137) x=0.68;
                                                                                                else
                                                                                                {
                                                                                                    if (ukd_fark<=145) x=0.69;
                                                                                                    else
                                                                                                    {
                                                                                                        if (ukd_fark<=153) x=0.7;
                                                                                                        else
                                                                                                        {
                                                                                                            if (ukd_fark<=162) x=0.71;
                                                                                                            else
                                                                                                            {
                                                                                                                if (ukd_fark<=170) x=0.72;
                                                                                                                else
                                                                                                                {
                                                                                                                    if (ukd_fark<=179) x=0.73;
                                                                                                                    else
                                                                                                                    {
                                                                                                                        if (ukd_fark<=188) x=0.74;
                                                                                                                        else
                                                                                                                        {
                                                                                                                            if (ukd_fark<=197) x=0.75;
                                                                                                                            else
                                                                                                                            {
                                                                                                                                if (ukd_fark<=206) x=0.76;
                                                                                                                                else
                                                                                                                                {
                                                                                                                                    if (ukd_fark<=215) x=0.77;
                                                                                                                                    else
                                                                                                                                    {
                                                                                                                                        if (ukd_fark<=225) x=0.78;
                                                                                                                                        else
                                                                                                                                        {
                                                                                                                                            if (ukd_fark<=235) x=0.79;
                                                                                                                                            else
                                                                                                                                            {
                                                                                                                                                if (ukd_fark<=245) x=0.8;
                                                                                                                                                else
                                                                                                                                                {
                                                                                                                                                    if (ukd_fark<=256) x=0.81;
                                                                                                                                                    else
                                                                                                                                                    {
                                                                                                                                                        if (ukd_fark<=267) x=0.82;
                                                                                                                                                        else
                                                                                                                                                        {
                                                                                                                                                            if (ukd_fark<=278) x=0.83;
                                                                                                                                                            else
                                                                                                                                                            {
                                                                                                                                                                if (ukd_fark<=290) x=0.84;
                                                                                                                                                                else
                                                                                                                                                                {
                                                                                                                                                                    if (ukd_fark<=302) x=0.85;
                                                                                                                                                                    else
                                                                                                                                                                    {
                                                                                                                                                                        if (ukd_fark<=315) x=0.86;
                                                                                                                                                                        else
                                                                                                                                                                        {
                                                                                                                                                                            if (ukd_fark<=328) x=0.87;
                                                                                                                                                                            else
                                                                                                                                                                            {
                                                                                                                                                                                if (ukd_fark<=344) x=0.88;
                                                                                                                                                                                else if (ukd_fark<=350) x=0.89;
                                                                                                                                                                            }
                                                                                                                                                                        }
                                                                                                                                                                    }
                                                                                                                                                                }
                                                                                                                                                            }
                                                                                                                                                        }
                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        if (mac_sonucu==1 && buyuk_mu==1)
                        {
                            degisim=k*(1-x);
                            mac_puani++;
                        }
                        else
                        {
                            if (mac_sonucu==-1 && buyuk_mu==1) degisim=k*(0-x);
                            else
                            {
                                if (mac_sonucu==1 && buyuk_mu==-1)
                                {
                                    degisim=k*x;
                                    mac_puani++;
                                }
                                else if (mac_sonucu==-1 && buyuk_mu==-1) degisim=k*(x-1);
                            }
                        }
                    }
                }
            }

            printf("Puan degisimi: %.2f\n",degisim);
            degisim_toplam=degisim+degisim_toplam;

            if (degisim>tek_max_degisim) //Bir mactaki en buyuk puan degisimini bulup verilerini toplamak icin.
            {
                tek_max=1;
                tek_max_degisim=degisim;
                tek_max_lisans=lisans_no;
            }
            else
            {
                if (degisim<tek_min_degisim) //Bir mactaki en kucuk puan degisimini bulup verilerini toplamak için.
                {
                    tek_min=1;
                    tek_min_degisim=degisim;
                    tek_min_lisans=lisans_no;
                }
            }

        }

        printf("\nLisans numarasi: %d",lisans_no);
        printf("\nTurnuvadaki toplam mac puani: %.2f",mac_puani);
        printf("\nToplam UKD degisimi: %.2f\n",degisim_toplam);
        son_ukd=ukd_puani+degisim_toplam;
        if (son_ukd<1000) son_ukd=0; //UKD puani 1000'in altina duserse sifirlanir.
        printf("Yeni UKD puani: %d\n",son_ukd);

        if (tek_max_lisans==lisans_no)
            tek_max_ukd=son_ukd;
        else
        {
            if (tek_max_lisans==0)
                tek_max_ukd=0;
        }
        if (tek_min_lisans==lisans_no)
            tek_min_ukd=son_ukd;
        else
        {
            if (tek_min_lisans==0)
                tek_min_ukd=0;
        }

        if (degisim_toplam>max_degisim) //Tum maclardaki en buyuk puan degisimini bulup verilerini toplamak için.
        {
            max=1;
            max_degisim=degisim_toplam;
            max_degisim_lisans=lisans_no;
            max_degisim_ukd=son_ukd;
        }
        else
        {
            if (degisim_toplam<min_degisim) //Tum maclardaki en kucuk puan degisimini bulup verilerini hesaplamak icin.
            {
                min=1;
                min_degisim=degisim_toplam;
                min_degisim_lisans=lisans_no;
                min_degisim_ukd=son_ukd;
            }
        }

        if (son_ukd>=2400) ukd2400++;
        else
        {
            if (son_ukd>=2000) ukd2000++;
            else
            {
                if (son_ukd>=1600) ukd1600++;
                else
                {
                    if (son_ukd>=1300) ukd1300++;
                    else
                    {
                        if (son_ukd>=1000) ukd1000++;
                        else sifirlanan++;
                    }
                }
            }
        }

        printf("Yas kategorisi: ");

        switch (kategori)
        {
        case 'A':
        case 'a':
            printf("Acik");
            acik++;
            acik_ukd=acik_ukd+son_ukd;
            break;
        case 'G':
        case 'g':
            printf("Gencler");
            gencler++;
            gencler_ukd=gencler_ukd+son_ukd;
            break;
        case 'Y':
        case 'y':
            printf("Yildizlar");
            yildizlar++;
            yildizlar_ukd=yildizlar_ukd+son_ukd;
            break;
        case 'K':
        case 'k':
            printf("Kucukler");
            kucukler++;
            kucukler_ukd=kucukler_ukd+son_ukd;
            break;
        case 'M':
        case 'm':
            printf("Minikler");
            minikler++;
            minikler_ukd=minikler_ukd+son_ukd;
            break;
        }

        ukd_top=ukd_top+son_ukd;

        if (son_ukd>max_ukd)
        {
            max_lisans=lisans_no;
            max_ukd=son_ukd;
            max_kategori=kategori;
        }
        if ((kategori=='m' || kategori=='M') && son_ukd>max_minikler_ukd)
        {
            max_minikler_lisans=lisans_no;
            max_minikler_ukd=son_ukd;
        }

        printf("\n\nLisans numarasini giriniz: ");
        scanf("%d",&lisans_no);

    }
    if (sayac!=0) //Hicbir veri girilmezse 0'a bolme hatasi olur. Bunu onlemek icin bu kullanilir.
    {
        ukd_ort=ukd_top/sayac;
        printf("\nUKD ortalamasi: %d\n",ukd_ort);

        if (acik>0) acik_ort=acik_ukd/acik;
        else acik_ort=0;
        printf("\nAcik kategorisindeki sporcu sayisi: %d, yuzdesi: %% %.2f, UKD ortalamalari: %d",acik,(float)100*acik/sayac,acik_ort);
        if (gencler>0) gencler_ort=gencler_ukd/gencler;
        else gencler_ort=0;
        printf("\nGencler kategorisindeki sporcu sayisi: %d, yuzdesi %% %.2f, UKD ortalamalari: %d",gencler,(float)100*gencler/sayac,gencler_ort);
        if (yildizlar>0) yildizlar_ort=yildizlar_ukd/yildizlar;
        else yildizlar_ort=0;
        printf("\nYildizlar kategorisindeki sporcu sayisi: %d, yuzdesi %% %.2f, UKD ortalamalari: %d",yildizlar,(float)100*yildizlar/sayac,yildizlar_ort);
        if (kucukler>0) kucukler_ort=kucukler_ukd/kucukler;
        else kucukler_ort=0;
        printf("\nKucukler kategorisindeki sporcu sayisi: %d, yuzdesi %% %.2f, UKD ortalamalari: %d",kucukler,(float)100*kucukler/sayac,kucukler_ort);
        if (minikler>0) minikler_ort=minikler_ukd/minikler;
        else minikler_ort=0;
        printf("\nMinikler kategorisindeki sporcu sayisi: %d, yuzdesi %% %.2f, UKD ortalamalari: %d",minikler,(float)100*minikler/sayac,minikler_ort);

        printf("\n\nUKD puani 2400 ve ustu olan sayisi: %d, yuzdesi: %.2f",ukd2400,(float)100*ukd2400/sayac);
        printf("\nUKD puani 2000-2399 arasi olan sayisi: %d, yuzdesi: %.2f",ukd2000,(float)100*ukd2000/sayac);
        printf("\nUKD puani 1600-1999 arasi olan sayisi: %d, yuzdesi: %.2f",ukd1600,(float)100*ukd1600/sayac);
        printf("\nUKD puani 1300-1599 arasi olan sayisi: %d, yuzdesi: %.2f",ukd1300,(float)100*ukd1300/sayac);
        printf("\nUKD puani 1000-1299 arasi olan sayisi: %d, yuzdesi: %.2f",ukd1000,(float)100*ukd1000/sayac);
        printf("\nUKD puani sifirlananlarin sayisi: %d, yuzdesi: %.2f",sifirlanan,(float)100*sifirlanan/sayac);

        printf("\n\nEn yuksek UKD puanina sahip sporcunun;\nLisans nosu: %d, Kategorisi: %c, UKD puani: %d",max_lisans,max_kategori,max_ukd);
        printf("\n\nMinikler kategorisindeki en yuksek UKD puanina sahip sporcunun;\nLisans nosu: %d, UKD puani: %d",max_minikler_lisans,max_minikler_ukd);
        if (max==1)
            printf("\n\nTurnuvada en cok UKD puani kazanan sporcunun;\nLisans nosu: %d, UKD puani: %d, Degisim miktari: %d",max_degisim_lisans,max_degisim_ukd,max_degisim);
        if (min==1)
            printf("\n\nTurnuvada en cok UKD puani kaybeden sporcunun;\nLisans nosu: %d, UKD puani: %d, Degisim miktari: %d",min_degisim_lisans,min_degisim_ukd,min_degisim);
        if (tek_max==1)
            printf("\n\nBir macta en cok UKD puani kazanan sporcunun;\nLisans nosu: %d, UKD puani: %d, Degisim miktari: %d",tek_max_lisans,tek_max_ukd,tek_max_degisim);
        if (tek_min==1)
            printf("\n\nBir macta en cok UKD puani kaybeden sporcunun;\nLisans nosu: %d, UKD puani: %d, Degisim miktari: %d",tek_min_lisans,tek_min_ukd,tek_min_degisim);
        if (puansiz_maclar!=0)
            puansiz_galibiyet_yuzde=(float)100*puansiz_galibiyet/puansiz_maclar;
        else
            puansiz_galibiyet_yuzde=0;
        printf("\n\nUKD puanina sahip sporcularin UKD puani olmayan sporculara kaybettikleri maclarin;\nSayisi: %d, Yuzdesi: %% %.2f\n",puansiz_galibiyet,puansiz_galibiyet_yuzde);

    }
    system("pause");
    return 0;
}
