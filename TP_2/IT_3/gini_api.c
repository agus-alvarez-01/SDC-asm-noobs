#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "gini_calc.h"

#define URL "https://api.worldbank.org/v2/country/arg/indicator/SI.POV.GINI?format=json&date=2011:2020"

#define MAX_JSON_SIZE 65536
#define MAX_RECORDS  32

typedef struct {
    int year;
    float gini;
} Record;

static char json_buffer[MAX_JSON_SIZE];
static size_t json_size = 0;

// Escritura del buffer de curl
size_t write_buffer(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t total = size * nmemb;

    if (json_size + total >= MAX_JSON_SIZE)
        return 0;

    memcpy(json_buffer + json_size, contents, total);
    json_size += total;
    json_buffer[json_size] = '\0';

    return total;
}

// parseo manual, sin usar cJson o Jasson
int parse_json(Record records[]) {
    int count = 0;
    char *p = json_buffer;
    while ((p = strstr(p, "\"date\":\"")) != NULL) {
        p += 8;
        int year = atoi(p);
        char *v = strstr(p, "\"value\":");
        if (!v) break;
        v += 8;
        if (strncmp(v, "null", 4) == 0) {
            p = v + 4;
            continue;
        }
        float gini = strtof(v, NULL);
        if (count < MAX_RECORDS) {
            records[count].year = year;
            records[count].gini = gini;
            count++;
        }
        p = v;
    }
    return count;
}

void sort_records(Record records[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (records[i].year > records[j].year) {
                Record tmp = records[i];
                records[i] = records[j];
                records[j] = tmp;
            }
        }
    }
}

int main(void) {
    CURL *curl;
    CURLcode res;
    Record records[MAX_RECORDS];

    // Recuperamos los datos
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (!curl) return 1;

    curl_easy_setopt(curl, CURLOPT_URL, URL);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    // por defecto, curl escribe en stdout, pero nosotros queremos que escriba en un buffer
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_buffer);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "Error: %s\n", curl_easy_strerror(res));
        return 1;
    }
    // parseo
    int count = parse_json(records);

    // ordenamos por año, de menor a mayor
    sort_records(records, count);

    // Llamamos la funcion en C
    printf("%-6s  %-16s %-16s\n", "Año", "GINI (float)", "GINI (int) + 1");
    printf("------------------------------------\n");

    for (int i = 0; i < count; i++) {
        int result = gini_convert(records[i].gini);

        printf("%-6d %-16.2f %-16d\n",
               records[i].year,
               records[i].gini,
               result);
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}
