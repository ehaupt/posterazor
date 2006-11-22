/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2006 by Alessandro Portale
	http://posterazor.sourceforge.net/

	This file is part of PosteRazor

	PosteRazor is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	
	PosteRazor is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with PosteRazor; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "PosteRazor.h"

int main(int argc, char *argv[])
{
	int error = 0;

	// This is no real main program, yet. It is just testing the PosteRazor API.

	PosteRazor* prz = PosteRazor::CreatePosteRazor();
	char errorMessage[1024];
	bool loaded = prz->LoadInputImage("c:\\image_cmyk.jpg", errorMessage, sizeof(errorMessage));

	if (loaded)
	{
		prz->SetPosterWidth(PosteRazorEnums::ePosterSizeModePages, 2.5);
		prz->SetPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignmentMiddle);
		prz->SetPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignmentCenter);
		int err = prz->SavePoster("c:\\poster.pdf");
		int huhu= 1;
	}

	delete prz;
	return error;
}