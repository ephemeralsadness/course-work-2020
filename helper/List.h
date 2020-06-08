#pragma once

#include<iostream>
#include<conio.h>
#include"../aleksei/Company.h"
// Лепёха А.А. Б8118-09.03.04прогин(2)

class MyList {
	/**
	 * Элемент списка, содержит целочисленное значение и указатель на следующий элемент
	 */
private:
	class elem {
	private:
		Company data;
		elem* next;
	public:
		/**
		 * Конструктор узла.
		 * @param data - число, которое будет храниться в узле.
		 * @param next - указатель на следующий узел.
		 */
		elem(Company data, elem* next = NULL) {
			this->data = data;
			this->next = next;
		}
		/**
		 * @return число, которое содержит данный элемент.
		 */
		Company get_data() const{
			return this->data;
		}
		/**
		 * @param _data - число, которое будет храниться в данном элементе.
		 */
		void set_data(Company _data) {
			this->data = _data;
		}
		/**
		 * @return - указатель на следующий элемент списка.
		 */
		elem* getPointer() const {
			return this->next;
		}
		/**
		 * @param _next - задаёт указатель на следующий элемент.
		 */
		void setPointer(elem* _next) {
			this->next = _next;
		}

		Company* GetDataPointer() {
			return &data;
		}
	};
	/**
	 * указатель на первый элемент списка (голову).
	 */
	elem* head;
	size_t last_comparison_amount;
public:
	/**
	 * Конструктор списка. Изначально список не должен иметь элементов,
	 * поэтому указатель на начало списка устанавливается нулевым.
	 */
	MyList(){
		head = NULL;
		last_comparison_amount = 0;
	}
	/**
	 * Деструктор списка. Узлы списка последовательно удаляются, начиная с head.
	 */
	~MyList() {
		if (head != NULL) {
			elem* temp = head;
			elem* buffer = head;
			while (temp->getPointer() != buffer) {
				head = (temp->getPointer());
				delete temp;
				temp = head;
			}
			head = NULL;
		}
	}


	/**
	 * Добавление элемента в конец списка.
	 * 1) Если список пуст, то первым элементом становится голова.
	 * 2) Если спиок состоит только из головы, то создаём новый элемент.
	 * 3) В остальных случаях создаём новый элемент в конце списка.
	 *
	 * @param _data - число которое будет хранить новый элемент.
	 */
	void push(Company _data)
	{

		/**
		 * Если список пуст, то _data заносится в голову списка, и голова в свою очередь ссылается на саму себя.
		 */
		if (isEmpty()){
			head = new elem(_data);
			head->setPointer(head);

		}
		/**
		 *  Если голова ссылается на саму себя, то создаём новый элемент со
		 * значением _data и ссылаем голову на новый элемент, а новый элемент на голову.
		 */
		else if (head == head->getPointer()) {
			elem* temp = head;
			head = new elem(_data);
			head->setPointer(temp);
			temp->setPointer(head);
			head->set_data(temp->get_data());
			temp->set_data(_data);
		}

		/**
		 * В остальных случаях создаём новый элемент в конце списка.
		 */
		else {
			elem* temp = head; //запоминаем ссылку на ячейку памяти головы
			head = new elem(_data); // создаём новую голову со значением _data
			head->setPointer(temp->getPointer()); //ссылаем голову на второй элемент списка
			Company a = temp->get_data(); // сохраняем число из старой ячейки памяти головы
			temp->set_data(head->get_data()); //изменяем значение, хранящееся в старой ячейке памяти головы на _data
			head->set_data(a); // записываем в новую голову значение старой
			temp->setPointer(head); // ссылаем старую ячейку головы на новую голову

		}
	}
	/**
	 * @return true, если список - пустой, иначе - false.
	 */
	bool isEmpty() const {
		return head == NULL;
	}
	/**
	 * @return текущее количество элементов списка.
	 */
	int get_size() const
	{
		if (isEmpty()) return 0;
		else {
			elem* temp = head;
			int i = 1;
			while (temp->getPointer() != head) {
				temp = temp->getPointer();
				i++;
			}
			return i;
		}
	}
	
	void Delete(Company data) {
		elem* temp = head;
		elem* buffer;
		int i = 0;
		int size = this->get_size();
		if (size == 1 && (temp->get_data().GetName() == data.GetName())) {
			delete temp;
			head = NULL;
		}
		while (i < size) {
			i++;
			if (temp->get_data().GetName() == data.GetName()) {
				buffer = temp->getPointer();
				temp->set_data(buffer->get_data());
				temp->setPointer(buffer->getPointer());
				delete buffer;
			}
			temp = temp->getPointer();
		}
	}
	/**
	 *Удаляет заданный элемент
	 * @param number - номер удаляемого элемента
	 */
	void DeleteByIndex(int number) {
		if (number < get_size()-1 && number>=0){  //если заданный элемент не последний
			int i = 0;
			elem* temp = head;
			while (i != number)	{
				temp = temp->getPointer();
				i++;
			}
			elem* buffer = temp->getPointer();
			temp->setPointer(buffer->getPointer());
			temp->set_data(buffer->get_data());
			delete buffer;
		}
		else
			if (number == get_size()-1){//если заданный элемент последний
			
				int i = 0;
				elem* temp = head;
				while (i != number){
					temp = temp->getPointer();
					i++;
				}
				elem* buffer = temp->getPointer();
				temp->setPointer(buffer->getPointer());
				temp->set_data(buffer->get_data());
				head = temp;
				delete buffer;
			}
	}

	Vector<Company> GetAllCompanies() const{
		Vector<Company> v;
		elem* temp = head;
		if (get_size() != 0) {
			do {
				v.PushBack(temp->get_data());
				temp = temp->getPointer();
			} while (temp != head);
		}
		return v;
	}
	 
	Company* Find(std::string name) {
		elem* temp = head;
		last_comparison_amount = 0;
		int i = 0;
		int size = this->get_size();
		while (i < size) {
			i++;
			last_comparison_amount++;
			if (temp->get_data().GetName() == name)
				return temp->GetDataPointer();
		}
		return NULL;
	}

	size_t GetLastComparisonAmount() const {
		return last_comparison_amount;
	}
};
