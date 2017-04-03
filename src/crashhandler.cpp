#include "crashhandler.h"
#include <QtCore/QDir>
#include <QtCore/QProcess>
#include <QtCore/QCoreApplication>
#include <QString>

#if define(Q_OS_LINUX)
#include "../libs/breakpad/src/client/linux/handler/exception_handler.h"
#elif defined(Q_OS_WIN32)
#include "../libs/breakpad/src/client/windows/handler/exception_handler.h"
#endif

class CrashHandlerPrivate
{
public:
    CrashHandlerPrivate()
    {
        pHandler = NULL;
    }

    ~CrashHandlerPrivate()
    {
        delete pHandler;
    }

    void InitCrashHandler(const QString& dumpPath);
    static google_breakpad::ExceptionHandler* pHandler;
    static bool bReportCrashesToSystem;
};

google_breakpad::ExceptionHandler* CrashHandlerPrivate::pHandler = NULL;
bool CrashHandlerPrivate::bReportCrashesToSystem = false;

#if defined(Q_OS_WIN32)
bool DumpCallback(const wchar_t* _dump_dir, const wchar_t* _minidump_id, void* context, EXCEPTION_POINTERS* exinfo, MDRawAssertionInfo* assertion, bool success)
#elif defined(Q_OS_LINUX)
bool DumpCallback(const google_breakpad::MinidumpDescriptor &md, void *context, bool success)
#endif
{
    Q_UNUSED(context);
#if defined(Q_OS_WIN32)
    Q_UNUSED(_dump_dir);
    Q_UNUSED(_minidump_id);
    Q_UNUSED(assertion);
    Q_UNUSED(exinfo);
#endif
    qDebug("BreakpadQt crash");

    return CrashHandlerPrivate::bReportCrashesToSystem ? success : true;
}

void CrashHandlerPrivate::InitCrashHandler(const QString& dumpPath)
{
    if ( pHandler != NULL )
        return;

#if defined(Q_OS_WIN32)
    std::wstring pathAsStr = (const wchar_t*)dumpPath.utf16();
    pHandler = new google_breakpad::ExceptionHandler(
                pathAsStr,
                0,
                DumpCallback,
                0,
                true
                );
#elif defined(Q_OS_LINUX)
    std::string pathAsStr = dumpPath.toStdString();
    google_breakpad::MinidumpDescriptor md(mathAsStr);
    pHandler = new google_breakpad::ExceptionHandler(
                md,
                0,
                DumpCallback,
                true,
                -1
                );
#endif
}

CrashHandler* CrashHandler::instance()
{
    static CrashHandler globalHandler;
    return &globalHandler;
}

CrashHandler::CrashHandler()
{
    d = new CrashHandlerPrivate();
}

CrashHandler::~CrashHandler()
{
    delete d;
}

void CrashHandler::setReportCrashesToSystem(bool report)
{
    d->bReportCrashesToSystem = report;
}

bool CrashHandler::writeMinidump()
{
    bool res = d->pHandler->WriteMinidump();
    if (res) {
        qDebug("BreakpadQt: writeMinidump() success.");
    } else {
        qWarning("BreakpadQt: writeMinidump() failed.");
    }
    return res;
}

void CrashHandler::Init(const QString& reportPath)
{
    d->InitCrashHandler(reportPath);
}
