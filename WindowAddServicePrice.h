#pragma once
#include <wx\wx.h>
#include "IndexManager.h"
#include <wx\Choice.h>

class WindowAddServicePrice :public wxDialog
{
	static struct data {
		std::string name_c;
		std::string name_s;
		std::string measure_s;
		double price_s;
	};
	data* data1 = nullptr;
public:
	WindowAddServicePrice(wxWindow* parent, wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_DIALOG_STYLE,
		const wxString& name = wxDialogNameStr);
	~WindowAddServicePrice();
	void SetManagerPointer(IndexManager& x);
	data* GetData();
private:
	wxButton* add = nullptr;
	wxStaticText* label1 = nullptr;
	wxStaticText* label2 = nullptr;
	wxStaticText* label3 = nullptr;
	wxStaticText* label4 = nullptr;
	wxChoice* company_name = nullptr;
	wxChoice* service_name = nullptr;
	wxTextCtrl* service_price = nullptr;
	wxTextCtrl* service_measure = nullptr;
	IndexManager* manager_pointer = nullptr;
	void ClickOnAdd(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};
