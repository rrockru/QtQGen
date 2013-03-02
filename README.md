QtQGen
======
Порт редактора игр для платформы QSP на Qt.

Для сборки проекта необходима Visual Studio 2010, библиотека Qt5, а так же необходима переменная окружения QTDIR,
в которой указан путь до корня библиотеки и библиотека QScintilla.

Qt лучше собирать из исходников, чтобы он не тащил с собой лишний хлам.<br/>
*Для сборки Qt требуются*<br/>
*ActivePerl(http://www.activestate.com/activeperl/downloads)*<br/>
*Python2.7,(http://python.org/download/)*<br/>
*Пути до Perl и Python должны быть прописаны в переменной PATH*<br/>
Собирается она следующим образом:<br/>
1. Скачиваем последнюю версию с http://qt-project.org<br/>
2. Распаковываем, например в C:\Qt<br/>
3. Запускаем Visual Studio Command Prompt (2010)<br/>
4. Переходим в папку C:\Qt\qtbase<br/>
5. Вводим <br/>
```
  configure -opengl desktop -no-plugin-manifests -D "_BIND_TO_CURRENT_VCLIBS_VERSION=1" -mp -nomake tests -nomake examples
```
6. После завершения предыдущей команды вводим<br/>
```
  nmake
```
7. Идем пить чай/кофе/пиво.<br/>
8. Когда компиляция завершится, создаем переменную окружения QTDIR с параметром<br/>
```
  C:\Qt\qtbase
```
9. Далее скачиваем библиотеку QScintilla (http://www.riverbankcomputing.com/software/qscintilla/download)<br/>
и распаковываем из архива папку Qt4Qt5 в, например, C:\Qt\QScintilla.<br/>
10. В распакованной папке редактируем файл qscintilla.pro:<br/>
в строке<br/>
```
CONFIG += qt warn_off release dll thread
```
заменяем dll на staticlib и добавляем debug<br/>
в строке<br/>
```
DEFINES = QSCINTILLA_MAKE_DLL QT SCI_LEXER
```
<br/>
удаляем QSCINTILLA_MAKE_DLL.<br/>
11. Запускаем через Visual Studio Command Prompt (2010) в папке с QScintilla<br/>
```
qmake
```
<br/>
```
nmake
```
<br/>
```
nmake install
```
<br/>
После этого можно собирать проект.
