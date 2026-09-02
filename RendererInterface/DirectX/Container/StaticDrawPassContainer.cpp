#include "StaticDrawPassContainer.h"

using namespace render::dx12::container;

///====================================================================
/// 初期化処理
///====================================================================

//@breif	=== 描画パス作成関数 ===
//@param	key_name	登録するキーの名前
//@param	pass		登録するパスクラスインスタンス
//@return	作成の成否
[[nodiscard]] bool StaticDrawPassContainer::register_draw_pass(const handle::PassKey& key, std::unique_ptr<pass::PassBase> pass) {

	//	mapに登録
	return add_value(key, std::move(pass));
}