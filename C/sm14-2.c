#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <dlfcn.h>
int main(int argc, char* argv[]) {
    void *handle = dlopen("libm.so.6", RTLD_NOW);
    if (!handle) {
        //error
        return 1;
    }
    void * func = dlsym(handle, argv[1]);
    if (!func) {
        dlclose(handle);
        return 1;
    }    //error
    double val;
    while(scanf ("%lf", &val) == 1) {
        double res = ((double (*) (double))func)(val);
        printf ("%.10g\n", res);
    }
    dlclose(handle);
    return 0;
}
