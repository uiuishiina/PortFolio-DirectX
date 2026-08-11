#pragma once
#include"../DirectXobject/StaticBufferResource.h"
#include"StaticContainerBase.h"
#include<unordered_map>
#include<memory>
#include<vector>
#include<concepts>

///====================================================================
/// 描画名前空間
///====================================================================

namespace render {

	///====================================================================
	/// DirectX名前空間
	///====================================================================

	namespace dx12 {

		///====================================================================
		/// テンプレートコンセプト名前空間
		///====================================================================

		namespace concepts {

			//@brief	== 初期作成描画バッファ継承コンセプト ==
			template<typename T>
			concept FromStaticBuffer = std::derived_from<T, object::StaticBufferResource>;
		};

		///====================================================================
		/// コンテナ名前空間
		///====================================================================

		namespace container {

			///====================================================================
			/// StaticBufferContainer クラス
			///====================================================================

			//@brief	=== 初期作成描画バッファリソースコンテナクラス ===
			class StaticBufferContainer final : public StaticContainerBase
			{
			public:
				///====================================================================
				/// クラス設定
				///====================================================================

				//コンストラクタ,デストラクタ
				StaticBufferContainer() = default;
				~StaticBufferContainer() = default;

				template<concepts::FromStaticBuffer T>
				[[nodiscard]] bool register_buffer(const std::string& key_name, std::unique_ptr<T> buffer);

				template<concepts::FromStaticBuffer T>
				[[nodiscard]] T* get_buffer(const std::string& key_name)const noexcept;

				template<concepts::FromStaticBuffer T>
				[[nodiscard]] T* get_buffer(UINT key)const noexcept;

			private:
				///====================================================================
				/// Private メンバー関数
				///====================================================================

				//@brief	== 描画バッファ保存マップ ===
				//@details	作成したバッファを保存するmap
				std::unordered_map<UINT, std::unique_ptr<object::StaticBufferResource>> buffer_map{};

				///====================================================================
				/// Private メンバー関数
				///====================================================================

				
				[[nodiscard]] object::StaticBufferResource* get_resource(UINT key)const noexcept;
			};


			template<concepts::FromStaticBuffer T>
			[[nodiscard]] bool StaticBufferContainer::register_buffer(const std::string& key_name,std::unique_ptr<T> buffer) {
				
				//  登録済みか確認
				auto hash = get_hash_key(key_name);
				if (hash.has_value()) {
					return false;
				}

				auto new_hash = allocate_hash(key_name);
				buffer_map.emplace(new_hash, std::move(buffer));

				return true;
			}

			template<concepts::FromStaticBuffer T>
			[[nodiscard]] T* StaticBufferContainer::get_buffer(const std::string& key_name)const noexcept {
				
				auto hash = get_hash_key(key_name);
				if (!hash.has_value()) {
					return nullptr;
				}
				return get_buffer(hash.value());
			}

			template<concepts::FromStaticBuffer T>
			[[nodiscard]] T* StaticBufferContainer::get_buffer(UINT key)const noexcept {

				auto value = get_resource(key);
				if (value == nullptr) {
					return nullptr;
				}

				return dynamic_cast<T*>(value);
			}
		};
	};
};