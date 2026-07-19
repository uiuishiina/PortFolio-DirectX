#pragma once
#include"FrameResource.h"
#include"Container/StaticHeapContainer.h"
#include"DirectXobject/RenderTarget.h"
#include<array>

namespace render {

	enum class RenderTargetSlot : uint32_t {
		BackBuffer,

		Count
	};
	inline constexpr size_t RenderTargetCount = static_cast<size_t>(RenderTargetSlot::Count);

	enum class DepthSlot : uint32_t {
		MainDepth,

		Count
	};

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

			std::array<RenderTarget*, RenderTargetCount> render_targets{};


			RenderTarget* get_target(RenderTargetSlot slot) const	{
				return render_targets[to_index(slot)];
			}
		};
	}
}