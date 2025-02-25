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

        template<typename TFunction>
        static void Launch(TFunction&& function);
        static void Join();

    private:
        // 싱글톤 패턴
        Manager() = default;
        static Manager& GetInstance();

    private:
        SERVER_CPPCORE_LOCK;
        Lock _lock;
        TlsGuard _tlsGuard;
        std::unordered_map<TlsGuard::ThreadId, std::thread> _idToThreadPairs;

    };

    template<typename TFunction>
    inline void Manager::Launch(TFunction&& function)
    {
        Manager& instance = GetInstance();

        // threadId를 promise로 전달 후 future로 받음
        std::promise<TlsGuard::ThreadId> threadIdPromise;
        std::future threadIdFuture = threadIdPromise.get_future();

        // function을 호출하는 스레드 생성
        std::thread thread = std::thread([function = std::forward<TFunction>(function), &threadIdPromise]()
                                         {
                                             TlsGuard tlsGuard;
                                             threadIdPromise.set_value(tlsGuard.GetThreadId());
                                         
                                             function();
                                         });

        SERVER_CPPCORE_LOCK_GUARD_TARGET(instance);

        // threadId를 키로 스레드를 저장
        instance._idToThreadPairs.emplace(threadIdFuture.get(), std::move(thread));
    }
}
