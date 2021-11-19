## Task

> **Цель работы**:
> научиться разрабатывать и использовать динамические библиотеки (DLL) с использованием Qt
> 
> Задание
> 
> Доработать программу, разработанную в лабораторной работе №1-2, внеся следующие изменения:
> 1. Выбрать 3 вспомогательные функции и вынести их описание
> и реализацию в динамическую библиотеку helper.dll.
> В основном приложении осуществить загрузку реализованных функций во время работы программы
> (at run-time, с использованием объекта QLibrary) и их вызов.
> 2. Выбрать вспомогательный класс и вынести его описание
> и реализацию в динамическую библиотеку helper_class.dll.
> В основном приложении осуществить загрузку реализованного класса во время компиляции (at compile-time).
> 3. Реализовать окно <<О программе>> в виде объекта динамической библиотеки about.dll
> с указанием автора программы, группы, курса и краткого описания разработанного приложения.
> Осуществить импорт указанной библиотеки и отображение соответствующего окна при выборе
> пункта меню <<О программе>>.
> 4. Реализовать расширения для приложения, позволяющие изменять оформление пунктов меню
> (шрифт, размер, начертание и т.д.).
> Соответствующие изменения должны происходить при выборе специального пункта меню.
> Создать как минимум три расширения такого типа.