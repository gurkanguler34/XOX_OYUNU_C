#include <stdio.h>
#include <stdlib.h>

char oyunTahtasi[3][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
};

int hamle;
char sira = 'X'; // Oyuna X başlar

void ekranTemizle();
void tahtaCiz();
int hamleYap(int secim, char oyuncu);
int kazananıKontrolEt();
int beraberlikKontrolEt();

int main(int argc, char const *argv[])
{
    int hamleSonucu;
    
    while(1)
    {
        ekranTemizle();
        tahtaCiz();
        
        printf("[+] Oyuncu %c, Lütfen Hamlenizi Giriniz (1-9) ---> ", sira);
        scanf("%d", &hamle);
        
        // Hamleyi kontrol et ve tahtaya işle
        hamleSonucu = hamleYap(hamle, sira);
        
        if (hamleSonucu == 1) {
            // Kazanan var mı kontrol et
            if (kazananıKontrolEt()) {
                ekranTemizle();
                tahtaCiz();
                printf("\n🎉 TEBRİKLER! Oyuncu %c Oyunu Kazandı! 🎉\n\n", sira);
                break; // Oyunu bitir
            }
            
            // Beraberlik var mı kontrol et
            if (beraberlikKontrolEt()) {
                ekranTemizle();
                tahtaCiz();
                printf("\n🤝 OYUN BERABERE BİTTİ! 🤝\n\n");
                break; // Oyunu bitir
            }
            
            // Oyun devam ediyorsa sırayı değiştir
            if (sira == 'X') sira = 'O';
            else sira = 'X';
        } else {
            // Hamle geçersizse kullanıcıyı uyar ve beklet
            printf("\n[!] GEÇERSİZ HAMLE! (1-9 arası boş bir hücre seçin)\n");
            printf("Devam etmek için Enter'a basın...");
            getchar(); // Scanf'ten kalan newline karakterini temizler
            getchar(); // Kullanıcının tuşa basmasını bekler
        }
    }
    return 0;
}

void tahtaCiz()
{
    printf("-----------------------------\n");
    printf("|   %c   |   %c   |   %c   |\n", oyunTahtasi[0][0], oyunTahtasi[0][1], oyunTahtasi[0][2]);
    printf("-----------------------------\n");
    printf("|   %c   |   %c   |   %c   |\n", oyunTahtasi[1][0], oyunTahtasi[1][1], oyunTahtasi[1][2]);
    printf("-----------------------------\n");
    printf("|   %c   |   %c   |   %c   |\n", oyunTahtasi[2][0], oyunTahtasi[2][1], oyunTahtasi[2][2]);
    printf("-----------------------------\n");
}

void ekranTemizle() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

// Girilen numarayı matris koordinatına çeviren ve kontrol eden fonksiyon
int hamleYap(int secim, char oyuncu) {
    if (secim < 1 || secim > 9) return 0;
    
    int satir = (secim - 1) / 3;
    int sutun = (secim - 1) % 3;
    
    if (oyunTahtasi[satir][sutun] != 'X' && oyunTahtasi[satir][sutun] != 'O') {
        oyunTahtasi[satir][sutun] = oyuncu;
        return 1; // Başarılı
    }
    
    return 0; // Hücre dolu
}

// Yatay, dikey ve çapraz eşleşmeleri kontrol eden fonksiyon
int kazananıKontrolEt() {
    int i;
    // Satır ve Sütun kontrolü
    for (i = 0; i < 3; i++) {
        if (oyunTahtasi[i][0] == oyunTahtasi[i][1] && oyunTahtasi[i][1] == oyunTahtasi[i][2]) return 1;
        if (oyunTahtasi[0][i] == oyunTahtasi[1][i] && oyunTahtasi[1][i] == oyunTahtasi[2][i]) return 1;
    }
    // Çapraz kontrolü
    if (oyunTahtasi[0][0] == oyunTahtasi[1][1] && oyunTahtasi[1][1] == oyunTahtasi[2][2]) return 1;
    if (oyunTahtasi[0][2] == oyunTahtasi[1][1] && oyunTahtasi[1][1] == oyunTahtasi[2][0]) return 1;
    
    return 0; // Henüz kazanan yok
}

// Tahtada boş yer kalıp kalmadığını kontrol eden fonksiyon
int beraberlikKontrolEt() {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            // Eğer hala sayılardan biri duruyorsa oyun bitmemiştir
            if (oyunTahtasi[i][j] != 'X' && oyunTahtasi[i][j] != 'O') {
                return 0; // Boş yer var, beraberlik yok
            }
        }
    }
    return 1; // Tüm hücreler X veya O, oyun berabere
}
