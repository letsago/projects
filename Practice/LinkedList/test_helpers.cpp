#include "headers/test_helpers.h"

uint32_t UnitTests::s_refCounters = 0;
std::vector<std::pair<std::string, bool>> UnitTests::s_summary;
typemap & UnitTests::s_registry() { static typemap impl; return impl; }

MemoryTracker& getTracker()
{
    static MemoryTracker s_tracker;
    return s_tracker;
}

void* operator new(size_t size)
{
    void* p = malloc(size);
    getTracker().addAllocation(p, size);
    return p;
}

void operator delete(void* p) noexcept
{
    getTracker().freeAllocations(p);
    free(p);
}