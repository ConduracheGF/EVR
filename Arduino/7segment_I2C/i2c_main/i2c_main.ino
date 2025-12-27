#include "functii_i2c.h"
#include "functii_uart.h"
#include "functii_afisare.h"

int main() {
    USART_Init(UBRR);
    setup_i2c();
    setup_7_segm();

    int cifra_input[5] = {0};
    int cnt=0, dp=-1;
    int negativ = 0;

    while (1) {
        unsigned char in = USART_Receive();

        if (in >= '0' && in <= '9') {
            if(cnt < 4){
                cifra_input[cnt] = in - '0';
                cnt++;
            }
        }
        else if (in == '.' || in == ',') {
            if (cnt > 0 && dp == -1) {
                dp = cnt - 1;
            }
        }
        else if (in == '-' && cnt == 0) {
            negativ = 1;
        }
        else if (in == ' ' || in == '\n') {
            int cifra[4] = {0};
            if(negativ){
                for (int i = 3; i > 0; i--) {
                    if (i-1 < cnt)
                        cifra[i] = cifra_input[i-1];
                    else
                        cifra[i] = 0;
                }
                cifra[0] = 0x0A;
            } else {
                for (int i = 0; i < 4; i++) {
                    if (i < cnt)
                        cifra[i] = cifra_input[i];
                    else
                        cifra[i] = 0;
                }
            }
            if (dp >= 0 && dp < 4) {
                cifra[negativ ? dp+1 : dp] |= 0x80;
            } else if (cnt > 0 && cnt < 4) {
                cifra[negativ ? cnt : cnt-1] |= 0x80;
            }
            
            afisare(cifra);
            cnt = 0;
            dp = -1;
            negativ = 0;
        }
    }
}
