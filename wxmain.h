#if !defined(INC_H___E1A3D71E_D33E_4425_90D6_D7922343A8DA__HEAD__)
#define INC_H___E1A3D71E_D33E_4425_90D6_D7922343A8DA__HEAD__

namespace local {

 class wxSkinXFrame : public wxFrame {
 public:
  wxSkinXFrame();
  wxSkinXFrame(wxWindow* parent,
   wxWindowID id,
   const wxPoint& pos = wxDefaultPosition,
   const wxSize& size = wxDefaultSize,
   long style = wxNO_BORDER | wxFRAME_SHAPED, //自绘一般默认为无边框
   const wxString& name = wxFrameNameStr);
  void Create(wxWindow* parent,
   wxWindowID id,
   const wxPoint& pos = wxDefaultPosition,
   const wxSize& size = wxDefaultSize,
   long style = wxNO_BORDER | wxFRAME_SHAPED,//自绘一般默认为无边框
   const wxString& name = wxFrameNameStr);
  void Init();
  ~wxSkinXFrame();
 public:
  void SetShapeImage(const wxImage& skin) { image_shape = skin; ReSetShape(); }
  void SetNormalImage(const wxImage& skin) { image_normal = skin; Refresh(); }
  void SetOverImage(const wxImage& skin) { image_over = skin; Refresh(); };
  void SetDisableImage(const wxImage& skin) { image_disable = skin; Refresh(); };
 public:
  bool SetShape(const wxImage& img);
 protected:
  void OnErase(wxEraseEvent& e) {};//擦除函数
  void OnPaint(wxPaintEvent& e);//绘制函数
  void OnSize(wxSizeEvent& e);//当窗口大小发生改变的时候
  void OnEnterWindow(wxMouseEvent& event);//鼠标进入窗口的时候
  void OnLeaveWindow(wxMouseEvent& event);//鼠标离开窗口的时候
 protected:
  void ReSetShape();
 protected:
  void OnMotion(wxMouseEvent& event);
  void OnLeftDown(wxMouseEvent& event);
  void OnLeftUp(wxMouseEvent& event);
  void OnMouseLost(wxMouseCaptureLostEvent& event);
 private:
  wxImage image_shape; //窗口形状
  wxImage image_normal; // 窗口皮肤
  wxImage image_over;//鼠标在窗口上面的皮肤
  wxImage image_disable;//窗口被禁用后的皮肤
  bool m_bInside;//鼠标是否在窗口里面
  wxPoint m_offset;//偏移坐标
  wxRect m_rect;
 private:
  //将类加入到RTTI中
  DECLARE_DYNAMIC_CLASS(wxSkinXFrame)
  DECLARE_EVENT_TABLE()
 };


 class UIWxFrame : public wxFrame {
 public:
  UIWxFrame(wxWindow* parent,
   wxWindowID id,
   const wxString& title,
   const wxPoint& pos = wxDefaultPosition,
   const wxSize& size = wxDefaultSize,
   long style = /*wxDEFAULT_FRAME_STYLE*/wxNO_BORDER | wxFRAME_SHAPED,
   const wxString& name = wxASCII_STR(wxFrameNameStr));
  virtual ~UIWxFrame();
 private:
  wxToolBar* m_pToolbarMain = nullptr;
  wxMenuBar* m_pMenuMain = nullptr;
  wxStatusBar* m_pStatusbarMain = nullptr;
 private:
  void OnSize(wxSizeEvent&);
  void OnClose(wxCloseEvent&);
  WXLRESULT MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam) override final;
  wxDECLARE_EVENT_TABLE();
 };

 class UIWxApp : public wxApp {
 public:
  UIWxApp();
  virtual ~UIWxApp();
 private:
  UIWxFrame* m_pFrame = nullptr;
 public:
  bool OnInit() override;
  int OnExit() override;
 private:
  void OnFrameShow(wxThreadEvent& event);
  void OnTerminate(wxThreadEvent& event);
 protected:
  std::vector<std::thread> m_Threads;
 };

 class WxMain final : public UIBase {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  WxMain(WindowConfig*);
 protected:
  void MainProcess() override final;
  void Release() const override final;
  void Center() const override final;
 private:
  ~WxMain();
 };

}///namespace local

/// /*新生®（上海）**/
/// /*2022_10_07T02:51:42.4170199Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___E1A3D71E_D33E_4425_90D6_D7922343A8DA__HEAD__



