#pragma once
#include <QtGlobal>

namespace sgv
{
	enum ResizeModeFlags: quint32
	{
		Up        = 0b0001,
		Down      = 0b0010,
		Left      = 0b0100,
		Right     = 0b1000,
		UpLeft    = Up|Left,
		UpRight   = Up|Right,
		DownLeft  = Down|Left,
		DownRight = Down|Right,
		All       = Up|Down|Left|Right,
		None      = 0,
	};

	Q_DECLARE_FLAGS(ResizeMode, ResizeModeFlags)
	Q_DECLARE_OPERATORS_FOR_FLAGS(ResizeMode)
}
