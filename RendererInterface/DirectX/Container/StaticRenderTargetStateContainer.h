#pragma once
#include"StaticContainerBase.h"
#include"../DrawPass/DrawRenderTargetState.h"
#include<string>
#include<unordered_map>
#include<memory>
#include<optional>
#include<vector>

///====================================================================
/// 描画名前空間
///====================================================================

namespace render {

	///====================================================================
	/// DirectX名前空間
	///====================================================================

	namespace dx12 {

		///====================================================================
		/// コンテナ名前空間
		///====================================================================

		namespace container {

			///====================================================================
			/// StaticRenderTargetStateContainer クラス
			///====================================================================

			//@brief	=== 描画パス用レンダーターゲット設定コンテナ ===
			class StaticRenderTargetStateContainer final : public StaticContainerBase
			{
			public:
				///====================================================================
				/// クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				StaticRenderTargetStateContainer() = default;
				~StaticRenderTargetStateContainer() = default;

				///====================================================================
				/// Public メンバー関数
				///====================================================================

				//@brief	=== 描画パス用レンダーターゲット設定作成関数 ==
				//@param	key_name	登録するキーの名前
				//@param	slots	登録するターゲットの種類配列
				//@return	作成の成否
				[[nodiscard]] bool create_render_target_state(const std::string& key_name, const std::vector<RenderTargetSlot>& render_target_slots, std::optional<DepthSlot> depth_slot = std::nullopt);

				//@brief	=== 描画パス用レンダーターゲット設定取得関数 ===
				//@param	key	描画パス用レンダーターゲット設定と紐づけたキー
				//@return	描画パス用レンダーターゲット設定クラス参照
				[[nodiscard]] state::DrawRenderTargetState* get_draw_state(UINT key)const noexcept;

				//@brief	=== 描画パス用レンダーターゲット設定取得関数オーバーロード ===
				//@param	key_name	描画パス用レンダーターゲット設定と紐づけたキーの名前
				//@return	描画パス用レンダーターゲット設定クラス参照
				[[nodiscard]] state::DrawRenderTargetState* get_draw_state(const std::string& key_name)const noexcept;

			private:
				///====================================================================
				/// Private メンバー変数
				///====================================================================

				//@brief	== 描画パス用レンダーターゲット設定保存マップ ===
				//@details	作成できた描画パス用レンダーターゲット設定を保存するmap
				std::unordered_map<UINT, std::unique_ptr<state::DrawRenderTargetState>> render_target_state_map{};

			};
		};
	};
};