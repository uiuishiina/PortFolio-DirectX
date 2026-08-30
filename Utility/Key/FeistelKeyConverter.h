#pragma once
#include"KeyConverterBase.h"


/// <summary>
/// キー名前空間
/// </summary>
namespace key {

	/// <summary>
	/// Feistelキー変換クラス
	/// </summary>
	/// <details>
	/// [ Feistel ] で暗号化するクラス
	/// </details>
	/// <typeparam name="T">エンコードするキー</typeparam>
	/// <typeparam name="U">デコードするキー</typeparam>
	template<concepts::HasKeyValue T, concepts::HasKeyValue U>
	class FeistelKeyConverter final : public KeyConverterBase<T,U>
	{
	public:
		/* ===== メンバー関数 ===== */

		/// <summary>
		/// コンストラクタ
		/// </summary>
		FeistelKeyConverter() = default;

		/// <summary>
		/// デストラクタ
		/// </summary>
		~FeistelKeyConverter() = default;

		/// <summary>
		/// エンコード関数
		/// </summary>
		/// <param name="value">エンコードしたいキー</param>
		/// <returns>エンコードされたキー</returns>
		[[nodiscard]] U encode_key(const T& value) const override {

			U result{};

			result.key_value = encrypt(value.key_value);

			return result;
		}

		/// <summary>
		/// デコード関数
		/// </summary>
		/// <param name="value">デコードしたいキー</param>
		/// <returns>デコードされたキー</returns>
		[[nodiscard]] T decode_key(const U& value) const override {

			T result{};

			result.key_value = decrypt(value.key_value);

			return result;
		}

	private:
		/* ===== メンバー変数 ===== */

		/// <summary>
		/// Feistelラウンド数
		/// </summary>
		static constexpr std::uint32_t ROUND_COUNT = 8;

		/// <summary>
		/// 32bitキーを構成する16bitデータ
		/// </summary>
		struct Block {
			std::uint16_t left;
			std::uint16_t right;
		};

		/* ===== メンバー関数 ===== */

		/// <summary>
		/// Feistelラウンド関数
		/// </summary>
		/// <param name="value">右半分</param>
		/// <param name="round_key">ラウンドキー</param>
		/// <returns>ラウンド結果</returns>
		static constexpr [[nodiscard]] std::uint16_t round_func(
			const std::uint16_t value,const std::uint32_t round_key) noexcept {

			std::uint32_t x = value;

			x ^= round_key;
			x *= 0x9E37u;
			x ^= x >> 8;
			x *= 0x85EBu;
			x ^= x >> 7;

			return static_cast<std::uint16_t>(x);
		}

		/// <summary>
		/// ラウンドキー生成関数
		/// </summary>
		/// <param name="round">ラウンド番号</param>
		/// <returns>ラウンドキー</returns>
		constexpr [[nodiscard]] std::uint32_t make_round_key(
			const std::uint32_t round) const noexcept {

			std::uint32_t key = this->conversion_constant;

			key += 0x9E3779B9u * (round + 1);

			key ^= key >> 16;
			key *= 0x85EBCA6Bu;
			key ^= key >> 13;

			return key;
		}

		/// <summary>
		/// 暗号化関数
		/// </summary>
		/// <param name="value">暗号化する値</param>
		/// <returns>暗号化した値</returns>
		constexpr [[nodiscard]] std::uint32_t encrypt(
			const std::uint32_t value) const noexcept {

			Block block{
				static_cast<std::uint16_t>(value >> 16),	// 左
				static_cast<std::uint16_t>(value)			// 右
			};

			for (std::uint32_t round = 0; round < ROUND_COUNT; ++round) {
				const std::uint16_t old_left = block.left;

				block.left = block.right;

				block.right = 
					static_cast<std::uint16_t>(
						old_left ^ 
						round_func(block.right, make_round_key(round))
						);
			}

			/*
				最終ラウンド後は
				Ln | Rn
				となっている。

				復号側と対称にするため、
				ここではスワップして
				Rn | Ln
				として返す。
			*/
			return (static_cast<std::uint32_t>(block.right) << 16) | static_cast<std::uint32_t>(block.left);
		}


		/// <summary>
		/// 32bit値をFeistel方式で復号する
		/// </summary>
		constexpr [[nodiscard]] std::uint32_t decrypt(
			const std::uint32_t value) const noexcept {

			Block block{
				static_cast<std::uint16_t>(value >> 16),
				static_cast<std::uint16_t>(value)
			};

			for (std::uint32_t round = ROUND_COUNT; round > 0; --round) {
				const std::uint16_t new_left = block.right;
				const std::uint16_t new_right =
					static_cast<std::uint16_t>(
						block.left ^
						round_func(block.right, make_round_key(round - 1))
						);

				block.left = new_left;
				block.right = new_right;
			}

			return (static_cast<std::uint32_t>(block.right) << 16) | static_cast<std::uint32_t>(block.left);
		}
	};
}