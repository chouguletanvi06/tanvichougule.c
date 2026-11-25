#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define MAX_DEPTH 100.0
#define MAX_PRESSURE 10.0
#define MAX_TEMP 40.0
#define MIN_BATTERY 20.0

struct Robot {
    int id;
    float depth, pressure, temperature, battery;
    char sensorStatus[20];
};

// Function declarations
void addRecord();
void displayRecords();
void analyzeData();
void generateReport();
int readRecords(struct Robot *r);
int isUnsafe(struct Robot *r);
void checkSafety(struct Robot *r);

// Read records from file
int readRecords(struct Robot *r)
{
    FILE *fp = fopen("robot_data.txt", "r");
    int count = 0;

    if (fp == NULL) return 0;

    while (count < MAX &&
        fscanf(fp, "%d,%f,%f,%f,%f,%19s",
        &r[count].id, &r[count].depth,
        &r[count].pressure, &r[count].temperature,
        &r[count].battery, r[count].sensorStatus) == 6)
        count++;

    fclose(fp);
    return count;
}

// Check whether robot data is unsafe
int isUnsafe(struct Robot *r)
{
    return r->depth > MAX_DEPTH ||
           r->pressure > MAX_PRESSURE ||
           r->temperature > MAX_TEMP ||
           r->battery < MIN_BATTERY ||
           r->sensorStatus[0] == 'F';
}

// Display safety status
void checkSafety(struct Robot *r)
{
    printf("\nSafety Analysis:\n");

    if (r->depth > MAX_DEPTH)
        printf("WARNING: Excessive depth!\n");

    if (r->pressure > MAX_PRESSURE)
        printf("WARNING: High pressure!\n");

    if (r->temperature > MAX_TEMP)
        printf("WARNING: High temperature!\n");

    if (r->battery < MIN_BATTERY)
        printf("WARNING: Low battery!\n");

    if (r->sensorStatus[0] == 'F')
        printf("WARNING: Sensor fault detected!\n");

    printf("STATUS: %s\n",
           isUnsafe(r) ? "UNSAFE CONDITION DETECTED!" :
                         "All parameters are NORMAL.");
}

// Add new record
void addRecord()
{
    FILE *fp = fopen("robot_data.txt", "a");
    struct Robot r;

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Robot ID: ");
    scanf("%d", &r.id);

    printf("Enter Depth (meters): ");
    scanf("%f", &r.depth);

    printf("Enter Pressure: ");
    scanf("%f", &r.pressure);

    printf("Enter Temperature: ");
    scanf("%f", &r.temperature);

    printf("Enter Battery Percentage: ");
    scanf("%f", &r.battery);

    printf("Enter Sensor Status (OK/FAULT): ");
    scanf("%19s", r.sensorStatus);

    fprintf(fp, "%d,%.2f,%.2f,%.2f,%.2f,%s\n",
        r.id, r.depth, r.pressure, r.temperature,
        r.battery, r.sensorStatus);

    fclose(fp);

    printf("\nRecord saved successfully!\n");
    checkSafety(&r);
}

// Display historical records
void displayRecords()
{
    struct Robot r[MAX];
    int count = readRecords(r);

    if (!count) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n========== HISTORICAL RECORDS ==========\n");

    for (int i = 0; i < count; i++) {
        printf("\nRobot ID: %d", r[i].id);
        printf("\nDepth: %.2f", r[i].depth);
        printf("\nPressure: %.2f", r[i].pressure);
        printf("\nTemperature: %.2f", r[i].temperature);
        printf("\nBattery: %.2f%%", r[i].battery);
        printf("\nSensor: %s\n", r[i].sensorStatus);
    }
}

// Analyze historical data
void analyzeData()
{
    struct Robot r[MAX];
    int count = readRecords(r), unsafe = 0;
    float depth = 0, pressure = 0, temp = 0, battery = 0;

    if (!count) {
        printf("\nNo data available for analysis!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        depth += r[i].depth;
        pressure += r[i].pressure;
        temp += r[i].temperature;
        battery += r[i].battery;

        if (isUnsafe(&r[i]))
            unsafe++;
    }

    printf("\n========== DATA ANALYSIS ==========\n");
    printf("\nTotal Records: %d", count);
    printf("\nAverage Depth: %.2f meters", depth / count);
    printf("\nAverage Pressure: %.2f", pressure / count);
    printf("\nAverage Temperature: %.2f", temp / count);
    printf("\nAverage Battery: %.2f%%", battery / count);
    printf("\nUnsafe Records: %d", unsafe);
    printf("\nSafe Records: %d\n", count - unsafe);
}

// Generate inspection report
void generateReport()
{
    struct Robot r[MAX];
    FILE *fp;
    int count = readRecords(r), unsafe = 0;

    if (!count) {
        printf("\nNo records available!\n");
        return;
    }

    fp = fopen("inspection_report.txt", "w");

    if (fp == NULL) {
        printf("\nUnable to create report!\n");
        return;
    }

    fprintf(fp, "UNDERWATER ROBOT INSPECTION REPORT\n");
    fprintf(fp, "===================================\n");

    for (int i = 0; i < count; i++) {
        fprintf(fp, "\nRobot ID: %d", r[i].id);
        fprintf(fp, "\nDepth: %.2f", r[i].depth);
        fprintf(fp, "\nPressure: %.2f", r[i].pressure);
        fprintf(fp, "\nTemperature: %.2f", r[i].temperature);
        fprintf(fp, "\nBattery: %.2f%%", r[i].battery);
        fprintf(fp, "\nSensor Status: %s", r[i].sensorStatus);

        if (isUnsafe(&r[i])) {
            fprintf(fp, "\nResult: UNSAFE");
            unsafe++;
        }
        else
            fprintf(fp, "\nResult: SAFE");

        fprintf(fp, "\n-----------------------------\n");
    }

    fprintf(fp, "\nTOTAL RECORDS: %d", count);
    fprintf(fp, "\nUNSAFE RECORDS: %d", unsafe);
    fprintf(fp, "\nSAFE RECORDS: %d", count - unsafe);

    fclose(fp);

    printf("\nInspection report generated successfully!");
    printf("\nFile name: inspection_report.txt\n");
}

// Main function
int main()
{
    int choice;

    do {
        printf("\n\n========================================");
        printf("\n UNDERWATER ROBOT INSPECTION SYSTEM");
        printf("\n========================================");
        printf("\n1. Add Robot Sensor Record");
        printf("\n2. Display Historical Records");
        printf("\n3. Analyze Sensor Data");
        printf("\n4. Generate Inspection Report");
        printf("\n5. Exit");
        printf("\n\nEnter your choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1: addRecord(); break;
            case 2: displayRecords(); break;
            case 3: analyzeData(); break;
            case 4: generateReport(); break;
            case 5: printf("\nExiting Program...\n"); break;
            default: printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 5);

    return 0;
