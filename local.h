#if !defined(INC_H___F92F8D7A_B486_4872_A589_75BEA5FC22DF__HEAD__)
#define INC_H___F92F8D7A_B486_4872_A589_75BEA5FC22DF__HEAD__

namespace local {

 const size_t NormalUserLimitDownSpeedValue = 100 * 1024;

 const char SystemConfigFilename[] = R"(system_configure.json)";
 const char FolderNameDownCache[] = R"(caches)";
 const char FolderNameInstalled[] = R"(res)";

 enum class CommonColorType {
  Red,
  Green,
  White,
  Black,
  Blue,
 };

 static const std::map<CommonColorType, DWORD> CommonColorMap = {
 {CommonColorType::Red,RGB(255,0,0)},
 {CommonColorType::Green,RGB(0,255,0)},
 {CommonColorType::Blue,RGB(0,0,255)},
 {CommonColorType::White,RGB(255,255,255)},
 {CommonColorType::Black,RGB(0,0,0)},
 };



}///namespace local












#if 0
@brief  @param  @return @author @date @version是代码书写的一种规范
@brief  ：简介，简单介绍函数作用
@param  ：介绍函数参数
@return：函数返回类型说明
@exception NSException 可能抛出的异常.
@author zhangsan：  作者
@date 2011 - 07 - 27 22:30 : 00 ：时间
@version 1.0 ：版本
@property ：属性介绍
#endif


#if 0
namespace xlapi_3_2_2_30 {
#pragma pack(push, 1)
 typedef struct tagDownTaskParam {
  int nReserved;
  wchar_t szTaskUrl[2084];          // 任务URL
  wchar_t szRefUrl[2084];           // 引用页
  wchar_t szCookies[4096];          // 浏览器cookie
  wchar_t szFilename[MAX_PATH];     // 下载保存文件名.
  wchar_t szReserved0[MAX_PATH];
  wchar_t szSavePath[MAX_PATH];     // 文件保存目录
  HWND  hReserved;
  BOOL bReserved;
  wchar_t szReserved1[64];
  wchar_t szReserved2[64];
  BOOL IsOnlyOriginal;            // 是否只从原始地址下载
  UINT nReserved1;
  BOOL DisableAutoRename;         // 禁止智能命名
  BOOL IsResume;                  // 是否用续传
  DWORD reserved[2048];
  tagDownTaskParam() {
   memset(this, 0, sizeof(*this));
   nReserved1 = 5;
   bReserved = FALSE;
   DisableAutoRename = FALSE;
   IsOnlyOriginal = FALSE;
   IsResume = TRUE;
  }
 }DownTaskParam;

 enum class DOWN_TASK_STATUS {
  NOITEM = 0,
  TSC_ERROR,
  TSC_PAUSE,
  TSC_DOWNLOAD,
  TSC_COMPLETE,
  TSC_STARTPENDING,
  TSC_STOPPENDING
 };
 enum class TASK_ERROR_TYPE {
  TASK_ERROR_UNKNOWN = 0x00,   // 未知错误
  TASK_ERROR_DISK_CREATE = 0x01,   // 创建文件失败
  TASK_ERROR_DISK_WRITE = 0x02,   // 写文件失败
  TASK_ERROR_DISK_READ = 0x03,   // 读文件失败
  TASK_ERROR_DISK_RENAME = 0x04,   // 重命名失败
  TASK_ERROR_DISK_PIECEHASH = 0x05,   // 文件片校验失败
  TASK_ERROR_DISK_FILEHASH = 0x06,   // 文件全文校验失败
  TASK_ERROR_DISK_DELETE = 0x07,   // 删除文件失败失败
  TASK_ERROR_DOWN_INVALID = 0x10,   // 无效的DOWN地址
  TASK_ERROR_PROXY_AUTH_TYPE_UNKOWN = 0x20,   // 代理类型未知
  TASK_ERROR_PROXY_AUTH_TYPE_FAILED = 0x21,   // 代理认证失败
  TASK_ERROR_HTTPMGR_NOT_IP = 0x30,   // http下载中无ip可用
  TASK_ERROR_TIMEOUT = 0x40,   // 任务超时
  TASK_ERROR_CANCEL = 0x41,   // 任务取消
  TASK_ERROR_TP_CRASHED = 0x42,   // MINITP崩溃
  TASK_ERROR_ID_INVALID = 0x43,   // TaskId 非法
 };
 typedef struct tagDownTaskInfo {
  DOWN_TASK_STATUS	stat;
  TASK_ERROR_TYPE		fail_code;
  wchar_t		szFilename[MAX_PATH];
  wchar_t		szReserved0[MAX_PATH];
  __int64     nTotalSize;         // 该任务总大小(字节)
  __int64     nTotalDownload;     // 下载有效字节数(可能存在回退的情况)
  float		fPercent;           // 下载进度
  int			nReserved0;
  int			nSrcTotal;          // 总资源数
  int			nSrcUsing;          // 可用资源数
  int			nReserved1;
  int			nReserved2;
  int			nReserved3;
  int			nReserved4;
  __int64     nReserved5;
  __int64		nDonationP2P;       // p2p贡献字节数
  __int64		nReserved6;
  __int64		nDonationOrgin;		// 原始资源共享字节数
  __int64		nDonationP2S;		// 镜像资源共享字节数
  __int64		nReserved7;
  __int64     nReserved8;
  int			nSpeed;             // 即时速度(字节/秒)
  int			nSpeedP2S;          // 即时速度(字节/秒)
  int			nSpeedP2P;          // 即时速度(字节/秒)
  bool		bIsOriginUsable;    // 原始资源是否有效
  float		fHashPercent;       // 现不提供该值
  int			IsCreatingFile;     // 是否正在创建文件
  DWORD		reserved[64];
  tagDownTaskInfo() {
   memset(this, 0, sizeof(DownTaskInfo));
   stat = DOWN_TASK_STATUS::TSC_PAUSE;
   fail_code = TASK_ERROR_TYPE::TASK_ERROR_UNKNOWN;
   fPercent = 0;
   bIsOriginUsable = false;
   fHashPercent = 0;
  }
 }DownTaskInfo;
 enum class DOWN_PROXY_TYPE {
  PROXY_TYPE_IE = 0,
  PROXY_TYPE_HTTP = 1,
  PROXY_TYPE_SOCK4 = 2,
  PROXY_TYPE_SOCK5 = 3,
  PROXY_TYPE_FTP = 4,
  PROXY_TYPE_UNKOWN = 255,
 };
 enum class DOWN_PROXY_AUTH_TYPE {
  PROXY_AUTH_NONE = 0,
  PROXY_AUTH_AUTO,
  PROXY_AUTH_BASE64,
  PROXY_AUTH_NTLM,
  PROXY_AUTH_DEGEST,
  PROXY_AUTH_UNKOWN,
 };
 typedef struct tagDOWN_PROXY_INFO {
  BOOL		bIEProxy;
  BOOL		bProxy;
  DOWN_PROXY_TYPE	stPType;
  DOWN_PROXY_AUTH_TYPE	stAType;
  wchar_t		szHost[2048];
  INT32		nPort;
  wchar_t		szUser[50];
  wchar_t		szPwd[50];
  wchar_t		szDomain[2048];
  tagDOWN_PROXY_INFO() {
   ::memset(this, 0x00, sizeof(*this));
  }
 }DOWN_PROXY_INFO;
 //struct WSAPROTOCOL_INFOW;
 // BT任务相关数据结构
 typedef struct tagTrackerInfo {
  wchar_t szTrackerUrl[1024];
  tagTrackerInfo() {
   ::memset(this, 0x00, sizeof(*this));
  }
 }TrackerInfo;
 typedef struct tagDownBTTaskParam {
  wchar_t szSeedFullPath[MAX_PATH];					//种子文件的全路径
  wchar_t szFilePath[MAX_PATH];						//文件保存目录
  DWORD dwNeedDownloadFileCount;						//指定要下载文件的个数
  DWORD* dwNeedDownloadFileIndexArray;				//要下载文件的在种子文件中的序号，从0开始计数
  DWORD dwTrackerInfoCount;							//下载使用的tracker服务器的个数
  TrackerInfo* pTrackerInfoArray;						//下载使用的tracker服务器的信息
  BOOL IsResume;										// 是否用续传
  tagDownBTTaskParam() {
   ::memset(this, 0x00, sizeof(*this));
  }
 }DownBTTaskParam;
 typedef struct tagBTTaskInfo {
  LONG lTaskStatus;				//任务状态, 0--正在运行,  10--暂停, 11--成功, 12--下载失败 
  DWORD dwUsingResCount;			//使用的资源数
  DWORD dwSumResCount;			//总资源数
  ULONGLONG ullRecvBytes;			//表示这个任务收到的字节数，这个值用来计算速度，不能用来计算进度
  ULONGLONG ullSendBytes;			//这个任务发送的字节
  BOOL bFileCreated;				//文件是否创建
  DWORD dwSeedCount;				//连接成功的种子peer个数
  DWORD dwConnectedBTPeerCount;	//连接成功的bt peer个数
  DWORD dwAllBTPeerCount;			//搜索到的总bt peer个数
  DWORD dwHealthyGrade;			//健康度，如健康度为987%时，healty_ grade的值为987
  tagBTTaskInfo() {
   ::memset(this, 0, sizeof(*this));
  }
 }BTTaskInfo;
 typedef struct tag_tracker_info {
  DWORD tracker_url_len;
  CHAR tracker_url[1024];		//tracker的url
  tag_tracker_info() {
   ::memset(this, 0, sizeof(*this));
  }
 }tracker_info;
 typedef struct tag_bt_file_info {
  ULONGLONG file_size;				//文件大小
  DWORD path_len;
  CHAR file_path[256];				//文件相对路径
  DWORD name_len;
  CHAR file_name[1024];				//文件名称
  tag_bt_file_info() {
   ::memset(this, 0, sizeof(*this));
  }
 }bt_file_info;
 typedef struct tag_bt_seed_file_info {
  CHAR info_id[20];
  DWORD title_len;
  CHAR title[1024];					//标题
  DWORD file_info_count;				//种子文件中包含可下载文件的个数
  bt_file_info* file_info_array;		//指针指向bt_file_info结构的数组
  DWORD tracker_count;				//种子文件中包含的tracker服务器的个数
  tracker_info* tracker_info_array;	//指针指向tracker_info数组
  DWORD publisher_len;
  CHAR publisher[8192];				//发布者说明
  DWORD publisher_url_len;
  CHAR publisher_url[1024];			//发布者url
  tag_bt_seed_file_info() {
   ::memset(this, 0, sizeof(*this));
  }
 }bt_seed_file_info;
 typedef struct tag_bt_data_file_item {
  DWORD path_len;
  CHAR file_path[256];				//文件绝对路径
  DWORD name_len;
  CHAR file_name[1024];				//文件名称
  tag_bt_data_file_item() {
   ::memset(this, 0, sizeof(*this));
  }
 }bt_data_file_item;
 typedef struct tag_bt_data_file_list {
  DWORD item_count;
  bt_data_file_item* item_array;
  tag_bt_data_file_list() {
   ::memset(this, 0, sizeof(*this));
  }
 }bt_data_file_list;
#pragma pack(pop)
}///namespace xlapi_3_2_2_30
#endif

/// /*新生®（上海）**/
/// /*2022_09_13T20:41:48.7855704Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___F92F8D7A_B486_4872_A589_75BEA5FC22DF__HEAD__
