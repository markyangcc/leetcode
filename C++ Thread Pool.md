C++ Thread Pool

```cpp
t1.join()
//join() waits until a thread completes
```

```cpp
t1.detach()
//Unless you need to have more flexibility AND are willing to provide a synchronization mechanism to wait for the thread completion on your own, in which case you may use detach
```

```cpp
//Passing parameters
线程——pass by value, 如果想使用pass by refference ,使用 std::ref(...)
```



```cpp
static unsigned int thread::hardware_concurrency() noexcept
//Returns a value that hints at the number of hardware thread contexts.
```

多线程如何使用大于CPU核心的线程，反而会造成上下文切换带来的效率负担



### 三、Data Race and Mutex

```cpp
void shared_print(string msg, int id) {
    mtx.lock();
    cout << msg << id << endl;	//如果此句话出现 exception, mtx 会一直lock
    mtx.unlock();
}
//use mutex to synchronize the access of common resource like cout

std::lock_guard<std::mutex> guard(mtx); //RAII
//这样使用

```

```cpp
//Avoid Data Race
1、Use mutex to syncrhonize data access
2、Never leak a handle of data to outside
3、Design interface appropriately
```

### 四、DeadLock

```cpp
void shared_print(string id, int value) {
    std::lock_guard<mutex> lockGuard(_mtx);
    std::lock_guard<mutex> lockGuard2(_mtx2);//lock先后顺序不同，可能死锁
    cout << "From " << id << ": " << value << endl;
}
void shared_print2(string id, int value) {
    std::lock_guard<mutex> lockGuard2(_mtx2);
    std::lock_guard<mutex> lockGuard(_mtx);//lock先后顺序不同，可能死锁
    cout << "From " << id << ": " << value << endl;
}

//shared_print2() locked _mtx2, shared_print() locked _mtx
//所以就死锁了
//解决办法是，1、两个函数lock资源临界资源的的顺序要相同
//			2、使用std::adopt_lock,    adopt---采纳
//adopt_lock means the mutex already locked and all you need to do is to adopt to the ownership of that mutex, so when you go out of scope remember to unlock the mutex
 void shared_print(string id, int value) {
        std::lock(_mtx,_mtx2);
        std::lock_guard<mutex> lockGuard(_mtx,std::adopt_lock);
        std::lock_guard<mutex> lockGuard2(_mtx2,std::adopt_lock);
        // ...
    }
void shared_print(string id, int value) {
        std::lock(_mtx,_mtx2);
        std::lock_guard<mutex> lockGuard(_mtx,std::adopt_lock);
        std::lock_guard<mutex> lockGuard2(_mtx2,std::adopt_lock);
        // ...
    }
```



```cpp
//多数情况下不需要同时lock(mtx, mtx2),
//通常lock一个完成相应任务释放掉，再lock另一个，核心是使用{}分割作用域 
void shared_print2(string id, int value) {
        {
        	std::lock_guard<mutex> lockGuard2(_mtx,std::adopt_lock);
            // ...
        }
        {
            std::lock_guard<mutex> lockGuard(_mtx2,std::adopt_lock);
        	// ...
        }
  }
```



```cpp
/*
1. Prefer locking single mutex
2. Avoid locking a mutex and then calling a user provided function.
3. Use std::lock() to lock more than one mutex
4. Lock the mutex in same order

Locking Granularity:
Fine-grained lock: protects small amount of data  细粒度
Coarse-grained lock: protects big amount of datal 粗粒度
*/
```



### 五、Unique Lock and Lazy Initialization

```cpp
void shared_print(string id, int value) {
        std::unique_lock<mutex> uniqueLock(_mtx, std::defer_lock);
        // ...

        uniqueLock.lock();
        _f << "From: " << id << ": " << value << endl;
        uniqueLock.unlock();

        uniqueLock.lock();
        // ...
        uniqueLock.unlock();
}
// 1、unique_lock() 可以多次 lock/unlock 域内的各种资源，需要互斥访问时加锁，其他操作不需要枷锁就不加锁，这是lock_guard() 无法做到的，lock_guard() 对一个作用域内全部加锁和解锁

// 2、unique_lock() 可以使用 std::move(...) 进行转移

// 3、unique_lock 缺点是重，如果更加关注效率可以采用lock_guard(),即lock/unlock)
```



```cpp
//并不是线程安全
//可能Thread A检查 f并没有locked，进入结构对文件进行加锁，当文件还没有被打开，Thread B执行到if判断，发现文件f没有打开，也对文件进行加锁，这样文件f就被打开了两次，不安全
void shared_print(string id, int value) {
        if(!_f.is_open()){
            std::unique_lock<mutex> locker(_mu_open);
            _f.open("log.txt");
        }
}

//这才是线程安全，对于判断文件是否打开操作也要加锁
void shared_print(string id, int value) {
    {
        std::unique_lock<mutex> locker(_mu_open);
        if(!_f.is_open()){
            _f.open("log.txt");
        }
    }
}

//比较麻烦，C++提供了另一种方式
std::once_flag _flag;
// ...
std::call_once(_flag,[&](){_f.open("log.txt");}
//保证lambda function只被call once 和只被一个Thread call，这种方式更加简单
```

unique_lock 对象同样也不负责管理 Mutex 对象的生命周期，unique_lock 对象只是简化了 Mutex 对象的上锁和解锁操作，方便线程对互斥量上锁，即在某个 unique_lock 对象的声明周期内，它所管理的锁对象会一直保持上锁状态；而 unique_lock 的生命周期结束之后，它所管理的锁对象会被解锁，这一点和 lock_guard 类似，但 unique_lock 给程序员提供了更多的自由



使用

```cpp
#include <condition_variable>
std::condition_variable cond;

cond.notify_one();	//only wakeup one thread
cond.notify_all();  //wakeup all the threads 如果程序需要唤醒不止一个进程
cond.wait(locker, <mostly lambda expression>);

// 使用nofify可以避免轮询浪费时间
```



````cpp
unique_lock<mutex> locker(mtx);
cond.wait(locker, []() { return !q.empty(); });	//spurious wake 虚假唤醒后发现 q是empty的继续sleep
// wait(unique_lock<mutex> & ,_Predicate)
````

```cpp
// 使用 condition_variable 可以让程序以固定的顺序执行
//用处是：synchronize the execution sequence of the threads
```



### 七、Future, Promise and async()

用于在主线程和子线程之间传递数据。

future，告诉主线程在未来给你传递数据   数据流向（child -> parent）

promise，告诉子线程承诺给你传递数据    数据流向（parent  -> child）

```cpp
// child pass data to parent
int factorial(int N) {
    int res = 1;
    for (int i = 1; i < N; ++i) {
        res += i;
    }
    return res;
}

int main() {
    std::future<int> fu = std::async(factorial, 4);
    int x = fu.get();
    cout << "x is :" << x << endl;

    return 0;
}
```



```cpp
std::future<int> fu = std::async(std::launch::async,factorial,4); // create another thread, new thread is borned

std::future<int> fu = std::async(std::launch::deferred,factorial,4); // not create a thread
// defer means, execution of this function until later on when the get() function is called

// so when the get() function is called, the factorial function will be executed in the same thread (important: in the same thread)

std::future<int> fu = std::async(std::launch::async | std::launch::deferred, factorial, 4); // default value

```



```cpp
std::promise<int> p;
std::future<int> f = p.get_future();

std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f));
p.set_value(4); // remember that you make a promise to pass a value to child thread in the future

//如果真的无法遵守承诺 pass a value, 就 set_exception()
p.set_exception(std::make_exception_ptr(std::runtime_error("Sorry, I really cannot pass a value")));
//Output:
terminate called after throwing an instance of 'std::runtime_error'
  what():  Sorry, I really cannot pass a value
```

```cpp
std::promise<int> p;
std::future<int> f = p.get_future();
std::shared_future<int> sf = f.share();//share it with multi Thread

std::future<int> fu = std::async(std::launch::async, factorial, sf);	// can pass by value
std::future<int> fu2 = std::async(std::launch::async, factorial, sf);
std::future<int> fu3 = std::async(std::launch::async, factorial, sf);
// ...10 Threads

p.set_value(4);


//shared_future is very convenient when you have a broadcast kind of communicate model
```



### 8: Using Callable Objects

```cpp

class A {
public:
    void f(int x, char c) {}
    long g(double x) { return 0; }
    int operator()(int N) { return 0; }

};

void foo(int x) {}

int main() {
    A a;
    std::thread t1(a, 6); 								//copy_of_a() in a different thread
    std::thread t2(std::ref(a), 6);						//a() in a different thread
    std::thread t3(A(), 6);								// create temp A, then temp A is move to thread t3
    std::thread t4([](int x) { return x * x; }, 6);		 //lambda function
    std::thread t5(foo, 7);
    std::thread t6(&A::f, a, 8, 'w');					//copy_of_a.f(8,'w') in a different thread
    std::thread t7(&A::f, &a, 8, 'w');					//copy_of_a.f(8,'w') in a different thread
    std::thread t8(std::move(a), 6);					// a() is no longer usable in main thread

    // 还有 std::bind() std::async std::call_once()都可以用来创建线程
    return 0;
}
```



### 9: packaged_task

```cpp
std::packaged_task<int(int)> t(factorial); 
t(6);	//always return void
int x = t.get_future().get(); //To get the t(6)'s return value
```

```cpp
    std::thread t1(factorial, 6);
    std::packaged_task<int(int)> t2(factorial);
    std::packaged_task<int(int)> t3(factorial, 6); //error, cannot pass another parameter like std::thread() 
    std::packaged_task<int(int)> t4(std::bind(factorial, 6)); // If we really need to pass parameter, use bind() function to bind the factorial function with its parameter and create a function object, then the function object is passed to the constructor of the packaged_task
```

```cpp
int main() {
    std::packaged_task<int()> t(std::bind(factorial, 6));	//cannot pass parameter, cause its already bound
    t(); 			//cannot pass parameter
    
    int x = t.get_future().get();
    cout << "packaged_task return: " << x << endl;

    return 0;
}
```

```cpp
// 使用packaged_task的意义是什么

int factorial(int N) {
    int res = 1;
    for (int i = N; i > 1; --i) {
        res += i;
    }
    cout << "result is: " << res << endl;
    return res;
}

int main() {
    // std::packaged_task<int()> t(std::bind(factorial, 6));
    auto t = std::bind(factorial,6);
    t(); //一般这里使用一个deque放进队列，等待另一个线程把它出队后来处理它，注意mutex & condition保证线程安全
    
	//if we just bind factorial and a interage, we cannot use get_future, this is the convenient of packaged_task
    int x = t.get_future().get();
    cout << "packaged_task return: " << x << endl; //crash

    return 0;
}
```



```cpp
/*
3 ways to get a future
1、-promise::get_future()
2、-packaged_task::get_future()
3、-async() return a future
*/ 
```



### 10: Review and Time Constrain

```cpp
sleep_for()
sleep_until()
wait_for()
wait_until()
```

