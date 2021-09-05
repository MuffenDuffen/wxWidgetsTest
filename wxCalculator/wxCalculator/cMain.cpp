#include "cMain.h"
#include "exprtk.hpp"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, 0, "Calculator", wxDefaultPosition)
{
	auto* masterSizer = new wxBoxSizer(wxVERTICAL);

	const wxFont font = wxFont(25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	
	input = new wxStaticText(this, 0, "", wxPoint(0, 0), wxSize(100, 35));
	input->SetFont(font);
	masterSizer->Add(input, 1, wxEXPAND, wxDOWN);

	output = new wxStaticText(this, 0, "", wxPoint(0, 0), wxSize(100, 35));
	output->SetFont(font);
	masterSizer->Add(output, 1, wxEXPAND, wxDOWN);

	buttons = new wxButton * [24];

	buttons[0] = new wxButton(this, 1000, "%");
	buttons[1] = new wxButton(this, 1001, "CE");
	buttons[2] = new wxButton(this, 1002, "C");
	buttons[3] = new wxButton(this, 1003, "del");
	buttons[4] = new wxButton(this, 1004, "1/x");
	buttons[5] = new wxButton(this, 1005, "x^2");
	buttons[6] = new wxButton(this, 1006, "sqrt(x)");
	buttons[7] = new wxButton(this, 1007, "/");
	buttons[8] = new wxButton(this, 1008, "7");
	buttons[9] = new wxButton(this, 1009, "8");
	buttons[10] = new wxButton(this, 1010, "9");
	buttons[11] = new wxButton(this, 1011, "*");
	buttons[12] = new wxButton(this, 1011, "4");
	buttons[13] = new wxButton(this, 1011, "5");
	buttons[14] = new wxButton(this, 1011, "6");
	buttons[15] = new wxButton(this, 1011, "-");
	buttons[16] = new wxButton(this, 1011, "1");
	buttons[17] = new wxButton(this, 1011, "2");
	buttons[18] = new wxButton(this, 1011, "3");
	buttons[19] = new wxButton(this, 1011, "+");
	buttons[20] = new wxButton(this, 1011, "+/-");
	buttons[21] = new wxButton(this, 1011, "0");
	buttons[22] = new wxButton(this, 1011, ".");
	buttons[23] = new wxButton(this, 1011, "=");

	// ReSharper disable once IdentifierTypo
	wxBoxSizer* sizers[6];

	sizers[0] = new wxBoxSizer(wxHORIZONTAL);
	sizers[1] = new wxBoxSizer(wxHORIZONTAL);
	sizers[2] = new wxBoxSizer(wxHORIZONTAL);
	sizers[3] = new wxBoxSizer(wxHORIZONTAL);
	sizers[4] = new wxBoxSizer(wxHORIZONTAL);
	sizers[5] = new wxBoxSizer(wxHORIZONTAL);
	
	const wxFont basicFont = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_THIN);

	for (int i = 0; i < 24; ++i)
	{
		buttons[i]->SetFont(basicFont);
		sizers[i / 3]->Add(buttons[i], 1, wxEXPAND, wxALL);
		if (i % 4 == 0)masterSizer->Add(sizers[i / 4], 1, wxEXPAND, wxALL);
		buttons[i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnBasicClicked, this);
	}
	
	this->SetSizerAndFit(masterSizer);
	//this->SetSizer(masterSizer);
	masterSizer->Layout();
}

cMain::~cMain()
{
	delete buttons;
}

void cMain::OnBasicClicked(wxCommandEvent& evt)
{
	if (evt.GetId() == 1009)
	{
		negative = !negative;
		wxString label = input->GetLabel();
		(negative) ? input->SetLabel("-" + label) : input->SetLabel(label.Remove(0, 1));
	}
	else if (evt.GetId() == 1011)
	{
		input->SetLabel(input->GetLabel() + '.');
	}
	else
	{
		input->SetLabel(input->GetLabel() + buttons[evt.GetId() - 1000]->GetLabel());
	}
	evt.Skip();
}

void cMain::Calculate() const
{
	exprtk::expression<double> exp;

	exprtk::parser<double> parser;

	const std::string inputString = input->GetLabel().utf8_string();

	if (!parser.compile(inputString, exp))
	{
		printf("Compilation error...\n");
	}

	double result = exp.value();

	output->SetLabel(std::to_string(result));
}

