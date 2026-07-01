#pragma once
#include"RendererInterface.h"
#include<memory>
#include<vector>

///====================================================================
/// DirectXオブジェクトクラス前方宣言
///====================================================================

class DXGI;
class Device;
struct GraphicsCommandObject;
class StaticHeapContainer;
class SwapChain;
class RenderTarget;
//class Fence;

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

	//コピー禁止,ムーブ禁止
	DirectXRenderer(const DirectXRenderer&) = delete;
	DirectXRenderer& operator=(const DirectXRenderer&) = delete;
	DirectXRenderer(DirectXRenderer&&) = delete;
	DirectXRenderer& operator=(DirectXRenderer&&) = delete;

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

	//@brief	== フレームカウント保存変数 ==
	//@details	何フレーム目かを保存
	unsigned long long int frame_count{};

	//@brief	== フレームバッファサイズ設定変数 ==
	//@details	描画バッファリングサイズを指定
	const unsigned int buffer_size = 2;

	/* -- 描画用 -- */

	//@brief	== DXGIインスタンス ==
	std::unique_ptr<DXGI> dxgi_{};

	//@brief	== Deviceインスタンス ==
	std::unique_ptr<Device> device_{};

	//@brief	== 描画用コマンドオブジェクト構造体インスタンス ==
	std::unique_ptr<GraphicsCommandObject> graphics_command_object{};

	//@brief	== 初期作成ディスクリプタヒープコンテナインスタンス ==
	std::unique_ptr<StaticHeapContainer> static_heap_container{};

	//@brief	== スワップチェーンインスタンス ==
	std::unique_ptr<SwapChain> swap_chain{};

	//@brief	== 最終描画先レンダーターゲットインスタンス ==
	std::vector<std::unique_ptr<RenderTarget>> render_targets{};

	
};