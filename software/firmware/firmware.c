#include "system.h"
#include "periphs.h"
#include <iob-uart.h>
#include <stdint.h>

static unsigned int Q[CMWC_CYCLE], c = 362436;

void random_init(unsigned int);
unsigned int cmwc_rand(void);

int main()
{
  int32_t y = 0;
  int32_t x = 0;
  int32_t y_1 = 0;
  uint8_t i = 0;
  uint8_t n = 100;
  //random_init(123);
  uart_printf("\n\n Low-pass filter the first 100 random signed numbers of the zero-average input x using equation y(n)=2*y(n-1)+x(n): \n\n");
  for (i = 1; i <= n; i = i +1) {
    //x = cmwc_rand();
    y = 2*y_1 + x;
    uart_printf("%d ->\t%d\n", i, y);
    y_1 = y;
  }
  return y;
}

void random_init(unsigned int seed){
    int i;

    Q[0] = seed;
    Q[1] = seed + PHI;
    Q[2] = seed + PHI + PHI;

    for (i = 3; i < CMWC_CYCLE; i++)
        Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHI ^ i;
}

unsigned int cmwc_rand(void){
    uint64_t t, a = 18782LL;
    static uint32_t i = 4095;
    uint32_t x, r = 0xfffffffe;
    i = (i + 1) & 4095;
    t = a * Q[i] + c;
    c = (t >> 32);
    x = t + c;
    if (x < c) {
        x++;
        c++;
    }
    return (Q[i] = r - x);
}
