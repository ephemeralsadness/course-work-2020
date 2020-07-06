#include "WindowFind.h"

wxBEGIN_EVENT_TABLE(FindWindowDialog, wxDialog)
EVT_BUTTON(wxID_OK, FindWindowDialog::ClickOnOk)
EVT_BUTTON(wxID_CANCEL, FindWindowDialog::ClickOnCancel)
EVT_CHOICE(wxID_SETUP, FindWindowDialog::Choosing)
wxEND_EVENT_TABLE()

FindWindowDialog::FindWindowDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
	Init();
	(void)Create(parent, id, title, pos, size, style, name);

	this->SetBackgroundColour(wxColour(255, 255, 255));

	lable1 = new wxStaticText(this, wxID_ANY, "�������� ��� �����");
	lable2 = new wxStaticText(this, wxID_ANY, "");
	wxArrayString choices;
	choices.Add("��������");
	choices.Add("��������");
	choices.Add("������ (������������)");
	choices.Add("������ (���������)");
	main_choice = new wxChoice(this, wxID_SETUP, wxDefaultPosition, wxDefaultSize, choices);
	name_to_find = new wxTextCtrl(this, wxID_ANY, "");
	top->Add(lable1, 1, wxALL, 10);
	top->Add(lable2, 1, wxALL, 10);
	ok_b = new wxButton(this, wxID_OK, "��");
	cancel_b = new wxButton(this, wxID_CANCEL, "������");
	ok_b->SetBackgroundColour(wxColour(127, 255, 212));
	cancel_b->SetBackgroundColour(wxColour(127, 255, 212));
	choice_mid->Add(main_choice, 1, wxALL | wxALIGN_CENTER, 10);
	choice_mid->Add(name_to_find, 1, wxALL | wxALIGN_CENTER, 10);
	bottom->Add(ok_b, 1, wxALL, 5);
	bottom->Add(cancel_b, 1, wxALL, 5);

	main_s->Add(top, 0, wxEXPAND);
	main_s->Add(choice_mid, 0, wxEXPAND);
	main_s->Add(bottom, 0, wxEXPAND);

	this->SetSizerAndFit(main_s);
}

FindWindowDialog::~FindWindowDialog()
{
}

void FindWindowDialog::SetManagerPointer(IndexManager& x) {
	manager = &x;
}

FindWindowDialog::data* FindWindowDialog::GetData() {
	return data1;
}

void FindWindowDialog::ClickOnOk(wxCommandEvent& event) {
	std::string str_choice = (std::string)main_choice->GetString(main_choice->GetSelection());
	std::string text_in = (std::string)name_to_find->GetLineText(0);
	if (text_in == "")
	{
		wxMessageBox("��������� ����!!");
	}
	else  if (str_choice == "��������") {
		data1 = new data;
		data1->choice_num = COMPANY;
		data1->main_str = text_in;

		this->Close();
		event.Skip();
	}
	else if (str_choice == "��������") {
		data1 = new data;
		data1->choice_num = CUSTOMER;
		data1->main_str = text_in;

		this->Close();
		event.Skip();
	}
	else if (str_choice == "������ (������������)") {
		data1 = new data;
		data1->choice_num = SERVICE_DURATION;
		data1->main_str = text_in;

		this->Close();
		event.Skip();
	}
	else if (str_choice == "������ (���������)") {
		data1 = new data;
		data1->choice_num = SERVICE_PRICE;
		data1->main_str = text_in;

		this->Close();
		event.Skip();
	}
	else {
		wxMessageBox("�������� ��� ������!!");
	}
}

void FindWindowDialog::ClickOnCancel(wxCommandEvent& event) {
	this->Close();
	event.Skip();
}

void FindWindowDialog::Choosing(wxCommandEvent& event) {
	std::string str = (std::string)main_choice->GetString(main_choice->GetSelection());

	if (str == "��������") {
		lable2->SetLabelText("������� ��� ��������");

	}
	else if (str == "��������") {
		lable2->SetLabelText("������� ��� ���������");
	}
	else if (str == "������ (������������)") {
		lable2->SetLabelText("������� �������� ������");
	}
	else if (str == "������ (���������)") {
		lable2->SetLabelText("������� �������� ������");
	}

}
