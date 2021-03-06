/*
 * Copyright 2015-2016. All rights reserved.
 * Distributed under the terms of the MIT license.
 *
 * Author:
 *	Humdinger, humdingerb@gmail.com
 */

#include <Catalog.h>
#include <ControlLook.h>

#include "App.h"
#include "ClipItem.h"
#include "ClipView.h"
#include "Constants.h"
#include "ContextPopUp.h"
#include "MainWindow.h"

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "ClipList"


ClipView::ClipView(const char* name)
	:
	BListView(name)
{
}


ClipView::~ClipView()
{
}


void
ClipView::AttachedToWindow()
{
	SetFlags(Flags() | B_FULL_UPDATE_ON_RESIZE | B_NAVIGABLE);

	BMessage message(ADJUSTCOLORS);
	fRunner	= new BMessageRunner(this, &message, kMinuteUnits * 60000000);

	BListView::AttachedToWindow();
}


void
ClipView::FrameResized(float width, float height)
{
	BListView::FrameResized(width, height);

	static const float spacing = be_control_look->DefaultLabelSpacing();

	for (int32 i = 0; i < CountItems(); i++) {
		ClipItem *sItem = dynamic_cast<ClipItem *> (ItemAt(i));
		BString string(sItem->GetClip());
		TruncateString(&string, B_TRUNCATE_END, width - kIconSize
			- spacing * 4);
		sItem->SetTitle(string);
	}
}

void
ClipView::Draw(BRect rect)
{
	SetHighColor(ui_color(B_CONTROL_BACKGROUND_COLOR));

	BRect bounds(Bounds());
	BRect itemFrame = ItemFrame(CountItems() - 1);
	bounds.top = itemFrame.bottom;
	FillRect(bounds);

	BListView::Draw(rect);
}


void
ClipView::MessageReceived(BMessage* message)
{
	switch (message->what) {
		case POPCLOSED:
		{
			fShowingPopUpMenu = false;
			break;
		}
		case ADJUSTCOLORS:
		{
			AdjustColors();
			Invalidate();
			break;
		}
		default:
		{
			BListView::MessageReceived(message);
			break;
		}
	}
}


void
ClipView::KeyDown(const char* bytes, int32 numBytes)
{
	switch (bytes[0]) {
		case B_DELETE:
		{
			Looper()->PostMessage(DELETE);
			break;
		}
		case B_LEFT_ARROW:
		case B_RIGHT_ARROW:
		{
			BMessage message(SWITCHLIST);
			message.AddInt32("listview", (int32)0);
			Looper()->PostMessage(&message);
			break;
		}
		default:
		{
			BListView::KeyDown(bytes, numBytes);
			break;
		}
	}
}


void
ClipView::AdjustColors()
{
	bool fade;
	int32 delay;
	int32 step;
	float maxlevel;
	bool pause;
	ClipdingerSettings* settings = my_app->Settings();
	if (settings->Lock()) {
		fade = settings->GetFade();
		step = settings->GetFadeStep();
		delay = settings->GetFadeDelay() * kMinuteUnits;
		maxlevel = 1.0 + 0.025 * settings->GetFadeMaxLevel();
		pause = settings->GetFadePause();
		settings->Unlock();
	}

	if (pause)
		return;

	int32 now(real_time_clock());
	for (int32 i = 0; i < CountItems(); i++) {
		ClipItem *sItem = dynamic_cast<ClipItem *> (ItemAt(i));
		if (fade) {
			int32 minutes = (now - sItem->GetTimeAdded()) / 60;
			float level = B_NO_TINT + (maxlevel/ step * ((float)minutes / delay));
			sItem->SetColor(tint_color(ui_color(B_LIST_BACKGROUND_COLOR),
			(level < maxlevel) ? level : maxlevel));  // limit to maxlevel
		} else
			sItem->SetColor(ui_color(B_LIST_BACKGROUND_COLOR));
	}
}


void
ClipView::MouseDown(BPoint position)
{
	BMessage message(SWITCHLIST);
	message.AddInt32("listview", (int32)1);
	Looper()->PostMessage(&message);

	BRect bounds(Bounds());
	BRect itemFrame = ItemFrame(CountItems() - 1);
	bounds.top = itemFrame.bottom;
	if (bounds.Contains(position) == false) {
		uint32 buttons = 0;
		if (Window() != NULL && Window()->CurrentMessage() != NULL)
			buttons = Window()->CurrentMessage()->FindInt32("buttons");

		if (buttons == B_SECONDARY_MOUSE_BUTTON)
			ShowPopUpMenu(ConvertToScreen(position));
	}
	BListView::MouseDown(position);
}


void
ClipView::ShowPopUpMenu(BPoint screen)
{
	if (fShowingPopUpMenu)
		return;

	ContextPopUp* menu = new ContextPopUp("PopUpMenu", this);

	BMenuItem* item = new BMenuItem(B_TRANSLATE("Remove clip"),
		new BMessage(DELETE));
	menu->AddItem(item);

	item = new BMenuItem(B_TRANSLATE("Add to favorites"),
		new BMessage(FAV_ADD));
	menu->AddItem(item);

	item = new BMenuItem(B_TRANSLATE("Paste to Sprunge.us"),
		new BMessage(PASTE_SPRUNGE));
	menu->AddItem(item);

	menu->SetTargetForItems(Looper());
	menu->Go(screen, true, true, true);
	fShowingPopUpMenu = true;
}
