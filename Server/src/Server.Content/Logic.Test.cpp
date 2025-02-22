#include "Server.Content/Global.Pch.h"
#include "Server.Content/Logic.Test.h"

namespace Server::Content::Logic
{
    void Test()
    {
        while (true)
        {
            std::cout << "Thread Id: " << CppCore::Thread::TlsGuard::GetThreadId() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}
