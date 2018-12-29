#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit> 
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include "compareLineEdit.h"
#include <QGroupBox>
#include <QFont>
#include <QFile>
#include <QPixmap>
#include "states.h"

QImage *greenState = new QImage(12, 11, QImage::Format_ARGB32);
QImage *yellowState = new QImage(12, 11, QImage::Format_ARGB32);
QImage *redState = new QImage(12, 11, QImage::Format_ARGB32);
QImage *emptyState = new QImage(12, 11, QImage::Format_ARGB32);


compareLineEdit::compareLineEdit(QWidget *parent) : QLineEdit(parent) {}

void compareLineEdit::dragEnterEvent(QDragEnterEvent *event) {
	if (event->mimeData()->hasText() or event->mimeData()->hasUrls()) {
		event->acceptProposedAction();
	}
}

void compareLineEdit::dropEvent(QDropEvent *event) {
	QUrl fUrl;
	QString fName;
	QFileInfo info;
	if (event->mimeData()->hasUrls()) {
		fUrl = event->mimeData()->urls()[0];
		fName = fUrl.toLocalFile();
		info.setFile(fName);
			if (info.isFile()) {
				setText(fName);
			}
	}
	event->acceptProposedAction();
}

void compareLineEdit::mouseDoubleClickEvent(QMouseEvent *event) {
	QFileDialog fDialog;
	QString fName;
	QFileInfo info;
	fName = fDialog.getOpenFileName(this, "Select File", QDir::homePath());
	if (!(fName.isEmpty())) {
		info.setFile(fName);
		if (info.isFile()) {
			setText(fName);
		}
	}
}


class compareWindow : public QWidget
{
        Q_OBJECT
public:
        compareWindow(void);
protected:
        QPushButton *compareButton;
	QPushButton *quitButton;
	QPushButton *resetButton;
	QGroupBox *fileAbox;
	QGroupBox *fileBbox;
	QLabel *fileAboxLabel;
	QLabel *fileBboxLabel;
	compareLineEdit *fileApath;
	compareLineEdit *fileBpath;
	QPushButton *fileApathBrowse;
	QPushButton *fileBpathBrowse;
	QLabel *aFileSizeLabel;
	QLabel *aFileSize;
	QLabel *aFileCreateLabel;
	QLabel *aFileCreate;
	QLabel *aFileChangeLabel;
	QLabel *aFileChange;
	QLabel *aFileMD5Label;
	QLabel *aFileMD5;
	QLabel *bFileSizeLabel;
	QLabel *bFileSize;
	QLabel *bFileCreateLabel;
	QLabel *bFileCreate;
	QLabel *bFileChangeLabel;
	QLabel *bFileChange;
	QLabel *aFileReadLabel;
	QLabel *aFileRead;
	QLabel *bFileReadLabel;
	QLabel *bFileRead;
	QLabel *bFileMD5Label;
	QLabel *bFileMD5;
	QPixmap *redDot;
	QPixmap *yellowDot;
	QPixmap *greenDot;
	QPixmap *emptyDot;
	QLabel *aStatus1;
	QLabel *aStatus2;
	QLabel *aStatus3;
	QLabel *aStatus4;
	QLabel *aStatus5;
	QLabel *bStatus1;
	QLabel *bStatus2;
	QLabel *bStatus3;
	QLabel *bStatus4;
	QLabel *bStatus5;
	QLabel *copyright;
public slots:
	void fileABrowse(void);
	void fileBBrowse(void);	
	void fileApathChanged(QString text);
	void fileBpathChanged(QString text);
	void filesCompare(void);
	void clearAll(void);
};

compareWindow::compareWindow(void) {
	this->setFixedSize(500, 300);
	this->setWindowTitle("File Comparison");
	compareButton = new QPushButton(this);
	compareButton->setGeometry(QRect(350, 255, 130, 40));
	compareButton->setText("Compare");
	quitButton = new QPushButton(this);
	quitButton->setGeometry(QRect(90, 255, 130, 40));
	quitButton->setText("Quit");
	resetButton = new QPushButton(this);
	resetButton->setGeometry(QRect(220, 255, 130, 40));
	resetButton->setText("Reset");
	fileAbox = new QGroupBox(this);
	fileBbox = new QGroupBox(this);
	fileAbox->setGeometry(QRect(20, 15, 460, 120));
	fileBbox->setGeometry(QRect(20, 140, 460, 120));
	fileAbox->setFlat(true);
	fileBbox->setFlat(true);
	fileAboxLabel = new QLabel(this);
	fileBboxLabel = new QLabel(this);
	fileAboxLabel->setGeometry(QRect(30, 8, 40, 15));
	fileBboxLabel->setGeometry(QRect(30, 133, 40, 15));
	fileAboxLabel->setText("  File A:");
	fileBboxLabel->setText("  File B:");
	fileAboxLabel->setFont(QFont("Arial", 10));
	fileBboxLabel->setFont(QFont("Arial", 10));
	fileAboxLabel->setBackgroundRole(QPalette::Window);
	fileBboxLabel->setBackgroundRole(QPalette::Window);
	fileAboxLabel->setAutoFillBackground(true);
	fileBboxLabel->setAutoFillBackground(true);
	fileApath = new compareLineEdit(fileAbox);
	fileApath->setGeometry(QRect(0, 10, 350, 25));
	fileApath->setAcceptDrops(true);
	fileBpath = new compareLineEdit(fileBbox);
	fileBpath->setGeometry(QRect(0, 10, 350, 25));
	fileBpath->setAcceptDrops(true);
	fileApathBrowse = new QPushButton(fileAbox);
	fileApathBrowse->setText("Browse...");
	fileApathBrowse->setGeometry(QRect(360, 5, 105, 38));
	fileBpathBrowse = new QPushButton(fileBbox);
	fileBpathBrowse->setText("Browse...");
	fileBpathBrowse->setGeometry(QRect(360, 5, 105, 38));
	createEmptyState(emptyState);
	createGreenState(greenState);
	createRedState(redState);
	createYellowState(yellowState);
	redDot = new QPixmap(QPixmap::fromImage(*redState));
	yellowDot = new QPixmap(QPixmap::fromImage(*yellowState));
	greenDot = new QPixmap(QPixmap::fromImage(*greenState));
	emptyDot = new QPixmap(QPixmap::fromImage(*emptyState));
	copyright = new QLabel(this);
	copyright->setGeometry(QRect(10, 250, 80, 55));
	copyright->setText("\x0A9 2013 Tobias Vogel\nLicensed under the\nGNU GPL v 2");
	copyright->setFont(QFont("Arial", 8));

	aFileSizeLabel = new QLabel(fileAbox);
	aFileSizeLabel->setGeometry(QRect(20, 40, 80, 20));
	aFileSizeLabel->setText("File size:");
	aFileSizeLabel->setFont(QFont("Arial", 12));
	aFileSize = new QLabel(fileAbox);
	aFileSize->setGeometry(QRect(120, 44, 120, 20));
	aFileSize->setText("");
	aFileSize->setFont(QFont("Arial", 12));
	aFileSize->setAlignment(Qt::AlignRight);
	aFileCreateLabel = new QLabel(fileAbox);
	aFileCreateLabel->setGeometry(QRect(20, 60, 80, 20));
	aFileCreateLabel->setText("Date Created:");
	aFileCreateLabel->setFont(QFont("Arial", 12));
	aFileCreate = new QLabel(fileAbox);
	aFileCreate->setGeometry(QRect(120, 64, 120, 20));
	aFileCreate->setText("");
	aFileCreate->setFont(QFont("Arial", 12));
	aFileCreate->setAlignment(Qt::AlignRight);
	aFileChangeLabel = new QLabel(fileAbox);
	aFileChangeLabel->setGeometry(QRect(270, 40, 80, 20));
	aFileChangeLabel->setText("Last Changed:");
	aFileChangeLabel->setFont(QFont("Arial", 12));
	aFileChange = new QLabel(fileAbox);
	aFileChange->setGeometry(QRect(370, 44, 120, 20));
	aFileChange->setText("");
	aFileChange->setFont(QFont("Arial", 12));
	aFileChange->setAlignment(Qt::AlignRight);
	aFileMD5Label = new QLabel(fileAbox);
	aFileMD5Label->setGeometry(QRect(20, 80, 80, 20));
	aFileMD5Label->setText("MD5 sum:");
	aFileMD5Label->setFont(QFont("Arial", 12));
	aFileMD5 = new QLabel(fileAbox);
	aFileMD5->setGeometry(QRect(175, 84, 280, 20));
	aFileMD5->setText("");
	aFileMD5->setFont(QFont("Arial", 12));
	aFileMD5->setAlignment(Qt::AlignRight);
	bFileSizeLabel = new QLabel(fileBbox);
	bFileSizeLabel->setGeometry(QRect(20, 40, 80, 20));
	bFileSizeLabel->setText("File size:");
	bFileSizeLabel->setFont(QFont("Arial", 12));
	bFileSize = new QLabel(fileBbox);
	bFileSize->setGeometry(QRect(120, 44, 120, 20));
	bFileSize->setText("");
	bFileSize->setFont(QFont("Arial", 12));
	bFileSize->setAlignment(Qt::AlignRight);
	bFileCreateLabel = new QLabel(fileBbox);
	bFileCreateLabel->setGeometry(QRect(20, 60, 80, 20));
	bFileCreateLabel->setText("Date Created:");
	bFileCreateLabel->setFont(QFont("Arial", 12));
	bFileCreate = new QLabel(fileBbox);
	bFileCreate->setGeometry(QRect(120, 64, 120, 20));
	bFileCreate->setText("");
	bFileCreate->setFont(QFont("Arial", 12));
	bFileCreate->setAlignment(Qt::AlignRight);
	bFileChangeLabel = new QLabel(fileBbox);
	bFileChangeLabel->setGeometry(QRect(270, 40, 80, 20));
	bFileChangeLabel->setText("Last Changed:");
	bFileChangeLabel->setFont(QFont("Arial", 12));
	bFileChange = new QLabel(fileBbox);
	bFileChange->setGeometry(QRect(370, 44, 120, 20));
	bFileChange->setText("");
	bFileChange->setFont(QFont("Arial", 12));
	bFileChange->setAlignment(Qt::AlignRight);
	bFileMD5Label = new QLabel(fileBbox);
	bFileMD5Label->setGeometry(QRect(20, 80, 80, 20));
	bFileMD5Label->setText("MD5 Sum:");
	bFileMD5Label->setFont(QFont("Arial", 12));
	bFileMD5 = new QLabel(fileBbox);
	bFileMD5->setGeometry(QRect(175, 84, 280, 20));
	bFileMD5->setText("");
	bFileMD5->setFont(QFont("Arial", 12));
	bFileMD5->setAlignment(Qt::AlignRight);
	aFileReadLabel = new QLabel(fileAbox);
	aFileReadLabel->setGeometry(QRect(270, 60, 80, 20));
	aFileReadLabel->setText("Last Read:");
	aFileReadLabel->setFont(QFont("Arial", 12));
	aFileRead = new QLabel(fileAbox);
	aFileRead->setGeometry(QRect(370, 64, 120, 20));
	aFileRead->setText("");
	aFileRead->setFont(QFont("Arial", 12));
	aFileRead->setAlignment(Qt::AlignRight);
	bFileReadLabel = new QLabel(fileBbox);
	bFileReadLabel->setGeometry(QRect(270, 60, 80, 20));
	bFileReadLabel->setText("Last Read:");
	bFileReadLabel->setFont(QFont("Arial", 12));
	bFileRead = new QLabel(fileBbox);
	bFileRead->setGeometry(QRect(370, 64, 120, 20));
	bFileRead->setText("");
	bFileRead->setFont(QFont("Arial", 12));
	bFileRead->setAlignment(Qt::AlignRight);



	aStatus1 = new QLabel(fileAbox);
	aStatus1->setGeometry(QRect(0, 44, 12, 11));
	aStatus1->setPixmap(*emptyDot);
	aStatus2 = new QLabel(fileAbox);
	aStatus2->setGeometry(QRect(0, 64, 12, 11));
	aStatus2->setPixmap(*emptyDot);
	aStatus3 = new QLabel(fileAbox);
	aStatus3->setGeometry(QRect(250, 44, 12, 11));
	aStatus3->setPixmap(*emptyDot);
	aStatus4 = new QLabel(fileAbox);
	aStatus4->setGeometry(QRect(250, 64, 12, 11));
	aStatus4->setPixmap(*emptyDot);
	bStatus1 = new QLabel(fileBbox);
	bStatus1->setGeometry(QRect(0, 44, 12, 11));
	bStatus1->setPixmap(*emptyDot);
	bStatus2 = new QLabel(fileBbox);
	bStatus2->setGeometry(QRect(0, 64, 12, 11));
	bStatus2->setPixmap(*emptyDot);
	bStatus3 = new QLabel(fileBbox);
	bStatus3->setGeometry(QRect(250, 44, 12, 11));
	bStatus3->setPixmap(*emptyDot);
	bStatus4 = new QLabel(fileBbox);
	bStatus4->setGeometry(QRect(250, 64, 12, 11));
	bStatus4->setPixmap(*emptyDot);
	aStatus5 = new QLabel(fileAbox);
	aStatus5->setGeometry(QRect(0, 84, 12, 11));
	aStatus5->setPixmap(*emptyDot);
	bStatus5 = new QLabel(fileBbox);
	bStatus5->setGeometry(QRect(0, 84, 12, 11));
	bStatus5->setPixmap(*emptyDot);



	QObject::connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
	QObject::connect(fileApathBrowse, SIGNAL(clicked()), this, SLOT(fileABrowse()));
	QObject::connect(fileBpathBrowse, SIGNAL(clicked()), this, SLOT(fileBBrowse()));
	QObject::connect(fileApath, SIGNAL(textChanged(QString)), this, SLOT(fileApathChanged(QString)));
	QObject::connect(fileBpath, SIGNAL(textChanged(QString)), this, SLOT(fileBpathChanged(QString)));
	QObject::connect(compareButton, SIGNAL(clicked()), this, SLOT(filesCompare()));
	QObject::connect(resetButton, SIGNAL(clicked()), this, SLOT(clearAll()));
}

void compareWindow::fileABrowse() {
	fileApath->setStyleSheet("");
	fileBpath->setStyleSheet("");
	QFileDialog fDialog;
	QString fName;
	QFileInfo info;
	fName = fDialog.getOpenFileName(this, "Select File", QDir::homePath());
	if (!(fName.isEmpty())) {
		info.setFile(fName);
		if (info.isFile()) {
			this->fileApath->setText(fName);
			this->fileApathChanged("");
		}
	}
	
}

void compareWindow::fileBBrowse() {
	fileApath->setStyleSheet("");
	fileBpath->setStyleSheet("");
	QFileDialog fDialog;
	QString fName;
	QFileInfo info;
	fName = fDialog.getOpenFileName(this, "Select File", QDir::homePath());
	if (!(fName.isEmpty())) {
		info.setFile(fName);
		if (info.isFile()) {
			this->fileBpath->setText(fName);
			this->fileBpathChanged("");
		}
	}
}

void compareWindow::fileApathChanged(QString text) {
	fileApath->setStyleSheet("");
	fileBpath->setStyleSheet("");
	QFileInfo info;
	long fSize;
	QDateTime fCreated;
	QDateTime fLastmod;
	QDateTime fLastread;
	QString fSizeString;
	info.setFile(fileApath->text());
		if (info.isFile()) {
			fSize = info.size();	
			fCreated = info.created();
			fLastmod = info.lastModified();
			fLastread = info.lastRead();
		}
	fSizeString.setNum(fSize);
	fSizeString += " Bytes";
	aFileSize->setText(fSizeString);
	aFileCreate->setText(fCreated.toString("dd.MM.yyyy hh:mm"));
	aFileChange->setText(fLastmod.toString("dd.MM.yyyy hh:mm"));
	aFileRead->setText(fLastread.toString("dd.MM.yyyy hh:mm"));
	if (bFileSize->text().isEmpty()) {
		aStatus1->setPixmap(*yellowDot);
	} else if (bFileSize->text() == aFileSize->text()) {
		aStatus1->setPixmap(*greenDot);
		bStatus1->setPixmap(*greenDot);
	} else if (bFileSize->text() != aFileSize->text()) {
		aStatus1->setPixmap(*redDot);
		bStatus1->setPixmap(*redDot);
	} else {
		aStatus1->setPixmap(*emptyDot);
		bStatus1->setPixmap(*emptyDot);
	}
	if (bFileChange->text().isEmpty()) {
		aStatus2->setPixmap(*yellowDot);
	} else if (bFileChange->text() == aFileChange->text()) {
		aStatus2->setPixmap(*greenDot);
		bStatus2->setPixmap(*greenDot);
	} else if (bFileChange->text() != aFileChange->text()) {
		aStatus2->setPixmap(*redDot);
		bStatus2->setPixmap(*redDot);
	} else {
		aStatus2->setPixmap(*emptyDot);
		bStatus2->setPixmap(*emptyDot);
	}
	if (bFileCreate->text().isEmpty()) {
		aStatus3->setPixmap(*yellowDot);
	} else if (bFileCreate->text() == aFileCreate->text()) {
		aStatus3->setPixmap(*greenDot);
		bStatus3->setPixmap(*greenDot);
	} else if (bFileCreate->text() != aFileCreate->text()) {
		aStatus3->setPixmap(*redDot);
		bStatus3->setPixmap(*redDot);
	} else {
		aStatus3->setPixmap(*emptyDot);
		bStatus3->setPixmap(*emptyDot);
	}
	if (bFileRead->text().isEmpty()) {
		aStatus4->setPixmap(*yellowDot);
	} else if (bFileRead->text() == aFileRead->text()) {
		aStatus4->setPixmap(*greenDot);
		bStatus4->setPixmap(*greenDot);
	} else if (bFileRead->text() != aFileRead->text()) {
		aStatus4->setPixmap(*redDot);
		bStatus4->setPixmap(*redDot);
	} else {
		aStatus4->setPixmap(*emptyDot);
		bStatus4->setPixmap(*emptyDot);
	}
}

void compareWindow::fileBpathChanged(QString text) {
	fileApath->setStyleSheet("");
	fileBpath->setStyleSheet("");
	QFileInfo info;
	long fSize;
	QDateTime fCreated;
	QDateTime fLastmod;
	QDateTime fLastread;
	QString fSizeString;
	info.setFile(fileBpath->text());
		if (info.isFile()) {
			fSize = info.size();	
			fCreated = info.created();
			fLastmod = info.lastModified();
			fLastread = info.lastRead();
		}
	fSizeString.setNum(fSize);
	fSizeString += " Bytes";
	bFileSize->setText(fSizeString);
	bFileCreate->setText(fCreated.toString("dd.MM.yyyy hh:mm"));
	bFileChange->setText(fLastmod.toString("dd.MM.yyyy hh:mm"));
	bFileRead->setText(fLastread.toString("dd.MM.yyyy hh:mm"));
	if (aFileSize->text().isEmpty()) {
		bStatus1->setPixmap(*yellowDot);
	} else if (aFileSize->text() == bFileSize->text()) {
		aStatus1->setPixmap(*greenDot);
		bStatus1->setPixmap(*greenDot);
	} else if (bFileSize->text() != aFileSize->text()) {
		aStatus1->setPixmap(*redDot);
		bStatus1->setPixmap(*redDot);
	} else {
		aStatus1->setPixmap(*emptyDot);
		bStatus1->setPixmap(*emptyDot);
	}
	if (aFileChange->text().isEmpty()) {
		bStatus2->setPixmap(*yellowDot);
	} else if (aFileChange->text() == bFileChange->text()) {
		aStatus2->setPixmap(*greenDot);
		bStatus2->setPixmap(*greenDot);
	} else if (bFileChange->text() != aFileChange->text()) {
		aStatus2->setPixmap(*redDot);
		bStatus2->setPixmap(*redDot);
	} else {
		aStatus2->setPixmap(*emptyDot);
		bStatus2->setPixmap(*emptyDot);
	}
	if (aFileCreate->text().isEmpty()) {
		bStatus3->setPixmap(*yellowDot);
	} else if (aFileCreate->text() == bFileCreate->text()) {
		aStatus3->setPixmap(*greenDot);
		bStatus3->setPixmap(*greenDot);
	} else if (bFileCreate->text() != aFileCreate->text()) {
		aStatus3->setPixmap(*redDot);
		bStatus3->setPixmap(*redDot);
	} else {
		aStatus3->setPixmap(*emptyDot);
		bStatus3->setPixmap(*emptyDot);
	}
	if (aFileRead->text().isEmpty()) {
		bStatus4->setPixmap(*yellowDot);
	} else if (aFileRead->text() == bFileRead->text()) {
		aStatus4->setPixmap(*greenDot);
		bStatus4->setPixmap(*greenDot);
	} else if (bFileRead->text() != aFileRead->text()) {
		aStatus4->setPixmap(*redDot);
		bStatus4->setPixmap(*redDot);
	} else {
		aStatus4->setPixmap(*emptyDot);
		bStatus4->setPixmap(*emptyDot);
	}
}


void compareWindow::filesCompare() {

	if (!((fileApath->text()).isEmpty()) && !((fileBpath->text()).isEmpty())) {
		QFileInfo test;
		test.setFile(fileApath->text());
		if (!(test.isFile())) {
			return;
		}
		test.setFile(fileBpath->text());
		if (!(test.isFile())) {
			return;
		}
	} else {
			return;
	}
{
	QCryptographicHash hash(QCryptographicHash::Md5);
	QFile in(fileApath->text());

	if (in.open(QIODevice::ReadOnly)) {
	char buf[2048];
	int bytesRead;
	qint64 overallBytesRead = 0;

	while ((bytesRead = in.read(buf, 2048)) > 0) {
		overallBytesRead += bytesRead;
		hash.addData(buf, bytesRead);
	}
	in.close();
	aFileMD5->setText(QString(hash.result().toHex()));
	} else {
	aFileMD5->setText("Error!");
	}
}
{
	QCryptographicHash hash(QCryptographicHash::Md5);
	QFile in(fileBpath->text());

	if (in.open(QIODevice::ReadOnly)) {
	char buf[2048];
	int bytesRead;
	qint64 overallBytesRead = 0;

	while ((bytesRead = in.read(buf, 2048)) > 0) {
		overallBytesRead += bytesRead;
		hash.addData(buf, bytesRead);
	}
	in.close();
	bFileMD5->setText(QString(hash.result().toHex()));
	} else {
	bFileMD5->setText("Error!");
	}

}
	if (aFileMD5->text() == bFileMD5->text()) {
		aStatus5->setPixmap(*greenDot);
		bStatus5->setPixmap(*greenDot);
	} else {
		aStatus5->setPixmap(*redDot);
		bStatus5->setPixmap(*redDot);
	}
	if ((aFileSize->text() == bFileSize->text()) &&
	    (aFileCreate->text() == bFileCreate->text()) &&
	    (aFileChange->text() == bFileChange->text()) &&
	    (aFileRead->text() == bFileRead->text()) &&
	    (aFileMD5->text() == bFileMD5->text())) {	
		fileApath->setStyleSheet("background-color: #99FF99;");
		fileBpath->setStyleSheet("background-color: #99FF99;");
	}else{
		fileApath->setStyleSheet("background-color: #FF9999;");
		fileBpath->setStyleSheet("background-color: #FF9999;");
	}




}

void compareWindow::clearAll() {
	fileApath->setText("");
	fileBpath->setText("");
	aFileSize->setText("");
	bFileSize->setText("");
	aFileCreate->setText("");
	bFileCreate->setText("");
	aFileChange->setText("");
	bFileChange->setText("");
	aFileMD5->setText("");
	aFileRead->setText("");
	bFileMD5->setText("");
	bFileRead->setText("");
	aStatus1->setPixmap(*emptyDot);
	aStatus2->setPixmap(*emptyDot);
	aStatus3->setPixmap(*emptyDot);
	aStatus4->setPixmap(*emptyDot);
	bStatus1->setPixmap(*emptyDot);
	bStatus2->setPixmap(*emptyDot);
	bStatus3->setPixmap(*emptyDot);
	bStatus4->setPixmap(*emptyDot);
	aStatus5->setPixmap(*emptyDot);
	bStatus5->setPixmap(*emptyDot);
	fileApath->setStyleSheet("");
	fileBpath->setStyleSheet("");
}

#include "moc_mainwindow.cpp"
#endif // MAINWINDOW_H
