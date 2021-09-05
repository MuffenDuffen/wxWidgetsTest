#pragma once
#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
	
	

public:
	wxButton** basic;
	wxStaticText* input;
	wxStaticText* output;

	bool negative = false;

	void OnBasicClicked(wxCommandEvent& evt);
	int Calculate(wxString& text);

	wxDECLARE_EVENT_TABLE();
};

