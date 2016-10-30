#include "DunoError.h"
#include <tchar.h>
using namespace DunoGUI;

void DunoError::out(LPCWSTR message)
{
	/* If window does not accept this, then say so */
	MessageBox(NULL,
		message,
		_T("DunoGUIError Out"),
		NULL);
	/* and quit with and error */
	exit(1);
}