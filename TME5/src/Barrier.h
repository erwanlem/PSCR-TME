#include <thread>
#include <mutex>
#include <condition_variable>
#include <stdio.h>


namespace pr {

    class Barrier
    {
    private:
        std::mutex m;
        std::condition_variable cond;

        int max;
        int counter;
        
    public:
        Barrier(int N) 
        : max(N)
        , counter(0) {};
        
        ~Barrier() {};


        void done();

        void waitFor();

    };


    void Barrier::done() {
        std::unique_lock<std::mutex> lg(m);

        if (++counter == max) {
            cond.notify_all();
        }
    }

    void Barrier::waitFor() {
        std::unique_lock<std::mutex> lg(m);

        while (counter != max) {
            cond.wait(lg);
        }
        return ;
    }

}