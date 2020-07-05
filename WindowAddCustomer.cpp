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
	add = new wxButton(this, wxID_ADD, "��������");
	add->SetBackgroundColour(wxColour(127, 255, 212));
	label1 = new wxStaticText(this, wxID_ANY, "��� ���������");
	label2 = new wxStaticText(this, wxID_ANY, "�������� ��������");
	label3 = new wxStaticText(this, wxID_ANY, "������������ ������");
	label4 = new wxStaticText(this, wxID_ANY, "����� ���������� ������");

	company_name = new wxChoice(this, 30001, wxDefaultPosition, wxSize(100, 25));
	service_name = new wxChoice(this, 30002, wxDefaultPosition, wxSize(100, 25));
	company_name->SetBackgroundColour(wxColour(255, 255, 255));
	service_name->SetBackgroundColour(wxColour(255, 255, 255));
	company_name->SetOwnBackgroundColour(wxColour(255, 255, 255));
	customer_name = new wxTextCtrl(this, 30003);
	service_volume = new wxTextCtrl(this, 30004);
	label->Add(label1, 1, wxALL | wxALIGN_BOTTOM, 10);
	label->Add(label2, 1, wxALL | wxALIGN_BOTTOM, 10);
	label->Add(label3, 1, wxALL | wxALIGN_BOTTOM, 10);
	label->Add(label4, 1, wxALL | wxALIGN_BOTTOM, 10);

	text_in->Add(customer_name, 1, wxALL, 10);
	text_in->Add(company_name, 1, wxALL, 10);
	text_in->Add(service_name, 1, wxALL, 10);
	text_in->Add(service_volume, 1, wxALL, 10);
	button->Add(add, 1, wxALL, 15);
	main_s->Add(label, 1, wxEXPAND, 10);
	main_s->Add(text_in, 1, wxEXPAND, 10);
	main_s->Add(button, 1, wxALIGN_RIGHT);
	this->SetSizerAndFit(main_s);
}

WindowAddCustomer::~WindowAddCustomer()
{
}

void WindowAddCustomer::SetManagerPointer(IndexManager& x) {
	manager_pointer = &x;
	Vector<Pair<Company, size_t>> companies = manager_pointer->LookUpCompanies();
	Vector<std::string> str_vec;
	for (int i = 0; i < companies.Size(); i++) {
		str_vec.PushBack(companies[i].first.GetName());
	}
	for (int i = 0; i < companies.Size(); i++)
		company_name->Append(str_vec[i]);
	company_name->SetSize(wxDefaultSize);
}

WindowAddCustomer::data* WindowAddCustomer::GetData() {
	return data1;
}

void WindowAddCustomer::ClickOnAdd(wxCommandEvent& event) {

	if (company_name->GetSelection() == wxNOT_FOUND && service_name->GetSelection() == wxNOT_FOUND) {
		wxMessageBox("�������� �������� � ������");
	}
	else if (company_name->GetSelection() == wxNOT_FOUND) {
		wxMessageBox("�������� ��������");
	}
	else if (service_name->GetSelection() == wxNOT_FOUND) {
		wxMessageBox("�������� ������");
	}
	else if (service_name->GetCount() == 0) {
		wxMessageBox("������ �������� �� ������������� �����");
	}
	else if (customer_name->IsEmpty() || service_volume->IsEmpty()) {
		wxMessageBox("��������� ������ ����!!");
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
		wxMessageBox("� ���� ��� ���� ������ ���� ����� ������������� �����!!");
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
