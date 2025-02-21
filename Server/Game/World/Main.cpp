#include "World/CommonPch.h"
#include "Content/Test.h"

using namespace Game;

int main()
{
    for (int32_t i = 0; i < 5; ++i)
    {
        Core::ThreadManager::Launch(Content::TestFunction);
    }

	return 0;
}
