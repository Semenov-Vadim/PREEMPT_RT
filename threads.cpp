#include <iostream>
#include <thread>
#include <sstream>  //to use stringstream
#include <cstdlib>  //to use exit()
#include <unistd.h> //to use usleep()

#define NANOSEC_IN_MICROSEC 1000


//puts the thread to sleep and compares the expected sleep time to the actual
void thread_sleep_and_compare(unsigned int usecs){
    struct timespec ts1, ts2;

    clock_gettime(CLOCK_REALTIME, &ts1);
    usleep(usecs);
    clock_gettime(CLOCK_REALTIME, &ts2);

    //converting nanosecs to microsecs
    std::cout<< (float(ts2.tv_nsec - ts1.tv_nsec) / NANOSEC_IN_MICROSEC) - usecs << " \n";
        
}

//arg[0] is countThreads
//arg[1] is usecs (sleep time of each thread)
int main(int argc, char *argv[]){

    unsigned int countThreads, 
                usecs;  //sleep time of each thread (measured in microseconds)
    

    //assigning the values of the main method parameters to variables
    std::stringstream convert(argv[1]);
    if (!(convert >> countThreads)){
        std::cout<<"Error occured during converting argv[1]";
        exit(0);
    }
	
    std::stringstream convert2(argv[2]);
    if (!(convert2 >> usecs)){
        std::cout<<"Error occured during converting argv[2]";
        exit(0);
    }


    std::cout<< "Expected execution time of each thread: " << usecs << " microsecs\n";
    std::cout<< "Difference between expected sleep time and real time (microseconds):\n";


    //creating and joining threads
    std::thread *threads = new std::thread[countThreads];
    for(int i = 0 ; i < countThreads ; i++){
        threads[i] = std::thread(thread_sleep_and_compare, usecs);
    }
    for(int i = 0 ; i < countThreads ; i++){
        threads[i].join();
    }

    return 0;
}
