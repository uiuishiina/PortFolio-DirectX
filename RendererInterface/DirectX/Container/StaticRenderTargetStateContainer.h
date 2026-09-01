#pragma once
#include"../DrawPass/DrawRenderTargetState.h"
#include"UniqueptrKeyMap.h"

/// <summary>
/// 描画名前空間
/// </summary>
namespace render {

	/// <summary>
	/// DirectX名前空間
	/// </summary>
	namespace dx12 {

		/// <summary>
		/// コンテナ名前空間
		/// </summary>
		namespace container {

			/* ========== 描画パス用レンダーターゲット設定キー定義 ========== */

			/// <summary>
			/// ハンドル名前空間
			/// </summary>
			namespace handle {

				/// <summary>
				/// レンダーターゲット設定用倫理側派生キー
				/// </summary>
				struct RenderTargetStateKey : public LogicalKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					RenderTargetStateKey() = default;

					/// <summary>
					/// 引数付きコンストラクタ
					/// </summary>
					/// <param name="key">キーに入れる値</param>
					explicit RenderTargetStateKey(std::uint32_t key) :
						LogicalKey{key} {}

					/// <summary>
					/// 引数付きコンストラクタ
					/// </summary>
					/// <param name="key">キーに入れる値</param>
					explicit RenderTargetStateKey(const char* key_name) :
						LogicalKey{ static_cast<std::uint32_t>(HandyItems::id::get_id::get_name_id<RenderTargetStateKey>(key_name))} {}
				};

				/// <summary>
				/// レンダーターゲット設定用保存側派生キー
				/// </summary>
				struct RTStateEncodeKey : public EncodeKey {

					/// <summary>
					/// コンストラクタ
					/// </summary>
					RTStateEncodeKey() = default;
				};
			}


			/// <summary>
			/// 描画パス用レンダーターゲット設定コンテナ
			/// </summary>
			class StaticRenderTargetStateContainer final : public UniqueptrKeyMap<
				handle::RenderTargetStateKey,
				handle::RTStateEncodeKey,
				state::DrawRenderTargetState
			>
			{
			public:
				/* ========== メンバー関数 ========== */

				/// <summary>
				/// コンストラクタ
				/// </summary>
				StaticRenderTargetStateContainer() = default;

				/// <summary>
				/// デストラクタ
				/// </summary>
				~StaticRenderTargetStateContainer() = default;

				/* ===== 追加関数 ===== */

				/// <summary>
				/// 描画パス用レンダーターゲット設定作成関数
				/// </summary>
				/// <param name="key"></param>
				/// <param name="render_target_slots"></param>
				/// <param name="depth_slot"></param>
				/// <returns></returns>
				[[nodiscard]] bool create_render_target_state(const handle::RenderTargetStateKey& key, const std::vector<RenderTargetSlot>& render_target_slots, std::optional<DepthSlot> depth_slot = std::nullopt);


				/* ===== 取得関数 ===== */
				
				/// <summary>
				/// ハンドル取得関数
				/// </summary>
				/// <param name="key_name">取得したいレンダーターゲット設定用に紐づいた倫理側キーの名前</param>
				/// <returns>レンダーターゲット設定用ハンドル</returns>
				[[nodiscard]] Handle get_handle_to_name(const char* key_name) noexcept {

					return this->get_handle(handle::RenderTargetStateKey(key_name));
				}

				[[nodiscard]] Handle get_handle_to_name(const char* key_name) const noexcept {

					return this->get_handle(handle::RenderTargetStateKey(key_name));
				}
			};
		};
	};
};