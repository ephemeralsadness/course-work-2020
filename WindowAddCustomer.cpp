#include "WindowAddCustomer.h"

wxBEGIN_EVENT_TABLE(WindowAddCustomer, wxDialog)
EVT_BUTTON(wxID_ADD, WindowAddCustomer::ClickOnAdd)
EVT_CHOICE(30001, WindowAddCustomer::CompanyChoice)
wxEND_EVENT_TABLE()


WindowAddCustomer::WindowAddCustomer(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{

	Init();

	(void)Create(parent, id, title, pos, size, style, name);
	this->SetBackgroundColour(wxColour(255, 255, 255));
	add = new wxButton(this, wxID_ADD, "Добавить");
	add->SetBackgroundColour(wxColour(127, 255, 212));
	label1 = new wxStaticText(this, wxID_ANY, "Имя заказчика");
	label2 = new wxStaticText(this, wxID_ANY, "Название компании");
	label3 = new wxStaticText(this, wxID_ANY, "Наименованеи услуги");
	label4 = new wxStaticText(this, wxID_ANY, "Объем заказаннйо услуги");
	wxBoxSizer* main_s = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* label = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* text_in = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* button = new wxBoxSizer(wxHORIZONTAL);
	company_name = new wxChoice(this, 30001);
	service_name = new wxChoice(this, 30002);
	company_name->SetBackgroundColour(wxColour(255, 255, 255));
	service_name->SetBackgroundColour(wxColour(255, 255, 255));
	company_name->SetOwnBackgroundColour(wxColour(255, 255, 255));
	customer_name = new wxTextCtrl(this, 30003);
	service_volume = new wxTextCtrl(this, 30004);
	label->Add(label1, 1, wxALL | wxALIGN_BOTTOM, 10);
	label->Add(label2, 1, wxALL | wxALIGN_BOTTOM, 10);
	label->Add(label3, 1, wxALL | wxALIGN_BOTTOM, 10);
	label->Add(label4, 1, wxALL | wxALIGN_BOTTOM, 10);

	text_in->Add(customer_name, 1, wxALL | wxALIGN_BOTTOM, 10);
	text_in->Add(company_name, 1, wxALL | wxALIGN_BOTTOM, 10);
	text_in->Add(service_name, 1, wxALL | wxALIGN_BOTTOM, 10);
	text_in->Add(service_volume, 1, wxALL | wxALIGN_BOTTOM, 10);
	button->Add(add, 1, wxALIGN_CENTER, 10);
	main_s->Add(label, 1, wxBOTTOM, 10);
	main_s->Add(text_in, 1, wxEXPAND, 10);
	main_s->Add(button, 1, wxALIGN_CENTER, 10);
	this->SetSizerAndFit(main_s);
}

WindowAddCustomer::~WindowAddCustomer()
{
}

void WindowAddCustomer::SetManagerPointer(IndexManager& x) {
	manager_pointer = &x;
	Vector<Pair<Company, size_t>> companies = manager_pointer->LookUpCompanies();
	for (int i = 0; i < companies.Size(); i++) {
		company_name->Append(companies[i].first.GetName());
	}
}

WindowAddCustomer::data* WindowAddCustomer::GetData() {
	return data1;
}

void WindowAddCustomer::ClickOnAdd(wxCommandEvent& event) {

	if (company_name->GetSelection() == wxNOT_FOUND && service_name->GetSelection() == wxNOT_FOUND) {
		wxMessageBox("Выберете компанию и услугу");
	}
	else if (company_name->GetSelection() == wxNOT_FOUND) {
		wxMessageBox("Выберете компанию");
	}
	else if (service_name->GetSelection() == wxNOT_FOUND) {
		wxMessageBox("Выберете услугу");
	}
	else if (service_name->GetCount() == 0) {
		wxMessageBox("Данная компания не предоставляет услуг");
	}
	else if (customer_name->IsEmpty() || service_volume->IsEmpty()) {
		wxMessageBox("Заполните пустые поля!!");
	}
	else try {
		data1 = new data;
		data1->name_company = company_name->GetString(company_name->GetSelection());
		data1->name_service = service_name->GetString(service_name->GetSelection());
		data1->name_customer = customer_name->GetLineText(0);
		data1->volume = std::stoul((std::string)service_volume->GetLineText(0));
		this->Close();
	}
	catch (std::exception& e) {
		wxMessageBox("В поле для цены должно быть целое положительное число!!");
	}
	event.Skip();
}

void WindowAddCustomer::CompanyChoice(wxCommandEvent& event)
{
	service_name->Clear();
	Company x; 
	x = manager_pointer->FindCompany((std::string)company_name->GetString(company_name->GetSelection()));
	for (int i = 0; i < x.GetServices().Size(); i++) {
		service_name->Append(x.GetServices()[i]);
	}
}
