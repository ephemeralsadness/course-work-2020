#pragma once
#include<wx\wx.h>
#include <wx\richtext\richtextbuffer.h>
#include <wx\listctrl.h>
#include"IndexManager.h"

class cMain :public wxFrame
{
public:
	cMain();
	~cMain();
private:
	wxMenuBar* m_menu_bar = nullptr;
	wxButton* add_to_list = new wxButton(this, 10101, "Добавить", wxDefaultPosition, wxSize(150, 50), 0);
	wxButton* remove_from_list = new wxButton(this, 10102, "Удалить", wxDefaultPosition, wxSize(150, 50), 0);
	wxButton* show_list = new wxButton(this, 10103, "Показать", wxDefaultPosition, wxSize(150, 50), 0);
	wxButton* search = new wxButton(this, 10104, "Найти", wxDefaultPosition, wxSize(150, 50), 0);
	wxBoxSizer* buttons_box = nullptr;
	wxBoxSizer* main_box = nullptr;
	wxListView* main_list = nullptr;
	wxDialog* choice = nullptr;
	IndexManager data_manager;

	void ClickOnMenuNew(wxCommandEvent& event);
	void ClickOnMenuOpen(wxCommandEvent& event);
	void ClickOnMenuSave(wxCommandEvent& event);
	void ClickOnMenuSaveAs(wxCommandEvent& event);
	void ClickOnMenuExit(wxCommandEvent& event);
	void ClickOnAdd(wxCommandEvent& event);
	void ClickOnRemove(wxCommandEvent& event);
	void ClickOnShow(wxCommandEvent& event);
	void ClickOnSearch(wxCommandEvent& event);
	void ClickOnCustomer(wxCommandEvent& event);
	void ClickOnCompany(wxCommandEvent& event);
	void ClickOnServicePrice(wxCommandEvent& event);
	void ClickOnServiceLength(wxCommandEvent& event);
	void ClickOnAddCustomer(wxCommandEvent& event);
	void ClickOnAddCompany(wxCommandEvent& event);
	void ClickOnAddServicePrice(wxCommandEvent& event);
	void ClickOnAddServiceDuration(wxCommandEvent& event);
	void ClickOnOkAdd(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();
};

