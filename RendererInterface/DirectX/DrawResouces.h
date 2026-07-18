#pragma once
#include"FrameResource.h"
#include"Container/StaticHeapContainer.h"
#include"DirectXobject/RenderTarget.h"


//そのフレームで使う描画リソースを保存する構造体
struct DrawResouces {

	FrameResource* frame_resouce{};

	StaticHeapContainer* static_heap_container{};

	RenderTarget* back_buffer{};
};