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
2. Распаковываем, например в C:\Qt
3. Запускаем Visual Studio Command Prompt (2010)
4. Переходим в папку C:\Qt\qtbase
5. Вводим  
    `configure -opengl desktop -no-plugin-manifests -D "_BIND_TO_CURRENT_VCLIBS_VERSION=1" -mp -nomake tests -nomake examples`
6. После завершения предыдущей команды вводим  
    `nmake`
7. Идем пить чай/кофе/пиво.
8. Когда компиляция завершится, создаем переменную окружения QTDIR с параметром  
    `C:\Qt\qtbase`

Cборка проекта
-------------------
1. Переходим в папку с проектом.
2. Запускаем  
    `qmake`  
    `nmake`
