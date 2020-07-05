#include "WindowAddServicePrice.h"

wxBEGIN_EVENT_TABLE(WindowAddServicePrice, wxDialog)
EVT_BUTTON(wxID_ADD, WindowAddServicePrice::ClickOnAdd)

wxEND_EVENT_TABLE()


WindowAddServicePrice::WindowAddServicePrice(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{

	Init();

	(void)Create(parent, id, title, pos, size, style, name);
	this->SetBackgroundColour(wxColour(255, 255, 255));
	add = new wxButton(this, wxID_ADD, "Добавить");
	add->SetBackgroundColour(wxColour(127, 255, 212));
	label1 = new wxStaticText(this, wxID_ANY, "Название компании");
	label2 = new wxStaticText(this, wxID_ANY, "Название услуги");
	label3 = new wxStaticText(this, wxID_ANY, "Цена услуги за у.е.");
	label4 = new wxStaticText(this, wxID_ANY, "Еденица измерения услуги");
	wxBoxSizer* main_s = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* label = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* text_in = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* button = new wxBoxSizer(wxHORIZONTAL);
	company_name = new wxChoice(this, 30001);
	service_name = new wxChoice(this, 30002);
	company_name->SetBackgroundColour(wxColour(255, 255, 255));
	service_name->SetBackgroundColour(wxColour(255, 255, 255));
	company_name->SetOwnBackgroundColour(wxColour(255, 255, 255));
	service_price = new wxTextCtrl(this, 30003);
	service_measure = new wxTextCtrl(this, 30004);
	label->Add(label2, 1, wxALL | wxALIGN_BOTTOM, 10);
	label->Add(label3, 1, wxALL | wxALIGN_BOTTOM, 10);
	label->Add(label4, 1, wxALL | wxALIGN_BOTTOM, 10);
	label->Add(label1, 1, wxALL | wxALIGN_BOTTOM, 10);
	text_in->Add(service_name, 1, wxALL | wxALIGN_BOTTOM, 10);
	text_in->Add(service_price, 1, wxALL | wxALIGN_BOTTOM, 10);
	text_in->Add(service_measure, 1, wxALL | wxALIGN_BOTTOM, 10);
	text_in->Add(company_name, 1, wxALL | wxALIGN_BOTTOM, 10);
	button->Add(add, 1, wxALIGN_CENTER, 10);
	main_s->Add(label, 1, wxBOTTOM, 10);
	main_s->Add(text_in, 1, wxEXPAND, 10);
	main_s->Add(button, 1, wxALIGN_CENTER, 10);
	this->SetSizerAndFit(main_s);
}

WindowAddServicePrice::~WindowAddServicePrice()
{
}

void WindowAddServicePrice::SetManagerPointer(IndexManager& x) {
	manager_pointer = &x;
	Vector<Pair<Company, size_t>> companies = manager_pointer->LookUpCompanies();
	Vector<Pair<ServiceDuration, size_t>> services = manager_pointer->LookUpServiceDurations();
	for (int i = 0; i < companies.Size(); i++) {
		company_name->Append(companies[i].first.GetName());
	}
	for (int i = 0; i < services.Size(); i++) {
		service_name->Append(services[i].first.GetName());
	}
}

WindowAddServicePrice::data* WindowAddServicePrice::GetData() {
	return data1;
}

void WindowAddServicePrice::ClickOnAdd(wxCommandEvent& event) {

	if (company_name->GetSelection() == wxNOT_FOUND && service_name->GetSelection() == wxNOT_FOUND) {
		wxMessageBox("Выберете компанию и услугу");
	}
	else if (company_name->GetSelection() == wxNOT_FOUND) {
		wxMessageBox("Выберете компанию");
	}
	else if (service_name->GetSelection() == wxNOT_FOUND) {
		wxMessageBox("Выберете услугу");
	}
	else if (service_price->IsEmpty() || service_measure->IsEmpty()) {
		wxMessageBox("Заполните пустые поля!!");
	}
	else try {
		data1 = new data;
		data1->name_c = company_name->GetString(company_name->GetSelection());
		data1->name_s = service_name->GetString(service_name->GetSelection());
		data1->measure_s = service_measure->GetLineText(0);
		data1->price_s = std::stod((std::string)service_price->GetLineText(0));
		this->Close();
	}
	catch (std::exception& e) {
		wxMessageBox("В поле для цены должно быть число!!");
	}
	event.Skip();
}
