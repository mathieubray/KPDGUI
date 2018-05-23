#include "KPDGUI.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);	
	KPDGUI *kpdgui = new KPDGUI;	
	kpdgui->show();	
	return app.exec();
}
