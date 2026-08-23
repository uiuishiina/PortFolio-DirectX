#pragma once
#include"NonMovable.h"
#include<vector>
#include<optional>

///====================================================================
/// 共有データ名前空間
///====================================================================

namespace sharedData {

	//@breif	=== シェアデータテンプレート構造体 ===
	template<typename T>
	class SharedDatas : public NonMovableBase
	{
	public:
		///====================================================================
		/// クラス設定
		///====================================================================
		
		//コンストラクタ,デストラクタ
		SharedDatas() = default;
		~SharedDatas() = default;

		///====================================================================
		/// Public メンバー関数
		///====================================================================
		
		//@brief	=== データ参照追加関数 ===
		//@param	data	追加するデータ参照
		void add_data(T& data) {
			datas_.push_back(data);
		}

		//@brief	=== シェアデータ参照取得関数 ===
		//@param	index	参照するデータインデックス
		//@return	データ参照 ... ないなら [ std::nullopt ]
		[[nodiscard]] std::optional<std::reference_wrapper<T>> get_data(size_t index)const noexcept {

			//	配列外参照なら [ nullopt ]
			if (index >= datas_.size()) {
				return std::nullopt;
			}
			return datas_[index];
		};

		//@breif	=== データ参照消去関数 ===
		void clear_datas() {
			datas_.clear();
		}

	private:
		///====================================================================
		/// Private メンバー変数
		///====================================================================

		//@brief	== シェアデータ参照保管配列 ==
		std::vector<std::optional<std::reference_wrapper<T>>> datas_{};

	};
};