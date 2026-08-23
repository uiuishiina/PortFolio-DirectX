#pragma once
#include"NonMovable.h"
#include"SharedData.h"
#include<tuple>
#include<memory>

///====================================================================
/// 共有データ名前空間
///====================================================================

namespace sharedData {

	///====================================================================
	/// 共有データ設定名前空間
	///====================================================================

	namespace desc {

		using BoolTuple = std::tuple<
			SharedDatas<bool>
		>;
	};

	///====================================================================
	/// ApplicationSharedData クラス
	///====================================================================

	//@brief	=== アプリケーションデータシェアクラス ===
	class ApplicationSharedData final : public NonMovableBase
	{
	public:
		///====================================================================
		/// クラス設定
		///====================================================================

		//コンストラクタ,デストラクタ
		ApplicationSharedData() = default;
		~ApplicationSharedData() = default;

		///====================================================================
		/// Public メンバー関数
		///====================================================================
		
		template<typename T>
		SharedDatas<T>& set_state()noexcept {
			return std::get<SharedDatas<T>>(bool_datas);
		};

		template<typename T>
		const SharedDatas<T>& get_state() const noexcept {
			return std::get<SharedDatas<T>>(bool_datas);
		};
		

	private:
		///====================================================================
		/// Private メンバー変数
		///====================================================================
		
		desc::BoolTuple bool_datas{};
	};
};