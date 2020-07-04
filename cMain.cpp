#include "cMain.h" 

#include <fstream>
#include <wx/grid.h>
#include <wx/minifram.h>

#include "WindowAddCompany.h"
#include "WindowAddServiceDuration.h"
#include "IndexManager.h"
#include "WindowAddServicePrice.h"
#include "WindowAddCustomer.h"
#include "RemoveWindow.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_MENU(wxID_OPEN, cMain::ClickOnMenuOpen)
EVT_MENU(wxID_SAVE, cMain::ClickOnMenuSave)
EVT_MENU(wxID_NEW, cMain::ClickOnMenuNew)
EVT_MENU(wxID_EXIT, cMain::ClickOnMenuExit)
EVT_MENU(11111, cMain::ClickOnReportGetCompaniesIncomes)
EVT_MENU(11112, cMain::ClickOnReportGetCompaniesClients)
EVT_MENU(11113, cMain::ClickOnReportGetCustomersServiceDurations)
EVT_MENU(11114, cMain::ClickOnReportGetServiceCompanies)
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
	menu_file->Append(wxID_NEW, "Новый\t");
	menu_file->Append(wxID_OPEN, "Открыть\t");
	menu_file->Append(wxID_SAVE, "Сохранить\t");
	menu_file->AppendSeparator();
	menu_file->Append(wxID_EXIT, "Выход");
	m_menu_bar->Append(menu_file, "Файл");

	wxMenu* menu_reports = new wxMenu();
	menu_reports->Append(11111, "Доходы компаний\t");
	menu_reports->Append(11112, "Клиенты компаний\t");
	menu_reports->Append(11113, "Длительность выполнения всех услуг\nдля каждого клиента\t");
	menu_reports->Append(11114, "Перечень всех услуг со списком компаний, \nкоторые их предоставляют");
	m_menu_bar->Append(menu_reports, "Отчёты");
	this->SetMenuBar(m_menu_bar);

	data_manager = new IndexManager();
}


cMain::~cMain() {

}

void cMain::ClickOnMenuNew(wxCommandEvent& event) {
	// TODO подтверждение действия
	delete data_manager;
	data_manager = new IndexManager();
}

void cMain::ClickOnMenuOpen(wxCommandEvent& event) {

	delete data_manager;
	data_manager = new IndexManager();

	wxFileDialog
		openFileDialog(this, _("Открыть файл..."), "", "",
			"(*.cw2020)|*.cw2020", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	data_manager->LoadData(openFileDialog.GetPath().ToStdString());
}

void cMain::ClickOnMenuSave(wxCommandEvent& event) {
	wxFileDialog
		openFileDialog(this, _("Сохранить файл..."), "", "",
			"(*.cw2020)|*.cw2020", wxFD_SAVE);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	data_manager->SaveData(openFileDialog.GetPath().ToStdString());
}

void cMain::ClickOnMenuExit(wxCommandEvent& event) {
	Close();
	event.Skip();
}

void cMain::ClickOnReportGetCompaniesIncomes(wxCommandEvent& event){
	wxFileDialog
		openFileDialog(this, _("Сохранить отчет..."), "", "",
			"(*.txt)|*.txt", wxFD_SAVE);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	data_manager->SaveCompaniesIncomes(openFileDialog.GetPath().ToStdString());
}

void cMain::ClickOnReportGetCompaniesClients(wxCommandEvent& event){
	wxFileDialog
		openFileDialog(this, _("Сохранить отчет..."), "", "",
			"(*.txt)|*.txt", wxFD_SAVE);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	data_manager->SaveCompaniesClients(openFileDialog.GetPath().ToStdString());
}

void cMain::ClickOnReportGetCustomersServiceDurations(wxCommandEvent& event){
	wxFileDialog
		openFileDialog(this, _("Сохранить отчет..."), "", "",
			"(*.txt)|*.txt", wxFD_SAVE);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	data_manager->SaveCustomersServiceDurations(openFileDialog.GetPath().ToStdString());
}

void cMain::ClickOnReportGetServiceCompanies(wxCommandEvent& event){
	wxFileDialog
		openFileDialog(this, _("Сохранить отчет..."), "", "",
			"(*.txt)|*.txt", wxFD_SAVE);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	data_manager->SaveServiceCompanies(openFileDialog.GetPath().ToStdString());
}

void cMain::ClickOnAdd(wxCommandEvent& event)
{
	wxWindow::SetFocus();
	choice = new wxDialog(this, wxID_ANY, "Выберете справочник");
	wxBoxSizer* s = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* s_main = new wxBoxSizer(wxVERTICAL);
	choice->SetBackgroundColour(wxColour(255, 255, 255));

	wxButton* ok = new wxButton(choice, 14000, "ОК", wxDefaultPosition, wxSize(150, 25));
	wxButton* cust = new wxButton(choice, 14001, "Добавить заказ", wxDefaultPosition, wxSize(150, 50));
	wxButton* comp = new wxButton(choice, 14002, "Добавить компанию", wxDefaultPosition, wxSize(150, 50));
	wxButton* serv_pr = new wxButton(choice, 14003, "Добавить услугу\n к компании", wxDefaultPosition, wxSize(150, 50));
	wxButton* serv_len = new wxButton(choice, 14004, "Добавить новую услугу", wxDefaultPosition, wxSize(150, 50));
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
	serv_len->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::ClickOnAddServiceDuration), nullptr, this);
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
	RemoveWindow* remove_dialog = new RemoveWindow(this, wxID_ANY, "Удаление");
	remove_dialog->SetManagerPointer(*data_manager);
	remove_dialog->ShowModal();
	if (remove_dialog->GetData() != nullptr) {
		switch (remove_dialog->GetData()->choice_num) {
		case 0:data_manager->RemoveCompany(remove_dialog->GetData()->main_str); break;
		case 1:data_manager->RemoveCustomer(remove_dialog->GetData()->main_str); break;
		case 2:data_manager->RemoveServiceDuration(remove_dialog->GetData()->main_str); break;
		case 3:data_manager->RemoveServicePrice(remove_dialog->GetData()->main_str, remove_dialog->GetData()->additional_str); break;
		}
	}
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
	data = data_manager->LookUpCompanies();

	main_list->AppendColumn("Хэш", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Компания", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Услуги", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Адрес", wxLIST_FORMAT_LEFT, 200);

	size_t size_of_services = 0;
	std::string str_buf = "";
	for (int i = 0; i < data.Size(); i++) {
		size_of_services = data[i].first.GetServices().Size();
		for (int j = 0; j < (size_of_services - 1) && size_of_services!=0; j++) {
			str_buf += data[i].first.GetServices()[j];
			str_buf += ", ";
		}
		if (size_of_services != 0) { 
			str_buf += data[i].first.GetServices()[data[i].first.GetServices().Size() - 1]; 
		}
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
	data = data_manager->LookUpServicePrices();
	main_list->AppendColumn("Услуга", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Компания", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Цена за еденицу измерения", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Еденица измерения", wxLIST_FORMAT_LEFT, 200);

	for (int i = 0; i < data.Size(); i++) {

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
	choice->SetFocus();
	main_list->ClearAll();

	Vector<Pair<ServiceDuration, size_t>> data;
	data = data_manager->LookUpServiceDurations();

	main_list->AppendColumn("Хэш", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Наименование услуги", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Минимальная длительность", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Максимальная длительность", wxLIST_FORMAT_LEFT, 200);

	
	std::string str_buf = "";
	for (int i = 0; i < data.Size(); i++) {
		main_list->InsertItem(i, std::to_string(data[i].second));
		main_list->SetItem(i, 1, data[i].first.GetName());
		main_list->SetItem(i, 2, std::to_string(data[i].first.GetMinDuration()));
		main_list->SetItem(i, 3, std::to_string(data[i].first.GetMaxDuration()));
		str_buf = "";
	}

	choice->Close();
	choice->SetFocus();
	event.Skip();
}

void cMain::ClickOnAddCustomer(wxCommandEvent& event)
{
	wxWindow::SetFocus();
	WindowAddCustomer* x = new WindowAddCustomer(this, wxID_ANY, "Добавление заказа");
	if (data_manager->LookUpCompanies().Size() == 0) {
		wxMessageBox("Список компаний пуст");
	}
	else {
		x->SetManagerPointer(*data_manager);
		x->ShowModal();
		if (x->GetData() != nullptr) {
			data_manager->AddCustomer(x->GetData()->name_customer, x->GetData()->name_service, x->GetData()->name_company, x->GetData()->volume);
		}
	}
	wxWindow::SetFocus();
	event.Skip();
}

void cMain::ClickOnAddCompany(wxCommandEvent& event)
{
	wxWindow::SetFocus();
	WindowAddCompany* x = new WindowAddCompany(this, wxID_ANY, "Добваление компании");
	x->ShowModal();
	if (x->GetData() != nullptr) {
		data_manager->AddCompany(x->GetData()->GetName(), x->GetData()->GetAddress());
	}
	wxWindow::SetFocus();
	event.Skip();
}

void cMain::ClickOnAddServicePrice(wxCommandEvent& event)
{
	wxWindow::SetFocus();
	WindowAddServicePrice* x = new WindowAddServicePrice(this, wxID_ANY, "Добавление услуги к компании");
	if (data_manager->LookUpCompanies().Size() == 0 && data_manager->LookUpServiceDurations().Size() == 0) {
		wxMessageBox("Список компаний и услуг пуст");
	} else if (data_manager->LookUpCompanies().Size() == 0) {
		wxMessageBox("Список компаний пуст");
	} else if ( data_manager->LookUpServiceDurations().Size() == 0) {
		wxMessageBox("Список услуг пуст");
	}
	else {
		x->SetManagerPointer(*data_manager);
		x->ShowModal();
		if (x->GetData() != nullptr) {
			data_manager->AddServicePrice(x->GetData()->name_s, x->GetData()->name_c, x->GetData()->price_s, x->GetData()->measure_s);
		}
	}
	wxWindow::SetFocus();
	event.Skip();
}

void cMain::ClickOnAddServiceDuration(wxCommandEvent& event)
{
	wxWindow::SetFocus();
	WindowAddServiceDuration* x = new WindowAddServiceDuration(this, wxID_ANY, "Добавление новой услуги");
	x->ShowModal();
	if (x->GetData() != nullptr) {
		data_manager->AddServiceDuration(x->GetData()->GetName(), x->GetData()->GetMinDuration(), x->GetData()->GetMaxDuration());
	}
	wxWindow::SetFocus();
	event.Skip();
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

	Vector<Customer> data = data_manager->LookUpCustomers();

	main_list->AppendColumn("Заказчик", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Компания", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Наименование услуги", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Объем услуги", wxLIST_FORMAT_LEFT, 200);

	for (int i = 0; i < data.Size(); i++) {

		main_list->InsertItem(i, data[i].GetName());
		main_list->SetItem(i, 1, data[i].GetCompanyName());
		main_list->SetItem(i, 2, data[i].GetService());
		main_list->SetItem(i, 3, std::to_string(data[i].GetVolume()));
	}

	choice->Close();
	choice->SetFocus();
	event.Skip();
}