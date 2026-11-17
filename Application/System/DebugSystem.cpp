#include "DebugSystem.h"

#include"Debug/HRESULTToString.h"

std::string App::DebugSystem::to_HRESULT(HRESULT hr)
{
    return HandyItems::Debug::hresult_to_string(hr);
}
