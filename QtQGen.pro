TARGET = QGen

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
}

CONFIG += precompile_header
PRECOMPILED_HEADER = src/stdafx.h

unix:LIBS += -lqscintilla2

windows {
    *-g++* {
        win32:LIBS += -lqscintilla2
    }
    *-msvc* {
        win32:LIBS += qscintilla2.lib
    }
}

QT += network xml

win32 {
	RC_FILE  = misc/win32/resource.rc
}

RESOURCES = misc/main_window.qrc

DEFINES += _UNICODE

HEADERS = \
	src/actioncode.h \
	src/actionslist.h \
	src/ActionsPanel.h \
	src/controls.h \
	src/datacontainer.h \
	src/game.h \
	src/IControls.h \
	src/ilocationpage.h \
	src/LocationActions.h \
	src/locationcode.h \
	src/locationdesc.h \
	src/locationpage.h \
	src/locationslistbox.h \
	src/MainToolBar.h \
	src/mainwindow.h \
	src/mergedialog.h \
	src/Settings.h \
	src/stdafx.h \
	src/SyntaxTextBox.h \
	src/tabswidget.h \
	src/toolbutton.h \
    src/updater.h \
    src/updaterdescriptiondlg.h \
    src/updateshow.h \
    src/IObserver.h \
    src/keywordsstore.h \
    src/qsphighlighter.h

SOURCES = \
	src/actioncode.cpp \
	src/actionslist.cpp \
	src/ActionsPanel.cpp \
	src/controls.cpp \
	src/datacontainer.cpp \
	src/game.cpp \
	src/LocationActions.cpp \
	src/locationcode.cpp \
	src/locationdesc.cpp \
	src/locationpage.cpp \
	src/locationslistbox.cpp \
	src/main.cpp \
	src/MainToolBar.cpp \
	src/mainwindow.cpp \
	src/mergedialog.cpp \
	src/Settings.cpp \
	src/SyntaxTextBox.cpp \
	src/tabswidget.cpp \
	src/toolbutton.cpp \
    src/updater.cpp \
    src/updaterdescriptiondlg.cpp \
    src/updateshow.cpp \
    src/keywordsstore.cpp \
    src/qsphighlighter.cpp

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
