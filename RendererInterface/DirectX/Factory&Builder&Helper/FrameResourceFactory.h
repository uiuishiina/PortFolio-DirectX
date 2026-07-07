#pragma once
#include"../FrameResource.h"
#include<vector>
#include<memory>

///====================================================================
/// FrameResourceFactory クラス
///====================================================================

//@brief	=== フレームリソースファクトリークラス ===
class FrameResourceFactory final
{
public:
	///====================================================================
	/// Public メンバー関数
	///====================================================================


	static [[nodiscard]] HRESULT create_frame_resources(ID3D12Device* device,UINT size,std::vector<std::unique_ptr<FrameResource>>& out);

private:
	///====================================================================
	/// クラス設定
	///====================================================================

	//コンストラクタ,デストラクタ
	FrameResourceFactory() = default;
	~FrameResourceFactory() = default;
};