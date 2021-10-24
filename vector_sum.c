#include <stdio.h>
#include <pthread.h>

static long long sum = 0;

struct args 
{
    int numi;
    int for_cnt;
    int *v;
};

void* test_f(void *arg_func)
{
    struct args* tmp = (struct args*)(arg_func);    
    for (int i = 0; i < tmp->for_cnt; i++) {
        printf("%lld, ", sum);
        sum += tmp->v[i + tmp->numi];
        printf("%lld\n", sum);
    }
    pthread_exit(NULL);
}

int vector_sum (int *v, int size, int nthreads)
{
    pthread_t thread;
    struct args in_func;
    in_func.for_cnt = size / nthreads;
    in_func.v = v;
    int i = 0;
    for (i = 0; i < nthreads; i++) {
        in_func.numi = i * in_func.for_cnt;
        pthread_create(&thread, NULL, test_f, &in_func);
        int status;
        pthread_join(thread, (void *) &status);
    }
    i--;
    in_func.for_cnt = size % nthreads;
    for (int j = 0; j < in_func.for_cnt; j++) {
        sum += v[j + i * size / nthreads];
    }
    return sum;
}