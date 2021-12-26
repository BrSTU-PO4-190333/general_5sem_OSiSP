; = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

; gpi_ Здесь мои константы

!define gpi_name "gpi_ My First Program" ; gpi_ константа
!define gpi_version "0.0.1" ; gpi_ константа

; = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

Name "${gpi_name}"
OutFile "${gpi_name} ${gpi_version} Setup.exe" ; gpi_ Название инсталятора
InstallDir "$PROGRAMFILES\gpi_MyFirstProgram" ; gpi_ папка установки
RequestExecutionLevel admin ; gpi_ запускается установщик от админа

; = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

; gpi_ Здесь перечисляем какие окна будут созданы

Page license ; gpi_cоздаем окно с лицензией
Page components ; gpi_ создает окно с флажками выбора секций 
Page directory ; gpi_ создает окно выбора установки
Page instfiles ; gpi_ создает окно с полосой установки
;Page custom gpi_nsDialogsPage ; создается своё окно, для неё пишем функцию
UninstPage uninstConfirm
UninstPage instfiles

; = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

; gpi_ Эта секция будет доступна после выбора галочки
; gpi_ Эта секция будет создавать ярлык на рабочем столе

Section "gpi_ Sozdat' yarlyk na rabochem stole" gpi_SecLinkDesktop
	CreateShortcut "$DESKTOP\${gpi_name}.lnk" \
		"$INSTDIR\gpi__App.exe.txt" ; gpi_ создаётся ярлык на рабочем столе
SectionEnd 

; = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

; gpi_ Эта секция будет доступна после выбора галочки
; gpi_ Эта секция будет создавать ярлыки в главном меню

Section "gpi_ Sozdat' yarlyk v menyu" gpi_SecLinkMenu
	CreateShortcut "$STARTMENU\${gpi_name}.lnk" \
		"$INSTDIR\gpi__App.exe.txt" ; gpi_ создаётся ярлык в меню
	CreateShortcut "$STARTMENU\${gpi_name} Uninstall.lnk" \
		"$INSTDIR\Uninstall.exe" ; gpi_ создаётся ярлык в меню
SectionEnd

; = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

; gpi_ Эта секция будет доступна после выбора галочки
; gpi_ Эта секция будет устанавливать программу для всех пользователей

Section "gpi_ Ustanovit' programmu dlya vsekh pol'zovatelej" gpi_SecInstApp
	SetOutPath "$INSTDIR"
  
	;ADD YOUR OWN FILES HERE...
	FILE "App\gpi__App.exe.txt"
	FILE "App\gpi_helper.dll.txt"
	FILE "App\gpi_helper_class.dll.txt"
	FILE "App\gpi_about.dll.txt"
  
	;Store installation folder
	WriteRegStr HKLM "Software\${gpi_name}" "" $INSTDIR ; почему-то не создается ключ
	
	;Create uninstaller
	WriteUninstaller "$INSTDIR\Uninstall.exe"
SectionEnd

; = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

; gpi_ В этой секции я делаю удалятор

Section "Uninstall"
	;ADD YOUR OWN FILES HERE...
	Delete "$INSTDIR\gpi__App.exe.txt"
	Delete "$INSTDIR\gpi_helper.dll.txt"
	Delete "$INSTDIR\gpi_helper_class.dll.txt"
	Delete "$INSTDIR\gpi_about.dll.txt"

	Delete "$STARTMENU\${gpi_name}.lnk"
	Delete "$STARTMENU\${gpi_name} Uninstall.lnk"
	
	Delete "$DESKTOP\${gpi_name}.lnk"

	Delete "$INSTDIR\Uninstall.exe"

	RMDir "$INSTDIR"

	DeleteRegKey /ifempty HKLM "Software\${gpi_name}"
SectionEnd

; = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
