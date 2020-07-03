#pragma once
#include <wx\wx.h>
#include "Company.h"

class AddCompany :public wxDialog
{
public:
    AddCompany(wxWindow* parent, wxWindowID id,
        const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE,
        const wxString& name = wxDialogNameStr);
    ~AddCompany();
    Company* GetData() {
        return data;
    }
private:
    wxButton* add = nullptr;
    wxStaticText* label1 = nullptr;
    wxStaticText* label2 = nullptr;
    wxTextCtrl* company_name = nullptr;
    wxTextCtrl* adress = nullptr;
    Company* data = nullptr;

    void ClickOnAdd(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};
