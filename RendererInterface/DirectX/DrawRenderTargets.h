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
	namespace state{

		///====================================================================
		/// DrawRenderTargets クラス
		///====================================================================

		//@brief	=== 描画パス用レンダーターゲット管理クラス ===
		class DrawRenderTargetState final
		{
		public:
			///====================================================================
			/// クラス設定
			///====================================================================

			//コンストラクタ,デストラクタ
			DrawRenderTargetState() = default;
			~DrawRenderTargetState() = default;

			//コピー禁止,ムーブ禁止
			DrawRenderTargetState(const DrawRenderTargetState&) = delete;
			DrawRenderTargetState& operator=(const DrawRenderTargetState&) = delete;
			DrawRenderTargetState(DrawRenderTargetState&&) = delete;
			DrawRenderTargetState& operator=(DrawRenderTargetState&&) = delete;

			///====================================================================
			/// Public メンバー関数
			///====================================================================
			

		private:
			///====================================================================
			/// Private メンバー関数
			///====================================================================

			std::vector<ID3D12Resource*> render_targets{};
		};
	}
}