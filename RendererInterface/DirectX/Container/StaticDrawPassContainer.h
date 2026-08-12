#pragma once
#include"../DrawPass/DrawPass.h"
#include"StaticContainerBase.h"
#include<unordered_map>
#include<memory>
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
			/// StaticDrawPassContainer クラス
			///====================================================================

			//@brief	=== 描画パスコンテナクラス ===
			class StaticDrawPassContainer final : public StaticContainerBase
			{
			public:
				///====================================================================
				/// クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				StaticDrawPassContainer() = default;
				~StaticDrawPassContainer() = default;

				///====================================================================
				/// Public メンバー関数
				///====================================================================

				//@breif	=== 描画パス作成関数 ===
				//@param	key_name	登録するキーの名前
				//@param	desc		作成する描画パス設定
				//@return	作成の成否
				[[nodiscard]] bool create_draw_pass(const std::string& key_name, desc::DrawPassDesc& desc);

				//@breif == = 描画パス呼び出し関数 == =
				//@details	無い場合は何もなし
				//@param	key		呼び出す描画パスと紐づけたキー
				//@param	resource	描画リソース
				void apply_draw_pass(UINT key, resources::DrawResources& resource)const noexcept;

				//@breif	=== 描画パス呼び出しオーバーロード関数 ===
				//@details	無い場合は何もなし
				//@param	key_name	呼び出す描画パスと紐づけたキーの名前
				//@param	resource	描画リソース
				void apply_draw_pass(const std::string& key_name, resources::DrawResources& resource)const noexcept;

			private:
				///====================================================================
				/// Private メンバー変数
				///====================================================================

				//@brief	== 描画パス保存マップ ===
				//@details	作成できた描画パスを保存するmap
				std::unordered_map<UINT, std::unique_ptr<pass::DrawPass>> pass_map{};

			};
		};
	};
};