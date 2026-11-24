#pragma once

#include"Container/DescriptorHeapContainer.h"
#include"Container/ShaderContainer.h"
#include"Container/RootSignatureContainer.h"
#include"Container/PiplineStateContainer.h"
#include"Container/DrawObjectConteiner.h"
#include"Container/CameraObjectContainer.h"

namespace DirectX {

	struct ContainerContext
	{
		/// <summary>
		/// ディスクリプタヒープコンテナインスタンス
		/// </summary>
		Container::DescriptorHeapContainer heap_container{};

		/// <summary>
		/// HLSLシェーダーコンテナインスタンス
		/// </summary>
		Container::ShaderContainer shader_container{};

		/// <summary>
		/// ルートシグネチャーコンテナインスタンス
		/// </summary>
		Container::RootSignatureContainer root_signature_container{};

		/// <summary>
		/// パイプラインステートコンテナインスタンス
		/// </summary>
		Container::PiplineStateContainer pipline_state_container{};

		/// <summary>
		/// 描画オブジェクトコンテナインスタンス
		/// </summary>
		Container::DrawObjectContainer draw_object_container{};

		/// <summary>
		/// カメラオブジェクトコンテナインスタンス
		/// </summary>
		Container::CameraObjectContainer camera_object_container{};

	};
}