#include "AddCompany.h"

wxBEGIN_EVENT_TABLE(AddCompany, wxDialog)
EVT_BUTTON(wxID_ADD, AddCompany::ClickOnAdd)

wxEND_EVENT_TABLE()


AddCompany::AddCompany(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{

	Init();

	(void)Create(parent, id, title, pos, size, style, name);
	this->SetBackgroundColour(wxColour(255, 255, 255));
	add = new wxButton(this, wxID_ADD, "Добавить");
	add->SetBackgroundColour(wxColour(127, 255, 212));
	label1 = new wxStaticText(this, wxID_ANY, "Название компании");
	label2 = new wxStaticText(this, wxID_ANY, "Название компании");
	wxBoxSizer* main_s = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* label = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* text_in = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* button = new wxBoxSizer(wxHORIZONTAL);
	adress = new wxTextCtrl(this, 30002);
	company_name = new wxTextCtrl(this, 30001);
	label->Add(label1, 0, wxALL | wxALIGN_BOTTOM, 10);
	label->Add(label2, 0, wxALL | wxALIGN_BOTTOM, 10);
	text_in->Add(company_name, 0, wxALL | wxALIGN_CENTER, 10);
	text_in->Add(adress, 0, wxALL | wxALIGN_CENTER, 10);
	button->Add(add, 0,wxALL, 10);
	main_s->Add(label, 2, wxBOTTOM, 10);
	main_s->Add(text_in, 2, wxEXPAND, 10);
	main_s->Add(button, 2, wxALL | wxEXPAND, 10);
	this->SetSizerAndFit(main_s); 

}

AddCompany::~AddCompany()
{
}


void AddCompany::ClickOnAdd(wxCommandEvent& event){
	std::string name, adr;
	if (!company_name->IsEmpty() && !adress->IsEmpty()) {
		name = company_name->GetLineText(0);
		adr = adress->GetLineText(0);
		data = new Company(name, Vector<std::string>(), adr);
		company_name->Clear();
		adress->Clear();
		this->Close();
	}
	else {
		wxMessageBox("Введите что нибудь!!!");
	}
	event.Skip();
}
