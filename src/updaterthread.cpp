// Copyright (C) 2013
// Shchannikov Dmitry (rrock DOT ru AT gmail DOT com)
// Nex (nex AT otaku DOT ru)
/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include "updaterthread.h"

UpdaterThread::UpdaterThread(IControls *controls, QObject *parent) :
    QObject(parent)
{
    _controls = controls;
    _updater = new Updater(_controls);
}

void UpdaterThread::process()
{
    QThread* thread = new QThread;
    moveToThread(thread);
    connect(thread, SIGNAL(started()), _updater, SLOT(CheckForUpdate()));
    connect(_updater, SIGNAL(finished()), this, SLOT(finished()));
    connect(_updater, SIGNAL(finished()), thread, SLOT(quit()));
    //connect(updater, SIGNAL(finished()), updater, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void UpdaterThread::finished()
{
    if (_updater->IsUpdateAvailable())
    {
        _controls->GetParent()->close();
        int res = _updater->LaunchUpdater();
        if (res != QGEN_UPDMSG_TRUE)
        {
            _controls->ShowMessage(res);
            return;
        }
    }
}
