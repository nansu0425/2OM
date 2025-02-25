#include "Server.CppCore/Global.Pch.h"

namespace Server::CppCore::Thread
{
    void DeadlockDetector::PushLock(LockName name)
    {
        DeadlockDetector& instance = GetInstance();
        std::stack<LockId>& lockStack = TlsGuard::GetLockStack();
        std::lock_guard guard(instance._lock);

        // name에 해당하는 락의 id
        LockId id = 0;

        auto pNameToId = instance._nameToId.find(name);

        // name에 해당하는 id가 없는 경우 새로운 id를 발급한다
        if (pNameToId == instance._nameToId.end())
        {
            id = static_cast<uint32_t>(instance._nameToId.size());
            instance._nameToId[name] = id;
            instance._idToName[id] = name;
        }
        // name에 해당하는 id가 있는 경우 가져온다
        else
        {
            id = pNameToId->second;
        }

        // 이전에 잠근 락이 있는 경우
        if (lockStack.empty() == false)
        {
            const LockId lastId = lockStack.top();

            // 마지막으로 잠근 락을 다시 잠그려고 한 경우 데드락 발생
            if (lastId == id)
            {
                instance.OnDeadlockDetected(id);
            }
            else
            {
                // 마지막으로 잠근 락의 다음 잠금 순서 락들
                NextOrderLocks& nextOrderLocks = instance._lockOrderGraph[lastId];

                // 현재 락이 다음 잠금 순서 존재하지 않으면 다음 잠금 순서에 추가 후 잠금 순서 사이클 검사
                if (nextOrderLocks.find(id) == nextOrderLocks.end())
                {
                    nextOrderLocks.insert(id);
                    instance.CheckLockOrderCycle();
                }
            }

        }

        // 락을 스택에 저장
        lockStack.push(id);
    }

    void DeadlockDetector::PopLock(LockName name)
    {
        DeadlockDetector& instance = GetInstance();
        std::stack<LockId>& lockStack = TlsGuard::GetLockStack();
        std::lock_guard guard(instance._lock);

        // 잠근 락이 없는데 락을 해제하려는 경우 프로그램 즉시 중단
        if (lockStack.empty())
        {
            std::abort();
        }

        LockId id = instance._nameToId[name];

        // 해제하려는 락이 마지막으로 잠근 락이 아니라면 프로그램 즉시 중단
        if (id != lockStack.top())
        {
            std::abort();
        }

        // 마지막으로 잠근 락을 스택에서 제거
        lockStack.pop();
    }

    DeadlockDetector& DeadlockDetector::GetInstance()
    {
        static std::unique_ptr<DeadlockDetector> pInstance(new DeadlockDetector());
        return *pInstance;
    }

    void DeadlockDetector::CheckLockOrderCycle()
    {
        const size_t numberOfTrackedLocks = _nameToId.size();

        _lockToDiscoveredOrder = std::vector<DiscoveredOrder>(numberOfTrackedLocks, -1);
        _nextDiscoveredOrder = 0;
        _lockToDfsCompleteFlag = std::vector<bool>(numberOfTrackedLocks, false);
        _childToParent = std::vector<LockId>(numberOfTrackedLocks, -1);

        // 잠금 순서 그래프의 모든 락에 대해 Dfs 수행
        for (LockId id = 0; id < numberOfTrackedLocks; ++id)
        {
            StartDfs(id);
        }

        _lockToDiscoveredOrder.clear();
        _nextDiscoveredOrder = 0;
        _lockToDfsCompleteFlag.clear();
        _childToParent.clear();
    }

    void DeadlockDetector::StartDfs(LockId id)
    {
        // 이미 발견된 락인 경우 리턴
        if (_lockToDiscoveredOrder[id] != -1)
        {
            return;
        }

        // 발견 순서를 기록
        _lockToDiscoveredOrder[id] = _nextDiscoveredOrder++;

        auto pLockToNextOrderLocks = _lockOrderGraph.find(id);

        // 현재 락의 다음 순서 락이 없는 경우에 dfs 종료
        if (pLockToNextOrderLocks == _lockOrderGraph.end())
        {
            _lockToDfsCompleteFlag[id] = true;
            return;
        }

        NextOrderLocks& nextOrderLocks = pLockToNextOrderLocks->second;

        for (const LockId nexOrderId : nextOrderLocks)
        {
            // 다음 순서 락이 이전에 탐색한 적 없는 락인 경우 dfs 수행
            if (_lockToDiscoveredOrder[nexOrderId] == -1)
            {
                _childToParent[nexOrderId] = id;
                StartDfs(nexOrderId);

                continue;
            }

            // 현재 락과 다음 순서 락의 간선이 순방향인 경우 교착 상태 위험이 없다
            if (_lockToDiscoveredOrder[id] < _lockToDiscoveredOrder[nexOrderId])
            {
                continue;
            }

            // 다음 순서 락의 dfs가 아직 진행 중인 경우 사이클이 존재하는 것이므로 교착 상태 위험이 생긴다
            if (_lockToDfsCompleteFlag[nexOrderId] == false)
            {
                OnDeadlockDetected(id, nexOrderId);
            }
        }

        // 현재 락의 dfs 완료 처리
        _lockToDfsCompleteFlag[id] = true;
    }

    void DeadlockDetector::OnDeadlockDetected(LockId id, LockId nextOrderId)
    {
        std::cout << "Deadlock detected: ";

        if (nextOrderId == -1)
        {
            std::cout << _idToName[id] << " <- " << _idToName[id];

            std::abort();
        }

        std::cout << _idToName[nextOrderId] << " <- " << _idToName[id];

        // 락 사이클의 잠금 순서를 역순으로 출력
        while (true)
        {
            std::cout << " <- " << _idToName[_childToParent[id]];
            id = _childToParent[id];

            if (id == nextOrderId)
            {
                break;
            }
        }

        std::abort();
    }
}
