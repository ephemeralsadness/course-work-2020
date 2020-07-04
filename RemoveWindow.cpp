#include "RemoveWindow.h"

wxBEGIN_EVENT_TABLE(RemoveWindow, wxDialog)
EVT_BUTTON(wxID_OK, RemoveWindow::ClickOnOk)
EVT_BUTTON(wxID_CANCEL, RemoveWindow::ClickOnCancel)
EVT_CHOICE(wxID_SETUP, RemoveWindow::Choosing)
EVT_CHOICE(wxID_APPLY, RemoveWindow::CompanyChosen)
wxEND_EVENT_TABLE()

RemoveWindow::RemoveWindow(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    Init();
    (void)Create(parent, id, title, pos, size, style, name);

    this->SetBackgroundColour(wxColour(255, 255, 255));
    
 
    wxArrayString choices;
    choices.Add("��������");
    choices.Add("��������");
    choices.Add("������");
    choices.Add("������ � ��������");

    main_choice = new wxChoice(this, wxID_SETUP, wxDefaultPosition, wxDefaultSize,choices);
    label1 = new wxStaticText(this, wxID_ANY, "�������� ��� �������:");
    top->Add(label1, 1, wxALL, 5);
    top->Add(main_choice, 1, wxALL, 5);
    top->Layout();
    ok_b = new wxButton(this, wxID_OK, "��");
    cancel_b = new wxButton(this, wxID_CANCEL, "������");
    bottom->Add(ok_b, 1, wxALL,5);
    bottom->Add(cancel_b, 1, wxALL, 5);
   
    label2 = new wxStaticText(this, wxID_ANY, "_______________");
    label3 = new wxStaticText(this, wxID_ANY, "_______________");
    first_choice = new wxChoice(this, wxID_APPLY);
    second_choice = new wxChoice(this, wxID_ANY);
    lable_mid->Add(label2, 1, wxALL | wxALIGN_BOTTOM, 10);
    lable_mid->Add(label3, 1, wxALL | wxALIGN_BOTTOM, 10);
    choice_mid->Add(first_choice, 1, wxALL | wxALIGN_BOTTOM, 10);
    choice_mid->Add(second_choice, 1, wxALL | wxALIGN_BOTTOM, 10);
    main_s->Add(top, wxEXPAND);
    main_s->Add(lable_mid, wxEXPAND);
    main_s->Add(choice_mid, wxEXPAND);
    main_s->Add(bottom, wxEXPAND);
    this->SetSizerAndFit(main_s);
}

RemoveWindow::~RemoveWindow(){
}

void RemoveWindow::SetManagerPointer(IndexManager& x){
    manager = &x;
}

RemoveWindow::data* RemoveWindow::GetData(){
    return data1;
}

void RemoveWindow::ClickOnOk(wxCommandEvent& event){
    if (main_choice->GetString(main_choice->GetSelection()) == "������ � ��������" && (first_choice->GetSelection() == wxNOT_FOUND || second_choice->GetSelection() == wxNOT_FOUND)) {
        wxMessageBox("�������� ��� �������!!");
    }
    else if (main_choice->GetSelection() == wxNOT_FOUND || first_choice->GetSelection() == wxNOT_FOUND) {
        wxMessageBox("�������� ��� �������!!");
    }
    else {
        data1 = new data;
        std::string str = (std::string)main_choice->GetString(main_choice->GetSelection());
        if (str == "��������") {
            data1->choice_num = COMPANY;
            data1->main_str = first_choice->GetString(first_choice->GetSelection());
        }
        else if (str == "��������") {
            data1->choice_num = CUSTOMER;
            data1->main_str = first_choice->GetString(first_choice->GetSelection());

        }
        else if (str == "������") {
            data1->choice_num = SERVICE_ALL;
            data1->main_str = first_choice->GetString(first_choice->GetSelection());
        }
        else if (str == "������ � ��������") {
            data1->choice_num = SERVICE_COMPANY;
            data1->main_str = first_choice->GetString(first_choice->GetSelection());
            data1->additional_str = second_choice->GetString(second_choice->GetSelection());
        }
        this->Close();
        event.Skip();
    }

}

void RemoveWindow::ClickOnCancel(wxCommandEvent& event)
{
    this->Close();
    event.Skip();
}

void RemoveWindow::Choosing(wxCommandEvent& event)
{
    
    std::string str = (std::string)main_choice->GetString(main_choice->GetSelection()) ;
    if (str == "��������") {
        choice_mid->Show(true);
        lable_mid->Show(true);
        choice_mid->Hide(second_choice);
        lable_mid->Hide(label3);
        label2->SetLabelText("�������� ��������");
        first_choice->Clear();
        Vector<std::string> str_vec;
        Vector<Pair<Company,size_t>> all_companies = manager->LookUpCompanies();
        for (size_t i = 0; i < all_companies.Size(); i++) {
            str_vec.PushBack(all_companies[i].first.GetName());
        }
        for (size_t i = 0; i < str_vec.Size(); i++)
            first_choice->Append(str_vec[i]);
    }
    else if (str == "��������") {
        choice_mid->Show(true);
        lable_mid->Show(true);
        choice_mid->Hide(second_choice);
        lable_mid->Hide(label3);
        label2->SetLabelText("�������� ���������");
        first_choice->Clear();
        Vector<std::string> str_vec;
        Vector<Customer> all_companies = manager->LookUpCustomers();
        for (size_t i = 0; i < all_companies.Size(); i++) {
            str_vec.PushBack(all_companies[i].GetName());
        }
        for (size_t i = 0; i < str_vec.Size(); i++)
            first_choice->Append(str_vec[i]);
    }
    else if (str == "������") {
        choice_mid->Show(true);
        lable_mid->Show(true);
        choice_mid->Hide(second_choice);
        lable_mid->Hide(label3);
        label2->SetLabelText("�������� ������");
        first_choice->Clear();
        Vector<std::string> str_vec;
        Vector<Pair<ServiceDuration,size_t>> all_companies = manager->LookUpServiceDurations();
        for (size_t i = 0; i < all_companies.Size(); i++) {
            str_vec.PushBack(all_companies[i].first.GetName());
        }
        for (size_t i = 0; i < str_vec.Size(); i++)
            first_choice->Append(str_vec[i]);
    }
    else if (str == "������ � ��������") {
        choice_mid->Show(true);
        lable_mid->Show(true);
        choice_mid->Hide(second_choice);
        lable_mid->Hide(label3);
        label2->SetLabelText("�������� ��������");
        first_choice->Clear();
        Vector<std::string> str_vec;
        Vector<Pair<Company, size_t>> all_companies = manager->LookUpCompanies();
        for (size_t i = 0; i < all_companies.Size(); i++) {
            str_vec.PushBack(all_companies[i].first.GetName());
        }
        for (size_t i = 0; i < str_vec.Size(); i++) {
            first_choice->Append(str_vec[i]);
        }
    }
    else {
        choice_mid->Hide(first_choice);
        lable_mid->Hide(label2);
        choice_mid->Hide(second_choice);
        lable_mid->Hide(label3);
    }

}

void RemoveWindow::CompanyChosen(wxCommandEvent& event){
    if (main_choice->GetString(main_choice->GetSelection()) == "������ � ��������") {
        label3->SetLabelText("�������� ������");
        lable_mid->Clear();
        lable_mid->Add(label2, 1, wxALL | wxALIGN_CENTER, 10);
        lable_mid->Add(label3, 1, wxALL | wxALIGN_CENTER, 10);
        choice_mid->Show(second_choice);
        lable_mid->Show(label3);
        second_choice->Clear();
        Company company = manager->FindCompany((std::string)first_choice->GetString(first_choice->GetSelection()));
        for (size_t i = 0; i < company.GetServices().Size(); i++)
            second_choice->Append(company.GetServices()[i]);
    }
}
