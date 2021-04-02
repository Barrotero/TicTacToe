#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <string.h>
#include <set>

int board[3][3];

int player;
int turnCounter; 
int victorious; 

void initBoard();
int checkBoard();

void initBoard() {

	int i, j;

	player = 1;
	turnCounter = 0;
	victorious = 0;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			board[i][j] = 0;
		}
	}

}

int checkBoard() {
	int i, j, p1, p2;

	//Verify Lines
	for (i = 0; i < 3; i++) {
		p1 = 0;
		p2 = 0;
		for (j = 0; j < 3; j++) {
			if (board[i][j] == 1) p1++;
			else if (board[i][j] == 2) p2++;
		}
		if (p1 == 3) {
			return 1;
		}
		else if (p2 == 3) {
			return 2;
		}
	}

	//Verify Columns
	for (j = 0; j < 3; j++) {
		p1 = 0;
		p2 = 0;
		for (i = 0; i < 3; i++) {
			if (board[i][j] == 1) p1++;
			else if (board[i][j] == 2) p2++;
		}
		if (p1 == 3) {
			return 1;
		}
		else if (p2 == 3) {
			return 2;
		}
	}
	
	//diagonal principal
	p1 = 0;
	p2 = 0;
	for (i = 0; i < 3; i++) {
		if (board[i][i] == 1) p1++;
		else if (board[i][i] == 2) p2++;
	}
	if (p1 == 3) {
		return 1;
	}
	else if (p2 == 3) {
		return 2;
	}

	//diagonal secundaria
	p1 = 0;
	p2 = 0;
	j = 2;
	for (i = 0; i < 3; i++) {
		if (board[i][j] == 1) p1++;
		else if (board[i][j] == 2) p2++;
		j--;
	}
	if (p1 == 3) {
		return 1;
	}
	else if (p2 == 3) {
		return 2;
	}
	return 0;
}



class TicTacToe : public wxApp {
public:
	virtual bool OnInit();
};

class MainFrame : public wxFrame {
public:
	MainFrame();
protected:
	wxMenuBar* m_mainMenuBar;
	wxMenu* m_menuGame;
	wxMenu* m_menuHelp;

	wxButton* m_btnUpLeft;
	wxButton* m_btnUpMid;
	wxButton* m_btnUpRight;

	wxButton* m_btnMidLeft;
	wxButton* m_btnMidMid;
	wxButton* m_btnMidRight;

	wxButton* m_btnLowLeft;
	wxButton* m_btnLowMid;
	wxButton* m_btnLowRight;

	wxStatusBar* m_statusBar;

	char m_msgStatusBar[200];


private:
	void OnNewGame(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);


	void EnableGrid();
	void DisableGrid();
	void EndGame();


	void OnBtnUpLeftClick(wxCommandEvent& event);
	void OnBtnUpMidClick(wxCommandEvent& event);
	void OnBtnUpRightClick(wxCommandEvent& event);

	void OnBtnMidLeftClick(wxCommandEvent& event);
	void OnBtnMidMidClick(wxCommandEvent& event);
	void OnBtnMidRightClick(wxCommandEvent& event);

	void OnBtnLowLeftClick(wxCommandEvent& event);
	void OnBtnLowMidClick(wxCommandEvent& event);
	void OnBtnLowRightClick(wxCommandEvent& event);


	void OnBtnUpLeftEnterWindow(wxCommandEvent& event);
	void OnBtnUpMidEnterWindow(wxCommandEvent& event);
	void OnBtnUpRightEnterWindow(wxCommandEvent& event);

	void OnBtnMidLeftEnterWindow(wxCommandEvent& event);
	void OnBtnMidMidEnterWindow(wxCommandEvent& event);
	void OnBtnMidRightEnterWindow(wxCommandEvent& event);

	void OnBtnLowLeftEnterWindow(wxCommandEvent& event);
	void OnBtnLowMidEnterWindow(wxCommandEvent& event);
	void OnBtnLowRightEnterWindow(wxCommandEvent& event);


	void OnBtnUpLeftLeaveWindow(wxCommandEvent& event);
	void OnBtnUpMidLeaveWindow(wxCommandEvent& event);
	void OnBtnUpRightLeaveWindow(wxCommandEvent& event);

	void OnBtnMidLeftLeaveWindow(wxCommandEvent& event);
	void OnBtnMidMidLeaveWindow(wxCommandEvent& event);
	void OnBtnMidRightLeaveWindow(wxCommandEvent& event);

	void OnBtnLowLeftLeaveWindow(wxCommandEvent& event);
	void OnBtnLowMidLeaveWindow(wxCommandEvent& event);
	void OnBtnLowRightLeaveWindow(wxCommandEvent& event);

};

bool TicTacToe::OnInit() {
	MainFrame* frame = new MainFrame();
	frame->Show();

	initBoard();
	
	return true;
}

enum {
	ID_NewGame = 1
};

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "Tic Tac Toe") {
	this->SetSizeHints(600, 600);

	m_mainMenuBar = new wxMenuBar(0);
	m_menuGame = new wxMenu();
	m_menuHelp = new wxMenu();

	m_mainMenuBar->Append(m_menuGame, "Game");
	m_mainMenuBar->Append(m_menuHelp, "Help");

	m_menuGame->Append(ID_NewGame, "&New Game\tCtrl-N", "Start a new match");
	m_menuGame->AppendSeparator();
	m_menuGame->Append(wxID_EXIT);

	m_menuHelp->Append(wxID_ABOUT);

	wxFont font(48, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	this->SetMenuBar(m_mainMenuBar);

	wxGridSizer* gBoard = new wxGridSizer(3, 3, 0, 0);
	gBoard->SetMinSize(500, 500);

	m_btnUpLeft = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnUpLeft->SetFont(font);
	gBoard->Add(m_btnUpLeft, 0, wxALL | wxEXPAND, 5);

	m_btnUpMid = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnUpMid->SetFont(font);
	gBoard->Add(m_btnUpMid, 0, wxALL | wxEXPAND, 5);

	m_btnUpRight = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnUpRight->SetFont(font);
	gBoard->Add(m_btnUpRight, 0, wxALL | wxEXPAND, 5);


	m_btnMidLeft = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnMidLeft->SetFont(font);
	gBoard->Add(m_btnMidLeft, 0, wxALL | wxEXPAND, 5);

	m_btnMidMid = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnMidMid->SetFont(font);
	gBoard->Add(m_btnMidMid, 0, wxALL | wxEXPAND, 5);

	m_btnMidRight = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnMidRight->SetFont(font);
	gBoard->Add(m_btnMidRight, 0, wxALL | wxEXPAND, 5);


	m_btnLowLeft = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnLowLeft->SetFont(font);
	gBoard->Add(m_btnLowLeft, 0, wxALL | wxEXPAND, 5);

	m_btnLowMid = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnLowMid->SetFont(font);
	gBoard->Add(m_btnLowMid, 0, wxALL | wxEXPAND, 5);

	m_btnLowRight = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnLowRight->SetFont(font);
	gBoard->Add(m_btnLowRight, 0, wxALL | wxEXPAND, 5);

	this->SetSizer(gBoard);
	this->Layout();

	m_statusBar = this->CreateStatusBar(1, wxST_SIZEGRIP, wxID_ANY);

	this->Centre(wxBOTH);

	DisableGrid();
	SetStatusText("Go to New Game to Start a match");


	Bind(wxEVT_MENU, &MainFrame::OnNewGame, this, ID_NewGame);
	Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);



	m_btnUpLeft->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnUpLeftClick), NULL, this);
	m_btnUpMid->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnUpMidClick), NULL, this);
	m_btnUpRight->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnUpRightClick), NULL, this);

	m_btnMidLeft->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnMidLeftClick), NULL, this);
	m_btnMidMid->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnMidMidClick), NULL, this);
	m_btnMidRight->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnMidRightClick), NULL, this);

	m_btnLowLeft->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnLowLeftClick), NULL, this);
	m_btnLowMid->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnLowMidClick), NULL, this);
	m_btnLowRight->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnLowRightClick), NULL, this);


	m_btnUpLeft->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnUpLeftEnterWindow), NULL, this);
	m_btnUpMid->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnUpMidEnterWindow), NULL, this);
	m_btnUpRight->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnUpRightEnterWindow), NULL, this);

	m_btnMidLeft->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnMidLeftEnterWindow), NULL, this);
	m_btnMidMid->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnMidMidEnterWindow), NULL, this);
	m_btnMidRight->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnMidRightEnterWindow), NULL, this);

	m_btnLowLeft->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnLowLeftEnterWindow), NULL, this);
	m_btnLowMid->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnLowMidEnterWindow), NULL, this);
	m_btnLowRight->Connect(wxEVT_ENTER_WINDOW, wxCommandEventHandler(MainFrame::OnBtnLowRightEnterWindow), NULL, this);

};

wxIMPLEMENT_APP(TicTacToe);

void MainFrame::EnableGrid() {
	m_btnUpLeft->Enable();
	m_btnUpMid->Enable();
	m_btnUpRight->Enable();

	m_btnMidLeft->Enable();
	m_btnMidMid->Enable();
	m_btnMidRight->Enable();

	m_btnLowLeft->Enable();
	m_btnLowMid->Enable();
	m_btnLowRight->Enable();


	m_btnUpLeft->SetLabelText("");
	m_btnUpMid->SetLabelText("");
	m_btnUpRight->SetLabelText("");

	m_btnMidLeft->SetLabelText("");
	m_btnMidMid->SetLabelText("");
	m_btnMidRight->SetLabelText("");

	m_btnLowLeft->SetLabelText("");
	m_btnLowMid->SetLabelText("");
	m_btnLowRight->SetLabelText("");
}

void MainFrame::DisableGrid() {

	m_btnUpLeft->Disable();
	m_btnUpMid->Disable();
	m_btnUpRight->Disable();

	m_btnMidLeft->Disable();
	m_btnMidMid->Disable();
	m_btnMidRight->Disable();

	m_btnLowLeft->Disable();
	m_btnLowMid->Disable();
	m_btnLowRight->Disable();


	m_btnUpLeft->SetLabelText("");
	m_btnUpMid->SetLabelText("");
	m_btnUpRight->SetLabelText("");

	m_btnMidLeft->SetLabelText("");
	m_btnMidMid->SetLabelText("");
	m_btnMidRight->SetLabelText("");

	m_btnLowLeft->SetLabelText("");
	m_btnLowMid->SetLabelText("");
	m_btnLowRight->SetLabelText("");
}

void MainFrame::EndGame() {
	char mensagem[200] = "";
	if (victorious == 0) {
		strcpy(mensagem, "TIED MATCH!");
	}
	else {
		if (victorious == 1) {
			strcpy(mensagem, "X - Player 1 Wins!");
		}
		else {
			if (victorious == 2) {
				strcpy(mensagem, "O - Player 2 Wins!");
			}
		}
	}
	strcat(mensagem, " Play again?");
	if (wxMessageBox(mensagem, "End of match!", wxYES_NO | wxICON_INFORMATION) == wxYES) {
		initBoard();
		EnableGrid();
	} 
	else {
		Close(true);
	}

}

void MainFrame::OnNewGame(wxCommandEvent& event) {
	EnableGrid();
	initBoard();
	SetStatusText("It is Player 1's turn!");
}

void MainFrame::OnExit(wxCommandEvent& event) {
	Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& event){
	wxMessageBox("This is a exemple of Tic Tac Toe in C/C++", "About Tic Tac Toe", wxOK | wxICON_INFORMATION);
}



void MainFrame::OnBtnUpLeftClick(wxCommandEvent& event) {
	if (m_btnUpLeft->IsEnabled()) {
		board[0][0] = player;
		m_btnUpLeft->Disable();
		if (player == 1) {
			m_btnUpLeft->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnUpLeft->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnBtnUpMidClick(wxCommandEvent& event) {
	if (m_btnUpMid->IsEnabled()) {
		board[0][1] = player;
		m_btnUpMid->Disable();
		if (player == 1) {
			m_btnUpMid->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnUpMid->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnBtnUpRightClick(wxCommandEvent& event) {
	if (m_btnUpRight->IsEnabled()) {
		board[0][2] = player;
		m_btnUpRight->Disable();
		if (player == 1) {
			m_btnUpRight->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnUpRight->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnBtnMidLeftClick(wxCommandEvent& event) {
	if (m_btnMidLeft->IsEnabled()) {
		board[1][0] = player;
		m_btnMidLeft->Disable();
		if (player == 1) {
			m_btnMidLeft->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnMidLeft->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnBtnMidMidClick(wxCommandEvent& event) {
	if (m_btnMidMid->IsEnabled()) {
		board[1][1] = player;
		m_btnMidMid->Disable();
		if (player == 1) {
			m_btnMidMid->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnMidMid->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnBtnMidRightClick(wxCommandEvent& event) {
	if (m_btnMidRight->IsEnabled()) {
		board[1][2] = player;
		m_btnMidRight->Disable();
		if (player == 1) {
			m_btnMidRight->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnMidRight->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnBtnLowLeftClick(wxCommandEvent& event) {
	if (m_btnLowLeft->IsEnabled()) {
		board[2][0] = player;
		m_btnLowLeft->Disable();
		if (player == 1) {
			m_btnLowLeft->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnLowLeft->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnBtnLowMidClick(wxCommandEvent& event) {
	if (m_btnLowMid->IsEnabled()) {
		board[2][1] = player;
		m_btnLowMid->Disable();
		if (player == 1) {
			m_btnLowMid->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnLowMid->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnBtnLowRightClick(wxCommandEvent& event) {
	if (m_btnLowRight->IsEnabled()) {
		board[2][2] = player;
		m_btnLowRight->Disable();
		if (player == 1) {
			m_btnLowRight->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnLowRight->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}




void MainFrame::OnBtnUpLeftEnterWindow(wxCommandEvent& event) {
	if (m_btnUpLeft->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Click here to mark a ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");
		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnBtnUpMidEnterWindow(wxCommandEvent& event) {
	if (m_btnUpMid->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Click here to mark a ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");
		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);
}

void MainFrame::OnBtnUpRightEnterWindow(wxCommandEvent& event) {
	if (m_btnUpRight->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Click here to mark a ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");
		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);
}

void MainFrame::OnBtnMidLeftEnterWindow(wxCommandEvent& event) {
	if (m_btnMidLeft->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Click here to mark a ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");
		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnBtnMidMidEnterWindow(wxCommandEvent& event) {
	if (m_btnMidMid->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Click here to mark a ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");
		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnBtnMidRightEnterWindow(wxCommandEvent& event) {
	if (m_btnMidRight->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Click here to mark a ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");
		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);
}

void MainFrame::OnBtnLowLeftEnterWindow(wxCommandEvent& event) {
	if (m_btnLowLeft->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Click here to mark a ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");
		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnBtnLowMidEnterWindow(wxCommandEvent& event) {
	if (m_btnLowMid->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Click here to mark a ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");
		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnBtnLowRightEnterWindow(wxCommandEvent& event) {
	if (m_btnLowRight->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Click here to mark a ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");
		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);
}


void MainFrame::OnBtnUpLeftLeaveWindow(wxCommandEvent& event) {
	if (m_btnUpLeft->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Click here to mark a ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");
		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnBtnUpMidLeaveWindow(wxCommandEvent& event) {
	if (m_btnUpMid->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Click here to mark a ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");
		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnBtnUpRightLeaveWindow(wxCommandEvent& event) {
	if (m_btnUpRight->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Click here to mark a ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");
		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);
}

void MainFrame::OnBtnMidLeftLeaveWindow(wxCommandEvent& event) {
	if (m_btnMidLeft->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Click here to mark a ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");
		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnBtnMidMidLeaveWindow(wxCommandEvent& event) {
	if (m_btnMidMid->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Click here to mark a ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");
		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnBtnMidRightLeaveWindow(wxCommandEvent& event) {
	if (m_btnMidRight->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Click here to mark a ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");
		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);
}

void MainFrame::OnBtnLowLeftLeaveWindow(wxCommandEvent& event) {
	if (m_btnLowLeft->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Click here to mark a ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");
		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnBtnLowMidLeaveWindow(wxCommandEvent& event) {
	if (m_btnLowMid->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Click here to mark a ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");
		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);
}
void MainFrame::OnBtnLowRightLeaveWindow(wxCommandEvent& event) {
	if (m_btnLowRight->IsEnabled()) {
		strcpy(m_msgStatusBar, "");
		strcpy(m_msgStatusBar, "Click here to mark a ");
		if (player == 1) {
			strcat(m_msgStatusBar, "X!");
		}
		else {
			if (player == 2) {
				strcat(m_msgStatusBar, "O!");
			}
		}
	}
	SetStatusText(m_msgStatusBar);
}

