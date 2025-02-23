#pragma once

namespace Server::CppCore::Tests::Thread
{
    TEST_CLASS(ManagerTest)
    {
    public:
        TEST_METHOD(TestManager);

    private:
        void IncreaseSharedResource();
        void LaunchCallbacks();

    private:
        std::vector<std::thread> _threads;
        CppCore::Concurrency::LockHolder _lockHolder;
        uint32_t _sharedResource = 0;
        const uint32_t _incrementCount = 100'000;

    };
}
