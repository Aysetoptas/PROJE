#include <stdio.h>
#include <time.h>
#include <string.h> // memset i�in gerekli

#define DAYS_IN_WEEK 7 // Haftan�n g�n say�s�

// Tarih ve saat bilgisini saklamak i�in struct
struct DateTime {
    int year, month, day;
    int hour, minute, second;
};

// Zaman� epoch format�nda da saklayabilecek union
union TimeData {
    struct DateTime dt;
    time_t epoch_time;
};

// Fonksiyon: struct DateTime � time_t d�n���m�
time_t convert_to_epoch(struct DateTime dt) {
    struct tm timeinfo;
    
    // Yap�y� s�f�rla
    memset(&timeinfo, 0, sizeof(struct tm));

    timeinfo.tm_year = dt.year - 1900;  // Y�l, 1900'dan itibaren hesaplan�r
    timeinfo.tm_mon = dt.month - 1;     // Aylar 0-11 aras�d�r
    timeinfo.tm_mday = dt.day;
    timeinfo.tm_hour = dt.hour;
    timeinfo.tm_min = dt.minute;
    timeinfo.tm_sec = dt.second;

    return mktime(&timeinfo); // time_t (epoch) de�erini d�nd�r�r
}

int main() {
    union TimeData start_time[DAYS_IN_WEEK], end_time[DAYS_IN_WEEK];
    time_t total_work_seconds = 0; // Toplam �al��ma s�resi
    int i; // D�ng� de�i�kenini fonksiyon ba��nda tan�mla (C89 uyumlulu�u i�in)

    printf("Lutfen haftanin her gunu icin calisma baslangic ve bitis saatlerini giriniz.\n");

    for (i = 0; i < DAYS_IN_WEEK; i++) { // i de�i�keni art�k fonksiyon ba��nda tan�mland�
        printf("\nGun %d - Calisma Baslangic Zamani (YYYY MM DD HH MM SS): ", i + 1);
        scanf("%d %d %d %d %d %d", 
              &start_time[i].dt.year, &start_time[i].dt.month, &start_time[i].dt.day, 
              &start_time[i].dt.hour, &start_time[i].dt.minute, &start_time[i].dt.second);

        printf("Gun %d - Calisma Bitis Zamani (YYYY MM DD HH MM SS): ", i + 1);
        scanf("%d %d %d %d %d %d", 
              &end_time[i].dt.year, &end_time[i].dt.month, &end_time[i].dt.day, 
              &end_time[i].dt.hour, &end_time[i].dt.minute, &end_time[i].dt.second);

        // Epoch zaman�na �evirme
        start_time[i].epoch_time = convert_to_epoch(start_time[i].dt);
        end_time[i].epoch_time = convert_to_epoch(end_time[i].dt);

        // G�nl�k �al��ma s�resi hesapla
        time_t daily_work_seconds = difftime(end_time[i].epoch_time, start_time[i].epoch_time);
        total_work_seconds += daily_work_seconds; // Haftal�k toplam� ekle

        printf("Gun %d icin calisma suresi: %ld saat %ld dakika\n", i + 1, 
               daily_work_seconds / 3600, (daily_work_seconds % 3600) / 60);
    }

    // Haftal�k toplam �al��ma s�resini hesapla
    long total_hours = total_work_seconds / 3600;
    long total_minutes = (total_work_seconds % 3600) / 60;

    printf("\nToplam haftalik calisma suresi: %ld saat %ld dakika\n", total_hours, total_minutes);

    return 0;
}

