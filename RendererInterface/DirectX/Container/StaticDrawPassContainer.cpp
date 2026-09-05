#include "StaticDrawPassContainer.h"

using namespace render::dx12::container;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/// <summary>
/// 描画パス作成関数
/// </summary>
/// <param name="key">登録するキーの名前</param>
/// <param name="pass">登録するパスクラスインスタンス</param>
/// <returns>作成の成否</returns>
[[nodiscard]] bool StaticDrawPassContainer::register_draw_pass(const handle::PassKey& key, std::unique_ptr<pass::PassBase> pass) {

	//	mapに登録
	return add_value(key, std::move(pass));
}