#pragma once

/* ========== Includeファイル ========== */

//	HandyItems
#include"Others/NonCopyableBase.h"

//	DirectX
#include<d3d12.h>
#include<wrl/client.h>

/// <summary>
/// DirectX名前空間
/// </summary>
namespace DirectX {

	/// <summary>
	/// リソースバリア管理クラス
	/// </summary>
	class ResourceBarrier : HandyItems::others::NonCopyableMovableBase
	{
	public:
		/* ========== Publicメンバー関数 ========== */

		//	コンストラクタ削除
		ResourceBarrier() = delete;

		/// <summary>
		/// リソースステート設定コンストラクタ
		/// </summary>
		/// <param name="state">初期設定リソースステート</param>
		ResourceBarrier(
			D3D12_RESOURCE_STATES state
		) :
			current_state{ state } {}

		/// <summary>
		/// デストラクタ
		/// </summary>
		~ResourceBarrier() = default;

		/* ===== 実行関数 ===== */

		/// <summary>
		/// リソースバリア遷移関数
		/// </summary>
		/// <param name="list">コマンドリスト参照</param>
		/// <param name="resource_">遷移するリソース</param>
		/// <param name="next_state">遷移先バリアステート</param>
		void barrier_transition(
			ID3D12GraphicsCommandList* list,
			ID3D12Resource* resource_,
			D3D12_RESOURCE_STATES next_state
		) {

			if (current_state == next_state) {
				return;
			}

			//  リソースバリア遷移
			const auto barrier = create_resource_barrier(
				resource_,
				current_state, next_state
			);

			list->ResourceBarrier(1, &barrier);
			current_state = next_state;
		}

	private:
		/* ========== Privateメンバー変数 ========== */

		/// <summary>
		/// 現在リソースステート
		/// </summary>
		D3D12_RESOURCE_STATES current_state{};

		/* ========== Privateメンバー関数 ========== */

		/* ===== 実行関数 ===== */

		/// <summary>
		/// リソースバリア作成関数
		/// </summary>
		/// <param name="resource">リソースバリアを作成するリソース</param>
		/// <param name="from">リソースの現在の状態</param>
		/// <param name="to">リソースの遷移先の状態</param>
		/// <returns>作成されたリソースバリア</returns>
		[[nodiscard]] D3D12_RESOURCE_BARRIER create_resource_barrier(
			ID3D12Resource* resource,
			D3D12_RESOURCE_STATES from,
			D3D12_RESOURCE_STATES to
		) noexcept {

			D3D12_RESOURCE_BARRIER barrier{};
			barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
			barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
			barrier.Transition.pResource = resource;
			barrier.Transition.StateBefore = from;
			barrier.Transition.StateAfter = to;
			barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

			return barrier;
		}

	};
}