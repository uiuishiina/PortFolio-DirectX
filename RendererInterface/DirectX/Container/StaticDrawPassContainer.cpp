#include "StaticDrawPassContainer.h"

using namespace render::dx12::container;

///====================================================================
/// 初期化処理
///====================================================================

//@breif	=== 描画パス作成関数 ===
//@param	key_name	登録するキーの名前
//@param	desc		作成する描画パス設定
//@return	作成の成否
[[nodiscard]] bool StaticDrawPassContainer::create_draw_pass(const std::string& key_name, render::dx12::desc::DrawPassDesc& desc) {

	//	すでに同名で登録されているなら登録失敗
	auto hash = get_hash_key(key_name);
	if (hash.has_value()) {
		return false;
	}

	//	インスタンス生成
	auto pass = std::make_unique<pass::DrawPass>();
	if (!pass->initialize_pass(desc)) {
		return false;
	}

	//  mapに登録
	auto new_hash = allocate_hash(key_name);
	pass_map.emplace(new_hash, std::move(pass));

	return true;
}

///====================================================================
/// 実行時処理関数
///====================================================================

//@breif == = 描画パス呼び出し関数 == =
//@details	無い場合は何もなし
//@param	key		呼び出す描画パスと紐づけたキー
//@param	resource	描画リソース
void StaticDrawPassContainer::apply_draw_pass(UINT key, resources::DrawResources& resource)const noexcept {

	const auto it = pass_map.find(key);
	if (it == pass_map.end()) {
		return;
	}

	it->second->apply(resource);
}

//@breif	=== 描画パス呼び出しオーバーロード関数 ===
//@details	無い場合は何もなし
//@param	key_name	呼び出す描画パスと紐づけたキーの名前
//@param	resource	描画リソース
void StaticDrawPassContainer::apply_draw_pass(const std::string& key_name, resources::DrawResources& resource)const noexcept {

	//  キーを取得
	auto hash = get_hash_key(key_name);
	if (!hash.has_value()) {
		return;
	}

	//	上の関数に処理を任せる
	apply_draw_pass(hash.value(), resource);
}