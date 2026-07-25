#include"../HashAllocator.h"
#include "StaticContainerBase.h"

///====================================================================
/// 初期化関数
///====================================================================

//@brief	=== コンストラクタ ===
StaticContainerBase::StaticContainerBase() {
	hash_allocator = std::make_unique<HashAllocator>();
}

//@brief	=== デストラクタ ===
StaticContainerBase::~StaticContainerBase() = default;

///====================================================================
/// 実行時処理関数群
///====================================================================

