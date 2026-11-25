#include<stdio.h>
#include<string.h>

struct Device {
    int id;
    char type[10];
    float vf, ir, vr;
    char status[6];
};

void getLimits(char type[], float *vfMax, float *irMax, float *vrMin) {
    if (strcmp(type,"Diode")==0) { *vfMax=0.8; *irMax=5; *vrMin=50;}
    else if (strcmp(type,"BJT")==0) { *vfMax=0.9; *irMax=10; *vrMin=40;}
    else if (strcmp(type,"MOSFET")==0) { *vfMax=4.0; *irMax=1; *vrMin=60;}
    else if (strcmp(type,"LED")==0) {*vfMax=3.6; *irMax=10; *vrMin=5;}


} 

int main() {
    int n, i, failcount=0;
    struct Device d[50];
    float vfMax, irMax, vrMin;

    printf("Enter number of devices:");
    scanf("%d", &n);

    for (i=0; i<n; i++) {
        printf("\nEnter details for Device %d:\n", i+1);
        printf("Device ID: "); scanf("%d", &d[i].id);
        printf("Device Type (Diode/BJT/MOSFET/LED): "); 
        printf("%s", d[i].type);
        printf("Forward Voltage Vf (V): "); scanf("%f", &d[i].vf);
        printf("Reverse Leakage Current Ir (mA): "); scanf("%f", &d[i].ir);
        printf("Reverse Voltage Vr (V): "); scanf("%f", &d[i].vr);

        getLimits (d[i].type, &vfMax, &irMax, &vrMin);
        if (d[i].vf > vfMax || d[i].ir > irMax || d[i].vr < vrMin) {
            strcpy(d[i].status, "Fail");
            failcount++;
        } else {
            strcpy(d[i].status, "Pass");
        }
    }

printf("\n--- test Report ---\n");
printf("ID\    Type\n.      Ir(mA)\n       Vr(V)\n       Status\n");

for (i=0; i<n; i++) {
    printf("%d\t%s\t%.2f\t%.2f\t%s\n", d[i].id, d[i].type, d[i].ir, d[i].vr, d[i].status);
}

printf("\nTotal Devices: %d\n", failcount);
return 0;
}
    