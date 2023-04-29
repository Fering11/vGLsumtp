#ifndef __VGCONFIG_H
#define __VGCONFIG_H
#include "define.h"
#include "share_head.h"
class vGApp;
//配置文件定义

// //////////////////// 核心配置 ///////////////
// 全部值必须存在，不可以存在缺省值
struct VGCORE_EXPORT vGC_Base {
	QString log_path;     //日志路径
	QString plugins_path; //插件路径
	QString skin_name;    //默认皮肤名称
	quint32 log_file_size = 0;  //日志文件最大体积(KB)
	quint16 log_file_count = 0; //日志文件最大数量
	quint16 duration_time = 0; //全局动画播放时间
	//假定眼镜屏幕不会随便变化
	quint16 sc_height = 0; //默认窗口高
	quint16 sc_width = 0;  //默认窗口宽
	quint8 log_level = 0; //日志等级
	quint8 easing_curve; //全局动画样式
	QSize win_size()const; //偷懒
};

// //////////////////// 皮肤方面 ////////////////
// 全部颜色为 RGBA 格式
// RGB 格式写进来也会自动转为 RGBA
// #aabbccdd
// 对于缺省值，会使用默认值替代(0xffffffff)
//主菜单

class VGCORE_EXPORT _vG_RGB {
public:
	_vG_RGB() :rgba_(NULL) {}
	_vG_RGB(QRgb _color) { rgba_ = _color; }
	//QColor::name
	static _vG_RGB from_name(QString _color);
	QString name()const;
	QRgb rgba()const { return rgba_; }
	void set(QRgb _color) { rgba_ = _color; }
private:
	QRgb rgba_;
};
struct vGC_Skin_Menu {
	_vG_RGB background;
	_vG_RGB logo;
};
//全局皮肤设定
struct vGC_Skin {
	_vG_RGB theme; //主题颜色(JSON格式为整形)
	vGC_Skin_Menu menu;
};
// ///////////////////// 通信 /////////////////////
// TODO 添加网络处理相关
struct vGC_Server {
};

class VGCORE_EXPORT vGConfig {
public:
	using json = nlohmann::json;
	//输入json后，会判断是否有核心变量存在
	//否则就抛出异常(json::exception类型异常)
	vGConfig();
	vGConfig(const json& _config);
	~vGConfig();
	//x由to_json替代
	//xvoid make_json(vGConfig::json& _json)const;
	vGC_Base base();
	vGC_Base base()const;
	vGC_Server server();
	vGC_Server server()const;
	friend void to_json(json& _json, const vGConfig& _data);
	friend void from_json(const json& _json, vGConfig& _data);
	//方便偷懒
	//x仅仅给vGApp提供修改接口
	friend class vGApp;

private:
	vGC_Base base_;
	vGC_Server server_;
};

//异常抛出函数
VGCORE_EXPORT void FrThrowError(FrErrorStatue _statue, const char* const _msg);

//json结构体转化

//通信 vGC_Server
VGCORE_EXPORT void to_json(nlohmann::json& _json, const vGC_Server& _data);
VGCORE_EXPORT void from_json(const nlohmann::json& _json, vGC_Server& _data);
//皮肤.菜单 vGC_Skin_Menu
VGCORE_EXPORT void to_json(nlohmann::json& _json, const vGC_Skin_Menu& _data);
VGCORE_EXPORT void from_json(const nlohmann::json& _json, vGC_Skin_Menu& _data);
//皮肤 vGC_Skin
VGCORE_EXPORT void to_json(nlohmann::json& _json, const vGC_Skin& _data);
VGCORE_EXPORT void from_json(const nlohmann::json& _json, vGC_Skin& _data);
//核心 vGC_Base
VGCORE_EXPORT void to_json(nlohmann::json& _json, const vGC_Base& _data);
VGCORE_EXPORT void from_json(const nlohmann::json& _json, vGC_Base& _data);
#endif //__VGCONFIG_H
