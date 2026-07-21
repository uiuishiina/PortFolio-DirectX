#pragma once
#include"FrameResource.h"
#include"Container/StaticHeapContainer.h"
#include"DirectXobject/RenderTarget.h"
#include<array>

///====================================================================
/// 描画名前空間
///====================================================================

namespace render {

	//	描画先を配列で分けるため作成

	//	イメージ
	///	|バックバッファ用インデックス|GBuffer用インデックス|...

	enum class RenderTargetSlot : uint32_t {
		BackBuffer,
		GBuffer,
		Count
	};

	enum class DepthSlot : uint32_t {
		MainDepth,

		Count
	};

	///====================================================================
	/// 描画リソース名前空間
	///====================================================================
	
	namespace resouces {

		template<class Enum>
		constexpr size_t to_index(Enum e) noexcept	{
			return static_cast<size_t>(e);
		}

		//そのフレームで使う描画リソースを保存する構造体
		struct DrawResouces {

			ID3D12GraphicsCommandList* graphics_list{};

			FrameResource* frame_resouce{};

			StaticHeapContainer* static_heap_container{};

			std::array<RenderTarget*, to_index(RenderTargetSlot::Count)> render_targets{};

			RenderTarget* get_target(RenderTargetSlot slot) const	{
				return render_targets[to_index(slot)];
			}
		};
	}
}