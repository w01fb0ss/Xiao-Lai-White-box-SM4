#include "WBMatrix/WBMatrix.h"
#include "sm4.h"

#define GET32(pc)  (\
((uint32_t)(pc)[0] << 24) ^\
((uint32_t)(pc)[1] << 16) ^\
((uint32_t)(pc)[2] <<  8) ^\
((uint32_t)(pc)[3]))

#define PUT32(st, ct)\
(ct)[0] = (uint8_t)((st) >> 24);\
(ct)[1] = (uint8_t)((st) >> 16);\
(ct)[2] = (uint8_t)((st) >>  8);\
(ct)[3] = (uint8_t)(st)

extern Aff32 M[32][3];
extern Aff32 C[32];
extern Aff32 D[32];
extern Aff32 SE[4];
extern Aff32 FE[4];
extern uint32_t Table[32][4][256];

typedef struct {
    Aff32 M[32][3];              // 32轮，每轮3个 Aff32
    Aff32 C[32];                 // 32轮常量 C
    Aff32 D[32];                 // 32轮常量 D
    Aff32 SE[4];                 // 输入部分的 Aff32 变换
    Aff32 FE[4];                 // 输出部分的 Aff32 变换
    uint32_t Table[32][4][256];  // 32轮，每轮4个字节，每个字节256个值
} WhiteBoxLut;


void printstate(unsigned char * in);
WhiteBoxLut wbsm4_gen(uint8_t *key);
void wbsm4_encrypt(unsigned char IN[], unsigned char OUT[]);
