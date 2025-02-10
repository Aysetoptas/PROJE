#include <stdio.h>
#include <time.h>
#include <string.h> // memset için gerekli

#define DAYS_IN_WEEK 7 // Haftanýn gün sayýsý

// Tarih ve saat bilgisini saklamak için struct
struct DateTime {
    int year, month, day;
    int hour, minute, second;
};

// Zamaný epoch formatýnda da saklayabilecek union
union TimeData {
    struct DateTime dt;
    time_t epoch_time;
};

// Fonksiyon: struct DateTime › time_t dönüþümü
time_t convert_to_epoch(struct DateTime dt) {
    struct tm timeinfo;
    
    // Yapýyý sýfýrla
    memset(&timeinfo, 0, sizeof(struct tm));

    timeinfo.tm_year = dt.year - 1900;  // Yýl, 1900'dan itibaren hesaplanýr
    timeinfo.tm_mon = dt.month - 1;     // Aylar 0-11 arasýdýr
    timeinfo.tm_mday = dt.day;
    timeinfo.tm_hour = dt.hour;
    timeinfo.tm_min = dt.minute;
    timeinfo.tm_sec = dt.second;

    return mktime(&timeinfo); // time_t (epoch) deðerini döndürür
}

int main() {
    union TimeData start_time[DAYS_IN_WEEK], end_time[DAYS_IN_WEEK];
    time_t total_work_seconds = 0; // Toplam çalýþma süresi
    int i; // Döngü deðiþkenini fonksiyon baþýnda tanýmla (C89 uyumluluðu için)

    printf("Lutfen haftanin her gunu icin calisma baslangic ve bitis saatlerini giriniz.\n");

    for (i = 0; i < DAYS_IN_WEEK; i++) { // i deðiþkeni artýk fonksiyon baþýnda tanýmlandý
        printf("\nGun %d - Calisma Baslangic Zamani (YYYY MM DD HH MM SS): ", i + 1);
        scanf("%d %d %d %d %d %d", 
              &start_time[i].dt.year, &start_time[i].dt.month, &start_time[i].dt.day, 
              &start_time[i].dt.hour, &start_time[i].dt.minute, &start_time[i].dt.second);

        printf("Gun %d - Calisma Bitis Zamani (YYYY MM DD HH MM SS): ", i + 1);
        scanf("%d %d %d %d %d %d", 
              &end_time[i].dt.year, &end_time[i].dt.month, &end_time[i].dt.day, 
              &end_time[i].dt.hour, &end_time[i].dt.minute, &end_time[i].dt.second);

        // Epoch zamanýna çevirme
        start_time[i].epoch_time = convert_to_epoch(start_time[i].dt);
        end_time[i].epoch_time = convert_to_epoch(end_time[i].dt);

        // Günlük çalýþma süresi hesapla
        time_t daily_work_seconds = difftime(end_time[i].epoch_time, start_time[i].epoch_time);
        total_work_seconds += daily_work_seconds; // Haftalýk toplamý ekle

        printf("Gun %d icin calisma suresi: %ld saat %ld dakika\n", i + 1, 
               daily_work_seconds / 3600, (daily_work_seconds % 3600) / 60);
    }

    // Haftalýk toplam çalýþma süresini hesapla
    long total_hours = total_work_seconds / 3600;
    long total_minutes = (total_work_seconds % 3600) / 60;

    printf("\nToplam haftalik calisma suresi: %ld saat %ld dakika\n", total_hours, total_minutes);

    return 0;
}

