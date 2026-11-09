#pragma once

/* ========== Includeファイル ========== */

#include"ComponentBase.h"
#include"Math/BaseStruct/Transform.h"

#include<memory>


namespace DirectX {

	/// <summary>
	/// オブジェクト機能統合名前空間
	/// </summary>
	namespace ClassModule {

		/// <summary>
		/// ディスクリプターヒープグループ名前空間
		/// </summary>
		namespace DescriptorGroup {

			template<typename T>
			class ConstantBufferGroup;
		}
	}
}

/// <summary>
/// アプリケーション名前空間
/// </summary>
namespace App {

	class TransfromComponent final : public ComponentBase
	{
	public:

		TransfromComponent(
			const HandyItems::Math::Transform& trans
		) :
			transform_{ trans }{};

		[[nodiscard]] const ComponentID get_type_id() const noexcept override {
			return HandyItems::id::get_id::get_type_id<TransfromComponent>();
		}

		[[nodiscard]] HandyItems::Math::Transform& get_transform() {
			return transform_;
		}

	private:

		HandyItems::Math::Transform transform_{};

		std::unique_ptr<
			DirectX::ClassModule::DescriptorGroup::ConstantBufferGroup
			<HandyItems::Math::Transform>
		>
			transform_buffer{};

	};
}