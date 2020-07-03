#pragma once
#include <wx\wx.h>
#include "IndexManager.h"
#include <wx\Choice.h>

class WindowAddCustomer :public wxDialog
{
    static struct data {
        std::string name_company;
        std::string name_service;
        std::string name_customer;
        std::uint16_t volume;
    };
    data* data1 = nullptr;
public:
    WindowAddCustomer(wxWindow* parent, wxWindowID id,
        const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE,
        const wxString& name = wxDialogNameStr);
    ~WindowAddCustomer();
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
    wxTextCtrl* service_volume = nullptr;
    wxTextCtrl* customer_name = nullptr;
    IndexManager* manager_pointer = nullptr;
    void ClickOnAdd(wxCommandEvent& event);
    void CompanyChoice(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};
