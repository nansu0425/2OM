#include "Server.CppCore.Tests/Global.Pch.h"
#include "Server.CppCore.Tests/Concurrency.LockTest.h"

namespace Server::CppCore::Tests::Concurrency
{
    void LockTest::TestLock()
    {
        _sharedResource = 0;
        const uint32_t targetResourceValue = 2'000'000;

        std::vector<std::thread> readers;
        const uint32_t numberOfReaders = 2;
        bool shouldContinueReading = true;

        for (uint32_t i = 0; i < numberOfReaders; ++i)
        {
            readers.emplace_back([this, &shouldContinueReading, targetResourceValue]()
                                 {
                                     while (shouldContinueReading)
                                     {
                                         Assert::IsFalse(targetResourceValue < ReadSharedResource());
                                     }
                                 });
        }

        std::vector<std::thread> writers;
        const uint32_t numberOfWriters = 2;

        for (uint32_t i = 0; i < numberOfWriters; ++i)
        {
            writers.emplace_back([this, numberOfWriters, targetResourceValue]()
                                 {
                                     for (int i = 0; i < targetResourceValue / numberOfWriters; ++i)
                                     {
                                         WriteSharedResource();
                                     }
                                 });
        }
        
        for (std::thread& writer : writers)
        {
            if (writer.joinable())
            {
                writer.join();
            }
        }

        shouldContinueReading = false;

        for (std::thread& reader : readers)
        {
            if (reader.joinable())
            {
                reader.join();
            }
        }

        Assert::IsTrue(ReadSharedResource() == targetResourceValue);
    }

    void LockTest::WriteSharedResource()
    {
        CppCore::Concurrency::ExclusiveLockGuard lock(_lockHolder);
        ++_sharedResource;
    }

    uint32_t LockTest::ReadSharedResource()
    {
        CppCore::Concurrency::SharedLockGuard lock(_lockHolder);
        return _sharedResource;
    }

}
