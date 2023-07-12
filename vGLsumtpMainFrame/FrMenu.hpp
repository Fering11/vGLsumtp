#ifndef FRMENU_HEAD
#define FRMENU_HEAD
#include "vghead.hpp"
#include "FrPlugin.hpp"
class FrMenuSwitch;
//主界面对象
//考虑到外部插件线程会对Menu进行switchPlugin的操作（线程安全）
class FrMenu :public FrMenuBase {
	Q_OBJECT
public:
	constexpr static FrPluginData* FrMenuPlugin = (FrPluginData*)0x1;

	FrMenu(QLayout* _lay, QWidget* _parent = nullptr);
	void launchPlugin(FrPluginData* _target);
	void releasePlugin(FrPluginData* _target);
	void switchPlugin(FrPluginData* _starter, FrPluginData* _destination);
	void killPlugin(FrPluginData* _target);
private:
	//切换应用的界面
	FrMenuSwitch* wid_switch;
	//切换后台的应用
	QWidget* wid_back;
}; 
//主界面插件切换，没有动画
//不考虑线程安全
class FrMenuSwitch :public QWidget {
	Q_OBJECT
public:
	static constexpr int center_side = 10;
	static constexpr double label_ratio = 1.0 / 10.0; //1:8:1
	//能确保该函数调用时插件已经完全加载
	FrMenuSwitch(FrMenu* _menu);
	void calculateSize(QSize _new_size, QRect _container[4]);
	//前进，和下面的函数一样，并不会更新界面
	bool advance();
	//后退
	bool retreat();
public slots:
	//更新插件缓存
	void updatePlugin();
	//更新界面显示的插件
	void updateImage();
signals:
	//信号，更新大小
	void updateSize(QSize _size);
	//信号，启动插件
	void activatePlugin(FrPluginData* _target);
protected:
	void keyPressEvent(QKeyEvent* _event);
	void resizeEvent(QResizeEvent* _event);

private:
	QLabel* left_;
	QLabel* center_;
	QLabel* right_;
	QLabel* description_;
	//考虑到插件不常更新
	std::vector<QPointer<FrPluginData>> frplugin_;
	vIterator<std::vector<QPointer<FrPluginData>>> iter_;
};
#endif