
/* ========== Includeファイル ========== */

#include "DirectXContext.h"

using namespace DirectX;

/* ========== Publicメンバー関数 ========== */

/// <summary>
/// コンストラクタ
/// </summary>
DirectXContext::DirectXContext() {

	dxgi_.register_unique(std::make_unique<ClassObject::DXGI>());
	device_.register_unique(std::make_unique<ClassObject::Device>());

}

/// <summary>
/// デストラクタ
/// </summary>
DirectXContext::~DirectXContext() = default;