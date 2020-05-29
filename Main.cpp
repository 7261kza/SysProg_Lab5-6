#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <future>
#include <random>
#include <ctime>
#include "Bear.h"

using namespace std;

int amountOfHoney = 100;
mutex mtx;
Bear bear;

void Bee()
{
    while (bearAlive)
    {
        unique_lock<mutex> ul(mtx);
        //mtx.lock();
        amountOfHoney += 5;
        cout << "ID потока = " << this_thread::get_id() << "\t Пчела принесла меду: " << amountOfHoney << endl;
        //mtx.unlock();
        ul.unlock();
        this_thread::sleep_for(chrono::milliseconds(rand() % 5000));
    }
}

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "ru");
    cout << "\t\tМеда в бочке: " << amountOfHoney << endl;
    this_thread::sleep_for(chrono::milliseconds(3000));
    
    thread bearThread(&Bear::eatOfHoney, bear, ref(amountOfHoney), ref(mtx));

    std::vector<std::future<void>> vector;    
        for (unsigned i = 0; i < 3; ++i)
        {
            vector.emplace_back(std::async(std::launch::async, Bee));
            this_thread::sleep_for(chrono::milliseconds(rand() % 2000));
        }       
 
 /*
    for (size_t i = 1; i <= 10; i++)
    {
        mtx.lock();
        cout << "ID потока = " << this_thread::get_id() << "\t main works\t" << i << endl;
        mtx.unlock();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
*/
    bearThread.join();

    return 0;
}