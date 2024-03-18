#include <stdint.h>

typedef struct SIU_PCR_FIELDS {
    uint8_t DSC : 2;
    uint8_t ODE : 1;
    uint8_t HYS : 1;
    uint8_t fill : 2;
    uint8_t WPE : 1;
    uint8_t WPS : 1;
}SIU_PCR_FIELDS;

typedef union SIU_PCR {
    uint8_t value;
    SIU_PCR_FIELDS bit_field;
}SIU_PCR;

extern void set_siu_pcr_fields(SIU_PCR *siu_pcr, uint8_t dsc, uint8_t ode, uint8_t hys, uint8_t wpe, uint8_t wps);

extern void decimal_to_binary(uint8_t value);

extern void display_siu_pcr(SIU_PCR *siu_pcr);