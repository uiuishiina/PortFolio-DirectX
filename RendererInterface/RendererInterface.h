#pragma once
#include"../windowInterface/windowInterface.h"
#include"../Application/SharedData/ApplicationSharedData.h"
#include"NonMovable.h"

///====================================================================
/// RendererInterface 基底クラス
///====================================================================

//@brief	=== 描画機能インターフェースクラス ===
class RendererInterface : public NonMovableBase
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	RendererInterface() = default;
	virtual ~RendererInterface() = default;

	///====================================================================
	/// Public メンバー関数
	///====================================================================

	//@brief	=== 描画機能作成関数 ===
	//@param	window			ウィンドウインターフェース
	//@param	shared_datas	
	//@details	作成したウィンドウに描画するため引数で参照を渡す
	//@return	作成の成否
	virtual [[nodiscard]] bool create_renderer(windowInterface* window, sharedData::ApplicationSharedData* shared_datas) = 0;

	//@brief	=== 描画更新関数 ===
	//@details	毎フレーム更新される想定
	virtual void update_renderer() = 0;

	//@brief	=== 描画機能終了処理関数 ===
	//@details	描画機能破棄前最終処理(非同期処理の待機など)をするための関数
	virtual void end_renderer() = 0;

protected:
	///====================================================================
	/// Protected メンバー関数
	///====================================================================

	//@brief	=== 描画更新前関数 ===
	//@details	描画機能を更新する際に先に処理する必要があるものを呼び出す関数
	virtual void begin_update_renderer() = 0;

	//@brief	=== 描画更新後関数 ===
	//@details	描画機能を更新した後に処理する必要があるものを呼び出す関数
	virtual void end_update_renderer() = 0;

	///====================================================================
	/// Protected メンバー変数
	///====================================================================

	sharedData::ApplicationSharedData* shared_datas{};

};