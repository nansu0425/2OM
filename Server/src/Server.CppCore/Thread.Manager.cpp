#include "Server.CppCore/Global.Pch.h"

namespace Server::CppCore::Thread
{
    Manager& Manager::GetInstance()
    {
        static std::unique_ptr<Manager> pInstance(new Manager());
        return *pInstance;
    }

    void Manager::Join()
    {
        Manager& instance = GetInstance();

        SERVER_CPPCORE_LOCK_GUARD_TARGET(instance);

        // 모든 스레드를 join
        for (auto& idToThread : instance._idToThreadPairs)
        {
            if (idToThread.second.joinable())
            {
                idToThread.second.join();
            }
        }

        instance._idToThreadPairs.clear();
    }
}
