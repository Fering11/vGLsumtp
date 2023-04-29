#ifndef __VGSHARE_HEAD
#define __VGSHARE_HEAD
//std C++17
//#define _ITERATOR_DEBUG_LEVEL 2
#include <set>
#include <deque>
#include <mutex>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <shared_mutex>
//公共头文件
//core widgets xml svg gui
#include <QDir>
#include <QList>
#include <QFile>
#include <QIcon>
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <QMutex>
#include <QThread>
#include <QString>
#include <QLayout>
#include <QPointer>
#include <QPainter>
#include <QProcess>
#include <QLibrary>
#include <QKeyEvent>
#include <QResource>
#include <QDateTime>
#include <QFileInfo>
#include <QTextStream>
#include <QMessageBox>
#include <QMainWindow>
#include <QResizeEvent> 
#include <QApplication>
#include <QSvgrenderer>
#include <QDomDocument>
#include <QTemporaryFile>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
// ../public
//spdlog
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/rotating_file_sink.h>
//nlohmann json
#include <nlohmann/json.hpp>

#include "vGCore_global.h"

enum class FrErrorStatue {
	Unknow,//未知错误
	InvalidParameter, //无效参数
	InvalidFile,  //无效文件
	Peripheral, //外围错误(非程序内部的错误)
	Nullptr		//空地址
};
class FrError :public std::exception {
public:
	FrError()noexcept :statue_(FrErrorStatue::Unknow),
		msg_(nullptr) {
	}
	explicit FrError(FrErrorStatue _statue, const char* const _msg)noexcept :
		statue_(_statue), msg_(nullptr) {
		if (_msg) {
			_set_msg(_msg);
		}
	}
	FrError(const FrError& _o)noexcept :msg_(nullptr), statue_(_o.statue_) {
		if (_o.msg_) {
			_set_msg(_o.msg_);
		}
	}
	~FrError() noexcept {
		if (msg_) {
			delete[] msg_;
		}
	}
	char const* what() const {
		return msg_ ? msg_ : "Unknow Error";
	}
	FrErrorStatue code() const {
		return statue_;
	}
private:
	void _set_msg(const char* const _msg) {
		size_t length = strnlen(_msg, 0xFFFF) + 1;
		msg_ = new char[length]();
		strcpy_s(msg_, length, _msg);
	}
	char* msg_;
	FrErrorStatue statue_;
};

#endif
