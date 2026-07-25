#pragma once
#include"../DirectXobject/DescriptorHeap.h"
#include"NonMovable.h"
#include<unordered_map>
#include<memory>
#include<vector>

///====================================================================
/// DescriptorHeapDesc 構造体
///====================================================================

//@brief	=== ディスクリプタヒープ作成補助構造体 ===
struct DescriptorHeapDesc
{
	//@brief	== ディスクリプターヒープタイプ設定 ==
	D3D12_DESCRIPTOR_HEAP_TYPE type;

	//@brief	== ディスクリプターヒープサイズ設定 ==
	UINT numDescriptors;

	//@brief	== シェーダー可視設定 ==
	D3D12_DESCRIPTOR_HEAP_FLAGS flags;
};

///====================================================================
/// StaticHeapContainer クラス
///====================================================================

//@brief	=== 初期作成ディスクリプタヒープコンテナクラス ===
class StaticHeapContainer final : public NonMovableBase
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	StaticHeapContainer() = default;
	~StaticHeapContainer() = default;

	///====================================================================
	/// Public メンバー関数
	///====================================================================

	//@brief	=== ディスクリプタヒープコンテナ作成関数 ===
	//@param	device	DirectX12 デバイス
	//@param	desc	ディスクリプタヒープ設定配列
	//@return	作成の可否
	[[nodiscard]] HRESULT create_static_heap_container(ID3D12Device* device, const std::vector<DescriptorHeapDesc>& desc);

	//@brief	=== ディスクリプタヒープ参照取得関数 ===
	//@param	type	ディスクリプターヒープタイプ
	//@return	ディスクリプターヒープポインター
	[[nodiscard]] DescriptorHeap* get_discriptor_heap(D3D12_DESCRIPTOR_HEAP_TYPE type);

private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================

	//@brief	== ディスクリプタヒープマップ ==
	std::unordered_map<D3D12_DESCRIPTOR_HEAP_TYPE, std::unique_ptr<DescriptorHeap>> static_heap_map{};
};