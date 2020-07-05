#pragma once
#include<wx/\wx.h>
#include<wx\Choice.h>
#include"IndexManager.h"

class RemoveWindow : public wxDialog
{
	enum { COMPANY, CUSTOMER, SERVICE_ALL, SERVICE_COMPANY };
	struct data {
		size_t choice_num;
		std::string main_str;
		std::string additional_str;
	};
public:
	RemoveWindow(wxWindow* parent, wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_DIALOG_STYLE,
		const wxString& name = wxDialogNameStr);
	~RemoveWindow();
	void SetManagerPointer(IndexManager& x);
	data* GetData();
private:

	data* data1 = nullptr;
	wxButton* cancel_b = nullptr;
	wxButton* ok_b = nullptr;
	wxChoice* main_choice = nullptr;
	wxChoice* first_choice = nullptr;
	wxChoice* second_choice = nullptr;
	wxStaticText* label1 = nullptr;
	wxStaticText* label2 = nullptr;
	wxStaticText* label3 = nullptr;
	IndexManager* manager = nullptr;
	wxBoxSizer* main_s = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* top = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lable_mid = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* choice_mid = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* bottom = new wxBoxSizer(wxHORIZONTAL);

	void ClickOnOk(wxCommandEvent& event);
	void ClickOnCancel(wxCommandEvent& event);
	void Choosing(wxCommandEvent& event);
	void CompanyChosen(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();
};

