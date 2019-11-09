// Qt file monitoring class. Usage is as follows:
// Make the CFileMonitor class a member in your file loading class.
// When loading files, call the various file monitor methods to add
// or remove files from monitoring. The onMonitorFiles() callback
// can be used to notify the appropriate code when a file has changed.

#pragma once

// system includes
#include <vector>
#include <map>

// Qt includes
#include <QtCore/QDateTime>
#include <QtCore/QObject>

// forward declarations
class QTimer;
class QFile;

namespace Utility
{
    // CFileMonitor derives from QObject to pick up QTimer support.
	class CFileMonitor : public QObject
	{
	public:
		CFileMonitor();
		virtual ~CFileMonitor();

        void addFileToMonitor(QFile* pFile);
        void removeFileFromMonitor(QFile* pFile);
        bool isFileMonitored(QFile* pFile);
        void changeMonitorTime(int nSecs);
    private:
        void onMonitorFiles();

        // We don't want copy or move constructors/assignment operators
        CFileMonitor(const CFileMonitor& rhs) = delete;
        CFileMonitor& operator=(const CFileMonitor& rhs) = delete;
        CFileMonitor(CFileMonitor&& rhs) = delete;
        CFileMonitor& operator=(CFileMonitor&& rhs) = delete;
    private:
    	QTimer*                       m_pFileMonitor;
        std::map<QFile*, QDateTime> m_FileModMap;
        std::vector<QFile*>         m_FilesToMonitor;
	};
}
