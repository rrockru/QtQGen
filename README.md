QtQGen
======
Порт редактора игр для платформы QSP на Qt.

Для сборки проекта необходима Visual Studio 2010, библиотека Qt5, а так же необходима переменная окружения QTDIR,
в которой указан путь до корня библиотеки.

Qt лучше собирать из исходников, чтобы он не тащил с собой лишний хлам.<br/>
*Для сборки требуются*<br/>
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
  C:\Qt
```

После этого можно собирать проект.
