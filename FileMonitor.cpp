// Qt File monitoring class implementation file

// System includes
#include <memory>

// Qt includes
#include <QtCore/QFileInfo>
#include <QtCore/QString>
#include <QtCore/QTimer>

// local includes
#include "FileMonitor.h"

using namespace Utility;

// ctor
CFileMonitor::CFileMonitor()
{
    m_pFileMonitor = new QTimer(this);
    QObject::connect(m_pFileMonitor, &QTimer::timeout, this, &CFileMonitor::onMonitorFiles);
    m_pFileMonitor->start(1000 * 10); // 10 second interval by default
}

// dtor
CFileMonitor::~CFileMonitor()
{
    if (m_pFileMonitor)
    {
        m_pFileMonitor->stop();
        delete m_pFileMonitor;
        m_pFileMonitor = nullptr;
    }
}

// Add a file to monitor. If it's not currently being monitored,
// add it to our file list, and add its 'last modified' time
// to the file/time_info map
void CFileMonitor::addFileToMonitor(QFile* pFile)
{
    if (!isFileMonitored(pFile))
    {
        QFileInfo fi(pFile->fileName());

        if (fi.exists())
        {
            m_FilesToMonitor.push_back(pFile);
            m_FileModMap[pFile] = fi.lastModified();
        }
        else
        {
            std::cerr << "File: " << pFile->fileName().toLatin1().constData()
                      << " doesn't exist!" << std::endl;
        }
    }
}

// If found, remove a given file from file monitoring
void CFileMonitor::removeFileFromMonitor(QFile* pFile)
{
    std::vector<QFile*>::const_iterator it = std::find(m_FilesToMonitor.begin(), m_FilesToMonitor.end(), pFile);
    
    if (it != m_FilesToMonitor.end())
    {
        m_FilesToMonitor.erase(it);
        m_FileModMap.erase(pFile);
    }
}

// Test if a file is currently being monitored
bool CFileMonitor::isFileMonitored(QFile* pFile)
{
    return std::find(m_FilesToMonitor.begin(), m_FilesToMonitor.end(), pFile) != m_FilesToMonitor.end();
}

// Change how often files are scanned for changes
void CFileMonitor::changeMonitorTime(int nSecs)
{
    if (m_pFileMonitor)
        m_pFileMonitor->setInterval(1000 * nSecs);
}

// File monitoring callback. Use this function to notify the appropriate
// code that a file has changed.
void CFileMonitor::onMonitorFiles()
{
    for (QFile* file_id : m_FilesToMonitor)
    {
        QFileInfo fi(file_id->fileName());
        QDateTime dt(fi.lastModified());

        if (dt != m_FileModMap[file_id])
        {
            // Do something useful here, if the file has changed
        }
    }
}
