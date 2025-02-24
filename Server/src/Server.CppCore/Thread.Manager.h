#pragma once

namespace Server::CppCore::Thread
{
    /*---------------*
     *    Manager    *
     *---------------*/

    class Manager
    {
    public:
        ~Manager();
        Manager(const Manager&) = delete;
        Manager& operator=(const Manager&) = delete;

        template<typename TFunction>
        static void Launch(TFunction&& function);
        static void Join();

    private:
        // 싱글톤 패턴
        Manager() = default;
        static Manager& GetInstance();

    private:
        TlsGuard _tlsGuard;
        std::shared_mutex _lock;
        std::unordered_map<uint32_t, std::thread> _threadPairs;

    };

    template<typename TFunction>
    inline void Manager::Launch(TFunction&& function)
    {
        Manager& instance = GetInstance();

        // threadId를 promise로 전달 후 future로 받음
        std::promise<uint32_t> threadIdPromise;
        std::future threadIdFuture = threadIdPromise.get_future();

        // function을 호출하는 스레드 생성
        std::thread thread = std::thread([function = std::forward<TFunction>(function), &threadIdPromise]()
                                         {
                                             TlsGuard tlsGuard;
                                             threadIdPromise.set_value(tlsGuard.GetThreadId());
                                         
                                             function();
                                         });

        std::lock_guard lock(instance._lock);

        // threadId를 키로 스레드를 저장
        instance._threadPairs.emplace(threadIdFuture.get(), std::move(thread));
    }
}
