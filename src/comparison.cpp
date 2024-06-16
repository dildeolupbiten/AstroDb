#include "../include/comparison.hpp"
#include "../include/utils.hpp"

Comparison::Comparison(str title, QWidget *parent) : Frame(title, parent) {
    mid = new QFrame(this);
    canvas = new Canvas(bottom);
    mid_left = new QFrame(mid);
    mid_right = new QFrame(mid);
    frame_x1 = new QFrame(mid_left);
    frame_n1 = new QFrame(mid_left);
    frame_x2 = new QFrame(mid_left);
    frame_n2 = new QFrame(mid_left);
    x1 = new QSpinBox(frame_x1);
    n1 = new QSpinBox(frame_n1);
    x2 = new QSpinBox(frame_x2);
    n2 = new QSpinBox(frame_n2);
    label_frame = new QFrame(mid_right);
    var_frame = new QFrame(mid_right);
    var_binomial_p_lower = new QLabel("0", label_frame);
    var_binomial_p = new QLabel("0", label_frame);
    var_binomial_p_upper = new QLabel("0", label_frame);
    var_cohens_d = new QLabel("0", label_frame);
    var_z_score = new QLabel("0", label_frame);
    reconfigItems();
};

void Comparison::reconfigItems() {
    setFrameStyle(QFrame::Box | QFrame::Raised);
    layout() -> removeWidget(bottom);
    layout() -> addWidget(mid);
    layout() -> addWidget(bottom);
    layout() -> setAlignment(top, Qt::AlignCenter);
    layout() -> setAlignment(bottom, Qt::AlignCenter);
    setObjectName("comparison");
    mid -> setLayout(new QHBoxLayout(mid));
    mid -> layout() -> addWidget(mid_left);
    mid -> layout() -> addWidget(mid_right);
    mid -> layout() -> setAlignment(mid_left, Qt::AlignCenter);
    mid -> layout() -> setAlignment(mid_right, Qt::AlignCenter);
    canvas -> setLayout(new QVBoxLayout(canvas));
    canvas -> setFixedWidth(700);
    canvas -> setStyleSheet("border: 1px solid #343a40; border-radius: 2px;");
    bottom -> layout() -> addWidget(canvas);
    QFrame *fill = new QFrame(bottom);
    fill -> setFixedHeight(50);
    bottom -> layout() -> addWidget(fill);
    bottom -> setFixedHeight(350);
    mid_left -> setLayout(new QVBoxLayout(mid_left));
    mid_left -> layout() -> addWidget(frame_x1);
    mid_left -> layout() -> addWidget(frame_n1);
    mid_left -> layout() -> addWidget(frame_x2);
    mid_left -> layout() -> addWidget(frame_n2);
    QLabel *label_x1 = new QLabel("x (Case)", frame_x1);
    label_x1 -> setStyleSheet("color: green;");
    frame_x1 -> setLayout(new QHBoxLayout(frame_x1));
    frame_x1 -> layout() -> addWidget(label_x1);
    frame_x1 -> layout() -> addWidget(x1);
    frame_x1 -> layout() -> setAlignment(label_x1, Qt::AlignCenter);
    frame_x1 -> layout() -> setAlignment(x1, Qt::AlignCenter);
    frame_x1 -> setFixedHeight(100);
    x1 -> setFixedWidth(100);
    QLabel *label_n1 = new QLabel("n (Case)", frame_n1);
    frame_n1 -> setLayout(new QHBoxLayout(frame_n1));
    label_n1 -> setStyleSheet("color: green;");
    frame_n1 -> layout() -> addWidget(label_n1);
    frame_n1 -> layout() -> addWidget(n1);
    frame_n1 -> layout() -> setAlignment(label_n1, Qt::AlignCenter);
    frame_n1 -> layout() -> setAlignment(n1, Qt::AlignCenter);
    frame_n1 -> setFixedHeight(100);
    n1 -> setFixedWidth(100);
    QLabel *label_x2 = new QLabel("x (Test)", frame_x2);
    label_x2 -> setStyleSheet("color: red;");
    frame_x2 -> setLayout(new QHBoxLayout(frame_x2));
    frame_x2 -> layout() -> addWidget(label_x2);
    frame_x2 -> layout() -> addWidget(x2);
    frame_x2 -> layout() -> setAlignment(label_x2, Qt::AlignCenter);
    frame_x2 -> layout() -> setAlignment(x2, Qt::AlignCenter);
    frame_x2 -> setFixedHeight(100);
    x2 -> setFixedWidth(100);
    QLabel *label_n2 = new QLabel("n (Test)", frame_n2);
    label_n2 -> setStyleSheet("color: red;");
    frame_n2 -> setLayout(new QHBoxLayout(frame_n2));
    frame_n2 -> layout() -> addWidget(label_n2);
    frame_n2 -> layout() -> addWidget(n2);
    frame_n2 -> layout() -> setAlignment(label_n2, Qt::AlignCenter);
    frame_n2 -> layout() -> setAlignment(n2, Qt::AlignCenter);
    frame_n2 -> setFixedHeight(100);
    n2 -> setFixedWidth(100);
    x1 -> setMinimum(0);
    x1 -> setMaximum(100000);
    x1 -> setSingleStep(1);
    n1 -> setMinimum(0);
    n1 -> setMaximum(100000);
    n1 -> setSingleStep(1);
    x2 -> setMinimum(0);
    x2 -> setMaximum(100000);
    x2 -> setSingleStep(1);
    n2 -> setMinimum(0);
    n2 -> setMaximum(100000);
    n2 -> setSingleStep(1);
    mid_right -> setLayout(new QVBoxLayout(mid_right));
    QFrame *mid_right_top = new QFrame(mid_right);
    QFrame *mid_right_bottom = new QFrame(mid_right);
    mid_right -> layout() -> addWidget(mid_right_top);
    mid_right -> layout() -> addWidget(mid_right_bottom);
    mid_right_top -> setLayout(new QHBoxLayout(mid_right_top));
    mid_right_top -> layout() -> addWidget(label_frame);
    mid_right_top -> layout() -> addWidget(var_frame);
    label_frame -> setLayout(new QVBoxLayout(label_frame));
    QLabel *binomial_p_lower = new QLabel("Binomial P(x >= k)", label_frame);
    QLabel *binomial_p = new QLabel("Binomial P(x == k)", label_frame);
    QLabel *binomial_p_upper = new QLabel("Binomial P(x <= k)", label_frame);
    QLabel *z_score = new QLabel("Z-Score", label_frame);
    QLabel *cohens_d = new QLabel("Cohen's D Effect Size", label_frame);
    label_frame -> layout() -> addWidget(binomial_p_lower);
    label_frame -> layout() -> addWidget(binomial_p);
    label_frame -> layout() -> addWidget(binomial_p_upper);
    label_frame -> layout() -> addWidget(cohens_d);
    label_frame -> layout() -> addWidget(z_score);
    var_frame -> setLayout(new QVBoxLayout(var_frame));
    var_frame -> layout() -> addWidget(var_binomial_p_lower);
    var_frame -> layout() -> addWidget(var_binomial_p);
    var_frame -> layout() -> addWidget(var_binomial_p_upper);
    var_frame -> layout() -> addWidget(var_cohens_d);
    var_frame -> layout() -> addWidget(var_z_score);
    CanvasVars vars = {
        var_binomial_p_lower, 
        var_binomial_p, 
        var_binomial_p_upper, 
        var_cohens_d, var_z_score
    };
    connect(
        x1, 
        QOverload<int>::of(&QSpinBox::valueChanged),
        [this, vars](){ canvas -> plot(x1, n1, x2, n2, vars); }
    );
    connect(
        n1,
        QOverload<int>::of(&QSpinBox::valueChanged),
        [this, vars](){ canvas -> plot(x1, n1, x2, n2, vars); }
    );
    connect(
        x2,
        QOverload<int>::of(&QSpinBox::valueChanged),
        [this, vars](){ canvas -> plot(x1, n1, x2, n2, vars); }
    );
    connect(
        n2,
        QOverload<int>::of(&QSpinBox::valueChanged),
        [this, vars](){ canvas -> plot(x1, n1, x2, n2, vars); }
    );
    x1 -> setValue(50);
    n1 -> setValue(100);
    x2 -> setValue(500);
    n2 -> setValue(1000);
    canvas -> plot(x1, n1, x2, n2, vars);
}

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPainterPath path1;
    QPainterPath path2;
    dict<str, list<double>> vp1 = case_group.values;
    dict<str, list<double>> vp2 = test_group.values;
    if (!vp1["x"].size() || !vp2["x"].size()) {
        return;
    }
    double maxX1 = *std::max_element(vp1["x"].begin(), vp1["x"].end());
    double maxY1 = *std::max_element(vp1["y"].begin(), vp1["y"].end());
    double maxX2 = *std::max_element(vp2["x"].begin(), vp2["x"].end());
    double maxY2 = *std::max_element(vp2["y"].begin(), vp2["y"].end());
    double maxX = std::max(maxX1, maxX2);
    double maxY = std::max(maxY1, maxY2);
    double height = this -> height();
    double width = this -> width();
    path1.moveTo(
        width * (vp1["x"][0] / maxX), 
        height - (vp1["y"][0] / maxY) * height
    );
    path2.moveTo(
        width * (vp2["x"][0] / maxX), 
        height - (vp2["y"][0] / maxY) * height
    );
    for (int i = 0; i < vp1["x"].size(); i++) {
        double scaledX1 = (width * (vp1["x"][i] / maxX));
        double scaledY1 = height - (height * (vp1["y"][i] / maxY));
        path1.lineTo(scaledX1, scaledY1);
        if (case_group.mean == vp1["x"][i]) {
            path1.lineTo(scaledX1, height - 0);
            path1.moveTo(scaledX1, scaledY1);
        }
    }
    for (int i = 0; i < vp2["x"].size(); i++) {
        double scaledX2 = (width * (vp2["x"][i] / maxX));
        double scaledY2 = height - (height * (vp2["y"][i] / maxY));
        path2.lineTo(scaledX2, scaledY2);
        if (test_group.mean == vp2["x"][i]) {
            path2.lineTo(scaledX2, height - 0);
            path2.moveTo(scaledX2, scaledY2);
        }
    }
    painter.setPen(QPen(Qt::green, 1));
    painter.drawPath(path1);
    painter.setPen(QPen(Qt::red, 1));
    painter.drawPath(path2);
}

void Canvas::plot(
    QSpinBox *x1, 
    QSpinBox *n1, 
    QSpinBox *x2, 
    QSpinBox *n2, 
    CanvasVars vars
){
    double x1_ = x1 -> value();
    double n1_ = n1 -> value();
    double x2_ = x2 -> value();
    double n2_ = n2 -> value();
    if (x1_ >= n1_ || x2_ >= n2_) { return; }
    case_group = plotValues(x1_, n1_, 0);
    test_group = plotValues(x2_, n2_, n1_);
    vars.binomial_p -> setText(
        QString::fromStdString(
            std::to_string(binom(n1_, x1_, x2_ / n2_) * 100) + " %"
        )
    );
    vars.binomial_p_lower -> setText(
        QString::fromStdString(
            std::to_string((1 - pmf(n1_, x1_ - 1, x2_ / n2_)) * 100) + " %")
    );
    vars.binomial_p_upper -> setText(
        QString::fromStdString(
            std::to_string(pmf(n1_, x1_, x2_ / n2_) * 100) + " %"
        )
    );
    vars.cohens_d -> setText(
        QString::fromStdString(
            std::to_string(cohensDValues(x1_, x2_, n1_, n2_))
        )
    );
    vars.z_score -> setText(
        QString::fromStdString(
            std::to_string(zscore(n1_, x1_, x2_ / n2_))
        )
    );
    update();
}

