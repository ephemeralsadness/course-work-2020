#include <wx/grid.h>
#include <wx/minifram.h>
#include <fstream>

#include "cMain.h" 
#include "IndexManager.h"
#include "WindowAddCompany.h"
#include "WindowAddServiceDuration.h"
#include "WindowAddServicePrice.h"
#include "WindowAddCustomer.h"
#include "WindowRemove.h"
#include "WindowFind.h"

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

	main_list = new wxListView(this, 20000, wxDefaultPosition, wxSize(800, 600));
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
	this->SetIcon({ "icon.png", wxBITMAP_TYPE_PNG });

	wxMenu* menu_file = new wxMenu();
	menu_file->Append(wxID_NEW, "Íîâûé\t");
	menu_file->Append(wxID_OPEN, "Îòêðûòü\t");
	menu_file->Append(wxID_SAVE, "Ñîõðàíèòü\t");
	menu_file->AppendSeparator();
	menu_file->Append(wxID_EXIT, "Âûõîä");
	m_menu_bar->Append(menu_file, "Ôàéë");

	wxMenu* menu_reports = new wxMenu();
	menu_reports->Append(11111, "Äîõîäû êîìïàíèé\t");
	menu_reports->Append(11112, "Êëèåíòû êîìïàíèé\t");
	menu_reports->Append(11113, "Äëèòåëüíîñòü âûïîëíåíèÿ âñåõ óñëóã\näëÿ êàæäîãî êëèåíòà\t");
	menu_reports->Append(11114, "Ïåðå÷åíü âñåõ óñëóã ñî ñïèñêîì êîìïàíèé, \nêîòîðûå èõ ïðåäîñòàâëÿþò");
	m_menu_bar->Append(menu_reports, "Îò÷¸òû");
	this->SetMenuBar(m_menu_bar);

	data_manager = new IndexManager();
}


cMain::~cMain() {

}

void cMain::ClickOnMenuNew(wxCommandEvent& event) {
	// TODO ïîäòâåðæäåíèå äåéñòâèÿ
	delete data_manager;
	data_manager = new IndexManager();
}

void cMain::ClickOnMenuOpen(wxCommandEvent& event) {

	delete data_manager;
	data_manager = new IndexManager();

	wxFileDialog
		openFileDialog(this, _("Îòêðûòü ôàéë..."), "", "",
			"(*.cw2020)|*.cw2020", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	data_manager->LoadData(openFileDialog.GetPath().ToStdString());
}

void cMain::ClickOnMenuSave(wxCommandEvent& event) {
	wxFileDialog
		openFileDialog(this, _("Ñîõðàíèòü ôàéë..."), "", "",
			"(*.cw2020)|*.cw2020", wxFD_SAVE);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	data_manager->SaveData(openFileDialog.GetPath().ToStdString());
}

void cMain::ClickOnMenuExit(wxCommandEvent& event) {
	Close();
	event.Skip();
}

void cMain::ClickOnReportGetCompaniesIncomes(wxCommandEvent& event) {
	wxFileDialog
		openFileDialog(this, _("Ñîõðàíèòü ôàéë..."), "", "",
			"(*.txt)|*.txt", wxFD_SAVE);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	data_manager->SaveCompaniesIncomes(openFileDialog.GetPath().ToStdString());
}

void cMain::ClickOnReportGetCompaniesClients(wxCommandEvent& event) {
	wxFileDialog
		openFileDialog(this, _("Ñîõðàíèòü ôàéë..."), "", "",
			"(*.txt)|*.txt", wxFD_SAVE);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	data_manager->SaveCompaniesClients(openFileDialog.GetPath().ToStdString());
}

void cMain::ClickOnReportGetCustomersServiceDurations(wxCommandEvent& event) {
	wxFileDialog
		openFileDialog(this, _("Ñîõðàíèòü ôàéë..."), "", "",
			"(*.txt)|*.txt", wxFD_SAVE);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	data_manager->SaveCustomersServiceDurations(openFileDialog.GetPath().ToStdString());
}

void cMain::ClickOnReportGetServiceCompanies(wxCommandEvent& event) {
	wxFileDialog
		openFileDialog(this, _("Ñîõðàíèòü ôàéë..."), "", "",
			"(*.txt)|*.txt", wxFD_SAVE);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	data_manager->SaveServiceCompanies(openFileDialog.GetPath().ToStdString());
}

void cMain::ClickOnAdd(wxCommandEvent& event)
{
	wxWindow::SetFocus();
	choice = new wxDialog(this, wxID_ANY, "Âûáåðåòå ñïðàâî÷íèê");
	wxBoxSizer* s = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* s_main = new wxBoxSizer(wxVERTICAL);
	choice->SetBackgroundColour(wxColour(255, 255, 255));

	wxButton* ok = new wxButton(choice, 14000, "ÎÊ", wxDefaultPosition, wxSize(150, 25));
	wxButton* cust = new wxButton(choice, 14001, "Äîáàâèòü çàêàç", wxDefaultPosition, wxSize(150, 50));
	wxButton* comp = new wxButton(choice, 14002, "Äîáàâèòü êîìïàíèþ", wxDefaultPosition, wxSize(150, 50));
	wxButton* serv_pr = new wxButton(choice, 14003, "Äîáàâèòü óñëóãó\n ê êîìïàíèè", wxDefaultPosition, wxSize(150, 50));
	wxButton* serv_len = new wxButton(choice, 14004, "Äîáàâèòü íîâóþ óñëóãó", wxDefaultPosition, wxSize(150, 50));
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
	try {
		wxWindow::SetFocus();
		RemoveWindow* remove_dialog = new RemoveWindow(this, wxID_ANY, "Óäàëåíèå");
		remove_dialog->SetManagerPointer(*data_manager);
		remove_dialog->ShowModal();
		if (remove_dialog->GetData() != nullptr) {
			switch (remove_dialog->GetData()->choice_num) {
			case 0:data_manager->RemoveCompany(remove_dialog->GetData()->main_str); break;
			case 1:data_manager->RemoveCustomer(remove_dialog->GetData()->main_str); break;
			case 2:data_manager->RemoveServiceDuration(remove_dialog->GetData()->main_str); break;
			case 3:data_manager->RemoveServicePrice(remove_dialog->GetData()->additional_str, remove_dialog->GetData()->main_str); break;

			}
		}
	}
	catch (std::invalid_argument e) {
		wxMessageBox(wxString::FromUTF8(e.what()));
	}
	wxWindow::SetFocus();
	event.Skip();
}

void cMain::ClickOnShow(wxCommandEvent& event)
{

	wxWindow::SetFocus();


	choice = new wxDialog(this, wxID_ANY, "Âûáåðåòå ñïðàâî÷íèê");
	wxBoxSizer* s = new wxBoxSizer(wxHORIZONTAL);
	choice->SetBackgroundColour(wxColour(255, 255, 255));

	wxButton* cust = new wxButton(choice, 13001, "Çàêàç÷èêè", wxDefaultPosition, wxSize(150, 50));
	wxButton* comp = new wxButton(choice, 13002, "Êîìïàíèè", wxDefaultPosition, wxSize(150, 50));
	wxButton* serv_pr = new wxButton(choice, 13003, "Öåíà óñëóã", wxDefaultPosition, wxSize(150, 50));
	wxButton* serv_len = new wxButton(choice, 13004, "Äëèòåëüíîñòü óñëóã", wxDefaultPosition, wxSize(150, 50));
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
	FindWindowDialog* window = new FindWindowDialog(this, wxID_ANY, "Ïîèñê");
	window->ShowModal();
	try {
		if (window->GetData() != nullptr) {
			main_list->ClearAll();
			switch (window->GetData()->choice_num) {
			case 0: {
				Company x = data_manager->FindCompany(window->GetData()->main_str);
				main_list->AppendColumn("Êîìïàíèÿ", wxLIST_FORMAT_LEFT, 200);
				main_list->AppendColumn("Óñëóãè", wxLIST_FORMAT_LEFT, 200);
				main_list->AppendColumn("Àäðåñ", wxLIST_FORMAT_LEFT, 200);

				size_t size_of_services = 0;
				std::string str_buf = "";
				size_of_services = x.GetServices().Size();
				for (int j = 0; j < (size_of_services - 1) && size_of_services != 0; j++) {
					str_buf += x.GetServices()[j];
					str_buf += ", ";
				}
				if (size_of_services != 0) {
					str_buf += x.GetServices()[x.GetServices().Size() - 1];
				}
				main_list->InsertItem(0, x.GetName());
				main_list->SetItem(0, 1, str_buf);
				main_list->SetItem(0, 2, x.GetAddress());
				break;
			}
			case 1: {
				Vector<Customer> x = data_manager->FindCustomer(window->GetData()->main_str);
				main_list->AppendColumn("Çàêàç÷èê", wxLIST_FORMAT_LEFT, 200);
				main_list->AppendColumn("Êîìïàíèÿ", wxLIST_FORMAT_LEFT, 200);
				main_list->AppendColumn("Íàèìåíîâàíèå óñëóãè", wxLIST_FORMAT_LEFT, 200);
				main_list->AppendColumn("Îáúåì óñëóãè", wxLIST_FORMAT_LEFT, 200);

				for (int i = 0; i < x.Size(); i++) {

					main_list->InsertItem(i, x[i].GetName());
					main_list->SetItem(i, 1, x[i].GetCompanyName());
					main_list->SetItem(i, 2, x[i].GetService());
					main_list->SetItem(i, 3, std::to_string(x[i].GetVolume()));
				}
				break;
			}
			case 2: {
				ServiceDuration x = data_manager->FindServiceDuration(window->GetData()->main_str);
				main_list->AppendColumn("Íàèìåíîâàíèå óñëóãè", wxLIST_FORMAT_LEFT, 200);
				main_list->AppendColumn("Ìèíèìàëüíàÿ äëèòåëüíîñòü", wxLIST_FORMAT_LEFT, 200);
				main_list->AppendColumn("Ìàêñèìàëüíàÿ äëèòåëüíîñòü", wxLIST_FORMAT_LEFT, 200);

				main_list->InsertItem(0, x.GetName());
				main_list->SetItem(0, 1, std::to_string(x.GetMinDuration()));
				main_list->SetItem(0, 2, std::to_string(x.GetMaxDuration()));

				break;
			}
			case 3: {
				Vector<ServicePrice> x = data_manager->FindServicePrice(window->GetData()->main_str);
				main_list->AppendColumn("Óñëóãà", wxLIST_FORMAT_LEFT, 200);
				main_list->AppendColumn("Êîìïàíèÿ", wxLIST_FORMAT_LEFT, 200);
				main_list->AppendColumn("Öåíà çà åäåíèöó èçìåðåíèÿ", wxLIST_FORMAT_LEFT, 200);
				main_list->AppendColumn("Åäåíèöà èçìåðåíèÿ", wxLIST_FORMAT_LEFT, 200);

				for (int i = 0; i < x.Size(); i++) {

					main_list->InsertItem(i, x[i].GetName());
					main_list->SetItem(i, 1, x[i].GetCompany());
					main_list->SetItem(i, 2, std::to_string(x[i].GetPrice()));
					main_list->SetItem(i, 3, x[i].GetMeasure());
				}
				break;
			}

			}
			size_t comparisons = data_manager->GetLastComparisonsAmount();
			wxMessageBox("Ïðîèçâåäåíî " + std::to_string(comparisons) + " ñðàâíåíèé");
		}
	}
	catch (std::invalid_argument e) {
		wxMessageBox(wxString::FromUTF8(e.what()));
	}
	wxWindow::SetFocus();
	event.Skip();
}

void cMain::ClickOnCompany(wxCommandEvent& event)
{
	choice->SetFocus();
	main_list->ClearAll();

	Vector<Pair<Company, size_t>> data;
	data = data_manager->LookUpCompanies();

	main_list->AppendColumn("Õýø", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Êîìïàíèÿ", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Óñëóãè", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Àäðåñ", wxLIST_FORMAT_LEFT, 200);

	size_t size_of_services = 0;
	std::string str_buf = "";
	for (int i = 0; i < data.Size(); i++) {
		size_of_services = data[i].first.GetServices().Size();
		for (int j = 0; j < (size_of_services - 1) && size_of_services != 0; j++) {
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
	main_list->AppendColumn("Óñëóãà", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Êîìïàíèÿ", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Öåíà çà åäåíèöó èçìåðåíèÿ", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Åäåíèöà èçìåðåíèÿ", wxLIST_FORMAT_LEFT, 200);

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

	main_list->AppendColumn("Õýø", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Íàèìåíîâàíèå óñëóãè", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Ìèíèìàëüíàÿ äëèòåëüíîñòü", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Ìàêñèìàëüíàÿ äëèòåëüíîñòü", wxLIST_FORMAT_LEFT, 200);


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
	try {
		wxWindow::SetFocus();
		WindowAddCustomer* x = new WindowAddCustomer(this, wxID_ANY, "Äîáàâëåíèå çàêàçà");
		if (data_manager->LookUpCompanies().Size() == 0) {
			wxMessageBox("Ñïèñîê êîìïàíèé ïóñò");
		}
		else {
			x->SetManagerPointer(*data_manager);
			x->ShowModal();
			if (x->GetData() != nullptr) {
				data_manager->AddCustomer(x->GetData()->name_customer, x->GetData()->name_service, x->GetData()->name_company, x->GetData()->volume);
			}
		}
	}
	catch (std::invalid_argument e) {
		wxMessageBox(wxString::FromUTF8(e.what()));
	}
	wxWindow::SetFocus();
	event.Skip();
}

void cMain::ClickOnAddCompany(wxCommandEvent& event)
{
	try {
		wxWindow::SetFocus();
		WindowAddCompany* x = new WindowAddCompany(this, wxID_ANY, "Äîáâàëåíèå êîìïàíèè");
		x->ShowModal();
		if (x->GetData() != nullptr) {
			data_manager->AddCompany(x->GetData()->GetName(), x->GetData()->GetAddress());
		}
	}
	catch (std::invalid_argument e) {
		wxMessageBox(wxString::FromUTF8(e.what()));
	}
	wxWindow::SetFocus();
	event.Skip();
}

void cMain::ClickOnAddServicePrice(wxCommandEvent& event)
{
	try {
		wxWindow::SetFocus();
		WindowAddServicePrice* x = new WindowAddServicePrice(this, wxID_ANY, "Äîáàâëåíèå óñëóãè ê êîìïàíèè");
		if (data_manager->LookUpCompanies().Size() == 0 && data_manager->LookUpServiceDurations().Size() == 0) {
			wxMessageBox("Ñïèñîê êîìïàíèé è óñëóã ïóñò");
		}
		else if (data_manager->LookUpCompanies().Size() == 0) {
			wxMessageBox("Ñïèñîê êîìïàíèé ïóñò");
		}
		else if (data_manager->LookUpServiceDurations().Size() == 0) {
			wxMessageBox("Ñïèñîê óñëóã ïóñò");
		}
		else {
			x->SetManagerPointer(*data_manager);
			x->ShowModal();
			if (x->GetData() != nullptr) {
				data_manager->AddServicePrice(x->GetData()->name_s, x->GetData()->name_c, x->GetData()->price_s, x->GetData()->measure_s);
			}
		}
	}
	catch (std::invalid_argument e) {
		wxMessageBox(wxString::FromUTF8(e.what()));
	}
	wxWindow::SetFocus();
	event.Skip();
}

void cMain::ClickOnAddServiceDuration(wxCommandEvent& event)
{
	try {
		wxWindow::SetFocus();
		WindowAddServiceDuration* x = new WindowAddServiceDuration(this, wxID_ANY, "Äîáàâëåíèå íîâîé óñëóãè");
		x->ShowModal();
		if (x->GetData() != nullptr) {
			data_manager->AddServiceDuration(x->GetData()->GetName(), x->GetData()->GetMinDuration(), x->GetData()->GetMaxDuration());
		}
	}
	catch (std::invalid_argument e) {
		wxMessageBox(wxString::FromUTF8(e.what()));
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

	main_list->AppendColumn("Çàêàç÷èê", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Êîìïàíèÿ", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Íàèìåíîâàíèå óñëóãè", wxLIST_FORMAT_LEFT, 200);
	main_list->AppendColumn("Îáúåì óñëóãè", wxLIST_FORMAT_LEFT, 200);

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
