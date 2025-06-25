#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <future>

using namespace std;

// Пример 1: Простое создание и запуск потоков
void example1_simple_threads() {
    auto thread_func = [](int id) {
        cout << "Thread " << id << " started" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "Thread " << id << " finished" << endl;
        };

    thread t1(thread_func, 1);
    thread t2(thread_func, 2);

    t1.join();
    t2.join();

    cout << "All finished" << endl;
}

// Пример 2: Гонка данных
void example2_data_race() {
    int counter = 0;
    const int iterations = 100'000;

    auto incrementer = [&counter, iterations]() {
        for (int i = 0; i < iterations; ++i) {
            ++counter;
        }
        };

    thread t1(incrementer);
    thread t2(incrementer);

    t1.join();
    t2.join();

    cout << "counter: " << 2 * iterations << endl;
    cout << "fact counter: " << counter << endl;
    cout << endl;
}

// Пример 3: Использование мьютекса для синхронизации
void example3_mutex() {
    int counter = 0;
    const int iterations = 100'000;
    mutex mtx;

    auto incrementer = [&counter, &mtx, iterations]() {
        for (int i = 0; i < iterations; ++i) {
            lock_guard<mutex> lock(mtx);
            ++counter;
        }
        };

    thread t1(incrementer);
    thread t2(incrementer);

    t1.join();
    t2.join();

    cout << "counter: " << 2 * iterations << endl;
    cout << "fact counter: " << counter << endl;
    cout << endl;
}

// Пример 4: Атомарные операции
void example4_atomic() {
    atomic<int> counter(0);
    const int iterations = 100000;

    auto incrementer = [&counter, iterations]() {
        for (int i = 0; i < iterations; ++i) {
            ++counter;
        }
        };

    thread t1(incrementer);
    thread t2(incrementer);

    t1.join();
    t2.join();

    cout << "counter: " << 2 * iterations << endl;
    cout << "fact counter: " << counter << endl;
    cout << endl;
}

// Пример 5: Условные переменные (condition variable)
void example5_condition_variable() {
    mutex mtx;
    condition_variable cv;
    bool ready = false;

    auto waiter = [&mtx, &cv, &ready]() {
        unique_lock<mutex> lock(mtx);
        cout << "Waiter thread: wait signal..." << endl;
        cv.wait(lock, [&ready] { return ready; });
        cout << "Waiter thread: received signal!" << endl;
        };

    auto notifier = [&mtx, &cv, &ready]() {
        this_thread::sleep_for(chrono::milliseconds(1000));
        {
            lock_guard<mutex> lock(mtx);
            ready = true;
            cout << "Notify thread: send signal" << endl;
        }
        cv.notify_one();
        };

    thread t1(waiter);
    thread t2(notifier);

    t1.join();
    t2.join();

    cout << endl;
}

// Пример 6: Deadlock (взаимная блокировка)
void example6_deadlock() {
    mutex mtx1, mtx2;

    auto thread1 = [&mtx1, &mtx2]() {
        lock_guard<mutex> lock1(mtx1);
        cout << "Thread 1: mtx1" << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
        lock_guard<mutex> lock2(mtx2);
        cout << "Thread 1: mtx2" << endl;
        };

    auto thread2 = [&mtx1, &mtx2]() {
        lock_guard<mutex> lock2(mtx2);
        cout << "Thread 2: mtx2" << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
        lock_guard<mutex> lock1(mtx1);
        cout << "Thread 2: mtx1" << endl;
        };

    thread t1(thread1);
    thread t2(thread2);

    //if (t1.joinable()) t1.detach();
    //if (t2.joinable()) t2.detach();

    cout << endl;
}

// Пример 7: std::lock для избежания deadlock
void example7_std_lock() {
    mutex mtx1, mtx2;

    auto thread_func = [&mtx1, &mtx2](int id) {
        cout << "Thread " << id << ": getting mutex" << endl;
        lock(mtx1, mtx2); // Захватываем оба мьютекса без deadlock
        lock_guard<mutex> lock1(mtx1, adopt_lock);
        lock_guard<mutex> lock2(mtx2, adopt_lock);
        cout << "Thread " << id << ": get both mutex" << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
        };

    thread t1(thread_func, 1);
    thread t2(thread_func, 2);

    t1.join();
    t2.join();

    cout << endl;
}

// Пример 8: std::async и std::future
void example8_async_future() {

    auto task = []() {
        this_thread::sleep_for(chrono::milliseconds(500));
        return 42;
        };

    future<int> fut = async(launch::async, task);
    cout << "Wait result..." << endl;
    cout << "Result: " << fut.get() << endl;
    cout << endl;
}

// Пример 9: Пул потоков с использованием std::async
void example9_thread_pool() {
    const int num_tasks = 10;
    vector<future<int>> futures;

    auto task = [](int id) {
        this_thread::sleep_for(chrono::milliseconds(100));
        return id * id;
        };

    for (int i = 0; i < num_tasks; ++i) {

        //future<int> new_future = async(launch::async, task, i);
        //futures.push_back(std::move(new_future));

        futures.emplace_back(async(launch::async, task, i));
    }

    for (auto& fut : futures) {
        cout << "Result: " << fut.get() << endl;
    }

    cout << endl;
}

// Пример 10: Thread-local storage
void example10_thread_local() {
    thread_local int counter = 0;
    mutex cout_mtx;

    auto thread_func = [&cout_mtx](int id) {
        for (int i = 0; i < 5; ++i) {
            ++counter;
            lock_guard<mutex> lock(cout_mtx);
            cout << "Thread " << id << ": counter = " << counter << endl;
        }
        };

    thread t1(thread_func, 1);
    thread t2(thread_func, 2);

    t1.join();
    t2.join();

    cout << endl;
}

// Пример 11: Оптимальный пул потоков с учетом CPU
void example11_optimal_thread_pool() {
    const unsigned int hardware_cores = thread::hardware_concurrency();
    cout << "Count cores: " << hardware_cores << endl;

    const unsigned int optimal_threads = max(1u, hardware_cores * 2 - 1);
    cout << "Count threads: " << optimal_threads << endl;

    vector<future<void>> thread_pool;
    atomic<int> tasks_completed(0);
    const int total_tasks = 20;

    auto worker_task = [&tasks_completed](int task_id) {
        this_thread::sleep_for(chrono::milliseconds(100)); // Имитация работы
        cout << "Task " << task_id << " finished in thread "
            << this_thread::get_id() << endl;
        tasks_completed++;
        };

    for (int i = 0; i < total_tasks; ++i) {
        if (thread_pool.size() >= optimal_threads) {
            for (auto it = thread_pool.begin(); it != thread_pool.end(); ) {
                if (it->wait_for(chrono::seconds(0)) == future_status::ready) {
                    it = thread_pool.erase(it);
                }
                else {
                    ++it;
                }
            }

            if (thread_pool.size() >= optimal_threads) {
                this_thread::sleep_for(chrono::milliseconds(10));
                i--; 
                continue;
            }
        }

        // Добавляем новую задачу в пул
        thread_pool.emplace_back(
            async(launch::async, worker_task, i)
        );
    }

    // 6. Ожидаем завершения всех задач
    for (auto& fut : thread_pool) {
        fut.wait();
    }

    cout << "Completed: "
        << tasks_completed << "/" << total_tasks << endl;
    cout << endl;
}

int main() {
    //example1_simple_threads();      // Простое создание потоков
    //example2_data_race();           // Гонка данных
    //example3_mutex();               // Использование мьютекса
    //example4_atomic();              // Атомарные операции
    //example5_condition_variable();  // Условные переменные
    //example6_deadlock();            // Deadlock
    //example7_std_lock();            // Избежание deadlock
    //example8_async_future();        // std::async и std::future
    //example9_thread_pool();         // Пул потоков
    //example10_thread_local();       // Thread-local storage
    example11_optimal_thread_pool();  // Thread-pool
    return 0;
}
