#pragma once
#include"DirectXobject/CommandQueue.h"
#include"DirectXobject/CommandAllocator.h"
#include"DirectXobject/GraphicsCommandList.h"
#include<memory>
#include<vector>

///====================================================================
/// GraphicsCommandObject構造体
///====================================================================

//@brief	=== 描画用コマンドオブジェクト構造体 ===
struct GraphicsCommandObject final {

	std::unique_ptr<CommandQueue> queue_{};
	std::vector<std::unique_ptr<CommandAllocator>> allocators_{};
	std::unique_ptr<GraphicsCommandList> list_{};

	///====================================================================
	/// 構造体設定
	///====================================================================

	//@brief	=== コンストラクタ ===
	GraphicsCommandObject() = delete;
	GraphicsCommandObject(UINT buffer_size) {

		queue_ = std::make_unique<CommandQueue>();

		allocators_.resize(buffer_size);
		for (auto& allocator : allocators_)	{
			allocator = std::make_unique<CommandAllocator>();
		}

		list_= std::make_unique<GraphicsCommandList>();
	}
};

///====================================================================
/// GraphicsCommandObjectFactoryクラス
///====================================================================

//@brief	=== 描画用コマンドオブジェクト構造体ファクトリー ===
class GraphicsCommandObjectFactory final
{
public:
	///====================================================================
	/// Public メンバー関数
	///====================================================================

	//@brief	=== 描画用コマンドオブジェクト構造体作成関数 ===
	//@param	device	DirectX12 デバイス
	//@param	outout	受け渡すインスタンス
	//@return	作成の成否
	static HRESULT create_GraphicsCommandObject(ID3D12Device* device,GraphicsCommandObject& out);
};