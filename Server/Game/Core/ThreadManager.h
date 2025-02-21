#pragma once

namespace Game::Core
{
    /*---------------------*
     *    ThreadManager    *
     *---------------------*/

    class ThreadManager
    {
    public:
        ThreadManager(const ThreadManager&) = delete;
        ThreadManager& operator=(const ThreadManager&) = delete;
        ~ThreadManager();

        template<typename TCallback>
        static void Launch(TCallback&& callback);
        static void Join();

    private:
        // 싱글톤 패턴
        ThreadManager();
        static ThreadManager& GetInstance();

    private:
        ThreadLocalGuard _threadLocalGuard;
        std::mutex _mutex;
        std::vector<std::thread> _threads;

    };

    template<typename TCallback>
    inline void ThreadManager::Launch(TCallback&& callback)
    {
        ThreadManager& instance = GetInstance();

        std::lock_guard<std::mutex> lockGuard(instance._mutex);

        instance._threads.emplace_back([callback = std::forward<TCallback>(callback)]()
                                       {
                                           ThreadLocalGuard threadLocalGuard;
                                           callback();
                                       });
    }
}
