#include "Server.World/Global.Pch.h"
#include "Server.Content/Logic.Test.h"

using namespace Server;

int main()
{
    for (int32_t i = 0; i < 5; ++i)
    {
        CppCore::Thread::Manager::Launch(Content::Logic::Test);
    }

	return 0;
}
