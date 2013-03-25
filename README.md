QtQGen
======
Порт редактора игр для платформы QSP на Qt.

Для сборки проекта необходима Visual Studio 2010, библиотека Qt5, а так же необходима переменная окружения QTDIR,
в которой указан путь до корня библиотеки.

Qt лучше собирать из исходников, чтобы он не тащил с собой лишний хлам.  

*Для сборки Qt требуются*  
*ActivePerl(http://www.activestate.com/activeperl/downloads)*  
*Python2.7,(http://python.org/download/)*  
*Пути до Perl и Python должны быть прописаны в переменной PATH*

Сборка Qt
-------------------
1. Скачиваем последнюю версию с http://qt-project.org
2. Распаковываем, например в C:\Qt (если инсталлятор, то не забываем установить галочки для Source Components)
3. Запускаем Visual Studio Command Prompt (2010)
4. Переходим в папку C:\Qt\qtbase
5. Редакатируем файл {путь_установки_Qt}\mkspecs\win32-msvc2005\qmake.conf (если у вас другая MSVC, то выбрать соответствующую папку).
    `QMAKE_CFLAGS_RELEASE = -O2 -MD` меняем на `QMAKE_CFLAGS_RELEASE    = -O2 -MT`
    `QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO += -O2 -MD -Zi` меняем на `QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO += -O2 -MT -Zi`
    `QMAKE_CFLAGS_DEBUG = -Zi -MDd` меняем на `QMAKE_CFLAGS_DEBUG      = -Zi -MTd`
    `CONFIG += qt warn_on release incremental flat link_prl precompile_header autogen_precompile_source copy_dir_files debug_and_release debug_and_release_target embed_manifest_dll embed_manifest_exe` удаляем `embed_manifest_dll embed_manifest_exe` 
6. Вводим  
    `configure -opengl desktop -mp -nomake tests -nomake examples -fully-process -opensource -confirm-license -platform win32-msvc2012`
7. После завершения предыдущей команды вводим  
    `nmake`
8. Идем пить чай/кофе/пиво. Сборка занимает примерно 20 минут.
9. Когда компиляция завершится, создаем переменную окружения QTDIR с параметром  
    `C:\Qt\qtbase`

Настройка Qt Creator
-------------------
1. Открываем "Инструменты->Параметры->Сборка и запуск".
2. Вкладка "Профили Qt", жмём "Добавить", выбираем файл  
    `.../qtbase/bin/qmake.exe`
3. Вкладка "Инструментарии", жмём "Добавить", в поле "Профиль Qt" выбираем свежесозданный профиль.
4. Назначаем этот инструментарий используемым по умолчанию.
5. Открываем в левой панели вкладку "Проекты", далее выбираем проект QtQgen, вкладку "Сборка и запуск". 
6. Если ещё не подключен наш новый инструментарий, подключаем через кнопку "Добавить". Старый удаляем (кнопочка "-").
7. Для вывода русских букв в окне сборки, используем [это решение](http://lab113.ru/qtcreator_kodirovka.php).

Примечание. Если ни с того ни с сего при сборке появляется куча ошибок типа   
    `ошибка: LNK2001: неразрешенный внешний символ`  
то выберите "Сборка->Запустить QMake".

Cборка проекта
-------------------
1. Переходим в папку с проектом.
2. Запускаем  
    `qmake`  
    `nmake`
