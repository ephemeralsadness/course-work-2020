#include "cMain.h" 
#include <wx/grid.h>
#include <wx/minifram.h>
#include "AddCompany.h"
#include "IndexManager.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_MENU(wxID_OPEN, cMain::ClickOnMenuNew)
EVT_MENU(wxID_SAVE, cMain::ClickOnMenuOpen)
EVT_MENU(wxID_SAVEAS, cMain::ClickOnMenuSave)
EVT_MENU(wxID_NEW, cMain::ClickOnMenuSaveAs)
EVT_MENU(wxID_EXIT, cMain::ClickOnMenuExit)
EVT_BUTTON(10101, cMain::ClickOnAdd)
EVT_BUTTON(10102, cMain::ClickOnRemove)
EVT_BUTTON(10103, cMain::ClickOnShow)
EVT_BUTTON(10104, cMain::ClickOnSearch)
EVT_BUTTON(13001, cMain::ClickOnCustomer)
EVT_BUTTON(13002, cMain::ClickOnCompany)
EVT_BUTTON(13003, cMain::ClickOnServicePrice)
EVT_BUTTON(13004, cMain::ClickOnServiceLength)
EVT_BUTTON(14000, cMain::ClickOnOkAdd)
EVT_BUTTON(14001, cMain::ClickOnCustomer)
EVT_BUTTON(14002, cMain::ClickOnCompany)
EVT_BUTTON(14003, cMain::ClickOnServicePrice)
EVT_BUTTON(14004, cMain::ClickOnServiceLength)
wxEND_EVENT_TABLE()


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Alex-Alex Course work", wxPoint(30, 30), wxSize(800, 600)) {
	wxWindow::SetFocus();
	this->SetBackgroundColour(wxColour(255, 255, 255));


	wxFont font(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	add_to_list->SetFont(font);
	remove_from_list->SetFont(font);
	show_list->SetFont(font);
	search->SetFont(font);
	add_to_list->SetBackgroundColour(wxColour(127, 255, 212));
	remove_from_list->SetBackgroundColour(wxColour(127, 255, 212));
	show_list->SetBackgroundColour(wxColour(127, 255, 212));
	search->SetBackgroundColour(wxColour(127, 255, 212));

	main_list = new wxListView(this, 20000, wxDefaultPosition, wxSize(250, 200));
	main_box = new wxBoxSizer(wxVERTICAL);
	buttons_box = new wxBoxSizer(wxHORIZONTAL);

	buttons_box->Add(add_to_list, 1, wxALL, 20);
	buttons_box->Add(remove_from_list, 1, wxALL, 20);
	buttons_box->Add(show_list, 1, wxALL, 20);
	buttons_box->Add(search, 1, wxALL, 20);

	main_box->Add(buttons_box, 0, wxALIGN_CENTER, 5);
	main_box->Add(main_list, 1, wxEXPAND | wxALL, 5);

	SetSizerAndFit(main_box);

	m_menu_bar = new wxMenuBar();
	SetMinClientSize(wxSize(800, 600));

	wxImage::AddHandler(new wxPNGHandler());
	this->SetIcon({ "icon2.png", wxBITMAP_TYPE_PNG });

	wxMenu* menu_file = new wxMenu();
	menu_file->Append(wxID_NEW, "Новый\tCtrl+N");
	menu_file->Append(wxID_OPEN, "Открыть\tCtrl+O");
	menu_file->Append(wxID_SAVE, "Сохранить\tCtrl+S");
	menu_file->Append(wxID_SAVEAS, "Сохранить как");
	menu_file->AppendSeparator();
	menu_file->Append(wxID_EXIT, "Выход");

	m_menu_bar->Append(menu_file, "Файл");

	this->SetMenuBar(m_menu_bar);
}


cMain::~cMain() {

}

void cMain::ClickOnMenuNew(wxCommandEvent& event) {

}

void cMain::ClickOnMenuOpen(wxCommandEvent& event) {

}

void cMain::ClickOnMenuSave(wxCommandEvent& event) {
}

void cMain::ClickOnMenuSaveAs(wxCommandEvent& event) {

}

void cMain::ClickOnMenuExit(wxCommandEvent& event) {
	Close();
	event.Skip();
}

void cMain::ClickOnAdd(wxCommandEvent& event)
{
	wxWindow::SetFocus();
	choice = new wxDialog(this, wxID_ANY, "Выберете справочник");
	wxBoxSizer* s = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* s_main = new wxBoxSizer(wxVERTICAL);
	choice->SetBackgroundColour(wxColour(255, 255, 255));

	wxButton* ok = new wxButton(choice, 14000, "Ok", wxDefaultPosition, wxSize(150, 25));
	wxButton* cust = new wxButton(choice, 14001, "Заказчики", wxDefaultPosition, wxSize(150, 50));
	wxButton* comp = new wxButton(choice, 14002, "Добавить компанию", wxDefaultPosition, wxSize(150, 50));
	wxButton* serv_pr = new wxButton(choice, 14003, "Цена услуг", wxDefaultPosition, wxSize(150, 50));
	wxButton* serv_len = new wxButton(choice, 14004, "Длительность услуг", wxDefaultPosition, wxSize(150, 50));
	ok->SetBackgroundColour(wxColour(127, 255, 212));
	cust->SetBackgroundColour(wxColour(127, 255, 212));
	comp->SetBackgroundColour(wxColour(127, 255, 212));
	serv_pr->SetBackgroundColour(wxColour(127, 255, 212));
	serv_len->SetBackgroundColour(wxColour(127, 255, 212));
	s->Add(cust, wxALL, 10);
	s->Add(comp, wxALL, 10);
	s->Add(serv_pr, wxALL, 10);
	s->Add(serv_len, wxALL, 10);
	cust->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::ClickOnAddCustomer), nullptr, this);
	comp->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::ClickOnAddCompany), nullptr, this);
	serv_pr->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::ClickOnAddServicePrice), nullptr, this);
	serv_len->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::ClickOnAddServiceLength), nullptr, this);
	ok->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::ClickOnOkAdd), nullptr, this);
	s_main->Add(s, 0, wxALL, 10);
	s_main->Add(ok, 0, wxALIGN_CENTER || wxALL, 10);
	choice->SetSizerAndFit(s_main);
	choice->ShowModal();

	wxWindow::SetFocus();
	event.Skip();
}

void cMain::ClickOnRemove(wxCommandEvent& event)
{
	wxWindow::SetFocus();





	wxWindow::SetFocus();
	event.Skip();
}

void cMain::ClickOnShow(wxCommandEvent& event)
{

	wxWindow::SetFocus();


	choice = new wxDialog(this, wxID_ANY, "Выберете справочник");
	wxBoxSizer* s = new wxBoxSizer(wxHORIZONTAL);
	choice->SetBackgroundColour(wxColour(255, 255, 255));

	wxButton* cust = new wxButton(choice, 13001, "Заказчики", wxDefaultPosition, wxSize(150, 50));
	wxButton* comp = new wxButton(choice, 13002, "Компании", wxDefaultPosition, wxSize(150, 50));
	wxButton* serv_pr = new wxButton(choice, 13003, "Цена услуг", wxDefaultPosition, wxSize(150, 50));
	wxButton* serv_len = new wxButton(choice, 13004, "Длительность услуг", wxDefaultPosition, wxSize(150, 50));
	cust->SetBackgroundColour(wxColour(127, 255, 212));
	comp->SetBackgroundColour(wxColour(127, 255, 212));
	serv_pr->SetBackgroundColour(wxColour(127, 255, 212));
	serv_len->SetBackgroundColour(wxColour(127, 255, 212));
	cust->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::ClickOnCustomer), nullptr, this);
	comp->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::ClickOnCompany), nullptr, this);
	serv_pr->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::ClickOnServicePrice), nullptr, this);
	serv_len->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::ClickOnServiceLength), nullptr, this);
	s->Add(cust, wxALL, 10);
	s->Add(comp, wxALL, 10);
	s->Add(serv_pr, wxALL, 10);
	s->Add(serv_len, wxALL, 10);

	choice->SetSizerAndFit(s);
	choice->ShowModal();
	wxWindow::SetFocus();
	event.Skip();
}

void cMain::ClickOnSearch(wxCommandEvent& event)
{
	wxWindow::SetFocus();




	wxWindow::SetFocus();
	event.Skip();
}

void cMain::ClickOnCompany(wxCommandEvent& event)
{
	choice->SetFocus();
	main_list->ClearAll();

	Vector<Pair<Company, size_t>> data;
	Vector<std::string> str;
	//data = data_manager.LookUpCompanies();

	main_list->AppendColumn("Хэш", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Компания", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Услуги", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Адрес", wxLIST_FORMAT_LEFT, 200);

	std::string str_buf;
	for (int i = 0; i < str.Size(); i++) {
		for (int j = 0; j < data[i].first.GetServices().Size(); j++) {
			str_buf += data[i].first.GetServices()[j];
			str_buf += ", ";
		}
		str_buf += data[i].first.GetServices()[data[i].first.GetServices().Size() - 1];
		main_list->InsertItem(i, std::to_string(data[i].second));
		main_list->SetItem(i, 1, data[i].first.GetName());
		main_list->SetItem(i, 2, str_buf);
		main_list->SetItem(i, 3, data[i].first.GetAddress());
		str_buf = "";
	}

	choice->Close();
	choice->SetFocus();
	event.Skip();
}

void cMain::ClickOnServicePrice(wxCommandEvent& event)
{
	choice->SetFocus();
	main_list->ClearAll();

	Vector<ServicePrice> data;

	for (int i = 0; i < 500; i++) {
		data.PushBack(ServicePrice(std::to_string(i), std::to_string(i), i, std::to_string(i)));
	}

	main_list->AppendColumn("Услуга", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Компания", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Цена за еденицу измерения", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Еденица измерения", wxLIST_FORMAT_LEFT, 200);

	for (int i = 0; i < 500; i++) {

		main_list->InsertItem(i, data[i].GetName());
		main_list->SetItem(i, 1, data[i].GetCompany());
		main_list->SetItem(i, 2, std::to_string(data[i].GetPrice()));
		main_list->SetItem(i, 3, data[i].GetMeasure());
	}

	choice->Close();
	choice->SetFocus();
	event.Skip();
}

void cMain::ClickOnServiceLength(wxCommandEvent& event)
{
	wxWindow::SetFocus();
	main_list->ClearAll();

	Vector<Pair<ServiceDuration, size_t>> data;

	for (int i = 1; i < 100; i++) {
		data.PushBack(Pair<ServiceDuration, size_t>(ServiceDuration(std::to_string(i), i, i), i));
	}

	main_list->AppendColumn("Хэш", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Услуга", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Минимальная длительность", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Максимальная длительность", wxLIST_FORMAT_LEFT, 200);

	for (int i = 0; i < 100; i++) {

		main_list->InsertItem(i, std::to_string(data[i].second));
		main_list->SetItem(i, 1, data[i].first.GetName());
		main_list->SetItem(i, 2, std::to_string(data[i].first.GetMinDuration()));
		main_list->SetItem(i, 3, std::to_string(data[i].first.GetMaxDuration()));
	}

	choice->Close();
	wxWindow::SetFocus();
	event.Skip();
}

void cMain::ClickOnAddCustomer(wxCommandEvent& event)
{

}

void cMain::ClickOnAddCompany(wxCommandEvent& event)
{
	wxWindow::SetFocus();
	AddCompany* x = new AddCompany(this, wxID_ANY, "123");
	x->ShowModal();
	//data_manager.AddCompany(x->GetData()->GetName(), x->GetData()->GetAddress());
	wxWindow::SetFocus();
	event.Skip();
}

void cMain::ClickOnAddServicePrice(wxCommandEvent& event)
{
}

void cMain::ClickOnAddServiceLength(wxCommandEvent& event)
{
}

void cMain::ClickOnOkAdd(wxCommandEvent& event)
{
	choice->Close();
	wxWindow::SetFocus();
	event.Skip();
}

void cMain::ClickOnCustomer(wxCommandEvent& event) {
	choice->SetFocus();
	main_list->ClearAll();

	Vector<Customer> data;

	for (int i = 0; i < 500; i++) {
		data.PushBack(Customer(std::to_string(i), std::to_string(i), std::to_string(i), i));
	}

	main_list->AppendColumn("Заказчик", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Компания", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Наименование услуги", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Объем услуги", wxLIST_FORMAT_LEFT, 200);

	for (int i = 0; i < 500; i++) {

		main_list->InsertItem(i, data[i].GetName());
		main_list->SetItem(i, 1, data[i].GetCompanyName());
		main_list->SetItem(i, 2, data[i].GetService());
		main_list->SetItem(i, 3, std::to_string(data[i].GetVolume()));
	}

	choice->Close();
	choice->SetFocus();
	event.Skip();
}