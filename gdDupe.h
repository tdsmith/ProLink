#pragma once

#include "gdDupeMessagesDialog.h"

class gdDupe
{
	public:
		gdDupe (void);
		~gdDupe (void);

		void Clear ();
		void Message (LPCTSTR, ...);		
		void ShowDupeMessagesDialog (CWnd *);

	protected:

		gdDupeMessagesDialog *m_pMessagesDialog;
};

gdDupe *gdGetDupe (void);