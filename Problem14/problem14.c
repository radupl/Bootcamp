#include <stdio.h>
#include <stdlib.h>
#include "problem14.h"


// Setting SIU_PCR given as function parameters.
void set_siu_pcr_fields(SIU_PCR *siu_pcr, uint8_t dsc, uint8_t ode, uint8_t hys, uint8_t wpe, uint8_t wps) {

    siu_pcr->bit_field.DSC = dsc;

    siu_pcr->bit_field.ODE = ode;

    siu_pcr->bit_field.HYS = hys;

    siu_pcr->bit_field.WPE = wpe;

    siu_pcr->bit_field.WPS = wps;

    siu_pcr->bit_field.fill = 0;
}

// Display SIU_PCR value in binary
void decimal_to_binary(uint8_t value) {

    while (value > 0) {
        printf("%d    ", value % 2);
        value /= 2;
    }
    printf("\n");
}

// Display SIU_PCR fields and entire value (in binary).
void display_siu_pcr(SIU_PCR *siu_pcr) {
    printf("\n\n---------SIU_PCR_FIELDS------------\n\n");
    printf("DSC: %d\n", siu_pcr->bit_field.DSC);
    printf("ODE: %d\n", siu_pcr->bit_field.ODE);
    printf("HYS: %d\n", siu_pcr->bit_field.HYS);
    printf("WPE: %d\n", siu_pcr->bit_field.WPE);
    printf("WPS: %d\n", siu_pcr->bit_field.WPS);
    printf("\n--------------SIU_PCR--------------\n\n");
    printf("  DSC    ODE  HYS   0    0   WPE  WPS\n");
    decimal_to_binary(siu_pcr->value);
}

int main () {

    SIU_PCR my_siu_pcr;

    uint8_t dsc, ode, hys, wpe, wps;

    printf("Insert DSC value: ");
    scanf("%hhu", &dsc);

    printf("Insert ODE value: ");
    scanf("%hhu", &ode);

    printf("Insert HYS value: ");
    scanf("%hhu", &hys);

    printf("Insert WPE value: ");
    scanf("%hhu", &wpe);

    printf("Insert WPS value: ");
    scanf("%hhu", &wps);

    set_siu_pcr_fields(&my_siu_pcr, dsc, ode, hys, wpe, wps);

    printf("\n\n");
    display_siu_pcr(&my_siu_pcr);
}