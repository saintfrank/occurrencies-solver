Computationally hard problem sample
===============

The solution aims at simplicity and bare-minimal overhead, while striving to provide the required functionalities with an  API that is as clear and immediate as possible. 



Usage
-----

Essentially compiling on Linux with ```gcc``` and ```make``` and running the binary, from any location. 

![gif](https://raw.githubusercontent.com/saintfrank/occurrencies-solver/master/challenge-sample.gif)


Deliverables
------------

1. The working code is for the communication component(s) is source ```/src```, which contains the three components  ```Producer```, ```Consumer``` and ```Framepool```.
2. The binary is airtime-challenge, compiled by make. It lasts 10 seconds, and get_screen_data and encode_and_send_screen_data are called periodically. Regarding their implementation they are hereby used to perform metrics and validation which are displayed at the end of binary execution. 
3. A description of the proceeding and choices, together with implementation notes, is present in the document ```doc/ABOUT```. 
The parts of code that I am most proud are most the ones that I have managed to not to write. ```/src``` remained explicit and simple, while providing the expected functionality.  
Additionally I remain satisfied about framepool's simplicity, no-copy and very reduced overhead.

Requirements
------------

1. Independent - yes, using pthread. Synchronization is internal to the framepool component. Number of additional frames that can be produced is set by macro ```POOL_SIZE``` in ```framepool.h```
2. Decoupled - yes, producer and consumer are overall independent
3. Can repeat - yes, the repeat function is implemented with zero overhead by the copy of reference to the old frame. implemented by framepool in function ```framepool_produce```, when called with argument ```NULL```
4. C/C++ - yes, C with pthreads compiled on Linux with gcc (5.1, x86). Makefile provided. No libraries.
5. Reasonable performance - yes. To guarantee this, the logic and data structures are all based on a no-copy strategy, random access arrays (circular) and very simple reference handling and increment. Further improvements described in ```doc/ABOUT````
6. Constant frame size. - yes



API
---

The API is illustrated and documented within the code, in the header files with comment and ASCII description. 

Further more it is also exemplified through the ```main.c``` file, which shows the lifecycle and a typical usage, as can be summarized here:

```C

    /*
     *  1 - initialization          
     *---------------------------------------*/
    
    framepool_init(&frames, buffers, refs);
    consumer_init(&cons, &frames);
    producer_init(&prod, &frames);
    
    pthread_create(&producer_thread, NULL, &producer_run, &prod);
    pthread_create(&consumer_thread, NULL, &consumer_run, &cons);
    
    /*
     *  2 - start         
     *---------------------------------------*/

    /* they can be started and stopped at runtime */
    consumer_start(&cons);
    producer_start(&prod);
    
    /*
     *  <--> frames produced and consumed ...        
     *--------------------------------------*/

    /*
     *  4 - stop, cleanup and exit          
     *---------------------------------------*/
    consumer_stop(&cons);                           
    producer_stop(&prod);

    /* they could be restarted, but we exit graciously, 
       they will exit thread at next cycle */
    consumer_close(&cons);                          
    producer_close(&prod);
    framepool_close(&frames);

    /* waiting for the threads, then printing metrics, cleanup and exit */ 
    pthread_join(producer_thread,NULL);
    pthread_join(consumer_thread,NULL);
```
