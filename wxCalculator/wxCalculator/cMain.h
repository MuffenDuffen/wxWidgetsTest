#pragma once
#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
	
	

public:
	wxButton** buttons;
	wxStaticText* input;
	wxStaticText* output;

	bool negative = false;
	wxString currentNumberChunk = "";

	void OnBasicClicked(wxCommandEvent& evt);
	void Calculate() const;

	wxDECLARE_EVENT_TABLE();
};

