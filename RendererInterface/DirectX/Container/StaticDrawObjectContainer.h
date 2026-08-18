#pragma once
#include"../DirectXobject/DrawObjectBase.h"
#include"StaticContainerBase.h"

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
			/// StaticDrawObjectContainer クラス
			///====================================================================
			
			//@brief	=== 描画オブジェクトコンテナクラス ===
			class StaticDrawObjectContainer final : public StaticContainerBase
			{
			public:
				///====================================================================
				/// クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				StaticDrawObjectContainer() = default;
				~StaticDrawObjectContainer() = default;

				//@breif	=== 描画オブジェクト登録関数 ===
				//@param	key_name	登録するキーの名前
				//@param	object		登録するオブジェクト
				//@return	登録の成否
				[[nodiscard]] bool register_draw_object(const std::string& key_name,
					std::unique_ptr<drawobject::DrawObjectBase> object);

				//@brief	=== 描画オブジェクト取得関数 ===
				//@param	key	描画オブジェクトと紐づけたキー
				//@return	描画オブジェクト参照
				[[nodiscard]] drawobject::DrawObjectBase* get_draw_object(UINT key)const noexcept;

				//@brief	=== 描画オブジェクト取得関数 ===
				//@param	key	描画オブジェクトと紐づけたキー
				//@return	描画オブジェクト参照
				[[nodiscard]] drawobject::DrawObjectBase* get_draw_object(const std::string& key_name)const noexcept;

			private:
				///====================================================================
				/// Private メンバー変数
				///====================================================================
				
				//@brief	== 描画オブジェクトマップ ==
				std::unordered_map<UINT, std::unique_ptr<drawobject::DrawObjectBase>> object_map{};

			};
		};
	};
};