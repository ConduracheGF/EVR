#include "functii_i2c.h"
#include "functii_uart.h"
#include "functii_afisare.h"

int main() {
    USART_Init(UBRR);
    setup_i2c();
    setup_7_segm();

    int cifra_input[5] = {0};
    int cnt=0, dp=-1;

    while (1) {
        unsigned char in = USART_Receive();

        if (in >= '0' && in <= '9') {
            cifra_input[cnt] = in - '0';
            cnt++;
            cnt %= 4;
        }
        else if (in == '.' || in == ',') {
            if (cnt > 0 && dp == -1) {
                dp = cnt - 1;
            }
        }
        else if (in == ' ' || in == '\n') {
            int cifra[4] = {0};
            for (int i = 0; i < 4; i++) {
                if (i < cnt)
                    cifra[i] = cifra_input[i];
                else
                    cifra[i] = 0;
            }
            
            if (dp >= 0 && dp < 4) {
                cifra[dp] |= 0x80;
            } else if (cnt < 4) {
                cifra[cnt-1] |= 0x80;
            }
            
            afisare(cifra);
            cnt = 0;
            dp = -1;
        }
    }
}
