#include "AnimationTreeBase.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

void AnimationTreeBase::createPropertiesWidget()
{
    assert(this->propertiesWidget == nullptr);

    preparePropertiesWidget(QStringLiteral("AnimationTreeBase"));
    QVBoxLayout *vAllLaout = new QVBoxLayout(this->propertiesWidget);
    QLabel *label = new QLabel(nullptr);
    label->setText("No properties");
    vAllLaout->addWidget(label);
    vAllLaout->insertStretch(2, 1);
}

void AnimationTreeBase::preparePropertiesWidget(const QString &name)
{
    assert(this->propertiesWidget == nullptr);

    this->propertiesWidget = new QWidget;
    this->propertiesWidget->setObjectName(name);
}
