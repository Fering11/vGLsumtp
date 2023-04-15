#include "vGLMenu.h"

vGLMenu::vGLMenu(QWidget* parent)
    : QMainWindow(parent)
{
    auto* _Parent = this;
    now_pos_ = 0;
    vGImageLabel* left_ = nullptr;
    vGImageLabel* center_ = nullptr;
    vGImageLabel* right_ = nullptr;
    left_ = new vGImageLabel(_Parent);
    left_->setObjectName("left");

    center_ = new vGImageLabel(_Parent);
    center_->setObjectName("center_");

    right_ = new vGImageLabel(_Parent);
    right_->setObjectName("right_");

    description_ = new vGImageLabel(_Parent);
    description_->setObjectName("description");

    buff_ = new vGImageLabel(_Parent);
    buff_->setObjectName("description");

    labs_.assign({ left_, center_,right_ });

    //不自动变化大小
    QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(_Parent->sizePolicy().hasHeightForWidth());
    left_->setSizePolicy(sizePolicy);
    center_->setSizePolicy(sizePolicy);
    right_->setSizePolicy(sizePolicy);
    description_->setSizePolicy(sizePolicy);
    buff_->setSizePolicy(sizePolicy);
    //内容居中显示
    left_->setAlignment(Qt::AlignCenter);
    right_->setAlignment(Qt::AlignCenter);
    center_->setAlignment(Qt::AlignCenter);
    description_->setAlignment(Qt::AlignCenter);
    buff_->setAlignment(Qt::AlignCenter);
    //图片填充
    left_->setScaledContents(true);
    right_->setScaledContents(true);
    center_->setScaledContents(true);
    description_->setScaledContents(true);
    buff_->setScaledContents(true);
    //透明度代理
    left_oe_ = new QGraphicsOpacityEffect(left_);
    left_->setGraphicsEffect(left_oe_);

    center_oe_ = new QGraphicsOpacityEffect(center_);
    center_->setGraphicsEffect(center_oe_);

    right_oe_ = new QGraphicsOpacityEffect(right_);
    right_->setGraphicsEffect(right_oe_);

    buff_oe_ = new QGraphicsOpacityEffect(buff_);
    buff_->setGraphicsEffect(buff_oe_);

    easing_curve_ = QEasingCurve::Type::InOutCirc;
    duration_time_ = 500;
}
void vGLMenu::updateLayout(Action _action) {
    const auto window_rect = this->rect();
    const auto ms_mark = window_rect.width() / 10;
    const auto wheight = window_rect.height();
    const auto wwidth = window_rect.width();
    //Center与其他框有空格 10
    constexpr int cen_side = 10;
    const auto cen_wid = wwidth - (ms_mark + cen_side) * 2;
    //const auto cen_wid = wwidth - ms_mark * 2 - cen_side * 2;
    const auto cen_hei = static_cast<int>(window_rect.height() * 0.9) - cen_side * 2;
    QRect ll, lr, lc, ld;
    //左侧
    if (wheight >= ms_mark) {
        ll = { 0,(wheight / 2 - ms_mark / 2),ms_mark ,ms_mark };
        lr = { wwidth - ms_mark,(wheight / 2 - ms_mark / 2) ,ms_mark,ms_mark };
    } else {
        ll = { (ms_mark / 2 - wheight / 2),0,wheight,wheight };
        lr = { (wwidth - ms_mark / 2 - wheight / 2),0,wheight,wheight };
    }
    if (cen_wid > cen_hei) {
        lc = { (cen_wid / 2 + 10 + ms_mark) - cen_hei / 2 ,cen_side,cen_hei,cen_hei };
    } else {
        //不想算了
        lc = { ms_mark, 0, window_rect.width() - ms_mark * 2, static_cast<int>(window_rect.height() * 0.9) };
    }
    ld = { ms_mark, static_cast<int>(window_rect.height() * 0.9), window_rect.width() - ms_mark * 2, window_rect.height() / 10 };
#if 1
    description_->setGeometry(ld);
    QEasingCurve::Type curve_style = (QEasingCurve::Type)easing_curve_;

    auto set_opacity = [](QLabel* _lab, qreal _re) {
        ((QGraphicsOpacityEffect*)_lab->graphicsEffect())->setOpacity(_re);
    };
    left_oe_->setOpacity(1);
    center_oe_->setOpacity(1);
    right_oe_->setOpacity(1);
    switch (_action)
    {
    case Left: {
        auto la_left= right();
        auto la_center = left();
        auto la_right = center();
        //assert(!la_left->pixmap());

        //隐藏la_left,buff_替代
        set_opacity(buff_, 0);
        buff_->setGeometry(la_left->rect());
        buff_->setPixmap(*la_left->pixmap());
        set_opacity(buff_, 1);
        set_opacity(la_left, 0);

        la_left->setPixmap(*la_left->nextPixmap());
        la_center->setPixmap(*la_center->nextPixmap());
        la_right->setPixmap(*la_right->nextPixmap());
        //大小变化
        QPropertyAnimation* cpag = new QPropertyAnimation(la_center, "geometry");
        QPropertyAnimation* rpag = new QPropertyAnimation(la_right, "geometry");
        //left和buff同步变化
        QPropertyAnimation* lpag = new QPropertyAnimation(la_left, "geometry");
        QPropertyAnimation* bpag = new QPropertyAnimation(buff_, "geometry");

        lpag->setDuration(duration_time_);
        bpag->setDuration(duration_time_);
        cpag->setDuration(duration_time_);
        rpag->setDuration(duration_time_);

        lpag->setEasingCurve(curve_style);
        bpag->setEasingCurve(curve_style);
        cpag->setEasingCurve(curve_style);
        rpag->setEasingCurve(curve_style);

        lpag->setStartValue(ll);
        bpag->setStartValue(ll);
        cpag->setStartValue(lc);
        rpag->setStartValue(lr);

        //Left ---> Right
        lpag->setEndValue(lr);
        bpag->setEndValue(lr);
        //Center ---> Left
        cpag->setEndValue(ll);
        //Right ---> Center
        rpag->setEndValue(lc);

        //添加 Left ---> Right时的透明度变化
        //隐藏buff_       1->0
        QPropertyAnimation* bpaop0 = new QPropertyAnimation(buff_->graphicsEffect(), "opacity", left());
        bpaop0->setDuration(duration_time_ / 2);
        bpaop0->setStartValue(1);
        bpaop0->setEndValue(0);
        bpaop0->setEasingCurve(curve_style);
        //显示left_       0->1
        QPropertyAnimation* rpaop1 = new QPropertyAnimation(la_left->graphicsEffect(), "opacity", left());
        rpaop1->setDuration(duration_time_ / 2);
        rpaop1->setStartValue(0);
        rpaop1->setEndValue(1);
        rpaop1->setEasingCurve(curve_style);
        //队列动画
        QSequentialAnimationGroup* rpaop_seq = new QSequentialAnimationGroup(this);
        rpaop_seq->addPause(duration_time_ / 2);
        rpaop_seq->addAnimation(rpaop1);

        //总队列
        QParallelAnimationGroup* pa_group = new QParallelAnimationGroup(this);

        pa_group->addAnimation(rpaop_seq);
        pa_group->addAnimation(bpaop0);
        pa_group->addAnimation(bpag);
        pa_group->addAnimation(cpag);
        pa_group->addAnimation(rpag);
        pa_group->addAnimation(lpag);
        pa_group->start(QParallelAnimationGroup::DeleteWhenStopped);
        break;
    }
    case Right: {
        //还没改变时的位置
        auto la_left = center();
        auto la_center = right();
        auto la_right = left();
        
         //隐藏la_left,buff_替代
        set_opacity(buff_, 0);
        buff_->setGeometry(la_right->rect());
        buff_->setPixmap(*la_right->pixmap());
        set_opacity(buff_, 1);
        set_opacity(la_right, 0);

        la_left->setPixmap(*la_left->nextPixmap());
        la_center->setPixmap(*la_center->nextPixmap());
        la_right->setPixmap(*la_right->nextPixmap());
        //大小变化
        QPropertyAnimation* lpag = new QPropertyAnimation(la_left, "geometry");
        QPropertyAnimation* cpag = new QPropertyAnimation(la_center, "geometry");
        //right与buff_同步变化
        QPropertyAnimation* rpag = new QPropertyAnimation(la_right, "geometry");
        QPropertyAnimation* bpag = new QPropertyAnimation(buff_, "geometry");

        lpag->setDuration(duration_time_);
        cpag->setDuration(duration_time_);
        rpag->setDuration(duration_time_);
        bpag->setDuration(duration_time_);

        lpag->setEasingCurve(curve_style);
        cpag->setEasingCurve(curve_style);
        rpag->setEasingCurve(curve_style);
        bpag->setEasingCurve(curve_style);
        
        lpag->setStartValue(ll);
        cpag->setStartValue(lc);
        rpag->setStartValue(lr);
        bpag->setStartValue(lr);

        //Left ---> Center
        lpag->setEndValue(lc);
        //Center ---> rigth
        cpag->setEndValue(lr);
        //Right ---> Left
        rpag->setEndValue(ll);
        bpag->setEndValue(ll);

        //Buff_逐渐变得透明
        QPropertyAnimation* rpaop0 = new QPropertyAnimation(buff_->graphicsEffect(), "opacity", left());
        rpaop0->setDuration(duration_time_ / 2);
        rpaop0->setStartValue(1);
        rpaop0->setEndValue(0);
        rpaop0->setEasingCurve(curve_style);
         //right变得明显
        QPropertyAnimation* rpaop1 = new QPropertyAnimation(la_right->graphicsEffect(), "opacity", left());
        rpaop1->setDuration(duration_time_ / 2);
        rpaop1->setStartValue(0);
        rpaop1->setEndValue(1);
        rpaop1->setEasingCurve(curve_style);
        //队列动画
        QSequentialAnimationGroup* rpaop_seq = new QSequentialAnimationGroup(this);
        rpaop_seq->addAnimation(rpaop0);
        rpaop_seq->addAnimation(rpaop1);

        //总队列
        QParallelAnimationGroup* pa_group = new QParallelAnimationGroup(this);

        pa_group->addAnimation(rpaop_seq);
        pa_group->addAnimation(cpag);
        pa_group->addAnimation(rpag);
        pa_group->addAnimation(lpag);
        pa_group->addAnimation(bpag);
        pa_group->start(QParallelAnimationGroup::DeleteWhenStopped);

        break;
    }
    case Resize: {
        auto la_left = left();
        auto la_center = center();
        auto la_right = right();

        //避免按太快导致透明度没完全恢复
        left_oe_->setOpacity(1);
        center_oe_->setOpacity(1);
        right_oe_->setOpacity(1);

        //大小变化
        QPropertyAnimation* lpag = new QPropertyAnimation(la_left, "geometry");
        QPropertyAnimation* cpag = new QPropertyAnimation(la_center, "geometry");
        QPropertyAnimation* rpag = new QPropertyAnimation(la_right, "geometry");

        lpag->setDuration(duration_time_);
        cpag->setDuration(duration_time_);
        rpag->setDuration(duration_time_);

        lpag->setEasingCurve(curve_style);
        cpag->setEasingCurve(curve_style);
        rpag->setEasingCurve(curve_style);

        //Left ---> Right
        lpag->setEndValue(ll);
        //Center ---> Left
        cpag->setEndValue(lc);
        //Right ---> Center
        rpag->setEndValue(lr);

        QParallelAnimationGroup* pa_group = new QParallelAnimationGroup(this);

        pa_group->addAnimation(cpag);
        pa_group->addAnimation(rpag);
        pa_group->addAnimation(lpag);
        pa_group->start(QParallelAnimationGroup::DeleteWhenStopped);
        break;
    }
    default:
        //啥也不做
        break;
    }
    description_->setText(QString::number(getPos()));
#endif
}
vGLMenu::~vGLMenu()
{}

void vGLMenu::resizeEvent(QResizeEvent * event)
{
    updateLayout(Resize);
}
unsigned int vGLMenu::getPos() const {
    return now_pos_;
}

quint16 vGLMenu::duration() const
{
    return duration_time_;
}

QEasingCurve::Type vGLMenu::easingCurve() const
{
    return QEasingCurve::Type(easing_curve_);
}

void vGLMenu::setDuration(quint16 _ms)
{
    duration_time_ = _ms;
}

void vGLMenu::setEasingCurve(QEasingCurve::Type _type)
{
    easing_curve_ = _type;
}

vGImageLabel* vGLMenu::left() {
    return labs_.front();
}
vGImageLabel* vGLMenu::center() {
    return labs_.at(1);
}
vGImageLabel* vGLMenu::right() {
    return labs_.back();
}
vGImageLabel* vGLMenu::left() const {
    return labs_.front();
}
vGImageLabel* vGLMenu::center() const {
    return labs_.at(1);
}
vGImageLabel* vGLMenu::right() const {
    return labs_.back();
}
void vGLMenu::add() {
    setPos(1);
}
void vGLMenu::sub() {
    setPos(-1);
}
void vGLMenu::setPos(int _size) {
    int real_size = _size % 3;//3个lab
    //data_pos_ = real_size;
    if (real_size < 0)
        real_size += 3;
    if (real_size == 1) {
        vGImageLabel* back = labs_.back();
        labs_.pop_back();
        labs_.push_front(back);
    } else if (real_size == 2) {
        vGImageLabel* front = labs_.front();
        labs_.pop_front();
        labs_.push_back(front);
    } else {
        //=0
    }
    now_pos_ = (now_pos_ + real_size) % 3;
}