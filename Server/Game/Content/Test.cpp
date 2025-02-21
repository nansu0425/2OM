#include "Content/CommonPch.h"
#include "Content/Test.h"

namespace Game::Content
{
    void TestFunction()
    {
        while (true)
        {
            std::cout << "Thread Id: " << Core::ThreadLocalGuard::GetThreadId() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}
