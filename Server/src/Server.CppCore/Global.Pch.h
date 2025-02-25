#pragma once

/*---------------*
 *    Windows    *
 *---------------*/

#include <Windows.h>

/*----------------*
 *    Standard    *
 *----------------*/

#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
#include <memory>
#include <string>
#include <string_view>
#include <sstream>
#include <shared_mutex>
#include <chrono>
#include <utility>
#include <cassert>
#include <future>

/*----------------------*
 *    Server.CppCore    *
 *----------------------*/

#include "Server.CppCore/Thread.DeadlockDetector.h"
#include "Server.CppCore/Thread.LockGuard.h"
#include "Server.CppCore/Global.Macro.h"
#include "Server.CppCore/Thread.TlsGuard.h"
#include "Server.CppCore/Thread.Manager.h"
