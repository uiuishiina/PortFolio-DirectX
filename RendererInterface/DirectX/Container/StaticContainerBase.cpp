#include"../HashAllocator.h"
#include "StaticContainerBase.h"

using namespace render::dx12::container;

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

//@brief	=== ハッシュキー取得関数 ===
//@param	key_name	登録したキーの名前
//@return	ハッシュキー...登録されてないなら [ std::nullopt ] を返す
[[nodiscard]] std::optional<UINT> StaticContainerBase::get_hash_key(const std::string& key_name)const noexcept {

    //  ハッシュキー取得
    auto hash = hash_allocator->get_hash(key_name);
    if (!hash.has_value()) {
        return std::nullopt;
    }
    return hash.value();
}

//@brief	=== ハッシュキー取得関数 ===
//@param	key	登録するキーネーム
//@return	登録したキー...登録済みなら登録してあるキーを返す
[[nodiscard]] UINT StaticContainerBase::allocate_hash(const std::string& key) {

    //  ハッシュキー作成
    return hash_allocator->allocate_hash(key);
}