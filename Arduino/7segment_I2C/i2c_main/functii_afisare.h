#ifndef FUNCTII_AFISARE_H_
#define FUNCTII_AFISARE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void setup_7_segm();
void reset_7_segm();
void afisare(int cifra[]);
void afisare_tensiune(uint16_t mV);

#ifdef __cplusplus
}
#endif

#endif