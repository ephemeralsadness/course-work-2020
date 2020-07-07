#include "WindowRemove.h"

wxBEGIN_EVENT_TABLE(WindowRemove, wxDialog)
EVT_BUTTON(wxID_OK, WindowRemove::ClickOnOk)
EVT_BUTTON(wxID_CANCEL, WindowRemove::ClickOnCancel)
EVT_CHOICE(wxID_SETUP, WindowRemove::Choosing)
EVT_CHOICE(wxID_APPLY, WindowRemove::CompanyChosen)
wxEND_EVENT_TABLE()

WindowRemove::WindowRemove(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
	Init();
	(void)Create(parent, id, title, pos, size, style, name);

	this->SetBackgroundColour(wxColour(255, 255, 255));


	wxArrayString choices;
	choices.Add("Компания");
	choices.Add("Заказчик");
	choices.Add("Услуга");
	choices.Add("Услуга у компании");

	main_choice = new wxChoice(this, wxID_SETUP, wxDefaultPosition, wxDefaultSize, choices);
	label1 = new wxStaticText(this, wxID_ANY, "Выберете что удалить:");
	top->Add(label1, 1, wxALL | wxALIGN_BOTTOM, 5);
	top->Add(main_choice, 1, wxALL | wxALIGN_BOTTOM, 5);
	ok_b = new wxButton(this, wxID_OK, "Ок");
	cancel_b = new wxButton(this, wxID_CANCEL, "Отмена");
	ok_b->SetBackgroundColour(wxColour(127, 255, 212));
	cancel_b->SetBackgroundColour(wxColour(127, 255, 212));
	label2 = new wxStaticText(this, wxID_ANY, "");
	label3 = new wxStaticText(this, wxID_ANY, "");
	first_choice = new wxChoice(this, wxID_APPLY);
	second_choice = new wxChoice(this, wxID_ANY);
	lable_mid->Add(label2, 1, wxALL | wxALIGN_BOTTOM, 10);
	lable_mid->Add(label3, 1, wxALL | wxALIGN_BOTTOM, 10);
	choice_mid->Add(first_choice, 1, wxALL | wxALIGN_CENTER, 10);
	choice_mid->Add(second_choice, 1, wxALL | wxALIGN_CENTER, 10);
	bottom->Add(ok_b, 1, wxALL, 5);
	bottom->Add(cancel_b, 1, wxALL, 5);
	main_s->Add(top, 0, wxBOTTOM);
	main_s->Add(lable_mid, 0, wxEXPAND);
	main_s->Add(choice_mid, 0, wxEXPAND);
	main_s->Add(bottom, 0, wxALIGN_CENTER);

	this->SetSizerAndFit(main_s);
}

WindowRemove::~WindowRemove() {
}

void WindowRemove::SetManagerPointer(IndexManager& x) {
	manager = &x;
}

WindowRemove::data* WindowRemove::GetData() {
	return data1;
}

void WindowRemove::ClickOnOk(wxCommandEvent& event) {
	if (main_choice->GetString(main_choice->GetSelection()) == "Услуга у компании" && (first_choice->GetSelection() == wxNOT_FOUND || second_choice->GetSelection() == wxNOT_FOUND)) {
		wxMessageBox("Выберете что удалить!!");
	}
	else if (main_choice->GetSelection() == wxNOT_FOUND || first_choice->GetSelection() == wxNOT_FOUND) {
		wxMessageBox("Выберете что удалить!!");
	}
	else {
		data1 = new data;
		std::string str = (std::string)main_choice->GetString(main_choice->GetSelection());
		if (str == "Компания") {
			data1->choice_num = COMPANY;
			data1->main_str = first_choice->GetString(first_choice->GetSelection());
		}
		else if (str == "Заказчик") {
			data1->choice_num = CUSTOMER;
			data1->main_str = first_choice->GetString(first_choice->GetSelection());

		}
		else if (str == "Услуга") {
			data1->choice_num = SERVICE_ALL;
			data1->main_str = first_choice->GetString(first_choice->GetSelection());
		}
		else if (str == "Услуга у компании") {
			data1->choice_num = SERVICE_COMPANY;
			data1->main_str = first_choice->GetString(first_choice->GetSelection());
			data1->additional_str = second_choice->GetString(second_choice->GetSelection());
		}
		this->Close();
		event.Skip();
	}

}

void WindowRemove::ClickOnCancel(wxCommandEvent& event)
{
	this->Close();
	event.Skip();
}

void WindowRemove::Choosing(wxCommandEvent& event)
{

	std::string str = (std::string)main_choice->GetString(main_choice->GetSelection());
	if (str == "Компания") {
		choice_mid->Show(true);
		lable_mid->Show(true);
		choice_mid->Hide(second_choice);
		lable_mid->Hide(label3);
		label2->SetLabelText("Выберете компанию");

		first_choice->Clear();
		Vector<std::string> str_vec;
		Vector<Pair<Company, size_t>> all_companies = manager->LookUpCompanies();
		for (size_t i = 0; i < all_companies.Size(); i++) {
			if(all_companies[i].first.GetName()!= all_companies[i-1].first.GetName() || i ==0)
				str_vec.PushBack(all_companies[i].first.GetName());
		}
		for (size_t i = 0; i < str_vec.Size(); i++)
			first_choice->Append(str_vec[i]);
	}
	else if (str == "Заказчик") {
		choice_mid->Show(true);
		lable_mid->Show(true);
		choice_mid->Hide(second_choice);
		lable_mid->Hide(label3);
		label2->SetLabelText("Выберете заказчика");
		first_choice->Clear();
		Vector<std::string> str_vec;
		Vector<Customer> all_companies = manager->LookUpCustomers();
		for (size_t i = 0; i < all_companies.Size(); i++) {
			if (all_companies[i].GetName() != all_companies[i - 1].GetName() || i == 0)
				str_vec.PushBack(all_companies[i].GetName());
		}
		for (size_t i = 0; i < str_vec.Size(); i++)
			first_choice->Append(str_vec[i]);
	}
	else if (str == "Услуга") {
		choice_mid->Show(true);
		lable_mid->Show(true);
		choice_mid->Hide(second_choice);
		lable_mid->Hide(label3);
		label2->SetLabelText("Выберете услугу");
		first_choice->Clear();
		Vector<std::string> str_vec;
		Vector<Pair<ServiceDuration, size_t>> all_companies = manager->LookUpServiceDurations();
		for (size_t i = 0; i < all_companies.Size(); i++) {
			if (i != 0)
			{
				if (all_companies[i].first.GetName() != all_companies[i - 1].first.GetName())
					str_vec.PushBack(all_companies[i].first.GetName());
			}
			else str_vec.PushBack(all_companies[i].first.GetName());
		}
		for (size_t i = 0; i < str_vec.Size(); i++)
			first_choice->Append(str_vec[i]);
	}
	else if (str == "Услуга у компании") {
		choice_mid->Show(true);
		lable_mid->Show(true);
		choice_mid->Hide(second_choice);
		lable_mid->Hide(label3);
		label2->SetLabelText("Выберете компанию");
		first_choice->Clear();
		Vector<std::string> str_vec;
		Vector<Pair<Company, size_t>> all_companies = manager->LookUpCompanies();
		for (size_t i = 0; i < all_companies.Size(); i++) {
			if (all_companies[i].first.GetName() != all_companies[i - 1].first.GetName() || i == 0)
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

void WindowRemove::CompanyChosen(wxCommandEvent& event) {
	if (main_choice->GetString(main_choice->GetSelection()) == "Услуга у компании") {
		label3->SetLabelText("Выберете услугу");
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
