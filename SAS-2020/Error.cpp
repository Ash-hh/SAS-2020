#include "Error.h"
#include <locale>


namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, " Недопустимый код"),
		ERROR_ENTRY(1, " Систсемный сбой"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, " Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, " Превышена длинна входного параметра"),
		ERROR_ENTRY(105, "Ошибка считывания кода: отсутствует символ открытия/закрытия текстовго дитерада  "), 
		ERROR_ENTRY(106, "Ошибка считывания кода: отсутствует открывающая/закрывающая скобка"), 
		ERROR_ENTRY(107, "Ошибка считывания кода: отсутствует открывающая/закрывающая фигурная скобка"),
		ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, " Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, " Неедопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, " Ошибка при создании файла протокола (-log)"),		
		ERROR_ENTRY_NODEF(113), ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY(200, "Заданный размер превыщает максимально возможный"),
		ERROR_ENTRY(201,"Обнаружена вторая точка входа" ), ERROR_ENTRY_NODEF(202), ERROR_ENTRY_NODEF(203),
		ERROR_ENTRY(204, "Превышен максимальный размер таблицы идентификаторов"), 
		ERROR_ENTRY(205, "Превыщен максимальный размер таблицы лексем"),
		ERROR_ENTRY(206, "Ошибка лексического анализа"),
		ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY_NODEF100(600), ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};

	/*
		цепочка не распознана с такого-то символа
			LT
			превышена ёмкость таблицы лексем
			превышен размер таблицы лексем
			отсутствие определения ?? Ошибка: ожидалось опредление??


	*/

	ERROR geterror(int id)
	{
		ERROR errs;

		if (id > 0 && id < ERROR_MAX_ENTRY)
		{
			errs.id = errors[id].id;
			strcpy_s(errs.message, errors[id].message);
		}
		else errs = errors[0];

		return errs;
	}

	ERROR geterroin(int id, int line = -1, int col = -1)
	{
		ERROR errs;

		if (id > 0 && id < ERROR_MAX_ENTRY)
		{
			errs.id = id;
			strcpy_s(errs.message, errors[id].message);
			errs.inext.col = col;
			errs.inext.line = line;

		}
		else errs = errors[0];

		return errs;
	}
}