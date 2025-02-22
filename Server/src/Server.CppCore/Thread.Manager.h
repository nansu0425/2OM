#pragma once

namespace Server::CppCore::Thread
{
    /*---------------*
     *    Manager    *
     *---------------*/

    class Manager
    {
    public:
        Manager(const Manager&) = delete;
        Manager& operator=(const Manager&) = delete;
        ~Manager();

        template<typename TCallback>
        static void Launch(TCallback&& callback);
        static void Join();

    private:
        // 싱글톤 패턴
        Manager();
        static Manager& GetInstance();

    private:
        TlsGuard _tlsGuard;
        Concurrency::LockHolder _lockHolder;
        std::vector<std::thread> _threads;

    };

    template<typename TCallback>
    inline void Manager::Launch(TCallback&& callback)
    {
        Manager& instance = GetInstance();

        Concurrency::ExclusiveLockGuard lockGuard(instance._lockHolder);

        instance._threads.emplace_back([callback = std::forward<TCallback>(callback)]()
                                       {
                                           TlsGuard tlsGuard;
                                           callback();
                                       });
    }
}
