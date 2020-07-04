#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/app.h>
#endif

#include "gui/main_window.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
    MainWindow *mainWindow = new MainWindow();
    mainWindow->Show(true);
    return true;
}