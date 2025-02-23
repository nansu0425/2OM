#include "Server.CppCore.Tests/Global.Pch.h"
#include "Server.CppCore.Tests/Thread.ManagerTest.h"

namespace Server::CppCore::Tests::Thread
{
    void ManagerTest::TestManager()
    {
        for (uint32_t i = 0; i < 10; ++i)
        {
            // Thread::Manager가 콜백을 실행시키는 스레드 생성
            _threads.emplace_back([this]()
                                  {
                                      LaunchCallbacks();
                                  });
        }

        // 모든 스레드가 종료될 때까지 대기
        for (std::thread& thread : _threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }

        CppCore::Thread::Manager::Join();

        // 공유 자원이 예상대로 증가했는지 확인
        Assert::AreEqual(_incrementCount * 10 * 10, _sharedResource);
    }

    void ManagerTest::IncreaseSharedResource()
    {
        CppCore::Concurrency::ExclusiveLockGuard lockGuard(_lockHolder);
        ++_sharedResource;
    }

    void ManagerTest::LaunchCallbacks()
    {
        for (uint32_t i = 0; i < 10; ++i)
        {
            // 공유 자원을 증가시키는 콜백을 실행
            CppCore::Thread::Manager::Launch([this]()
                                             {
                                                 for (uint32_t i = 0; i < _incrementCount; ++i)
                                                 {
                                                     IncreaseSharedResource();
                                                 }
                                             });
        }
    }

}
