#pragma once
#include<d3d12.h>
#include<vector>
#include<functional>

///====================================================================
/// 描画名前空間
///====================================================================
namespace render {

	///====================================================================
	/// 描画設定名前空間
	///====================================================================

	namespace state {

		///====================================================================
		/// DrawStateDesc 構造体
		///====================================================================

		//@brief	=== 描画設定補助構造体 ===
		struct DrawStateDesc {

			ID3D12RootSignature* root_signature{};

			ID3D12PipelineState* pipline_state{};

			D3D12_VIEWPORT viewport_{};

			D3D12_RECT	rect_{};
		};

		///====================================================================
		/// Drawstate クラス
		///====================================================================

		//@brief	=== 描画設定クラス ===
		class Drawstate final
		{
		public:
			///====================================================================
			/// クラス設定
			///====================================================================

			//コンストラクタ,デストラクタ
			Drawstate() = default;
			~Drawstate() = default;

			//コピー禁止,ムーブ禁止
			Drawstate(const Drawstate&) = delete;
			Drawstate& operator=(const Drawstate&) = delete;
			Drawstate(Drawstate&&) = delete;
			Drawstate& operator=(Drawstate&&) = delete;

			///====================================================================
			/// Public メンバー関数
			///====================================================================

			//@breif	=== 描画設定作成関数 ===
			//@param	desc	描画設定補助構造体
			//@return	作成の成否
			[[nodiscard]] bool creaate_draw_state(DrawStateDesc& desc);

			//@brief	=== 描画設定セット関数 ===
			//@param	list	描画用コマンドリスト
			void set_draw_state(ID3D12GraphicsCommandList* list);

		private:
			///====================================================================
			/// Private メンバー関数
			///====================================================================
			
			std::vector<ID3D12Resource*> render_targets{};

			ID3D12RootSignature* root_signature{};

			ID3D12PipelineState* pipline_state{};

			D3D12_VIEWPORT viewport_{};

			D3D12_RECT	rect_{};
		};
	}
}