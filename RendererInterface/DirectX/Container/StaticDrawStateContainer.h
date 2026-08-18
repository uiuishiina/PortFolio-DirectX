#pragma once
#include"StaticContainerBase.h"
#include"../DrawPass/DrawState.h"

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
			/// StaticDrawStateContainer クラス
			///====================================================================

			//@brief	=== 描画設定コンテナ ===
			class StaticDrawStateContainer final : public StaticContainerBase
			{
			public:
				///====================================================================
				/// クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				StaticDrawStateContainer() = default;
				~StaticDrawStateContainer() = default;

				///====================================================================
				/// Public メンバー関数
				///====================================================================
				
				//@brief	=== 描画設定作成関数 ===
				//@param	key_name	登録するキーの名前
				//@param	desc	描画設定
				//@return	作成の成否
				[[nodiscard]] bool create_draw_state(const std::string& key_name, desc::DrawStateDesc& desc);

				//@brief	=== 描画設定取得関数 ===
				//@param	key	描画設定と紐づけたキー
				//@return	描画設定クラス参照
				[[nodiscard]] state::Drawstate* get_draw_state(UINT key)const noexcept;

				//@brief	=== 描画設定取得関数オーバーロード ===
				//@param	key_name	描画設定と紐づけたキーの名前
				//@return	描画設定クラス参照
				[[nodiscard]] state::Drawstate* get_draw_state(const std::string& key_name)const noexcept;

			private:
				///====================================================================
				/// Private メンバー変数
				///====================================================================

				//@brief == 描画設定保存マップ == =
				//@details	作成できた描画設定を保存するmap
				std::unordered_map<UINT, std::unique_ptr<state::Drawstate>> state_map{};

			};
		};
	};
};