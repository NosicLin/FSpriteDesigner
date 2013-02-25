#include "DsPropertyDisplay.h"
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <float.h>

DsPropertyDisplay::DsPropertyDisplay(QWidget* parent)
	:QWidget(parent)
{
    int vLayoutSpace = 20;
    int indentation =30;
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background,QColor(255,255,255));
    this->setPalette(palette);

    //===================================
    //setup mainLayout
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QMargins margins(30,11,30,50);
    mainLayout->setContentsMargins (margins);


    //1 setup position
    posLabel = new QLabel(tr("Position:"));
    posXLabel = new QLabel(tr("X:"));
    posYLabel = new QLabel(tr("Y:"));
    posXDoubleSpinbox = new QDoubleSpinBox(this);
    posYDoubleSpinbox = new QDoubleSpinBox(this);
    posXDoubleSpinbox->setDecimals(4);
    posXDoubleSpinbox->setRange(DBL_MIN,DBL_MAX);
    posXDoubleSpinbox->setSingleStep(1);
    posYDoubleSpinbox->setDecimals(4);
    posYDoubleSpinbox->setRange(DBL_MIN,DBL_MAX);
    posYDoubleSpinbox->setSingleStep(1);

    //2 setup angle
    angleLabel = new QLabel(tr("Angle:"));
    angLabel = new QLabel(tr("An:"));
    angleSpinDoubleBox = new QDoubleSpinBox(this);
    angleSpinDoubleBox->setDecimals(4);
    angleSpinDoubleBox->setRange(DBL_MIN,DBL_MAX);
    angleSpinDoubleBox->setSingleStep(1);


    //3 setup scale
    scaleLabel = new QLabel(tr("Scale:"));
    scaleXLabel = new QLabel(tr("SX:"));
    scaleYLabel = new QLabel(tr("SY:"));
    scaleXDoubleSpinBox = new QDoubleSpinBox(this);
    scaleYDoubleSpinBox = new QDoubleSpinBox(this);

    scaleXDoubleSpinBox->setDecimals(4);
    scaleXDoubleSpinBox->setRange(DBL_MIN,DBL_MAX);
    scaleXDoubleSpinBox->setSingleStep(0.05);

    scaleYDoubleSpinBox->setDecimals(4);
    scaleYDoubleSpinBox->setRange(DBL_MIN,DBL_MAX);
    scaleYDoubleSpinBox->setSingleStep(0.05);

    //4 setup TextureArea
    textureLabel = new QLabel(tr("TextureArea:"));
    textureX0Label = new QLabel(tr("TX0:"));
    textureY0Label = new QLabel(tr("TY0:"));
    textureX1Label = new QLabel(tr("TX1:"));
    textureY1Label = new QLabel(tr("TY1:"));

    textureX0DoubleSpinBox = new QDoubleSpinBox(this);
    textureY0DoubleSpinBox = new QDoubleSpinBox(this);
    textureX1DoubleSpinBox = new QDoubleSpinBox(this);
    textureY1DoubleSpinBox = new QDoubleSpinBox(this);

    textureX0DoubleSpinBox->setDecimals(6);
    textureX0DoubleSpinBox->setRange(DBL_MIN,DBL_MAX);
    textureX0DoubleSpinBox->setSingleStep(0.01);
    textureY0DoubleSpinBox->setDecimals(6);
    textureY0DoubleSpinBox->setRange(DBL_MIN,DBL_MAX);
    textureY0DoubleSpinBox->setSingleStep(0.01);

    textureX1DoubleSpinBox->setDecimals(6);
    textureX1DoubleSpinBox->setRange(DBL_MIN,DBL_MAX);
    textureX1DoubleSpinBox->setSingleStep(0.01);
    textureY1DoubleSpinBox->setDecimals(6);
    textureY1DoubleSpinBox->setRange(DBL_MIN,DBL_MAX);
    textureY1DoubleSpinBox->setSingleStep(0.01);

    //5 setup offset
    offsetLabel = new QLabel(tr("Offset:"));
    offsetXLabel = new QLabel(tr("X:"));
    offsetYLabel = new QLabel(tr("Y:"));
    offsetXDoubleSpinbox = new QDoubleSpinBox(this);
    offsetYDoubleSpinbox = new QDoubleSpinBox(this);
    offsetXDoubleSpinbox->setDecimals(4);
    offsetXDoubleSpinbox->setRange(DBL_MIN,DBL_MAX);
    offsetXDoubleSpinbox->setSingleStep(1);
    offsetYDoubleSpinbox->setDecimals(4);
    offsetYDoubleSpinbox->setRange(DBL_MIN,DBL_MAX);
    offsetYDoubleSpinbox->setSingleStep(1);

    //1 setup position layout
    QVBoxLayout* posMainLayout = new QVBoxLayout;
    QGridLayout* posButtonLayout = new QGridLayout;
    //posButtonLayout->setRowStretch(0,0);
    posButtonLayout->setSpacing(0);     //set both the vertical and horizontal spacing to spacing

    posButtonLayout->addItem(new QSpacerItem(indentation,0),0,0,1,1);
    posButtonLayout->addWidget(posXLabel,0,1,1,1,Qt::AlignRight);
    posButtonLayout->addWidget(posXDoubleSpinbox,0,2,1,3);
    posButtonLayout->addItem(new QSpacerItem(0,0),0,3,1,10);

    posButtonLayout->addItem(new QSpacerItem(indentation,0),1,0,1,1);
    posButtonLayout->addWidget(posYLabel,1,1,1,1);
    posButtonLayout->addWidget(posYDoubleSpinbox,1,2,1,3);
    posButtonLayout->addItem(new QSpacerItem(0,0),1,3,1,10);

    posMainLayout->addWidget(posLabel);
    posMainLayout->addLayout(posButtonLayout);
    posMainLayout->addItem(new QSpacerItem(0,vLayoutSpace));
    mainLayout->addLayout(posMainLayout);

    //2 setup angle layout
    QVBoxLayout* angMainLayout = new QVBoxLayout;
    QHBoxLayout* angButtonLayout = new QHBoxLayout;
    angButtonLayout->setSpacing(0);     //set both the vertical and horizontal spacing to spacing
    angButtonLayout->addItem(new QSpacerItem(indentation,0));
    angButtonLayout->addWidget(angLabel,1);
    angButtonLayout->addWidget(angleSpinDoubleBox,3);
    angButtonLayout->addStretch(10);

    angMainLayout->addWidget(angleLabel);
    angMainLayout->addLayout(angButtonLayout);
    angMainLayout->addItem(new QSpacerItem(0,vLayoutSpace));
    mainLayout->addLayout(angMainLayout);

    //3 setup scale layout
    QVBoxLayout* scaleMainLayout = new QVBoxLayout;
    QGridLayout* scaleButtonLayout = new QGridLayout;
   // scaleButtonLayout->setRowStretch(0,0);
    scaleButtonLayout->setSpacing(0);     //set both the vertical and horizontal spacing to spacing
    scaleButtonLayout->addItem(new QSpacerItem(indentation,0),0,0,1,1);
    scaleButtonLayout->addWidget(scaleXLabel,0,1,1,1);
    scaleButtonLayout->addWidget(scaleXDoubleSpinBox,0,2,1,3);
    scaleButtonLayout->addItem(new QSpacerItem(0,0),0,3,1,10);

    scaleButtonLayout->addItem(new QSpacerItem(indentation,0),1,0,1,1);
    scaleButtonLayout->addWidget(scaleYLabel,1,1,1,1);
    scaleButtonLayout->addWidget(scaleYDoubleSpinBox,1,2,1,3);
    scaleButtonLayout->addItem(new QSpacerItem(0,0),1,3,1,10);

    scaleMainLayout->addWidget(scaleLabel);
    scaleMainLayout->addLayout(scaleButtonLayout);
    scaleMainLayout->addItem(new QSpacerItem(0,vLayoutSpace));
    mainLayout->addLayout(scaleMainLayout);

    //4 setup TextureArea layout
    QVBoxLayout* textureMainLayout = new QVBoxLayout;
    QGridLayout* textureButtonLayout = new QGridLayout;
  //  textureButtonLayout->setRowStretch(0,0);
    textureButtonLayout->setSpacing(0);     //set both the vertical and horizontal spacing to spacing

    textureButtonLayout->addItem(new QSpacerItem(indentation,0),0,0,1,1);
    textureButtonLayout->addWidget(textureX0Label,0,1,1,1);
    textureButtonLayout->addWidget(textureX0DoubleSpinBox,0,2,1,3);
    textureButtonLayout->addItem(new QSpacerItem(0,0),0,3,1,10);

    textureButtonLayout->addItem(new QSpacerItem(indentation,0),1,0,1,1);
    textureButtonLayout->addWidget(textureY0Label,1,1,1,1);
    textureButtonLayout->addWidget(textureY0DoubleSpinBox,1,2,1,3);
    textureButtonLayout->addItem(new QSpacerItem(0,0),1,3,1,10);

    textureButtonLayout->addItem(new QSpacerItem(indentation,0),2,0,1,1);
    textureButtonLayout->addWidget(textureX1Label,2,1,1,1);
    textureButtonLayout->addWidget(textureX1DoubleSpinBox,2,2,1,3);
    textureButtonLayout->addItem(new QSpacerItem(0,0),2,3,1,10);

    textureButtonLayout->addItem(new QSpacerItem(indentation,0),3,0,1,1);
    textureButtonLayout->addWidget(textureY1Label,3,1,1,1);
    textureButtonLayout->addWidget(textureY1DoubleSpinBox,3,2,1,3);
    textureButtonLayout->addItem(new QSpacerItem(0,0),3,3,1,10);

    textureMainLayout->addWidget(textureLabel);
    textureMainLayout->addLayout(textureButtonLayout);
    textureMainLayout->addItem(new QSpacerItem(0,vLayoutSpace));
    mainLayout->addLayout(textureMainLayout);

    //5 setup offset layout
    QVBoxLayout* offsetMainLayout = new QVBoxLayout;
    QGridLayout* offsetButtonLayout = new QGridLayout;
   // offsetButtonLayout->setRowStretch(0,0);
    offsetButtonLayout->setSpacing(0);     //set both the vertical and horizontal spacing to spacing

    offsetButtonLayout->addItem(new QSpacerItem(indentation,0),0,0,1,1);
    offsetButtonLayout->addWidget(offsetXLabel,0,1,1,1);
    offsetButtonLayout->addWidget(offsetXDoubleSpinbox,0,2,1,3);
    offsetButtonLayout->addItem(new QSpacerItem(0,0),0,3,1,10);

    offsetButtonLayout->addItem(new QSpacerItem(indentation,0),1,0,1,1);
    offsetButtonLayout->addWidget(offsetYLabel,1,1,1,1);
    offsetButtonLayout->addWidget(offsetYDoubleSpinbox,1,2,1,3);
    offsetButtonLayout->addItem(new QSpacerItem(0,0),1,3,1,10);

    offsetMainLayout->addWidget(offsetLabel);
    offsetMainLayout->addLayout(offsetButtonLayout);
    offsetMainLayout->addItem(new QSpacerItem(0,vLayoutSpace));
    mainLayout->addLayout(offsetMainLayout);

    mainLayout->addStretch();
    this->setLayout(mainLayout);
}
