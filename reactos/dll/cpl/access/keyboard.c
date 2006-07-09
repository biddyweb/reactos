/* $Id$
 *
 * PROJECT:         ReactOS System Control Panel
 * LICENSE:         GPL - See COPYING in the top level directory
 * FILE:            lib/cpl/system/advanced.c
 * PURPOSE:         Memory, start-up and profiles settings
 * COPYRIGHT:       Copyright 2004 Johannes Anderwald (j_anderw@sbox.tugraz.at)
 * UPDATE HISTORY:
 *      03-04-2004  Created
 */
#include <windows.h>
#include <stdlib.h>
#include "resource.h"
#include "access.h"

/* Property page dialog callback */
INT_PTR CALLBACK
KeyboardPageProc(
  HWND hwndDlg,
  UINT uMsg,
  WPARAM wParam,
  LPARAM lParam
)
{
  UNREFERENCED_PARAMETER(lParam)
  UNREFERENCED_PARAMETER(hwndDlg)
  switch(uMsg)
  {
    case WM_INITDIALOG:
      break;
    case WM_COMMAND:
    {
      switch(LOWORD(wParam))
      {
        case IDC_STICKY_BOX:
        {
          break;
        }

        case IDC_STICKY_BUTTON:
        {
          break;
        }

        case IDC_FILTER_BOX:
        {
          break;
        }

        case IDC_FILTER_BUTTON:
        {
          break;
        }

        case IDC_TOGGLE_BOX:
        {
          break;
        }

        case IDC_TOGGLE_BUTTON:
        {
          break;
        }
        default:
           break;
      }
    }
  }
  return FALSE;
}
