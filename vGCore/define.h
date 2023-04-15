//定义一些全局宏
#ifndef DEFINE_HEAD
#define DEFINE_HEAD
#define _AP_PLUGINS_PATH    (R"(./plugins)")  //默认插件目录
#define _AP_SKINS_PATH      (R"(./skins)")    //默认皮肤目录

#define QU8(_str)            (QString::fromUtf8(_str))
#define QSTD(_qstring)       (_qstring.toStdString())
#define QCURDIR              (QDir(QDir::currentPath()))
#define QN2S(_number)        (QString::number(_number,10))
//关于程序动作宏
#define _APP_RESTART             (0x1001)          //应用重启，设置qApp->exit
//错误宏
#define _AE_APP_UNKNOW           (0x2000)        //不知道什么异常
#define _AE_LOG_FILE             (0x2001)          //日志文件错误
#define _AE_CONFIG_FILE          (0x2002)       //配置文件错误
#define _AE_SKIN_FILE            (0x2003)        //皮肤配置文件错误
#define _AE_FUNC_PARAM           (0x2004)        //传入错误的参数
#define _AE_PLUGIN_NULL          (0x2005)        //没有插件

#define _AE_PERM_FAILD           (0x4001)        //权限不足
//json数组二进制
#define _AE_JSON_BINARY 0

#endif 
