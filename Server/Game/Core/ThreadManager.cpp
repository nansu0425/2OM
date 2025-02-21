#include "Core/CommonPch.h"

namespace Game::Core
{
    ThreadManager::~ThreadManager()
    {
        Join();
    }

    ThreadManager::ThreadManager()
    {}

    ThreadManager& ThreadManager::GetInstance()
    {
        static std::unique_ptr<ThreadManager> pInstance(new ThreadManager());
        return *pInstance;
    }

    void ThreadManager::Join()
    {
        ThreadManager& instance = GetInstance();

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
