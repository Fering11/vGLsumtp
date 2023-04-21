#include "vGConfig.h"
// ////////vGC_Base
void to_json(nlohmann::json& _json, const vGC_Base& _data)
{
	_json["log_path"] = _data.log_path.toStdString();
	_json["plugins"] = _data.plugins_path.toStdString();
	_json["skin_name"] = _data.skin_name.toStdString();
	_json["log_file_size"] = _data.log_file_size;
	_json["log_file_count"] = _data.log_file_count;
	_json["screen_height"] = _data.sc_height;
	_json["screen_width"] = _data.sc_width;
	_json["log_level"] = _data.log_level;
	_json["duration_time"] = _data.duration_time;
	_json["easing_curve"] = _data.easing_curve;
	
}

void from_json(const nlohmann::json& _json, vGC_Base& _data)
{
	_data.log_path = QString::fromStdString(_json.at("log_path").get<std::string>());
	_data.plugins_path = QString::fromStdString(_json.at("plugins").get<std::string>());
	_data.skin_name = QString::fromStdString(_json.at("skin_name").get<std::string>());
	_data.log_file_size = _json.at("log_file_size").get<quint32>();
	_data.log_file_count = _json.at("log_file_count").get<quint16>();
	_data.sc_height = _json.at("screen_height").get <quint16>();
	_data.sc_width = _json.at("screen_width").get <quint16>();
	_data.log_level = _json.at("log_level").get<quint8>();
	_data.duration_time = _json.at("duration_time").get<quint16>();
	_data.easing_curve = _json.at("easing_curve").get<quint8>();
}

// //////////vGC_Skin
//去掉# ，转为整形
//错误抛异常
QRgb __String2Rgba(QString _color) {
	bool ok = false;
	auto reg = _color.right(_color.length() - 1).toUInt(&ok, 16);
	if (!ok) {
		throw FrError(FrErrorStatue::InvalidFile, "The Skin file has been broken.");
	} else if (reg < 0x1000000) {//是rgb的格式转为rgba的格式
		reg += 0xff000000;
	}
	return reg;
}
QRgb __String2Rgba(std::string _color) {
	return __String2Rgba(QString::fromStdString(_color));
}

QRgb __JsonDRT(const nlohmann::json& _json, const char* const _key) {
	if (_json.contains(_key)) {
		return __String2Rgba(_json.at(_key).get<std::string>());
	} else {
		return 0xFFFFFFFF;
	}
}
//uint -> string
void to_json(nlohmann::json& _json, const vGC_Skin& _data) {
	_json["theme"] = _data.theme.name().toStdString();
	_json["menu"] = _data.menu;
}
//string -> uint
void from_json(const nlohmann::json& _json, vGC_Skin& _data) {
	_data.theme = __JsonDRT(_json, "theme");
	if (_json.contains("menu"))
		_data.menu = _json.at("menu");
}
// //vGC_Skin_Menu
void to_json(nlohmann::json& _json, const vGC_Skin_Menu& _data) {
	_json["background"] = _data.background.name().toStdString();
	_json["logo"] = _data.logo.name().toStdString();
}
void from_json(const nlohmann::json& _json, vGC_Skin_Menu& _data) {
	_data.background = __JsonDRT(_json, "background");
	_data.logo = __JsonDRT(_json, "logo");
}

// /////////vGC_Server
void to_json(nlohmann::json& _json, const vGC_Server& _data)
{
	Q_UNUSED(_json);
	Q_UNUSED(_data);
	//现在还不使用
}

void from_json(const nlohmann::json& _json, vGC_Server& _data)
{
	Q_UNUSED(_json);
	Q_UNUSED(_data);
}

void to_json(vGConfig::json& _json, const vGConfig& _data)
{
	_json["base"] = _data.base_;
	_json["server"] = _data.server_;
	//_json["skin"] = _data.skin_;
}

void from_json(const vGConfig::json& _json, vGConfig& _data)
{
	_data.base_ = _json.at("base").get<vGC_Base>();
	_data.server_ = _json.at("server").get<vGC_Server>();
	//_data.skin_ = _json.at("skin").get<vGC_Skin>();
}

vGConfig::vGConfig() :
	base_(), server_()
{
}

vGConfig::vGConfig(const json& _config){
	from_json(_config, *this);
}

vGConfig::~vGConfig()
{
}

vGC_Base vGConfig::base(){
	return base_;
}

vGC_Base vGConfig::base()const{
	return base_;
}

vGC_Server vGConfig::server(){
	return server_;
}

vGC_Server vGConfig::server() const{
	return server_;
}
// ///////////_vG_RGB
_vG_RGB _vG_RGB::from_name(QString _color) {
	return { __String2Rgba(_color) };
}

QString _vG_RGB::name() const
{
	return QU8("#%1").arg(QString::number(rgba_, 16));
}

QSize vGC_Base::win_size() const
{
	return QSize(sc_width,sc_height);
}
