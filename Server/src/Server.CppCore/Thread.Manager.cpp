#include "Server.CppCore/Global.Pch.h"

namespace Server::CppCore::Thread
{
    Manager& Manager::GetInstance()
    {
        static std::unique_ptr<Manager> pInstance(new Manager());
        return *pInstance;
    }

    Manager::~Manager()
    {
        Join();
    }

    void Manager::Join()
    {
        Manager& instance = GetInstance();

        std::lock_guard lock(instance._lock);

        // _threadPairs에 저장된 모든 스레드를 join
        for (auto& pair : instance._threadPairs)
        {
            if (pair.second.joinable())
            {
                pair.second.join();
            }
        }

        instance._threadPairs.clear();
    }
}
