#include <pthread.h>
#include <sched.h>
#include <iostream>

void* helloworld ( void *arg ){
    int cpuid = sched_getcpu();
    std::cout<< "Hello pthread on cpu " << cpuid << std::endl;
    return NULL;
}

int main(void){

    std::cout<<" pthread create\n";
    pthread_t handle;
    pthread_attr_t attr;
    pthread_attr_init( &attr );
    cpu_set_t cpus;
    CPU_ZERO( &cpus );

    // Set bit cpu0 to enable in mask.
    CPU_SET( 0,  &cpus );
    pthread_attr_setaffinity_np( &attr,sizeof(cpu_set_t), &cpus );
    int ret = pthread_create( &handle, &attr , &helloworld, NULL );
    if( ret != 0) {
        std::cout<< "Errorcode " << ret << std::endl;
    }
    void* retvalue;
    pthread_join( handle, &retvalue );

    return 0;
}