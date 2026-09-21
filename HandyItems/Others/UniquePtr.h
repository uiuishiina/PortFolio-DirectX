#pragma once

/* ========== Includeファイル ========== */

#include<memory>
#include"Debug/DebugLogSystem.h"

/// <summary>
/// 便利アイテム名前空間
/// </summary>
namespace HandyItems {

	/// <summary>
	/// その他名前空間
	/// </summary>
	namespace others {

		template<typename T>
		class UniqueWeakPtr;

		/// <summary>
		/// Unique参照カウントクラス
		/// </summary>
		/// <typeparam name="T">unique_ptrの型</typeparam>
		template<typename T>
		class UniqueBlock 
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			UniqueBlock() = default;

			/// <summary>
			/// デストラクタ
			/// </summary>
			~UniqueBlock() = default;

			/* ===== Unique操作関数 ===== */

			/// <summary>
			/// Unique作成関数
			/// </summary>
			/// <param name="ptr">unique内オブジェクト参照</param>
			void make_unique(
				T* ptr
			) {

				ptr_ = ptr;
				live_unique = true;
				++refcount_;
			}

			/// <summary>
			/// Unique入れ替え関数
			/// </summary>
			/// <param name="ptr">入れ替えるunique内オブジェクト参照</param>
			void replace_unique(
				T* ptr
			) {
				ptr_ = ptr;
			}

			/// <summary>
			/// Unique削除関数
			/// </summary>
			void delete_unique() {

				//	すでに削除されているならreturn
				if (!has_unique()) {
					return;
				}

				ptr_ = nullptr;
				live_unique = false;
				delete_weak();
			}


			/* ===== Weak操作関数 ===== */

			/// <summary>
			/// 参照カウント追加関数
			/// </summary>
			/// <details>
			/// UniqueWeakPtrがptr_を参照し始めたとき呼び出す
			/// </details>
			void make_weak() {

				++refcount_;
			}

			/// <summary>
			/// 参照カウント削除関数
			/// </summary>
			/// <details>
			/// 参照カウントがなくなったときこのクラスを破棄する
			/// </details>
			void delete_weak() {

				--refcount_;

				if (refcount_ == 0 && !live_unique) {
					delete this;
				}
			}

			/// <summary>
			/// unique_ptr生存フラグ取得関数
			/// </summary>
			/// <returns>unique_ptr生存フラグ</returns>
			[[nodiscard]] bool has_unique() const {
				return live_unique;
			}

			/// <summary>
			/// unique_ptr参照取得関数
			/// </summary>
			/// <returns>unique_ptr参照... ないなら [ nullptr ]</returns>
			[[nodiscard]] T* get_unique() const {
				return has_unique() ? ptr_ : nullptr;
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// unique_ptr生存フラグ
			/// </summary>
			bool live_unique = false;

			/// <summary>
			/// 参照カウント
			/// </summary>
			std::uint32_t refcount_{};

			/// <summary>
			/// unique_ptr参照
			/// </summary>
			T* ptr_{};

		};


		/// <summary>
		/// Uniqueインスタンス保存クラス
		/// </summary>
		/// <typeparam name="T">std::unique_ptrの型</typeparam>
		template<typename T>
		class UniquePtr 
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			/// <summary>
			/// コンストラクタ
			/// </summary>
			/// <details>
			/// block_を [ new ] で確保... [ delete ] はblock_側がやるため触らない
			/// </details>
			UniquePtr():
				block_{ new UniqueBlock<T>{} } {}

			/// <summary>
			/// デストラクタ
			/// </summary>
			~UniquePtr() {
				if (block_) {
					delete_unique();
				}
			}

			/// <summary>
			/// ムーブコンストラクタ
			/// </summary>
			/// <param name="ptr">右辺値</param>
			UniquePtr(UniquePtr&& ptr) :
				unique_{ std::move(ptr.unique_) },
				block_{ std::exchange(ptr.block_, nullptr) } {}

			//	コピーコンストラクタ削除
			UniquePtr(const UniquePtr&) = delete;

			//	コピー演算子削除
			UniquePtr& operator=(const UniquePtr&) = delete;

			//	ムーブ演算子削除
			UniquePtr& operator=(UniquePtr&&) = delete;


			/// <summary>
			/// Unique登録関数
			/// </summary>
			/// <param name="ptr">登録する右辺値</param>
			void register_unique(
				std::unique_ptr<T>&& ptr
			) {
				//	どちらかが nullptr なら return
				if (!ptr || !block_) {
					return;
				}

				unique_ = std::move(ptr);

				//	前身がblock_に登録されているなら入れ替え
				if (block_->has_unique()) {
					block_->replace_unique(unique_.get());
				}
				else {
					block_->make_unique(unique_.get());
				}
			}

			/// <summary>
			/// Unique削除関数
			/// </summary>
			void delete_unique() {

				//	nullptr なら return
				if (!block_) {
					return;
				}

				//	unique削除後、block_を扱えないように
				unique_ = nullptr;
				block_->delete_unique();
				block_ = nullptr;
			}

			/// <summary>
			/// unique_ptr本体参照取得関数
			/// </summary>
			/// <returns>本体参照</returns>
			[[nodiscard]] T* get() const noexcept {

				if (!block_->has_unique()) {
					DEBUG_ERROR_LOG("Not Found Unique");
					return nullptr;
				}
				return unique_.get();
			}

			/// <summary>
			/// unique_ptr本体参照アロー演算子オーバーロード
			/// </summary>
			/// <returns>本体参照</returns>
			[[nodiscard]] T* operator -> () const noexcept {
				return get();
			}

			/// <summary>
			/// unique_ptr生存フラグ取得関数
			/// </summary>
			/// <returns>unique_ptr生存フラグ</returns>
			[[nodiscard]] bool has_unique() const noexcept {
				return block_->has_unique();
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// 友達登録
			/// </summary>
			friend UniqueWeakPtr<T>;

			/// <summary>
			/// unique_ptr本体
			/// </summary>
			std::unique_ptr<T> unique_{};

			/// <summary>
			/// UniqueBlock参照
			/// </summary>
			UniqueBlock<T>* block_{};

			/// <summary>
			/// 友達呼び出し関数
			/// </summary>
			/// <returns>UniqueBlock参照</returns>
			[[nodiscard]] UniqueBlock<T>* get_block() const {
				return block_;
			}

		};


		/// <summary>
		/// Unique参照保存クラス
		/// </summary>
		/// <typeparam name="T">std::unique_ptrの型</typeparam>
		template<typename T>
		class UniqueWeakPtr
		{
		public:
			/* ========== Publicメンバー関数 ========== */

			//	コンストラクタ削除
			UniqueWeakPtr() = delete;

			/// <summary>
			/// 引数付きコンストラクタ
			/// </summary>
			/// <param name="p">Uniqueインスタンス保存クラス参照</param>
			UniqueWeakPtr(
				const UniquePtr<T>* p
			) :
				block_{ 
				p ? p->get_block() : nullptr 
			} {
			
				make_weak();
			}

			/// <summary>
			/// デストラクタ
			/// </summary>
			~UniqueWeakPtr() {
				if (block_) {
					block_->delete_weak();
				}
			}

			/// <summary>
			/// unique生存チェック関数
			/// </summary>
			/// <returns>生存フラグ</returns>
			[[nodiscard]] bool check() const {
				
				if (block_) {
					return block_->has_unique();
				}
				else {
					return false;
				}
			}

			/// <summary>
			/// weak参照作成関数
			/// </summary>
			/// <returns>参照できるなら [ true ]</returns>
			bool make_weak() {

				if (block_) {
					if (!is_active_weak) {
						is_active_weak = true;
						block_->make_weak();
					}
					return true;
				}

				return false;
			}

			/// <summary>
			/// weak参照経由unique_ptr取得関数
			/// </summary>
			/// <returns>unique_ptr参照... ないなら [ nullptr ]</returns>
			[[nodiscard]] T* get() const {
				return block_ ? block_->get_unique() : nullptr;
			}

			[[nodiscard]] T* operator -> () const {
				return get();
			}

		private:
			/* ========== Privateメンバー変数 ========== */

			/// <summary>
			/// Unique参照カウントクラス参照
			/// </summary>
			UniqueBlock<T>* block_{};

			/// <summary>
			/// Weak参照可能フラグ
			/// </summary>
			/// <details>
			/// block_に購読対象として登録してあるなら [ true ]
			/// </details>
			bool is_active_weak = false;

		};

		/// <summary>
		/// Unique参照保存クラス作成補助関数
		/// </summary>
		/// <typeparam name="T">std::unique_ptrの型</typeparam>
		/// <param name="unique">Uniqueインスタンス保存クラス参照</param>
		/// <returns>作成したUnique参照保存クラス</returns>
		template<typename T>
		[[nodiscard]] static UniqueWeakPtr<T> make_unique_weak(const UniquePtr<T>& unique) {
			return UniqueWeakPtr<T>{&unique};
		}

	}
}