
#include <stdio.h>
#include <time.h>
#include <string.h> // memset için eklenmesi gereken kütüphane

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
    union TimeData time1, time2;
    
    // Kullanýcýdan ilk tarih ve saat bilgisini alma
    printf("Ilk tarihi giriniz (YYYY MM DD HH MM SS): ");
    scanf("%d %d %d %d %d %d", 
          &time1.dt.year, &time1.dt.month, &time1.dt.day, 
          &time1.dt.hour, &time1.dt.minute, &time1.dt.second);

    // Kullanýcýdan ikinci tarih ve saat bilgisini alma
    printf("Ikinci tarihi giriniz (YYYY MM DD HH MM SS): ");
    scanf("%d %d %d %d %d %d", 
          &time2.dt.year, &time2.dt.month, &time2.dt.day, 
          &time2.dt.hour, &time2.dt.minute, &time2.dt.second);

    // Epoch zamanýna çevirme
    time1.epoch_time = convert_to_epoch(time1.dt);
    time2.epoch_time = convert_to_epoch(time2.dt);

    // Epoch zamanlarýný ve farklarýný ekrana yazdýrma
    printf("\nIlk tarih için Epoch zamaný: %ld\n", time1.epoch_time);
    printf("Ikinci tarih için Epoch zamaný: %ld\n", time2.epoch_time);
    printf("Iki tarih arasýndaki fark: %ld saniye\n", 
           difftime(time2.epoch_time, time1.epoch_time));

    return 0;
}

