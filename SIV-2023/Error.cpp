#include "pch.h"
#include "Error.h"
#include <iostream>
#include <cstring>

namespace Error
{
	// 0-99		 C�������� ������
	// 100-109	 ������ ����������
	// 110-119	 ������ �������� � ������ ������
	// 120-129	 ������ ���������� ������ ������ � ���������������
	// 130-139	 ������ ���������� ������� �������

	// ������� ������
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		// ��� ������ ��� ��������� 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(0,"��������� ������: ������������ ��� ������"),
		ERROR_ENTRY(1,"��������� ������: ��������� ����"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3),
		ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY(10, "������ ���������: �������� -in ������ ���� �����"),
		ERROR_ENTRY(11, "������ ���������: ��������� ����� �������� ���������"),
		ERROR_ENTRY(12, "������ ���������: �������� -out ������ ���� �����"),
		ERROR_ENTRY_NODEF(13),
		ERROR_ENTRY_NODEF(14), ERROR_ENTRY_NODEF(15), ERROR_ENTRY_NODEF(16), ERROR_ENTRY_NODEF(17),
		ERROR_ENTRY_NODEF(18), ERROR_ENTRY_NODEF(19),
		ERROR_ENTRY(20, "������ �����: ������ ��� �������� ����� � �������� ����� (-in:)"),
		ERROR_ENTRY(21, "������ �����: ������ ��� �������� ����� ��������� (-log:)"),
		ERROR_ENTRY(22, "������ �����: ������ ��� �������� ����� � �������� ������ (-lex:)"),
		ERROR_ENTRY(23, "������ �����: ������ ��� �������� ����� � �������� ��������������� (-id:)"),
		ERROR_ENTRY_NODEF(24), ERROR_ENTRY_NODEF(25), ERROR_ENTRY_NODEF(26),
		ERROR_ENTRY_NODEF(27), ERROR_ENTRY_NODEF(28), ERROR_ENTRY_NODEF(29),
		ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY_NODEF10(100),
		ERROR_ENTRY(110, "������ ������������ �����������: ������������ ������ � �������� ����� (-in:)"),
		ERROR_ENTRY(111, "������ ������������ �����������: ��������� ������� ������� ������"),
		ERROR_ENTRY(112, "������ ������������ �����������: ��������� ���������� ����� � ������� ������"),
		ERROR_ENTRY(113, "������ ������������ �����������: � ������� ������ ����������� ������ � �������� �������"),
		ERROR_ENTRY(114, "������ ������������ �����������: ��������� ������� ������� ���������������"),
		ERROR_ENTRY(115, "������ ������������ �����������: ��������� ���������� ����� � ������� ���������������"),
		ERROR_ENTRY(116, "������ ������������ �����������: � ������� ��������������� ����������� ������ � �������� �������"),
		ERROR_ENTRY(117, "������ ������������ �����������: �� ������� ���������� ��� �������"),
		ERROR_ENTRY(118, "������ ������������ �����������: ��������� ������� ������� �������"),
		ERROR_ENTRY(119, "������ ������������ �����������: ��������� ���������� ������� � ������� �������"),
		ERROR_ENTRY(120, "������ ������������ �����������: ������ � ���������� ��������� ������ �� ������"),
		ERROR_ENTRY(121, "������ ������������ �����������: ������ � �������� ���������� ��������"),
		ERROR_ENTRY_NODEF(122), ERROR_ENTRY_NODEF(123), ERROR_ENTRY_NODEF(124), ERROR_ENTRY_NODEF(125),
		ERROR_ENTRY_NODEF(126), ERROR_ENTRY_NODEF(127), ERROR_ENTRY_NODEF(128), ERROR_ENTRY_NODEF(129),
		ERROR_ENTRY(130, "������ �������������� �������: ��������� ����� ������ � 255 ��������"),
		ERROR_ENTRY(131, "������ �������������� �������: ������� main ��� ����� ����������"),
		ERROR_ENTRY(132, "������ �������������� �������: ��������� ����� �������"),
		ERROR_ENTRY(133, "������ �������������� �������: ��������� �������� �������������� �������� (2 byte)"),
		ERROR_ENTRY(134, "������ �������������� �������: �� ������� ����� ����� � ��������� (main)"),
		ERROR_ENTRY(135, "������ �������������� �������: ������������� � ����� ������ �� ������"),
		ERROR_ENTRY(136, "������ �������������� �������: ��������� ���������� ��������������"),
		ERROR_ENTRY(137, "������ �������������� �������: �������������� ����� � ���������"),
		ERROR_ENTRY(138, "������ �������������� �������: ������� ����� ���������� � �������"),
		ERROR_ENTRY(139, "������ �������������� �������: ��������� ���������� �������"),
		ERROR_ENTRY(140, "������ �������������� �������: �������������� ���������� ����������� � ���������� �������"),
		ERROR_ENTRY(141, "������ �������������� �������: �������������� ���������� ���������� �������"),
		ERROR_ENTRY(142, "������ �������������� �������: ������������� ��������� �� �������� ��������������� � �� ������ �������� ��������"),
		ERROR_ENTRY(143, "������ �������������� �������: ������ ������� ��� ����� ����������"),
		ERROR_ENTRY(144, "������ �������������� �������: � ������ ������� ����������� ()"),
		ERROR_ENTRY(145, "������ �������������� �������: ��� ������������� �������� �� ������������� ���� �������"),
		ERROR_ENTRY(146, "������ �������������� �������: �������� �� ������������ ��� ������ �� ��������"),
		ERROR_ENTRY(147, "������ �������������� �������: � ������� ����������� ������������ ��������"),
		ERROR_ENTRY(148, "������ �������������� �������: ������� �� 0 �����������"),
		ERROR_ENTRY(149, "������ �������������� �������: ������������ ��������� �������"),
		ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200),ERROR_ENTRY_NODEF100(300),ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "������ ��������������� �������: �������� ��������� ���������"),
		ERROR_ENTRY(601, "������ ��������������� �������: ������ � ����������� ����� ����"),
		ERROR_ENTRY(602, "������ ��������������� �������: ������ � ���������"),
		ERROR_ENTRY(603, "������ ��������������� �������: ������ � ���������� �������"),
		ERROR_ENTRY(604, "������ ��������������� �������: ������ � ���������� ���������� �������"),
		ERROR_ENTRY(605, "������ ��������������� �������: ��������� ��������"),
		ERROR_ENTRY(606, "������ ��������������� �������: ������ � �������� �����������"),
		ERROR_ENTRY(607, "������ ��������������� �������: ������ ����"),
		ERROR_ENTRY_NODEF(608),ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF10(610), ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680), ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700),ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900),
	};

	ERROR geterror(int id)
	{
		ERROR error_info;
		if (id > 0 && id < ERROR_MAX_ENTRY)
		{
			error_info.id = errors[id].id;
			strcpy(error_info.message, errors[id].message);
			error_info.inext.col = -1;
			error_info.inext.line = -1;
		}
		else
		{
			error_info.id = errors[0].id;
			strcpy(error_info.message, errors[0].message);
		}
		return error_info;
	}

	ERROR geterrorin(int id, int line, int col)
	{
		ERROR error_info;
		if (id > 0 && id < ERROR_MAX_ENTRY)
		{
			error_info.id = errors[id].id;
			error_info.inext.col = col + 1;
			error_info.inext.line = line + 1;
			strcpy(error_info.message, errors[id].message);
			return error_info;
		}
		else
		{
			error_info.id = 0;
			error_info.inext.col = -1;
			error_info.inext.line = -1;
			strcpy(error_info.message, errors[0].message);
			return error_info;
		}
	};
};