#pragma once
#include"DirectXobject/DescriptorHeap.h"
#include<unordered_map>
#include<memory>
#include<vector>

///====================================================================
/// DescriptorHeapDesc構造体
///====================================================================

//@brief	=== ディスクリプタヒープ作成補助構造体 ===
struct DescriptorHeapDesc
{
	D3D12_DESCRIPTOR_HEAP_TYPE type;
	UINT numDescriptors;
	D3D12_DESCRIPTOR_HEAP_FLAGS flags;
};

///====================================================================
/// StaticHeapContainerクラス
///====================================================================

//@brief	=== 初期作成ディスクリプタヒープコンテナクラス ===
class StaticHeapContainer final
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	StaticHeapContainer() = default;
	~StaticHeapContainer() = default;

	//コピー禁止,ムーブ禁止
	StaticHeapContainer(const StaticHeapContainer&) = delete;
	StaticHeapContainer& operator=(const StaticHeapContainer&) = delete;
	StaticHeapContainer(StaticHeapContainer&&) = delete;
	StaticHeapContainer& operator=(StaticHeapContainer&&) = delete;

	///====================================================================
	/// Public メンバー関数
	///====================================================================

	//@brief	=== ディスクリプタヒープコンテナ作成関数 ===
	//@param	device	DirectX12 デバイス
	//@param	desc	ディスクリプタヒープ設定配列
	//@return	作成の可否
	[[nodiscard]] HRESULT create_static_heap_container(ID3D12Device* device, const std::vector<DescriptorHeapDesc>& desc);

private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================

	//@brief	== ディスクリプタヒープマップ ==
	std::unordered_map<D3D12_DESCRIPTOR_HEAP_TYPE, std::unique_ptr<DescriptorHeap>> static_heap_map{};
};