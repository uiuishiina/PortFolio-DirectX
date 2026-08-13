#pragma once
#include"RendererInterface.h"
#include<memory>
#include<vector>
#include<string>

///====================================================================
/// UINT互換typeof
///====================================================================

typedef unsigned int        UINT;
typedef unsigned __int64    UINT64;

///====================================================================
/// DirectXオブジェクトクラス前方宣言
///====================================================================

namespace render {

	namespace dx12 {

		class DirectXRendererContext;

	};
};

///====================================================================
/// DirectXRenderer クラス
///====================================================================

//@brief	=== DirectX描画機能クラス ===
class DirectXRenderer final : public RendererInterface
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	DirectXRenderer();
	~DirectXRenderer();

	///====================================================================
	/// Public メンバー関数
	///====================================================================

	//@brief	=== 描画機能作成関数 ===
	//@param	window	ウィンドウインターフェース
	//@details	作成したウィンドウに描画するため引数で参照を渡す
	//@return	作成の成否
	[[nodiscard]] bool create_renderer(windowInterface* window)override;

	//@brief	=== 描画更新関数 ===
	//@details	毎フレーム更新される想定
	void update_renderer()override;

	//@brief	=== 描画機能終了処理関数 ===
	//@details	描画機能破棄前最終処理(非同期処理の待機など)をするための関数
	void end_renderer()override;

protected:
	///====================================================================
	/// Protected メンバー関数
	///====================================================================
	
	//@brief	=== 描画更新前関数 ===
	//@details	描画機能を更新する際に先に処理する必要があるものを呼び出す関数
	void begin_update_renderer()override;

	//@brief	=== 描画更新後関数 ===
	//@details	描画機能を更新した後に処理する必要があるものを呼び出す関数
	void end_update_renderer()override;

private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================

	/* -- 設定 -- */

	//@brief	== ウィンドウサイズ保存変数 ==
	WindowSize window_size{};

	//@brief	== フレームバッファサイズ設定変数 ==
	//@details	描画バッファリングサイズを指定
	const UINT buffer_size = 2;

	//@breif	== フレームリソースサイズ設定変数 ==
	//@details	描画に使うフレームリソースサイズを指定
	const UINT frame_resouse_size = 2;

	//@brief	== フレームカウント保存変数 ==
	//@details	何フレーム目かを保存
	UINT64 frame_count{};

	//@brief	== フレームリソースサイクル管理用変数 ==
	//@details	使用するフレームリソースインデックスを保存
	UINT64 current_frame_index{};

	//@brief	== DirectX描画機能インスタンス保存クラスインスタンス ==
	//@details	制作途中
	std::unique_ptr<render::dx12::DirectXRendererContext> renderer_context{};

	//@brief	== 描画パス呼び出し順保存配列 ==
	std::vector<std::string> pass_order{};

	///====================================================================
	/// Private メンバー関数
	///====================================================================

	//@brief	=== フレームリソース使用可能確認関数 ===
	//@details	フレームリソースが使用可能な状態か確認する関数
	void sync_frame_resource();
};