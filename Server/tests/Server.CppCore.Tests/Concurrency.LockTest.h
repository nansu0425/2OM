#pragma once

namespace Server::CppCore::Tests::Concurrency
{
    TEST_CLASS(LockTest)
    {
    public:
        TEST_METHOD(TestLock);

    private:
        void WriteSharedResource();
        uint32_t ReadSharedResource();

    private:
        uint32_t _sharedResource = 0;
        CppCore::Concurrency::LockHolder _lockHolder;

    };
}
