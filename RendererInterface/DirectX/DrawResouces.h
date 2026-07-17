#pragma once
#include"FrameResource.h"
#include"Container/StaticHeapContainer.h"
#include"DirectXobject/RenderTarget.h"

struct DrawResouces {

	FrameResource* frame_resouce{};

	StaticHeapContainer* static_heap_container{};

	RenderTarget* back_buffer{};
};