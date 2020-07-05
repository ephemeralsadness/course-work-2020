#pragma once
#include <wx\wx.h>
#include "ServiceDuration.h"

class WindowAddServiceDuration :public wxDialog
{
public:
	WindowAddServiceDuration(wxWindow* parent, wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_DIALOG_STYLE,
		const wxString& name = wxDialogNameStr);
	~WindowAddServiceDuration();
	ServiceDuration* GetData() {
		return data;
	}
private:
	wxButton* add = nullptr;
	wxStaticText* label1 = nullptr;
	wxStaticText* label2 = nullptr;
	wxStaticText* label3 = nullptr;
	wxTextCtrl* name_ser = nullptr;
	wxTextCtrl* min_dur = nullptr;
	wxTextCtrl* max_dur = nullptr;
	ServiceDuration* data = nullptr;

	void ClickOnAdd(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};
