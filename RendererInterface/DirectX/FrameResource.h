#pragma once
#include"DirectXobject/CommandAllocator.h"
#include<memory>

///====================================================================
/// FrameResouse クラス
///====================================================================

//@brief	=== フレームリソースクラス ===
class FrameResource final
{
public:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	FrameResource() = default;
	~FrameResource() = default;

	//コピー禁止,ムーブ禁止
	FrameResource(const FrameResource&) = delete;
	FrameResource& operator=(const FrameResource&) = delete;
	FrameResource(FrameResource&&) = delete;
	FrameResource& operator=(FrameResource&&) = delete;

	///====================================================================
	/// Public メンバー関数
	///====================================================================
	
	//@brief	=== フレームリソース作成関数 ===
	//@param	device	DirectX12 デバイス
	//@return	作成の成否
	[[nodiscard]] HRESULT create_frame_resource(ID3D12Device* device);

	//@brief	===	描画用コマンドアロケータークラス参照取得関数 ===
	//@return	コマンドアロケータークラスインスタンス
	[[nodiscard]] CommandAllocator* get_graphics_allocator()const noexcept;

private:
	///====================================================================
	/// Private メンバー変数
	///====================================================================

	//@breif	== 描画用コマンドアロケータークラス ==
	std::unique_ptr<CommandAllocator> graphics_allocator{};
};