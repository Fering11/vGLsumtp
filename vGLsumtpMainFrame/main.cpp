/*
* 2023/1/6 vGLsumtp
* include:
* Qt
* nlohmann
* 
* version:
* 0.0.2
* log path:
* ./log/***.log
* 用空间来换取时间
* 插件全部是加载到内存，在插件量多的时候，估计会出问题
*/
#include "vgmainwindow.h"
#include "vghead.hpp"
//TODO 主要信息保存(对于默认日志文件保存位置)
QStringList restart_arguments(std::shared_ptr<vGAppInfomation> _arg) {
	QStringList result;
	result << QU8("--restart-count") << (QString::number(_arg->restart_count_));
	result << QU8("--log-level") << (QString::number(_arg->log_level));
	result << QU8("--log-size") << (QString::number(_arg->log_file_size));
	result << QU8("--log-count") << (QString::number(_arg->log_file_count));
	nlohmann::json err;
	if (_arg->msg_buf.size()) {
		auto& last_msg = _arg->msg_buf.back();
		err["code"] = last_msg.left(last_msg.indexOf('|')).toUInt(nullptr, 10);//错误代码
		err["msg"] = last_msg.right(last_msg.length() - last_msg.indexOf('|')).toStdString();
	} else {
		//没有错误提示，预料之外的行为
		err["code"] = _AE_APP_UNKNOW;
		err["msg"] = "unknow error";
	}
	result << QU8("--error-json") << QString::fromStdString(err.dump());
	return result;
}
//TODO 调试程序，重启测试
int startup(int argc, char* argv[])
{
#ifdef __linux__
	//linux必须以root权限执行
	if (geteuid() != 0) {
		qDebug() << "Error: Program must run as the root.\n";
		exit(_AE_PERM_FAILD);
	}
#endif
	int exit_code = 0;
	std::shared_ptr<vGAppInfomation> vgArgument(new vGAppInfomation());
	vgArgument->version_ = QU8("0.0.1"); //版本
	vgArgument->app_name = QU8("vGLsumtp"); //app名称
	//vgArgument->attribute_ = IntoApp;
	vgArgument->attribute_ = NULL;
	qsrand(time(nullptr));

	QCURDIR.mkdir(QU8("plugins")); //插件文件夹
	QCURDIR.mkdir(QU8("log"));     //日志文件夹
	vGApp app(argc, argv, vgArgument); //主APP
	try {
		app.initialize(); //进行初始化
		//日志系统可以使用
		vgDebug("The integration is initialized");//初始完毕
		vGMainWindow main_window;//主窗口
		main_window.show();
		exit_code = app.exec();
	}
	catch (const vGError& _err) {
		//异常在这被捕捉是不可逆回的错误
		//TODO 进行更友好的提示(或者不提示，进行重启，设置信息)
		QString why = QString::fromUtf8("Code:%1\r\nMsg:%2\r\n Program will restart...").
			arg(QN2S(_err.code()), QString::fromStdString(_err.what()));
		QMessageBox::information(nullptr, QU8("异常"), why);
		if (vgArgument->attribute_ & Restart) {
			exit_code = _APP_RESTART;//重启
		} else exit_code = _err.code();
	}
	catch (const std::exception& _err) {
		QMessageBox::information(nullptr, QString::fromUtf8("异常"), QString::fromUtf8("未知异常:%1").arg(QString::fromUtf8(_err.what())));
		//TODO 无法处理的错误
	}
	switch (exit_code)
	{
	case _APP_RESTART://应用重启
	{
		auto restarup_detail = app._getRestartInfo();
		restarup_detail->restart_count_ += 1;
		//使用默认参数
		if (restarup_detail->restart_count_ > 5) {
			//应该交给守护进程处理,重启5次不正常,不进行重启
			QMessageBox box(QMessageBox::Critical, QU8("应用启动失败!"), QU8("未知异常导致应用无法启动"));
			box.show();
			return _AE_APP_UNKNOW;
		}
		//不能使用日志，因为不知道有没有初始化完全
		bool suc = QProcess::startDetached(qApp->applicationFilePath(), restart_arguments(restarup_detail));
		QMessageBox::warning(nullptr, QU8("Restart"), QU8("Programing is preparing for restarting!\r\nresult:%1").arg(QN2S(suc)));
		break;
	}
	default:
		break;
	}
	return exit_code;
}

int main(int argc, char** argv) {
	int result = startup(argc, argv);
	return result;
}