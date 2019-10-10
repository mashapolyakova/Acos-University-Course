#include<stdio.h>
void code(unsigned int a) {
    if (a == 0) {
        printf("00\n");
        return;
    }
    int bits[5];
    for (int i = 0; i < 5; ++i) {
        bits[i] = 0;
    }
    int pass = 1 << 7;
    for (int i = 0; i < 5; ++i) {
        bits[i] = a  >> 7;
        bits[i] = a - (bits[i] << 7);
        a = a >> 7;
        /*printf("for i = %d%, bits[i] = %d\n", i, bits[i]);*/
    }
    int i = 0;
    while (i < 4) {
        if (bits[i + 1] != 0) {
            for (int j = 0; j < i + 1; ++j) {
                bits[j] = bits[j]|pass;
            }
        }
        /*printf("for i = %d%, bits[i] = %d\n", i, bits[i]);*/
        ++i;
    }
    /*bits[i + 1] ^= pass;*/
    i = 0;
    while (i < 5 && bits[i] != 0) {
        printf("%02x ", bits[i]);
        ++i;
    }
    printf("\n");

}
int main() {
    unsigned int a;
    while (scanf("%u", &a) == 1) {
        code(a);
    }
}
