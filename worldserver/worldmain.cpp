#include "WorldMain.h"

void WorldMain::run()
{
    //=================
    //Command line init
    //=================

    m_threadCommandLine = new QThread();
    m_commandLine = new CommandLine();
    m_commandLine->moveToThread(m_threadCommandLine);

    connect(m_threadCommandLine, SIGNAL(started()), m_commandLine, SLOT(run()));
    connect(m_commandLine, SIGNAL(finished()), m_threadCommandLine, SLOT(quit()));
    connect(m_commandLine, SIGNAL(finished()), m_threadCommandLine, SLOT(deleteLater()));

    //===============
    //World loop init
    //===============

    m_threadWorldLoop = new QThread();
    m_worldLoop = new WorldLoop();
    m_worldLoop->moveToThread(m_threadWorldLoop);

    connect(m_threadWorldLoop, SIGNAL(started()), m_worldLoop, SLOT(run()));
    connect(m_worldLoop, SIGNAL(finished()), m_threadWorldLoop, SLOT(quit()));
    connect(m_worldLoop, SIGNAL(finished()), m_threadWorldLoop, SLOT(deleteLater()));

    //===========
    //World start
    //===========

    QTime t;
    t.start();

    Log::Write(LOG_TYPE_NORMAL, "WW      WW         kk     BBBBB                 ");
    Log::Write(LOG_TYPE_NORMAL, "WW      WW   aa aa kk  kk BB   B   oooo  xx  xx ");
    Log::Write(LOG_TYPE_NORMAL, "WW   W  WW  aa aaa kkkkk  BBBBBB  oo  oo   xx   ");
    Log::Write(LOG_TYPE_NORMAL, " WW WWW WW aa  aaa kk kk  BB   BB oo  oo   xx   ");
    Log::Write(LOG_TYPE_NORMAL, "  WW   WW   aaa aa kk  kk BBBBBB   oooo  xx  xx ");
    Log::Write(LOG_TYPE_NORMAL, "");
    Log::Write(LOG_TYPE_NORMAL, "Wakfu sandbox developped by Sgt Fatality & Totomakers.");
    Log::Write(LOG_TYPE_NORMAL, "");
    Log::Write(LOG_TYPE_NORMAL, "Press ctrl + c to quit.");

    if (!sWorldServer->Initialize())
        QCoreApplication::exit();


    Log::Write(LOG_TYPE_NORMAL, "Worldserver started in %s sec.", QString::number(t.elapsed() / IN_MILLISECONDS).toLatin1().data());

    m_threadCommandLine->start();
    m_threadWorldLoop->start();
}

void WorldMain::stop()
{
    m_commandLine->stop();
    m_worldLoop->stop();

    delete m_commandLine;
    delete m_worldLoop;

    sWorldServer->Delete();
}