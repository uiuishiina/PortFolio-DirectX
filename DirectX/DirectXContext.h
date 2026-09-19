#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Others/NonCopyableBase.h"
#include"Others/UniquePtr.h"

//	DirectX
#include"ClassObject/DXGI.h"
#include"ClassObject/Device.h"

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	using namespace HandyItems::others;

	/// <summary>
	/// DirectXオブジェクトインスタンス構造体
	/// </summary>
	struct DirectXContext final : NonCopyableBase {
		
		/* ========== Publicメンバー変数 ========== */

		/// <summary>
		/// DXGIインスタンス
		/// </summary>
		UniquePtr<ClassObject::DXGI> dxgi_{};

		/// <summary>
		/// Deviceインスタンス
		/// </summary>
		UniquePtr<ClassObject::Device> device_{};

		/* ========== Publicメンバー関数 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		DirectXContext();

		/// <summary>
		/// デストラクタ
		/// </summary>
		~DirectXContext();

	};
}