/****************************************************************************
 **
 ** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
 ** Contact: http://www.qt-project.org/legal
 **
 ** This file is part of the examples of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:BSD$
 ** You may use this file under the terms of the BSD license as follows:
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
 **   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
 **     of its contributors may be used to endorse or promote products derived
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

 #include <QtGui>
 #include <QtOpenGL>

 #include "glwidget.h"
 #include "mainwindow.h"
 #include "ui_grabber.h"

//obs
 MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
 {
     ui->setupUi(this);
 }

 void MainWindow::renderIntoPixmap()
 {
     QSize size = getSize();
     if (size.isValid()) {
         QPixmap pixmap = ui->glWidget->renderPixmap(size.width(), size.height());
         setPixmap(pixmap);
     }
 }

 void MainWindow::grabFrameBuffer()
 {
     QImage image = ui->glWidget->grabFrameBuffer();
     setPixmap(QPixmap::fromImage(image));
 }

 void MainWindow::clearPixmap()
 {
     setPixmap(QPixmap());
 }

 void MainWindow::about()
 {
     QMessageBox::about(this, tr("About Grabber"),
             tr("The <b>Grabber</b> example demonstrates two approaches for "
                "rendering OpenGL into a Qt pixmap."));
 }

 void MainWindow::setPixmap(const QPixmap &pixmap)
 {
     ui->pixmapLabel->setPixmap(pixmap);
     QSize size = pixmap.size();
     if (size - QSize(1, 0) == ui->pixmapLabelArea->maximumViewportSize())
         size -= QSize(1, 0);
     ui->pixmapLabel->resize(size);
 }

 QSize MainWindow::getSize()
 {
     bool ok;
     QString text = QInputDialog::getText(this, tr("Grabber"),
                                          tr("Enter pixmap size:"),
                                          QLineEdit::Normal,
                                          tr("%1 x %2").arg(ui->glWidget->width())
                                                       .arg(ui->glWidget->height()),
                                          &ok);
     if (!ok)
         return QSize();

     QRegExp regExp(tr("([0-9]+) *x *([0-9]+)"));
     if (regExp.exactMatch(text)) {
         int width = regExp.cap(1).toInt();
         int height = regExp.cap(2).toInt();
         if (width > 0 && width < 2048 && height > 0 && height < 2048)
             return QSize(width, height);
     }

     return ui->glWidget->size();
 }
