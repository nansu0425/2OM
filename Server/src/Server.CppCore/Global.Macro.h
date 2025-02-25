#pragma once

/*--------------*
 *    Thread    *
 *--------------*/

#define SERVER_CPPCORE_LOCK_ARRAY(count)                    Server::CppCore::Thread::Lock _locks[count];
#define SERVER_CPPCORE_LOCK                                 SERVER_CPPCORE_LOCK_ARRAY(1)
#define SERVER_CPPCORE_LOCK_GUARD_INDEX(index, target)      Server::CppCore::Thread::LockGuard guard##index(target._locks[index], typeid(&target).name());
#define SERVER_CPPCORE_LOCK_GUARD_TARGET(target)            SERVER_CPPCORE_LOCK_GUARD_INDEX(0, target)
#define SERVER_CPPCORE_LOCK_GUARD                           SERVER_CPPCORE_LOCK_GUARD_TARGET((*this))
