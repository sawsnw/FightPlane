#include "framework.h"
#include <map>


static struct Config cfg;
static wxBitmap pCanvas;
static wxMemoryDC *memDc;
static map<string,wxBitmap*> imgCache;

AppFramework::AppFramework() {
    wxImage::AddHandler(new wxJPEGHandler);
    wxImage::AddHandler(new wxPNGHandler);
    getConfig(&cfg);
    //创建一个用于绘制的canvas，并将canvas初始颜色设置为白色
    pCanvas.Create(cfg.width,cfg.height);
    memDc = new wxMemoryDC(pCanvas);
    memDc->SetBackground(*wxWHITE_BRUSH);
    memDc->Clear();
}

bool AppFramework::OnInit() {
    frame = new Frame(cfg.title, cfg.width, cfg.height, cfg.frequency);
    onInit();
    frame->Show(true);
    return true;
}

int AppFramework::OnExit() {
    onExit();
    return 0;
}

wxBEGIN_EVENT_TABLE(MyCanvas, wxPanel)
EVT_PAINT(MyCanvas::OnPaint)
wxEND_EVENT_TABLE()

MyCanvas::MyCanvas(wxWindow* parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size, wxSUNKEN_BORDER){
}

MyCanvas::~MyCanvas(){

}

void MyCanvas::OnPaint(wxPaintEvent& WXUNUSED(event)) {
    wxPaintDC destDc(this);
    onPaint();
    destDc.Blit(0, 0, 320, 480, memDc, 0, 0);
    return;
}

void Frame::OnKeyDown(wxKeyEvent &event) {
    int keyCode = event.GetKeyCode();
    KeyCode key;
    switch (keyCode) {
        case WXK_UP:
            key=KEY_UP;
            break;
        case WXK_DOWN:
            key=KEY_DOWN;
            break;
        case WXK_LEFT:
            key=KEY_LEFT;
            break;
        case WXK_RIGHT:
            key=KEY_RIGHT;
            break;
        case WXK_SPACE:
            key=KEY_SPACE;
            break;
        default:
            key=KEY_INVALID;
    }
    if(key!=KEY_INVALID){
        onKeyDown(key);
    }
}

void Frame::OnKeyUp(wxKeyEvent &event) {
    int keyCode = event.GetKeyCode();
    KeyCode key;
    switch (keyCode) {
        case WXK_UP:
            key=KEY_UP;
            break;
        case WXK_DOWN:
            key=KEY_DOWN;
            break;
        case WXK_LEFT:
            key=KEY_LEFT;
            break;
        case WXK_RIGHT:
            key=KEY_RIGHT;
            break;
        case WXK_SPACE:
            key=KEY_SPACE;
            break;
        default:
            key=KEY_INVALID;
    }
    if(key!=KEY_INVALID){
        onKeyUp(key);
    }
}

void Frame::OnTimer(wxTimerEvent &event) {
    timer.Stop();
    onTimer();
    Refresh();
    timer.Start();
}

void Frame::OnPaint(wxPaintEvent &event) {
    onPaint();
    wxClientDC destDc(this);
    destDc.Blit(0, 0, width, height, memDc, 0, 0);
}



Frame::Frame(char *title, int width, int height, int frequency) : wxFrame(NULL, wxID_ANY, title) {
    this->width = width;
    this->height = height;
    SetSize(width, height);
    timer.Bind(wxEVT_TIMER, &Frame::OnTimer, this);
    timer.Start(frequency);
#if 1
    m_canvas = new MyCanvas(this, wxID_ANY, wxPoint(0, 0), wxSize(320, 480));
    m_canvas->Bind(wxEVT_KEY_DOWN, &Frame::OnKeyDown, this);
    m_canvas->Bind(wxEVT_KEY_UP, &Frame::OnKeyUp, this);
#else
    pannel = new wxPanel(this);
    pannel->Bind(wxEVT_KEY_DOWN, &Frame::OnKeyDown, this);
    pannel->Bind(wxEVT_KEY_UP, &Frame::OnKeyUp, this);
    Connect(wxEVT_PAINT, wxPaintEventHandler(Frame::OnPaint));
#endif
}

/*
 * 获取Memory Device Content
 */
wxMemoryDC *GetMemDc(){
    return memDc;
}

/*
 *设置Pen
 * r、g、b分别代表Red、Green、Blue
 * width代表线宽
 * style代表风格
 */
void SetPen(wxMemoryDC *dc,unsigned char r, unsigned char g, unsigned char b,int width,PenStyle style){
    wxColor color(r, g, b);
    wxPen pen(color,width,style);
    dc->SetPen(pen);
}

void SetBrush(wxMemoryDC *dc,unsigned char r, unsigned char g, unsigned char b){
    wxColor color(r, g, b);
    wxBrush brush(color);
    dc->SetBrush(brush);
}

/*
 *在memDc上画一条直线
 * x1、y1、x2、y2分别代表起止点的坐标
 * r、g、b分别代表Red、Green、Blue
 * width代表线宽
 * style代表风格
 */
void DrawLine(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b,int width , PenStyle style) {
    SetPen(memDc,r,g,b,width,style);
    memDc->DrawLine(x1, y1, x2, y2);
}

/*
 *在memDc上画一个圆
 * x和y代表圆心
 * radius代表半径
 * r、g、b分别代表Red、Green、Blue
 * width代表线宽
 * style代表风格
 */
void DrawCircle(int x,int y,int radius,unsigned char r, unsigned char g, unsigned char b,int width , PenStyle style){
    SetPen(memDc,r,g,b,width,style);
    memDc->DrawCircle(x,y,radius);
}

/*
 *在memDc上画一个点
 * x和y代表点
 * r、g、b分别代表Red、Green、Blue
 */
void DrawPoint(int x,int y,unsigned char r, unsigned char g, unsigned char b){
    SetPen(memDc,r,g,b,1,PENSTYLE_SOLID);
    memDc->DrawPoint(x,y);
}

/*
 * 显示文本
 * x、y代表起始位置
 * text代表要显示的文本内容
 */
void DrawText(int x,int y,string text){
    memDc->DrawText(wxString(text),x,y);
}

/*
 * 加载一张图片到缓存
 * imgName代表图片文件的路径
 * width和height获得图片的宽和高
 */
bool LoadImage(string imgName,int &width,int &height){
    wxBitmap *pImgBitmap=NULL;
    map<string, wxBitmap*>::iterator iter=imgCache.find(imgName);
    if (iter!=imgCache.end()){//found
        pImgBitmap=iter->second;

    }else{//no found
        wxImage image;
        if (!image.LoadFile(imgName, wxBITMAP_TYPE_PNG)) {
            cout << "can't load image:" << imgName << endl;
            return false;
        }
        pImgBitmap = new wxBitmap(image);
        imgCache.insert(std::make_pair(imgName,pImgBitmap));
    }
    width=pImgBitmap->GetWidth();
    height=pImgBitmap->GetHeight();
    return true;
}

/*
 * 画一张图片
 * imgName代表图片文件的路径
 * srcRect和destRect：将图片的指定区域srcRect画到memDc的destRect区域
 */
void DrawImage(string imgName, Rect &srcRect, Rect &destRect) {
    wxBitmap *pImgBitmap=NULL;
    map<string, wxBitmap*>::iterator iter = imgCache.find(imgName);
    if (iter!=imgCache.end()){//found
        pImgBitmap=iter->second;
    }else{//no found
        wxImage image;
        if (!image.LoadFile(imgName, wxBITMAP_TYPE_PNG)) {
            cout << "can't load image:" << imgName << endl;
            return;
        }
        pImgBitmap = new wxBitmap(image);
        imgCache.insert(std::make_pair(imgName,pImgBitmap));
    }
#if 0
    int width=pImgBitmap->GetWidth();
    int height=pImgBitmap->GetHeight();
#endif
    wxBitmap subBitmap = pImgBitmap->GetSubBitmap(srcRect);
    memDc->DrawBitmap(subBitmap, destRect.x, destRect.y);
}

wxIMPLEMENT_APP(AppFramework);
