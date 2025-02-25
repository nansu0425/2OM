#include "Server.World/Global.Pch.h"
#include "Server.Content/Logic.Deadlock.h"

using namespace Server;

int main()
{
    Content::Logic::A a;
    Content::Logic::B b;
    Content::Logic::C c;

    Content::Logic::RunDeadlockThreads(a, b, c);

    CppCore::Thread::Manager::Join();

	return 0;
}
