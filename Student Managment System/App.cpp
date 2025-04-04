#include "App.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    MainFrame* mainFrame = new MainFrame("Student Managament System");
    mainFrame->Maximize(true);
    mainFrame->Center();
    mainFrame->Show();
    return true;
}
