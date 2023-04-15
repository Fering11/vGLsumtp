#ifndef VGMAINMENU_H
#define VGMAINMENU_H

#include "vghead.hpp"

class vGMainMenu;
//偷懒类
class vGMainMenu_Private :public QObject {
	Q_OBJECT
	Q_PROPERTY(qint32 front_show READ front_show WRITE set_front_show)
public:
	vGMainMenu_Private(vGMainMenu* _parent);
	//_value > 0 show
	//_value <=0 hide
	quint32 front_show();
	void set_front_show(qint32 _value);
private:
	vGMainMenu* vp();
};
class vGMainMenu : public vGMenuBase
{
	Q_OBJECT
	friend class vGMainMenu_Private;
public:
	//background必须设置
	explicit vGMainMenu(QLayout* background, QWidget* parent = nullptr);
	~vGMainMenu();
	quint32 itemPos() const noexcept { return item_pos_; }

signals:

public slots:
	//释放layout中的_object
	void ReleaseWindow(vGAppWidBase* _object);
	//注册一个_object,并且在主界面上显示
	void LaunchWidget(vGAppWidBase* _object);
	void UpdateSkin() override;
	virtual void UpdateLayout(Action _action, QSize _new_size = {});
	//ac_* UI操作函数,会自动更新UI
	//向左推移
	void ac_turnLeft();
	//向右推移
	void ac_turnRight();
	//进入app
	void ac_enter();
protected:
	virtual void keyPressEvent(QKeyEvent* _event);
	//动画
	virtual QAbstractAnimation* __ac_enter(QSize _size = {})override;
	virtual QAbstractAnimation* __ac_escape(QSize _size = {})override;
private:
	//Ui::vGMainMenu *ui;
	qint16 item_pos_;
	//上一次前台
	QPointer<QWidget> last_app_;
	vGMainMenu_Private* private_;
};

#endif // VGMAINMENU_H
