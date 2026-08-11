#include"StaticBufferContainer.h"

using namespace render::dx12::container;

[[nodiscard]] render::dx12::object::StaticBufferResource* StaticBufferContainer::get_resource(UINT key)const noexcept {

    const auto it = buffer_map.find(key);
    if (it == buffer_map.end()) {
        return nullptr;
    }
    return it->second.get();
}