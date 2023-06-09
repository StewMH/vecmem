/*
 * VecMem project, part of the ACTS project (R&D line)
 *
 * (c) 2021-2022 CERN for the benefit of the ACTS project
 *
 * Mozilla Public License Version 2.0
 */

// Local include(s).
#include "vecmem/memory/arena_memory_resource.hpp"

#include "alignment.hpp"
#include "arena.hpp"
#include "vecmem/utils/debug.hpp"

namespace vecmem {

arena_memory_resource::arena_memory_resource(memory_resource& upstream,
                                             std::size_t initial_size,
                                             std::size_t maximum_size)
    : m_arena(std::make_unique<details::arena>(initial_size, maximum_size,
                                               upstream)) {}

arena_memory_resource::~arena_memory_resource() {}

void* arena_memory_resource::do_allocate(std::size_t bytes, std::size_t) {

    if (bytes == 0) {
        return nullptr;
    }

    void* ptr = m_arena->allocate(details::align_up(bytes));
    VECMEM_DEBUG_MSG(2, "Allocated %lu bytes at %p", bytes, ptr);
    return ptr;
}

void arena_memory_resource::do_deallocate(void* p, std::size_t bytes,
                                          std::size_t) {

    if (p == nullptr) {
        return;
    }

    VECMEM_DEBUG_MSG(2, "De-allocating memory at %p", p);
    m_arena->deallocate(p, details::align_up(bytes));
}

}  // namespace vecmem
