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

namespace render {

	namespace dx12 {

		namespace object {
			class DXGI;
			class Device;
			class CommandQueue;
			class GraphicsCommandList;

			class SwapChain;
			class RenderTarget;
			class Fence;
			class RootSignature;
			class PipelineState;
		};
		namespace container {
			class StaticHeapContainer;
			class StaticShaderContainer;
			class StaticRootSignatureContainer;
			class StaticPiplineStateContainer;

			class StaticDrawStateContainer;
			class StaticRenderTargetStateContainer;
		};
		namespace resources {
			class FrameResource;
		};
		namespace mesh {
			class Mesh;
		};
		namespace state {
			class DrawRenderTargetState;
		};
		namespace command {
			class DrawCommands;
		};
		namespace pass {
			class DrawPass;
		};
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
	std::unique_ptr<render::dx12::object::DXGI> dxgi_{};

	//@brief	== Deviceインスタンス ==
	std::unique_ptr<render::dx12::object::Device> device_{};

	//@brief	== 描画用コマンドキューインスタンス ==
	std::unique_ptr<render::dx12::object::CommandQueue> graphics_queue{};

	//@brief	== 描画用コマンドリストインスタンス ==
	std::unique_ptr<render::dx12::object::GraphicsCommandList> graphics_list{};

	//@brief	== フレームリソース配列インスタンス ==
	std::vector<std::unique_ptr<render::dx12::resources::FrameResource>> frame_resources{};

	//@brief	== スワップチェーンインスタンス ==
	std::unique_ptr<render::dx12::object::SwapChain> swap_chain{};

	//@brief	== 最終描画先レンダーターゲットインスタンス ==
	std::vector<std::unique_ptr<render::dx12::object::RenderTarget>> render_targets{};

	//@brief	== Fenceインスタンス ==
	std::unique_ptr<render::dx12::object::Fence> fence_{};

	UINT normal_pipline{};

	/* -- コンテナ各種 -- */

	//@brief	== 初期作成ディスクリプタヒープコンテナインスタンス ==
	std::unique_ptr<render::dx12::container::StaticHeapContainer> static_heap_container{};

	//@brief	== シェーダーコンテナインスタンス ==
	std::unique_ptr<render::dx12::container::StaticShaderContainer> shader_container{};

	//@brief	== ルートシグネチャーコンテナインスタンス ==
	std::unique_ptr<render::dx12::container::StaticRootSignatureContainer> root_signature_container{};

	//@brief	== パイプラインステートコンテナインスタンス ==
	std::unique_ptr<render::dx12::container::StaticPiplineStateContainer> pipline_container{};

	//@brief	== 描画設定コンテナインスタンス ==
	std::unique_ptr<render::dx12::container::StaticDrawStateContainer> static_draw_state_container{};

	//@brief	== 描画パス用レンダーターゲット設定コンテナインスタンス ==
	std::unique_ptr<render::dx12::container::StaticRenderTargetStateContainer> static_render_target_state_container{};



	//@brief	== ポリゴンインスタンス ==
	std::unique_ptr<render::dx12::mesh::Mesh> polygon_{};
	std::unique_ptr<render::dx12::mesh::Mesh> Color_polygon_{};

	std::unique_ptr<render::dx12::pass::DrawPass> NormalPass_{};
	std::unique_ptr<render::dx12::pass::DrawPass> Color_Pass_{};

	std::unique_ptr<render::dx12::command::DrawCommands> NormalCommands_{};

	std::unique_ptr<render::dx12::command::DrawCommands> Color_Commands_{};
	
	///====================================================================
	/// Private メンバー関数
	///====================================================================

	//@brief	=== フレームリソース使用可能確認関数 ===
	//@details	フレームリソースが使用可能な状態か確認する関数
	void sync_frame_resource();
};