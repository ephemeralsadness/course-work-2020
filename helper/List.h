#pragma once

#include<iostream>
#include<conio.h>
#include"../aleksei/Company.h"
// ����� �.�. �8118-09.03.04������(2)

class MyList {
	/**
	 * ������� ������, �������� ������������� �������� � ��������� �� ��������� �������
	 */
private:
	class elem {
	private:
		Company data;
		elem* next;
	public:
		/**
		 * ����������� ����.
		 * @param data - �����, ������� ����� ��������� � ����.
		 * @param next - ��������� �� ��������� ����.
		 */
		elem(Company data, elem* next = NULL) {
			this->data = data;
			this->next = next;
		}
		/**
		 * @return �����, ������� �������� ������ �������.
		 */
		Company get_data() const{
			return this->data;
		}
		/**
		 * @param _data - �����, ������� ����� ��������� � ������ ��������.
		 */
		void set_data(Company _data) {
			this->data = _data;
		}
		/**
		 * @return - ��������� �� ��������� ������� ������.
		 */
		elem* getPointer() const {
			return this->next;
		}
		/**
		 * @param _next - ����� ��������� �� ��������� �������.
		 */
		void setPointer(elem* _next) {
			this->next = _next;
		}

		Company* GetDataPointer() {
			return &data;
		}
	};
	/**
	 * ��������� �� ������ ������� ������ (������).
	 */
	elem* head;
	size_t last_comparison_amount;
public:
	/**
	 * ����������� ������. ���������� ������ �� ������ ����� ���������,
	 * ������� ��������� �� ������ ������ ��������������� �������.
	 */
	MyList(){
		head = NULL;
		last_comparison_amount = 0;
	}
	/**
	 * ���������� ������. ���� ������ ��������������� ���������, ������� � head.
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
	 * ���������� �������� � ����� ������.
	 * 1) ���� ������ ����, �� ������ ��������� ���������� ������.
	 * 2) ���� ����� ������� ������ �� ������, �� ������ ����� �������.
	 * 3) � ��������� ������� ������ ����� ������� � ����� ������.
	 *
	 * @param _data - ����� ������� ����� ������� ����� �������.
	 */
	void push(Company _data)
	{

		/**
		 * ���� ������ ����, �� _data ��������� � ������ ������, � ������ � ���� ������� ��������� �� ���� ����.
		 */
		if (isEmpty()){
			head = new elem(_data);
			head->setPointer(head);

		}
		/**
		 *  ���� ������ ��������� �� ���� ����, �� ������ ����� ������� ��
		 * ��������� _data � ������� ������ �� ����� �������, � ����� ������� �� ������.
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
		 * � ��������� ������� ������ ����� ������� � ����� ������.
		 */
		else {
			elem* temp = head; //���������� ������ �� ������ ������ ������
			head = new elem(_data); // ������ ����� ������ �� ��������� _data
			head->setPointer(temp->getPointer()); //������� ������ �� ������ ������� ������
			Company a = temp->get_data(); // ��������� ����� �� ������ ������ ������ ������
			temp->set_data(head->get_data()); //�������� ��������, ���������� � ������ ������ ������ ������ �� _data
			head->set_data(a); // ���������� � ����� ������ �������� ������
			temp->setPointer(head); // ������� ������ ������ ������ �� ����� ������

		}
	}
	/**
	 * @return true, ���� ������ - ������, ����� - false.
	 */
	bool isEmpty() const {
		return head == NULL;
	}
	/**
	 * @return ������� ���������� ��������� ������.
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
	 *������� �������� �������
	 * @param number - ����� ���������� ��������
	 */
	void DeleteByIndex(int number) {
		if (number < get_size()-1 && number>=0){  //���� �������� ������� �� ���������
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
			if (number == get_size()-1){//���� �������� ������� ���������
			
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
