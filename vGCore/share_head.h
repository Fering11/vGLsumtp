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

class vGError :public std::runtime_error{
public:
	vGError(unsigned int _code, const char* const _msg = "")noexcept :
		runtime_error(_msg), code_(_code) {}
	unsigned int code() const noexcept {
		return code_;
	}
private:
	std::string what_;
	unsigned int code_;

};
#endif
