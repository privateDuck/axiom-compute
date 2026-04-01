If your architecture absolutely mandates a single instance (for example, you are wrapping a massive Machine Learning model, a physics engine, or a hardware-bound resource) and the operations are highly computationally expensive, you must shift your design from a **synchronous API** to an **asynchronous command queue**.

If you simply put a standard `std::mutex` over your singleton and multiple Dart Isolates try to call it, the first isolate will lock the C++ execution, and the subsequent isolates will completely freeze while waiting for the lock. This destroys the asynchronous nature of Dart.

To do this safely, you need to combine a thread-safe C++ singleton with Dart's asynchronous native ports (`Dart_PostCObject`).

Here is the robust, industry-standard architecture for this exact scenario.

### 1. The C++ Architecture: The Worker Queue
Instead of Dart calling a C++ function and waiting for the expensive result, Dart should simply hand off the work to C++ and immediately return. The C++ singleton manages a dedicated background thread to process these requests one by one.

```cpp
// singleton_engine.h (Internal C++ Code)
#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>
#include <functional>

class ComputeEngine {
public:
    // Meyer's Singleton: Thread-safe in C++11 and later
    static ComputeEngine& getInstance() {
        static ComputeEngine instance;
        return instance;
    }

    // Delete copy/move constructors to strictly enforce single instance
    ComputeEngine(ComputeEngine const&) = delete;
    void operator=(ComputeEngine const&) = delete;

    // Dart calls this. It returns instantly.
    void enqueueTask(int taskId, intptr_t dartPortId);

private:
    ComputeEngine();
    ~ComputeEngine();
    
    void workerLoop(); // The heavy lifting runs here

    std::queue<std::pair<int, intptr_t>> taskQueue;
    std::mutex queueMutex;
    std::condition_variable cv;
    std::thread workerThread;
    bool stopRequested = false;
};
```

### 2. The C API Layer: Enforcing the Singleton
Your C API should no longer have `create_context()`. The API implicitly targets the singleton.

```cpp
// api.cpp
#include "singleton_engine.h"
#include "dart_api_dl.h" // Required for asynchronous callbacks to Dart

extern "C" {
    // Optional: Call once at app startup to initialize Dart's DL API
    intptr_t init_native_api(void* data) {
        return Dart_InitializeApiDL(data);
    }

    // Dart sends a task ID and a Port ID to receive the answer later
    void execute_heavy_computation(int task_id, intptr_t dart_port_id) {
        // We route the request directly to the singleton instance
        ComputeEngine::getInstance().enqueueTask(task_id, dart_port_id);
    }
}
```

### 3. How C++ Talks Back to Dart (The Async Handshake)
When the C++ background thread finishes the expensive computation, it uses `Dart_PostCObject` to send the result back to the specific Isolate that requested it.

```cpp
void ComputeEngine::workerLoop() {
    while (true) {
        std::pair<int, intptr_t> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            cv.wait(lock, [this]{ return !taskQueue.empty() || stopRequested; });
            
            if (stopRequested && taskQueue.empty()) return;
            
            task = taskQueue.front();
            taskQueue.pop();
        }

        // --- DO EXPENSIVE COMPUTATION HERE ---
        // e.g., double result = run_massive_algorithm();
        
        // --- SEND RESULT BACK TO DART ---
        Dart_CObject dartObject;
        dartObject.type = Dart_CObject_kInt64; // Or string, array, etc.
        dartObject.value.as_int64 = 42; /* The result */

        // This safely crosses the C++/Dart boundary asynchronously
        Dart_PostCObject_DL(task.second, &dartObject); 
    }
}
```

### Why this is the safest approach:
* **True Singleton:** C++ strictly enforces `ComputeEngine` as a single instance. Dart literally cannot instantiate a second one because there is no API exposed to do so.
* **Non-Blocking:** If Isolate A and Isolate B both call `execute_heavy_computation()` at the exact same millisecond, the C++ layer just pushes both requests to the `std::queue` (which takes microseconds) and returns control to Dart immediately.
* **Crash Prevention:** You avoid Dart isolates violently terminating the C++ process because the C++ worker thread acts as an independent buffer.

If multiple Dart isolates request these expensive operations at once, do you want the C++ queue to process them strictly First-In-First-Out (FIFO), or do you need a way for newer requests to cancel older, pending operations to save CPU cycles?