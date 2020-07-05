#include "ForwardList.h"

namespace Aleksei /* но сделал Саня */ {

	/**
	 * Конструктор по умолчанию
	 */
	ForwardList::ForwardList() noexcept
		: head(nullptr),
		size(0),
		last_comparison_amount(0) {}


	/**
	 * Деструктор
	 * Последовательно удаляет узлы списка, начиная с head
	 */
	ForwardList::~ForwardList() noexcept {
		DeallocateList(head);
	}


	/**
	 * Конструктор копирования
	 * Конструирует список, последовательно вставляя
	 * копии всех объектов списка another в том же порядке,
	 * в каком они были в списке another.
	 *
	 * @param another - список, из которого копируются объекты
	 */
	ForwardList::ForwardList(const ForwardList& another) noexcept
		: head(nullptr),
		size(another.size),
		last_comparison_amount(0) {

		// если another - пустой список, то копировать нечего
		if (another.Empty())
			return;

		// копируем первый элемент списка another
		head = AllocateNode(std::move(another.head->data));
		Node* this_ptr = head;
		Node* another_ptr = another.head->next;

		// последовательно копируем остальные элементы another
		while (another_ptr != nullptr) {
			this_ptr->next = AllocateNode(std::move(another_ptr->data));
			this_ptr = this_ptr->next;
			another_ptr = another_ptr->next;
		}

		// размер этого списка теперь равен размеру another
		size = another.size;
	}


	/**
	 * Оператор присваивания копированием
	 * Работает как конструктор копирования с тем отличием, что
	 * уже есть созданный объект ForwardList, с которым надо
	 * произвести такие операции, что он станет копией списка another.
	 *
	 * @param another - список, из которого копируются объекты
	 */
	ForwardList& ForwardList::operator = (const ForwardList& another) noexcept {
		// Если this и &another - одинаковые списки, то
		// у нас нет нужды в их копировании.
		if (this == &another)
			return *this;

		if (another.Empty()) {                          // если another - пустой список
			// удаляем все элементы списка, начиная с head
			// и устанавливаем размер равный 0
			DeallocateList(head);
			size = 0;
		}
		else if (this->Empty()) {                     // если текущий список - пустой
		 // создается новый объект списка при помощи
		 // конструктора копирования, после чего
		 // вызывается оператор перемещающего присваивания
		 // от нового объекта.
		 // теоретически, это должно работать без std::move,
		 // но так безопаснее.
			*this = std::move(ForwardList(another));
		}
		else if (this->Size() < another.Size()) {      // если текущий список меньше another
	  // создается два указателя на узлы разных списков
			Node* this_ptr = head;
			Node* another_ptr = another.head;

			// копируем все объекты в текущий список,
			// не изменяя структуру узлов (не создавая новые)
			while (this_ptr->next != nullptr) {
				this_ptr->data = another_ptr->data;
				this_ptr = this_ptr->next;
				another_ptr = another_ptr->next;
			}

			// копируем последний объект, для которого
			// найдется узел в текущем списке
			this_ptr->data = another_ptr->data;
			another_ptr = another_ptr->next;

			// добавляем новые узлы для объектов, которым
			// не хватило места, и добавляем их в список
			while (another_ptr != nullptr) {
				this_ptr->next = AllocateNode(std::move(another_ptr->data));
				this_ptr = this_ptr->next;
				another_ptr = another_ptr->next;
			}

		}
		else {                                        // если текущий список больше/равен another
	  // создается два указателя на узлы разных списков
			Node* this_ptr = head;
			Node* another_ptr = another.head;

			// копируем все объекты в текущий список,
			// не изменяя структуру узлов (не создавая новые)
			while (another_ptr->next != nullptr) {
				this_ptr->data = another_ptr->data;
				this_ptr = this_ptr->next;
				another_ptr = another_ptr->next;
			}

			// копируем последний элемент в текущий список
			this_ptr->data = another_ptr->data;

			// удаляем оставшиеся/неиспользованные узлы из
			// списка и отнимаем от размера количество удаленных
			// узлов, получая новый размер списка.
			size -= DeallocateList(this_ptr->next);
		}
		return *this;
	}


	/**
	 * Конструктор перемещения
	 * Конструирует список за константное время,
	 * делая список another невалидным для использования
	 *
	 * @param another - список, из которого перемещаются объекты
	 */
	ForwardList::ForwardList(ForwardList&& another) noexcept
		: head(another.head),
		size(another.size),
		last_comparison_amount(another.last_comparison_amount) {

		// начало списка another должно стать nullptr, потому что
		// иначе это может привести к ошибкам (например delete дважды
		// по одному и тому же месту в деструкторе)
		another.head = nullptr;
		size = 0;

	}


	/**
	 * Оператор присваивания перемещением
	 * Работает как конструктор перемещения с тем отличием, что
	 * уже есть созданный объект ForwardList. Список another
	 * будет невалидным для использования.
	 *
	 * @param another - список, из которого копируются объекты
	 */
	ForwardList& ForwardList::operator = (ForwardList&& another) noexcept {
		// подробнее в операторе присваивания копированием
		if (this == &another)
			return *this;

		// удаляем текущий список
		DeallocateList(head);

		// перемещаем поля списка another в текущий список.
		head = another.head;
		size = another.size;
		last_comparison_amount = another.last_comparison_amount;
		another.head = nullptr;
		size = 0;

		return *this;
	}


	/**
	 * Вставка объекта
	 * Вставка производится в начало списка. Список позволяет
	 * хранить повторяющиеся значения
	 *
	 * @param value - объект для вставки
	 */
	void ForwardList::Push(value_t value) noexcept {
		// создаем новый узел
		Node* new_head = AllocateNode(std::move(value));
		// заменяем начало списка новым узлом
		new_head->next = head;
		head = new_head;

		++size;
	}


	/**
	 * Удаление объекта
	 * Удаляет первое вхождение объекта с ключом (полем name)
	 * key. Если объекта с таким ключом в списке нет, то список
	 * не изменяется.
	 *
	 * @param key ключ, по которому надо удалить объект
	 * @return true, если объект был удален, иначе - false
	 */
	bool ForwardList::Erase(const key_t& key) noexcept {
		// обнуляем переменную, хранящую последнее кол-во сравнений
		last_comparison_amount = 0;

		if (Empty()) {                                          // если список - пустой
			return false;
		}
		else if (Equals(head->data.GetName(), key)) {     // если начало списка содержит
															 // объект с ключом key
		 // изменяем переменную, хранящую размер списка
			--size;
			// удаляем первый узел списка
			Node* temp_ptr = head;
			head = head->next;
			DeallocateNode(temp_ptr);

			return true;

		}
		else {                                                // ищем объект в списке
			Node* prev_ptr = head;
			Node* this_ptr = head->next;

			while (this_ptr != nullptr) {
				// если объект с таким ключом найден
				if (Equals(this_ptr->data.GetName(), key)) {
					// изменяем переменную, хранящую размер списка
					--size;
					// удаляем этот узел списка
					prev_ptr->next = this_ptr->next;
					DeallocateNode(this_ptr);
					return true;
				}
			}

		}

		return false;
	}


	/**
	 * Поиск объекта по ключу.
	 * Ищет первое вхождение объекта с ключом key
	 *
	 * @param key ключ, по которому надо найти объект
	 * @return константный указатель на первый элемент списка с данным ключом, или
	 *         nullptr, если объекта с данным ключом
	 */
	const ForwardList::value_t* ForwardList::Find(const key_t& key) const noexcept {
		// обнуляем переменную, хранящую последнее кол-во сравнений
		last_comparison_amount = 0;

		// если список - пустой, то возвращаем nullptr
		if (Empty())
			return nullptr;

		// просматриваем каждый элемент списка
		for (Node* it = head; it != nullptr; it = it->next) {
			// если ключи совпали, возвращаем указатель на объект Company
			if (Equals(key, it->data.GetName()))
				return &it->data;
		}

		return nullptr;
	}


	/**
	 * Поиск объекта по ключу.
	 * Ищет первое вхождение объекта с ключом key
	 *
	 * @param key ключ, по которому надо найти объект
	 * @return указатель на первый элемент списка с данным ключом, или
	 *         nullptr, если объекта с данным ключом
	 */
	ForwardList::value_t* ForwardList::Find(const key_t& key) noexcept {
		// вызываем константный метод Find
		return const_cast<value_t*>(
			static_cast<const ForwardList*>(this)->Find(key)
			);
	}


	/**
	 * Преобразование в Vector<value_t>
	 * Копирует объекты, хранящиеся в списке в Vector и возвращает его
	 *
	 * @return Vector<value_t>, состоящий из объектов, хранящихся в списке
	 */
	Vector<ForwardList::value_t> ForwardList::ToVector() const noexcept {
		// создаем Vector с зарезервированной памятью под size элементов
		Vector<value_t> result;
		result.Reserve(size);

		ForEach([&result](const value_t& value) {
			result.PushBack(value);
			});

		return result;
	}

	/**
	 * Преобразование в Vector<const value_t*>
	 * Копирует указатели на объекты, хранящиеся в списке в Vector и возвращает его
	 *
	 * @return Vector<const value_t*>, состоящий из указателей на объекты, хранящихся в списке
	 */
	Vector<const ForwardList::value_t*> ForwardList::ToPointerVector() const noexcept {
		// создаем Vector с зарезервированной памятью под size элементов
		Vector<const value_t*> result;
		result.Reserve(size);

		ForEach([&result](const value_t& value) {
			result.PushBack(&value);
			});

		return result;
	}
	/**
	 * Размер списка
	 *
	 * @return количество элементов в списке
	 */
	size_t ForwardList::Size() const noexcept {
		return size;
	}


	/**
	 * Проверка на пустоту
	 *
	 * @return true, если список - пустой, иначе - false
	 */
	bool ForwardList::Empty() const noexcept {
		return head == nullptr;
	}


	/**
	 * Количество сравнений
	 *
	 * @return количество сравнений объектов Company за последний
	 *         вызов метода Find/Remove
	 */
	size_t ForwardList::LastComparisonAmount() const noexcept {
		return last_comparison_amount;
	}


	/**
	 * Аллокация нового узла
	 *
	 * @param data - объект класса Company
	 * @return указатель на новый узел с объектом Company
	 */
	ForwardList::Node* ForwardList::AllocateNode(value_t data) const noexcept {
		return new Node{ std::move(data), nullptr };
	}


	/**
	 * Деаллокация узла
	 *
	 * @param node узел, который надо деаллоцировать
	 */
	void ForwardList::DeallocateNode(Node* node) const noexcept {
		delete node;
	}


	/**
	 * Деаллокация списка, начиная с узла start
	 *
	 * @param start узел, с которого надо начать последовательную
	 *        деаллокацию
	 * @return количество удаленных узлов
	 */
	size_t ForwardList::DeallocateList(Node* start) const noexcept {
		size_t counter = 0;

		while (start != nullptr) {
			// удаляем узел start
			Node* temp = start->next;
			DeallocateNode(start);
			start = temp;
			++counter;
		}

		return counter;
	}


	/**
	 * Проверка ключей на равенство
	 *
	 * @param lhs ключ первого объекта
	 * @param rhs ключ второго объекта
	 * @return true, если ключи равны, иначе - false
	 */
	bool ForwardList::Equals(const key_t& lhs, const key_t& rhs) const noexcept {
		++last_comparison_amount;
		return lhs == rhs;
	}
}
