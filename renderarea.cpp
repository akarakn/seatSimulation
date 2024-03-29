/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "renderarea.h"

#include <QPainter>
#include <QPaintEvent>
#include<QDebug>

//! [0]
RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    QFont newFont = font();
    newFont.setPixelSize(12);
    setFont(newFont);

    QFontMetrics fontMetrics(newFont);
    xBoundingRect = fontMetrics.boundingRect(tr("x"));
    yBoundingRect = fontMetrics.boundingRect(tr("y"));
}
//! [0]

//! [1]
void RenderArea::setOperations(const QList<Operation> &operations)
{
    this->operations = operations;
    update();
}
//! [1]

//! [2]
void RenderArea::setShape1(const QPainterPath &shape)
{
    this->shape1 = shape;
    update();
}

void RenderArea::setShape2(const QPainterPath &shape)
{
    this->shape2 = shape;
    update();
}
//! [2]

//! [3]
QSize RenderArea::minimumSizeHint() const
{
    return QSize(250, 250);
}
//! [3]

//! [4]
QSize RenderArea::sizeHint() const
{
    return QSize(250, 250);
}
//! [4]

//! [5]
void RenderArea::paintEvent(QPaintEvent *event)
{
    QPainter painter1(this);
    QPainter painter2(this);
    painter1.setRenderHint(QPainter::Antialiasing);
    painter1.fillRect(event->rect(), QBrush(Qt::white));

    painter1.translate(125, 125);
    painter1.drawLine(-0,125,250,125);
//! [5]

//! [6]
    painter1.save();
    rotatePainter(painter1);
    //movePainter(painter1);
    //transformPainter(painter1);
    drawShape1(painter1);
    painter1.restore();

    painter2.setRenderHint(QPainter::Antialiasing);
    //painter2.fillRect(event->rect(), QBrush(Qt::white));

    painter2.translate(125, 125);
//! [5]

//! [6]
    painter2.save();
    movePainter(painter2);
    drawShape2(painter2);
    painter2.restore();

//! [6]

//! [7]
    //drawOutline(painter1);
//! [7]

//! [8]
    //transformPainter(painter);
    //drawCoordinates(painter);
}
//! [8]

//! [9]
void RenderArea::drawCoordinates(QPainter &painter)
{
    painter.setPen(Qt::red);

    painter.drawLine(0, 0, 50, 0);
    painter.drawLine(48, -2, 50, 0);
    painter.drawLine(48, 2, 50, 0);
    painter.drawText(60 - xBoundingRect.width() / 2,
                     0 + xBoundingRect.height() / 2, tr("x"));

    painter.drawLine(0, 0, 0, 50);
    painter.drawLine(-2, 48, 0, 50);
    painter.drawLine(2, 48, 0, 50);
    painter.drawText(0 - yBoundingRect.width() / 2,
                     60 + yBoundingRect.height() / 2, tr("y"));
}
//! [9]

//! [10]
void RenderArea::drawOutline(QPainter &painter)
{
    painter.setPen(Qt::darkGreen);
    painter.setPen(Qt::DashLine);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(0, 0, 100, 100);
}
//! [10]

//! [11]
void RenderArea::drawShape1(QPainter &painter)
{
    painter.fillPath(shape1, Qt::blue);
}
void RenderArea::drawShape2(QPainter &painter)
{
    painter.fillPath(shape2, Qt::red);
}
//! [11]

//! [12]
void RenderArea::transformPainter(QPainter &painter)
{
    for (int i = 0; i < operations.size(); ++i) {
        switch (operations[i]) {
        case Translate:
            painter.translate(50, 50);
            break;
        case Scale:
            painter.scale(0.75, 0.75);
            break;
        case Rotate:
            painter.rotate(60);
            break;
        case NoTransformation:
        default:
            ;
        }
    }
}
void RenderArea::rotatePainter(QPainter &painter){
    qDebug()<<"rotate: "<<angle;
    painter.translate(50,0);
    painter.rotate(this->angle);
    painter.translate(-50,0);

}
void RenderArea::movePainter(QPainter &painter){
    qDebug()<<"move: "<<height;
    painter.translate(0,this->height);
}


void RenderArea::setAngle(int angle){
    qDebug()<<"new angle: "<<angle;
    this->angle = angle;
    update();

}
void RenderArea::setHeight(int heigth){
    qDebug()<<"new move: "<<heigth;
    this->height = heigth;
    update();

}
//! [12]
