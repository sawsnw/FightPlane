#ifndef __FRAMEWORK_H__
#define __FRAMEWORK_H__

#include <wx/wx.h>
#include <wx/peninfobase.h>
#include <string>

using namespace std;

struct Config {
    char title[32];
    int width;
    int height;
    int frequency;//refresh frequency
};

enum KeyCode {
    KEY_INVALID = -1,
    KEY_UP = 1,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_SPACE
};

enum PenStyle {
    PENSTYLE_SOLID = wxPENSTYLE_SOLID,
    PENSTYLE_DOT = wxPENSTYLE_DOT,
    PENSTYLE_LONG_DASH = wxPENSTYLE_LONG_DASH,
    PENSTYLE_SHORT_DASH = wxPENSTYLE_SHORT_DASH,
    PENSTYLE_DOT_DASH = wxPENSTYLE_DOT_DASH,
    PENSTYLE_USER_DASH = wxPENSTYLE_USER_DASH,

    PENSTYLE_TRANSPARENT = wxPENSTYLE_TRANSPARENT,

    PENSTYLE_STIPPLE_MASK_OPAQUE = wxPENSTYLE_STIPPLE_MASK_OPAQUE,
    PENSTYLE_STIPPLE_MASK = wxPENSTYLE_STIPPLE_MASK,
    PENSTYLE_STIPPLE = wxPENSTYLE_STIPPLE,

    PENSTYLE_BDIAGONAL_HATCH = wxPENSTYLE_BDIAGONAL_HATCH,
    PENSTYLE_CROSSDIAG_HATCH = wxPENSTYLE_CROSSDIAG_HATCH,
    PENSTYLE_FDIAGONAL_HATCH = wxPENSTYLE_FDIAGONAL_HATCH,
    PENSTYLE_CROSS_HATCH = wxPENSTYLE_CROSS_HATCH,
    PENSTYLE_HORIZONTAL_HATCH = wxPENSTYLE_HORIZONTAL_HATCH,
    PENSTYLE_VERTICAL_HATCH = wxPENSTYLE_VERTICAL_HATCH,
    PENSTYLE_FIRST_HATCH = wxPENSTYLE_FIRST_HATCH,
    PENSTYLE_LAST_HATCH = wxPENSTYLE_LAST_HATCH
};

#define Rect wxRect

extern void getConfig(struct Config *cfg);

extern bool onInit();

extern int onExit();

extern void onKeyDown(KeyCode key);

extern void onKeyUp(KeyCode key);

extern void onTimer();

extern void onPaint();

extern wxMemoryDC *GetMemDc();

extern void
SetPen(wxMemoryDC *dc,unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, int width = 1, PenStyle style = PENSTYLE_SOLID);

extern void
SetBrush(wxMemoryDC *dc,unsigned char r, unsigned char g, unsigned char b);

extern void
DrawLine(int x1, int y1, int x2, int y2, unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, int width = 1,
         PenStyle style = PENSTYLE_SOLID);

extern void
DrawCircle(int x, int y, int radius, unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, int width = 1,
           PenStyle style = PENSTYLE_SOLID);

extern void
DrawPoint(int x, int y, unsigned char r = 0, unsigned char g = 0, unsigned char b = 0);

extern void DrawText(int x, int y, string text);

extern bool LoadImage(string imgName, int &width, int &height);

extern void DrawImage(string imgName, Rect &srcRect, Rect &destRect);

class MyCanvas : public wxPanel {
public:
    MyCanvas(wxWindow *parent, wxWindowID, const wxPoint &pos, const wxSize &size);

    ~MyCanvas();

    void OnPaint(wxPaintEvent &event);

private:

wxDECLARE_EVENT_TABLE();
};


class Frame : public wxFrame {
private:
    wxTimer timer;
    int width, height;

    void OnKeyDown(wxKeyEvent &event);

    void OnKeyUp(wxKeyEvent &event);

    void OnTimer(wxTimerEvent &event);

    void OnPaint(wxPaintEvent &event);

public:
    MyCanvas *m_canvas;
    wxPanel *pannel;

    Frame(char *title, int width, int height, int frequency);
};

class AppFramework : public wxApp {
    Frame *frame;
public:

    AppFramework();

    bool OnInit();

    int OnExit();
};

#endif