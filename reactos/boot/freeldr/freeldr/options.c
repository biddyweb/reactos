/*
 *  FreeLoader
 *  Copyright (C) 1998-2003  Brian Palmer  <brianp@sginet.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <freeldr.h>

PCSTR	OptionsMenuList[] =
{
	"Safe Mode",
	"Safe Mode with Networking",
	"Safe Mode with Command Prompt",

	"SEPARATOR",

	"Enable Boot Logging",
	"Enable VGA Mode",
	"Last Known Good Configuration",
	"Directory Services Restore Mode",
	"Debugging Mode",

	"SEPARATOR",

#ifdef HAS_OPTION_MENU_CUSTOM_BOOT
	"Custom Boot",
#endif
#ifdef HAS_OPTION_MENU_REBOOT
	"Reboot",
#endif
};

enum OptionMenuItems
{
	SAFE_MODE = 0,
	SAFE_MODE_WITH_NETWORKING = 1,
	SAFE_MODE_WITH_COMMAND_PROMPT = 2,

	SEPARATOR1 = 3,

	ENABLE_BOOT_LOGGING = 4,
	ENABLE_VGA_MODE = 5,
	LAST_KNOWN_GOOD_CONFIGURATION = 6,
	DIRECTORY_SERVICES_RESTORE_MODE = 7,
	DEBUGGING_MODE = 8,

	SEPARATOR2 = 9,

#ifdef HAS_OPTION_MENU_CUSTOM_BOOT
	CUSTOM_BOOT = 10,
#endif
#ifdef HAS_OPTION_MENU_REBOOT
	REBOOT = 11,
#endif
};

ULONG		OptionsMenuItemCount = sizeof(OptionsMenuList) / sizeof(OptionsMenuList[0]);

VOID DoOptionsMenu(VOID)
{
	ULONG		SelectedMenuItem;

	if (!UiDisplayMenu(OptionsMenuList, OptionsMenuItemCount, 0, -1, &SelectedMenuItem, TRUE, NULL))
	{
		// The user pressed ESC
		return;
	}

	// Clear the backdrop
	UiDrawBackdrop();

	switch (SelectedMenuItem)
	{
	case SAFE_MODE:
		break;
	case SAFE_MODE_WITH_NETWORKING:
		break;
	case SAFE_MODE_WITH_COMMAND_PROMPT:
		break;
	//case SEPARATOR1:
	//	break;
	case ENABLE_BOOT_LOGGING:
		break;
	case ENABLE_VGA_MODE:
		break;
	case LAST_KNOWN_GOOD_CONFIGURATION:
		break;
	case DIRECTORY_SERVICES_RESTORE_MODE:
		break;
	case DEBUGGING_MODE:
		break;
	//case SEPARATOR2:
	//	break;
#ifdef HAS_OPTION_MENU_CUSTOM_BOOT
	case CUSTOM_BOOT:
		OptionMenuCustomBoot();
		break;
#endif
#ifdef HAS_OPTION_MENU_REBOOT
	case REBOOT:
		OptionMenuReboot();
		break;
	}
#endif
}
