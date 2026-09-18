
#include"../Application/Application.h"

namespace {

	/* ========== Publicメンバー変数 ========== */

	/* ========== Publicメンバー関数 ========== */

	/* ========== Privateメンバー変数 ========== */

	/* ========== Privateメンバー関数 ========== */

	/* ========== Includeファイル ========== */

	/* ===== 初期化関数 ===== */

	/* ===== 実行関数 ===== */
}

/// <summary>
/// エントリー関数
/// </summary>
/// <returns>正常終了なら [ 0 ],エラーなら [ 1 ]</returns>
int main() {

	App::Application App{};

	if (!App.initialize_app()) {
		return 1;
	}
	else {
		App.run_app();
	}

	return 0;
}