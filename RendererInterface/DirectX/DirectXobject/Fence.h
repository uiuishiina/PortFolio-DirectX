#pragma once
#include"Others/NonCopyableBase.h"
#include<d3d12.h>
#include<wrl/client.h>

/// <summary>
/// 描画機能名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// DX12オブジェクトラッパークラス名前空間
		/// </summary>
		namespace object {

			/// <summary>
			/// フェンスクラス
			/// </summary>
			class Fence final : public others::NonCopyableBase
			{
			public:
				/* ========== クラス設定 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				Fence() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~Fence() = default;


				/* ========== Publicメンバー関数 ========== */

				/* -- 作成関数 -- */

				/// <summary>
				/// フェンス作成関数
				/// </summary>
				/// <param name="device">DirectX12デバイス参照</param>
				/// <returns>作成の成否</returns>
				[[nodiscard]] HRESULT create_fence(ID3D12Device* device);


				/* -- フェンス利用関数 -- */

				/// <summary>
				/// フェンスシグナル関数
				/// </summary>
				/// <param name="command_queue">シグナルするコマンドキュー参照</param>
				/// <returns>シグナルした値</returns>
				[[nodiscard]] const UINT64 signal(ID3D12CommandQueue* command_queue);

				/// <summary>
				/// フェンス待機関数
				/// </summary>
				/// <param name="completed_value">待機するフェンスの値</param>
				void wait_to_completed_value(UINT64 completed_value) const noexcept;


				/* -- 取得関数 -- */

				/// <summary>
				/// フェンス値取得関数
				/// </summary>
				/// <returns>動作完了したフェンス値</returns>
				[[nodiscard]] const UINT64 get_completed_value() const noexcept;

				/// <summary>
				/// 現在シグナル値取得関数
				/// </summary>
				/// <returns>フェンスの値</returns>
				[[nodiscard]] const UINT64 get_now_signal_value()const noexcept;

				/// <summary>
				/// フェンス取得関数
				/// </summary>
				/// <returns>フェンス参照</returns>
				[[nodiscard]] ID3D12Fence* get_fence()const noexcept;

			private:
				/* ========== Privateメンバー変数 ========== */

				/// <summary>
				/// フェンスインスタンス
				/// </summary>
				Microsoft::WRL::ComPtr<ID3D12Fence> fence_{};

				/// <summary>
				/// フェンスイベント
				/// </summary>
				HANDLE wait_event{};

				/// <summary>
				/// フェンスの値
				/// </summary>
				UINT64 fence_value{};

			};
		}
	}
}