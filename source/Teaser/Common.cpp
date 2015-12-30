//------------------------------------------------------------
// <copyright file="Common.cpp" autor="Markus Perz">
//     Copyright (c) Markus Perz. All rights reserved.
// </copyright>
//------------------------------------------------------------

#include <Teaser/Common.hpp>

namespace Teaser
{

void showMessageBox(MessageBoxType type, std::string title, std::string msg)
{

	u32 flags;

	switch (type)
	{
		case MessageBoxType::Information:
		{
			flags = SDL_MESSAGEBOX_INFORMATION;
			break;
		}

		case MessageBoxType::Warning:
		{
			flags = SDL_MESSAGEBOX_WARNING;
			break;
		}

		case MessageBoxType::Error:
		{
			flags = SDL_MESSAGEBOX_ERROR;
			break;
		}
	}

	SDL_ShowSimpleMessageBox(flags, title.c_str(), msg.c_str(), 0);
}

void fatal(std::string msg)
{
	LOCAL_PERSIST std::string prefix = "[ERROR] ";
	showMessageBox(MessageBoxType::Error, "Fatal Error", prefix+msg);
	SDL_Quit();
	exit(EXIT_FAILURE);
}

} // namespace Teaser