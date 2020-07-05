#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/event.h>
    #include <wx/frame.h>
    #include <wx/log.h> 
    #include <wx/menu.h>
    #include <wx/msgdlg.h> 
#endif

#define CHESS_BOARD_SIZE 600

class MainWindow : public wxFrame
{
public:
    MainWindow();
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};
enum
{
    ID_Hello = 1
};

#endif