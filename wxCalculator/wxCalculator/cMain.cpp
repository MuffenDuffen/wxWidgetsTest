#include "cMain.h"
#include "exprtk.hpp"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, 0, "Calculator", wxDefaultPosition)
{
	auto* masterSizer = new wxBoxSizer(wxVERTICAL);

	const wxFont font = wxFont(25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_SEMIBOLD);
	
	input = new wxStaticText(this, 0, "", wxPoint(0, 0), wxSize(100, 35));
	input->SetFont(font);
	masterSizer->Add(input, 1, wxEXPAND, wxDOWN);

	output = new wxStaticText(this, 0, "", wxPoint(0, 0), wxSize(100, 40));
	output->SetFont(font);
	masterSizer->Add(output, 1, wxEXPAND, wxDOWN);

	buttons = new wxButton * [24];

	buttons[0] = new wxButton(this, 1000, "%");
	buttons[1] = new wxButton(this, 1001, "CE");
	buttons[2] = new wxButton(this, 1002, "C");
	buttons[3] = new wxButton(this, 1003, "Del");
	buttons[4] = new wxButton(this, 1004, "1/x");
	buttons[5] = new wxButton(this, 1005, "x^2");
	buttons[6] = new wxButton(this, 1006, "Sqrt(x)");
	buttons[7] = new wxButton(this, 1007, "/");
	buttons[8] = new wxButton(this, 1008, "7");
	buttons[9] = new wxButton(this, 1009, "8");
	buttons[10] = new wxButton(this, 1010, "9");
	buttons[11] = new wxButton(this, 1011, "*");
	buttons[12] = new wxButton(this, 1012, "4");
	buttons[13] = new wxButton(this, 1013, "5");
	buttons[14] = new wxButton(this, 1014, "6");
	buttons[15] = new wxButton(this, 1015, "-");
	buttons[16] = new wxButton(this, 1016, "1");
	buttons[17] = new wxButton(this, 1017, "2");
	buttons[18] = new wxButton(this, 1018, "3");
	buttons[19] = new wxButton(this, 1019, "+");
	buttons[20] = new wxButton(this, 1020, "+/-");
	buttons[21] = new wxButton(this, 1021, "0");
	buttons[22] = new wxButton(this, 1022, ".");
	buttons[23] = new wxButton(this, 1023, "=");

	// ReSharper disable once IdentifierTypo
	wxBoxSizer* sizers[6];

	sizers[0] = new wxBoxSizer(wxHORIZONTAL);
	sizers[1] = new wxBoxSizer(wxHORIZONTAL);
	sizers[2] = new wxBoxSizer(wxHORIZONTAL);
	sizers[3] = new wxBoxSizer(wxHORIZONTAL);
	sizers[4] = new wxBoxSizer(wxHORIZONTAL);
	sizers[5] = new wxBoxSizer(wxHORIZONTAL);
	
	const wxFont basicFont = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	for (int i = 0; i < 24; ++i)
	{
		buttons[i]->SetFont(basicFont);
		sizers[i / 4]->Add(buttons[i], 1, wxEXPAND, wxALL);
		if (i % 4 == 0) masterSizer->Add(sizers[i / 4], 1, wxEXPAND, wxALL);
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
	switch (evt.GetId())
	{
		//%
		case 1000:
			input->SetLabel("0");
			break;
		//CE
		case 1001:
			input->SetLabel(input->GetLabel().Remove(input->GetLabel().find_last_not_of("0123456789")));
			break;
		//C
		case 1002:
			input->SetLabel("");
			output->SetLabel("");
			break;
		//Del
		case 1003:
			input->SetLabel(input->GetLabel().substr(0, input->GetLabel().length() - 1));
			break;
		//(1/x)
		case 1004:
			input->SetLabel(input->GetLabel().substr(0, input->GetLabel().length() - currentNumberChunk.length()));
			input->SetLabel(input->GetLabel() + "1/(" + currentNumberChunk + ")");
			currentNumberChunk = "";
			break;
		//(x^2)
		case 1005:
			input->SetLabel(input->GetLabel().substr(0, input->GetLabel().length() - currentNumberChunk.length()));
			input->SetLabel(input->GetLabel() + "(" + currentNumberChunk + "^" + "2" + ")");
			currentNumberChunk = "";
			break;
		//(Sqrt(x))
		case 1006:
			input->SetLabel(input->GetLabel().substr(0, input->GetLabel().length() - currentNumberChunk.length()));
			input->SetLabel(input->GetLabel() + "(sqrt(" + currentNumberChunk + "))");
			currentNumberChunk = "";
			break;
		//(/)
		case 1007:
			input->SetLabel(input->GetLabel() + "/");
			currentNumberChunk = "";
			break;
		//7
		case 1008:
			input->SetLabel(input->GetLabel() + "7");
			currentNumberChunk += "7";
			break;
		//8
		case 1009:
			input->SetLabel(input->GetLabel() + "8");
			currentNumberChunk += "8";
			break;
		//9
		case 1010:
			input->SetLabel(input->GetLabel() + "9");
			currentNumberChunk += "9";
			break;
		//(*)
		case 1011:
			input->SetLabel(input->GetLabel() + "*");
			currentNumberChunk = "";
			break;
		//4
		case 1012:
			input->SetLabel(input->GetLabel() + "4");
			currentNumberChunk += "4";
			break;
		//5
		case 1013:
			input->SetLabel(input->GetLabel() + "5");
			currentNumberChunk += "5";
			break;
		//6
		case 1014:
			input->SetLabel(input->GetLabel() + "6");
			currentNumberChunk += "6";
			break;
		//(-)
		case 1015:
			input->SetLabel(input->GetLabel() + "-");
			currentNumberChunk = "";
			break;
		//1
		case 1016:
			input->SetLabel(input->GetLabel() + "1");
			currentNumberChunk += "1";
			break;
		//2
		case 1017:
			input->SetLabel(input->GetLabel() + "2");
			currentNumberChunk += "2";
			break;
		//3
		case 1018:
			input->SetLabel(input->GetLabel() + "3");
			currentNumberChunk += "3";
			break;
		//(+)
		case 1019:
			input->SetLabel(input->GetLabel() + "+");
			currentNumberChunk = "";
			break;
		//(+/-)
		case 1020:
			negative = !negative;
			(negative) ? input->SetLabel("-" + input->GetLabel()) : input->SetLabel(input->GetLabel().Remove(0, 1));
			break;
		//0
		case 1021:
			input->SetLabel(input->GetLabel() + "0");
			currentNumberChunk += "0";
			break;
		//.
		case 1022:
			input->SetLabel(input->GetLabel() + '.');
			break;
		//Calculate
		case 1023: 
			Calculate();
			input->SetLabel("");
			break;
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

	std::string str = std::to_string(result);

	if (str.find('.') != std::string::npos)
	{
		// Remove trailing zeroes
		str = str.substr(0, str.find_last_not_of('0') + 1);
		// If the decimal point is now the last character, remove that as well
		if (str.find('.') == str.size() - 1)
		{
			str = str.substr(0, str.size() - 1);
		}
	}
	
	output->SetLabel(str);
}

