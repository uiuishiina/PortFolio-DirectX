#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Others/NonCopyableBase.h"

//	DirectX
#include"DirectXContext.h"
#include"Initializer/InitializeCore.h"

//	その他
#include<concepts>
#include<cstdint>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// 初期作成時ログ出力クラス
	/// </summary>
	class InitializeLog final
	{
	public:
		/* ========== Publicメンバー関数 ========== */

		/// <summary>
		/// HRESULTログ出力関数
		/// </summary>
		/// <param name="hr">ログに出力するHRESULT</param>
		static void hresult_log(
			HRESULT hr
		);

		/// <summary>
		/// HRESULTエラーログ出力関数
		/// </summary>
		/// <param name="hr">ログに出力するHRESULT</param>
		static void hresult_error_log(
			HRESULT hr
		);

	private:
		/* ========== Privateメンバー関数 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		InitializeLog() = default;

		/// <summary>
		/// デストラクタ
		/// </summary>
		~InitializeLog() = default;

	};

	/// <summary>
	/// DirectX初期化クラス
	/// </summary>
	/// <typeparam name="Core">Core初期化クラス</typeparam>
	template<
	typename Core = Initialize::InitializeCore
	>
	requires
	std::derived_from<Core, Initialize::InitializeCore>
	class DirectXInitializer final : HandyItems::others::NonCopyableMovableBase 
	{
	public:
		/* ========== Publicメンバー関数 ========== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		DirectXInitializer() = default;

		/// <summary>
		/// デストラクタ
		/// </summary>
		~DirectXInitializer() = default;

		/* ===== 初期化関数 ===== */

		[[nodiscard]] bool initialize(
			DirectXContext* context,
			HWND hwnd,
			std::uint32_t width,
			std::uint32_t height,
			UINT back_buffer_size,
			UINT frame_resource_size
		) {
			Core core{};

			auto hr = core.initialize_core(
				context,
				hwnd,
				width,
				height,
				back_buffer_size
			);
			if (FAILED(hr)) {

				InitializeLog::hresult_error_log(hr);
				return false;
			}

			return true;
		}

	};

}