#include "Server.CppCore/Global.Pch.h"

namespace Server::CppCore::Thread
{
    Manager::~Manager()
    {
        Join();
    }

    Manager::Manager()
    {}

    Manager& Manager::GetInstance()
    {
        static std::unique_ptr<Manager> pInstance(new Manager());
        return *pInstance;
    }

    void Manager::Join()
    {
        Manager& instance = GetInstance();

        for (std::thread& thread : instance._threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }

        instance._threads.clear();
    }
}
