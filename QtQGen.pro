TARGET = QGen

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
}

CONFIG += precompile_header
PRECOMPILED_HEADER = src/stdafx.h

QT += network xml

win32 {
    RC_ICONS  = misc/icons/qgen.ico
}

RESOURCES = misc/main_window.qrc

DEFINES += _UNICODE

HEADERS = \
    src/actioncode.h \
    src/actionslist.h \
    src/controls.h \
    src/datacontainer.h \
    src/game.h \
    src/ilocationpage.h \
    src/locationcode.h \
    src/locationdesc.h \
    src/locationpage.h \
    src/locationslistbox.h \
    src/mainwindow.h \
    src/mergedialog.h \
    src/stdafx.h \
    src/tabswidget.h \
    src/toolbutton.h \
    src/updater.h \
    src/updaterdescriptiondlg.h \
    src/updateshow.h \
    src/keywordsstore.h \
    src/qsphighlighter.h \
    src/searchdialog.h \
    src/searchdatastore.h \
    src/actionspanel.h \
    src/icontrols.h \
    src/iobserver.h \
    src/maintoolbar.h \
    src/settings.h \
    src/syntaxtextbox.h \
    src/locationactions.h \
    src/updaterthread.h \
    src/optionsdialog.h \
    src/colorwidget.h \
    src/fontwidget.h \
    src/crashhandler.h

SOURCES = \
    src/actioncode.cpp \
    src/actionslist.cpp \
    src/controls.cpp \
    src/datacontainer.cpp \
    src/game.cpp \
    src/locationcode.cpp \
    src/locationdesc.cpp \
    src/locationpage.cpp \
    src/locationslistbox.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/mergedialog.cpp \
    src/tabswidget.cpp \
    src/toolbutton.cpp \
    src/updater.cpp \
    src/updaterdescriptiondlg.cpp \
    src/updateshow.cpp \
    src/keywordsstore.cpp \
    src/qsphighlighter.cpp \
    src/searchdialog.cpp \
    src/searchdatastore.cpp \
    src/actionspanel.cpp \
    src/locationactions.cpp \
    src/maintoolbar.cpp \
    src/settings.cpp \
    src/syntaxtextbox.cpp \
    src/updaterthread.cpp \
    src/optionsdialog.cpp \
    src/colorwidget.cpp \
    src/fontwidget.cpp \
    src/crashhandler.cpp

TRANSLATIONS = \
    misc/langs/qgen_ru.ts \
    misc/langs/qgen_en.ts

OTHER_FILES += \
    misc/win32/resource.rc \
    misc/langs/qgen_ru.ts \
    misc/langs/qgen_ru.qm \
    misc/langs/qgen_en.ts \
    misc/icons/toolbar_undo.xpm \
    misc/icons/toolbar_text_search.xpm \
    misc/icons/toolbar_redo.xpm \
    misc/icons/toolbar_options.xpm \
    misc/icons/toolbar_location_rename.xpm \
    misc/icons/toolbar_location_paste.xpm \
    misc/icons/toolbar_location_new.xpm \
    misc/icons/toolbar_location_delete.xpm \
    misc/icons/toolbar_location_copy.xpm \
    misc/icons/toolbar_location_clear.xpm \
    misc/icons/toolbar_game_play.xpm \
    misc/icons/toolbar_game_info.xpm \
    misc/icons/toolbar_file_saveas.xpm \
    misc/icons/toolbar_file_save.xpm \
    misc/icons/toolbar_file_open.xpm \
    misc/icons/toolbar_action_rename.xpm \
    misc/icons/toolbar_action_new.xpm \
    misc/icons/toolbar_action_delete.xpm \
    misc/icons/qgen.xpm \
    misc/icons/qgen.ico \
    misc/icons/menu_undo.xpm \
    misc/icons/menu_text_search.xpm \
    misc/icons/menu_text_paste.xpm \
    misc/icons/menu_text_delete.xpm \
    misc/icons/menu_text_cut.xpm \
    misc/icons/menu_text_copy.xpm \
    misc/icons/menu_redo.xpm \
    misc/icons/menu_help_search.xpm \
    misc/icons/menu_help.xpm \
    misc/icons/menu_game_play.xpm \
    misc/icons/menu_game_new.xpm \
    misc/icons/menu_game_info.xpm \
    misc/icons/menu_file_save.xpm \
    misc/icons/menu_file_open.xpm \
    misc/icons/menu_exit.xpm \
    misc/icons/locstabs_page_fixed.xpm \
    misc/icons/locslist_location_ball_opened.xpm \
    misc/icons/locslist_location_ball_closed.xpm \
    misc/icons/locslist_folder_opened.xpm \
    misc/icons/locslist_folder_closed.xpm \
    misc/icons/locslist_action_ball.xpm \
    misc/icons/cross.xpm \
    misc/icons/about_logo.xpm \
    TODO.txt \
    History.txt

FORMS += \
    src/optionsdialog.ui \
    src/mainwindow.ui

win32:release {
    SRCDIR = $${_PRO_FILE_PWD_}
    SRCDIR ~= s,/,\\,g
    QMAKE_POST_LINK += $$quote($${PWD}\\build\\win32\\make.package.cmd $${SRCDIR}$$escape_expand(\n\t))
}

win32-msvc* {
    QMAKE_LFLAGS_RELEASE += /INCREMENTAL:NO
    QMAKE_CFLAGS_RELEASE += /Zi
    QMAKE_LFLAGS_RELEASE += /debug /opt:ref /opt:icf
}

include($$PWD/breakpad.pri)
