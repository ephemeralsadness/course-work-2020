#include "cMain.h" 
#include <wx/grid.h>

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
	
	main_list = new wxListCtrl(this,wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_ICON, wxDefaultValidator, "MyList");
	main_box = new wxBoxSizer(wxVERTICAL);
	buttons_box = new wxBoxSizer(wxHORIZONTAL);

	buttons_box->Add(add_to_list,1, wxALL,  20);       
	buttons_box->Add(remove_from_list,1, wxALL, 20);       
	buttons_box->Add(show_list,1, wxALL,20);        
	buttons_box->Add(search,1, wxALL,20);
	
	main_box->Add(buttons_box,0, wxALIGN_CENTER,5);        
	main_box->Add(main_list,4,  wxEXPAND | wxALL,5);

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

void cMain::ClickOnMenuNew(wxCommandEvent& event){

}

void cMain::ClickOnMenuOpen(wxCommandEvent& event){

}

void cMain::ClickOnMenuSave(wxCommandEvent& event){
}

void cMain::ClickOnMenuSaveAs(wxCommandEvent& event){

}

void cMain::ClickOnMenuExit(wxCommandEvent& event){
	Close();
	event.Skip();
}

void cMain::ClickOnAdd(wxCommandEvent& event)
{
	wxWindow::SetFocus();
	event.Skip();
}

void cMain::ClickOnRemove(wxCommandEvent& event)
{
	wxWindow::SetFocus();
	event.Skip();
}

void cMain::ClickOnShow(wxCommandEvent& event)
{
	wxWindow::SetFocus();
	event.Skip();
}

void cMain::ClickOnSearch(wxCommandEvent& event)
{
	wxWindow::SetFocus();
	event.Skip();
}
