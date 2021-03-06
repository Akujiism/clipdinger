/*
 * Copyright 2015-2016. All rights reserved.
 * Distributed under the terms of the MIT license.
 *
 * Author:
 *	Humdinger, humdingerb@gmail.com
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define OUTPUT_PORT_NAME	"Clipdinger output port"

static const char *kApplicationSignature = "application/x-vnd.Clipdinger";
static const char kSettingsFolder[] = "Clipdinger";
static const char kSettingsFile[] = "Clipdinger_settings";
static const char kHistoryFile[] = "Clipdinger_history";
static const char kFavoriteFile[] = "Clipdinger_favorites";

static const int32 kDefaultLimit = 100;
static const int32 kDefaultAutoPaste = 1;
static const int32 kDefaultFade = 0;
static const int32 kDefaultFadeDelay = 6;
static const int32 kDefaultFadeStep = 5;
static const int32 kDefaultFadeMaxLevel = 8;
static const int32 kIconSize = 16;
static const int32 kMaxTitleChars = 100;
static const int32 kMinuteUnits = 10; // minutes per unit

#define DELETE				'dele'
#define FAV_DELETE			'delf'
#define FAV_ADD				'addf'
#define	FAV_EDIT			'edif'
#define UPDATE_FAV_DISPLAY	'updf'
#define ESCAPE				'esca'
#define POPCLOSED			'pmcl'
#define F_KEY				'fkey'

#define PASTE_SPRUNGE		'pssp'
#define CLEAR_HISTORY		'clhi'
#define HELP				'help'
#define	FAV_UP				'favu'
#define FAV_DOWN			'favd'
#define INSERT_HISTORY		'ihis'
#define INSERT_FAVORITE		'ifav'
#define ADJUSTCOLORS		'acol'
#define PAUSE				'paus'
#define SETTINGS			'sett'
#define SWITCHLIST			'swls'

#define	AUTOPASTE			'auto'
#define FADE				'fade'
#define DELAY				'dely'
#define STEP				'step'
#define LEVEL				'levl'
#define CANCEL				'cncl'
#define OK					'okay'
#define UPDATE_SETTINGS		'uset'

#endif //CONSTANTS_H
