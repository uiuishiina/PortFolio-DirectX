#include "StaticDrawObjectContainer.h"

using namespace render::dx12::container;

///====================================================================
/// 初期化関数
///====================================================================

//@breif	=== 描画オブジェクト登録関数 ===
//@param	key_name	登録するキーの名前
//@param	object		登録するオブジェクト
//@return	登録の成否
[[nodiscard]] bool StaticDrawObjectContainer::register_draw_object(const std::string& key_name,
	 std::unique_ptr<render::dx12::drawobject::DrawObjectBase> object) {

	//	すでに同名で登録されているなら登録失敗
	auto hash = get_hash_key(key_name);
	if (hash.has_value()) {
		return false;
	}

	//  mapに登録
	auto new_hash = allocate_hash(key_name);
	object_map.emplace(new_hash, std::move(object));

	return true;
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@brief	=== 描画オブジェクト取得関数 ===
//@param	key	描画オブジェクトと紐づけたキー
//@return	描画オブジェクト参照
[[nodiscard]] render::dx12::drawobject::DrawObjectBase* StaticDrawObjectContainer::get_draw_object(UINT key)const noexcept {

	const auto it = object_map.find(key);
	if (it == object_map.end()) {
		return nullptr;
	}
	return it->second.get();
}

//@brief	=== 描画オブジェクト取得関数 ===
//@param	key	描画オブジェクトと紐づけたキー
//@return	描画オブジェクト参照
[[nodiscard]] render::dx12::drawobject::DrawObjectBase* StaticDrawObjectContainer::get_draw_object(const std::string& key_name)const noexcept {

	//  キーを取得
	auto hash = get_hash_key(key_name);
	if (!hash.has_value()) {
		return nullptr;
	}

	//  上の関数に処理を任せる
	return get_draw_object(hash.value());
}