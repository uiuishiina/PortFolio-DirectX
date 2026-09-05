#include "StaticDrawObjectContainer.h"

using namespace render::dx12::container;

/* ==================================================================== */
// Publicメンバー関数
/* ==================================================================== */

/// <summary>
/// 描画オブジェクト登録関数
/// </summary>
/// <param name="key">登録したい倫理側のキー</param>
/// <param name="object">登録したいオブジェクト</param>
/// <returns>登録の成否</returns>
[[nodiscard]] bool StaticDrawObjectContainer::register_draw_object(const handle::DrawObjectKey key,
	 std::unique_ptr<render::dx12::drawobject::DrawObjectBase> object) {

	//  mapに登録
	return add_value(key, std::move(object));
}