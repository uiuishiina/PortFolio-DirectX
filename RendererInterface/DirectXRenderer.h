#pragma once
#include"RendererInterface.h"
#include<memory>
#include<vector>

///====================================================================
/// UINT互換typeof
///====================================================================

typedef unsigned int        UINT;
typedef unsigned __int64    UINT64;

///====================================================================
/// DirectXオブジェクトクラス前方宣言
///====================================================================

class DXGI;
class Device;
class CommandQueue;
class GraphicsCommandList;

class FrameResource;
class StaticHeapContainer;
class SwapChain;
class RenderTarget;
class Fence;
class RootSignature;
class PiplineState;

class StaticShaderContainer;
class StaticRootSignatureContainer;
class StaticPiplineStateContainer;

namespace polygon {
	class Polygon;
}

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

	/* -- 設定 -- */

	//@brief	== ウィンドウサイズ保存変数 ==
	WindowSize window_size{};

	//@brief	== フレームバッファサイズ設定変数 ==
	//@details	描画バッファリングサイズを指定
	const UINT buffer_size = 2;

	//@breif	== フレームリソースサイズ設定変数 ==
	//@details	描画に使うフレームリソースサイズを指定
	const UINT frame_resouse_size = 3;

	//@brief	== フレームカウント保存変数 ==
	//@details	何フレーム目かを保存
	UINT64 frame_count{};

	//@brief	== フレームリソースサイクル管理用変数 ==
	//@details	使用するフレームリソースインデックスを保存
	UINT64 current_frame_index{};

	//@brief	== 背景色保存関数 ==
	const float back_ground_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	/* -- 描画用 -- */

	//@brief	== DXGIインスタンス ==
	std::unique_ptr<DXGI> dxgi_{};

	//@brief	== Deviceインスタンス ==
	std::unique_ptr<Device> device_{};

	//@brief	== 描画用コマンドキューインスタンス ==
	std::unique_ptr<CommandQueue> graphics_queue{};

	//@brief	== 描画用コマンドリストインスタンス ==
	std::unique_ptr<GraphicsCommandList> graphics_list{};

	//@brief	== フレームリソース配列インスタンス ==
	std::vector<std::unique_ptr<FrameResource>> frame_resources{};

	//@brief	== 初期作成ディスクリプタヒープコンテナインスタンス ==
	std::unique_ptr<StaticHeapContainer> static_heap_container{};

	//@brief	== スワップチェーンインスタンス ==
	std::unique_ptr<SwapChain> swap_chain{};

	//@brief	== 最終描画先レンダーターゲットインスタンス ==
	std::vector<std::unique_ptr<RenderTarget>> render_targets{};

	//@brief	== Fenceインスタンス ==
	std::unique_ptr<Fence> fence_{};

	//@brief	== シェーダーコンテナインスタンス ==
	std::unique_ptr<StaticShaderContainer> shader_container{};

	//@brief	== ルートシグネチャーコンテナインスタンス ==
	std::unique_ptr<StaticRootSignatureContainer> root_signature_container{};

	//@brief	== パイプラインステートコンテナインスタンス ==
	std::unique_ptr<StaticPiplineStateContainer> pipline_container{};

	UINT normal_pipline{};

	//@brief	== ポリゴンインスタンス ==
	std::unique_ptr<polygon::Polygon> polygon_{};
	
	///====================================================================
	/// Private メンバー関数
	///====================================================================

	//@brief	=== フレームリソース使用可能確認関数 ===
	//@details	フレームリソースが使用可能な状態か確認する関数
	void sync_frame_resource();
};