#include<stdio.h>
int main() {
    long long int x, y;
    long long int res = 0;
    while(scanf("%llx-%llx", &x, &y) == 2) {
        res += (y - x);
        scanf("%*[^\n]");
    }
    printf("%lld\n", res);
}
