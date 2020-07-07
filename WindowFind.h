#pragma once
#include<wx\wx.h>
#include<wx\Choice.h>"
#include"IndexManager.h"

class WindowFind : public wxDialog
{
	enum { COMPANY, CUSTOMER, SERVICE_DURATION, SERVICE_PRICE };
	struct data {
		size_t choice_num;
		std::string main_str;
	};
public:
	WindowFind(wxWindow* parent, wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_DIALOG_STYLE,
		const wxString& name = wxDialogNameStr);
	~WindowFind();
	void SetManagerPointer(IndexManager& x);
	data* GetData();

private:
	data* data1 = nullptr;
	wxButton* cancel_b = nullptr;
	wxButton* ok_b = nullptr;
	wxChoice* main_choice = nullptr;
	wxStaticText* lable1 = nullptr;
	wxStaticText* lable2 = nullptr;
	IndexManager* manager = nullptr;
	wxTextCtrl* name_to_find = nullptr;
	wxBoxSizer* main_s = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* top = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* choice_mid = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* bottom = new wxBoxSizer(wxHORIZONTAL);

	void ClickOnOk(wxCommandEvent& event);
	void ClickOnCancel(wxCommandEvent& event);
	void Choosing(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();

};

