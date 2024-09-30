#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

typedef struct {
    int x;
    long y;
} Point;

long decode_value(const char *value, int base) {
    return strtol(value, NULL, base);  // Convert value from given base to base 10
}

void store_points(cJSON *json, int n, Point points[]) {
    for (int i = 1; i <= n; i++) {
        char key[4];
        sprintf(key, "%d", i);
        cJSON *point = cJSON_GetObjectItem(json, key);
        
        int base = cJSON_GetObjectItem(point, "base")->valueint;
        const char *value = cJSON_GetObjectItem(point, "value")->valuestring;
        
        long y = decode_value(value, base);
        points[i-1].x = i;
        points[i-1].y = y;
    }
}

double lagrange_interpolation(Point points[], int k) {
    double constant = 0.0;

    for (int i = 0; i < k; i++) {
        double term = points[i].y;
        for (int j = 0; j < k; j++) {
            if (i != j) {
                term *= (0.0 - points[j].x) / (points[i].x - points[j].x);
            }
        }
        constant += term;
    }
    
    return constant;
}

void detect_wrong_points(Point points[], int n, double constant) {
    printf("Detecting wrong points...\n");
    for (int i = 0; i < n; i++) {
        if (points[i].y != constant) {  // Example logic, modify for full polynomial
            printf("Wrong point detected at x = %d, y = %ld\n", points[i].x, points[i].y);
        }
    }
}

void parse_json() {
    FILE *file = fopen("input.json", "r");
    if (!file) {
        printf("Error: Could not open file.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *data = (char *)malloc(length);
    fread(data, 1, length, file);
    fclose(file);

    cJSON *json = cJSON_Parse(data);
    if (!json) {
        printf("Error parsing JSON.\n");
        free(data);
        return;
    }

    cJSON *keys = cJSON_GetObjectItem(json, "keys");
    int n = cJSON_GetObjectItem(keys, "n")->valueint;
    int k = cJSON_GetObjectItem(keys, "k")->valueint;

    printf("Number of roots (n): %d\n", n);
    printf("Minimum roots required (k): %d\n", k);

    Point points[n];
    store_points(json, n, points);

    double constant = lagrange_interpolation(points, k);
    printf("Secret (constant term): %f\n", constant);

    detect_wrong_points(points, n, constant);

    cJSON_Delete(json);
    free(data);
}

int main() {
    parse_json();
    return 0;
}
