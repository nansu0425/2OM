#pragma once

namespace Server::CppCore::Thread
{
    /*------------------------*
     *    DeadlockDetector    *
     *------------------------*/

    class DeadlockDetector
    {
    public:
        using Lock = std::shared_mutex;
        using LockName = std::string_view;
        using LockId = int32_t;
        using NextOrderLocks = std::unordered_set<LockId>;
        using DiscoveredOrder = int32_t;

    public:
        // 락 잠금을 시도할 때 TlsGuard의 락 스택에 락을 추가
        static void PushLock(LockName name);
        // 락 해제를 시도할 때 TlsGuard의 락 스택에서 락을 제거
        static void PopLock(LockName name);

    private:
        DeadlockDetector() = default;
        static DeadlockDetector& GetInstance();

        void CheckLockOrderCycle();
        void StartDfs(LockId currentId);
        void OnDeadlockDetected(LockId currnetId, LockId nextOrderId = -1);

    private:
        Lock _lock;
        std::unordered_map<LockName, LockId> _nameToId;
        std::unordered_map<LockId, LockName> _idToName;
        std::unordered_map<LockId, NextOrderLocks> _lockOrderGraph;

        std::vector<DiscoveredOrder> _lockToDiscoveredOrder;
        DiscoveredOrder _nextDiscoveredOrder = 0;
        std::vector<bool> _lockToDfsCompleteFlag;
        std::vector<LockId> _childToParent;

    };
}
