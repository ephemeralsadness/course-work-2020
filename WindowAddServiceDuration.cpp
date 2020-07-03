#include "WindowAddServiceDuration.h"

wxBEGIN_EVENT_TABLE(WindowAddServiceDuration, wxDialog)
EVT_BUTTON(wxID_ADD, WindowAddServiceDuration::ClickOnAdd)

wxEND_EVENT_TABLE()


WindowAddServiceDuration::WindowAddServiceDuration(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{

	Init();

	(void)Create(parent, id, title, pos, size, style, name);
	this->SetBackgroundColour(wxColour(255, 255, 255));
	add = new wxButton(this, wxID_ADD, "Добавить");
	add->SetBackgroundColour(wxColour(127, 255, 212));
	label1 = new wxStaticText(this, wxID_ANY, "Наименование услуги");
	label2 = new wxStaticText(this, wxID_ANY, "Минимальная длительность");
	label3 = new wxStaticText(this, wxID_ANY, "Максимальная длительность");
	wxBoxSizer* main_s = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* label = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* text_in = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* button = new wxBoxSizer(wxHORIZONTAL);
	max_dur = new wxTextCtrl(this, 30003);
	min_dur = new wxTextCtrl(this, 30002);
	name_ser = new wxTextCtrl(this, 30001);
	label->Add(label1, 1, wxALL | wxALIGN_BOTTOM, 10);
	label->Add(label2, 1, wxALL | wxALIGN_BOTTOM, 10);
	label->Add(label3, 1, wxALL | wxALIGN_BOTTOM, 10);
	text_in->Add(name_ser, 1, wxALL | wxALIGN_BOTTOM, 10);
	text_in->Add(min_dur, 1, wxALL | wxALIGN_BOTTOM, 10);
	text_in->Add(max_dur, 1, wxALL | wxALIGN_BOTTOM, 10);
	button->Add(add, 1, wxALIGN_CENTER, 10);
	main_s->Add(label, 1, wxBOTTOM, 10);
	main_s->Add(text_in, 1, wxEXPAND, 10);
	main_s->Add(button, 1, wxALIGN_CENTER, 10);
	this->SetSizerAndFit(main_s);;
}

WindowAddServiceDuration::~WindowAddServiceDuration()
{
}

bool CheckDurationsAreCorrect(double min_duration, double max_duration) {
	return min_duration >= 0 && max_duration >= 0 && min_duration <= max_duration;
}

void WindowAddServiceDuration::ClickOnAdd(wxCommandEvent& event) {
	std::string name_str;
	double min_dur_str, max_dur_str;
	if (!name_ser->IsEmpty() && !min_dur->IsEmpty() && !max_dur->IsEmpty()) {
		name_str = name_ser->GetLineText(0);
		try{
			min_dur_str = std::stod((std::string)(min_dur->GetLineText(0)));
			max_dur_str = std::stod((std::string)(max_dur->GetLineText(0)));
			if (CheckDurationsAreCorrect(min_dur_str, max_dur_str))
			{
				data = new ServiceDuration(name_str, min_dur_str, max_dur_str);
				name_ser->Clear();
				min_dur->Clear();
				max_dur->Clear();
				this->Close();
			}
			else {
				wxMessageBox("Некорректный диапазон длительностей");
			}

		}
		catch (std::exception& e){
			wxMessageBox("В полях для чисел должны быть числа!!");
		}
		
	}
	else {
		wxMessageBox("Поля не могут быть пустыми!!");
	}
	event.Skip();
}
