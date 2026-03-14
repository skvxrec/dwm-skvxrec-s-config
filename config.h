/* See LICENSE file for copyright and license details. */
/* Constants */
#define TERMINAL "alacritty"
#define TERMCLASS "alacritty"
#define BROWSER "firefox"

/* appearance */
static unsigned int borderpx  = 3;
static unsigned int snap      = 5;
static unsigned int gappih    = 0;
static unsigned int gappiv    = 0;
static unsigned int gappoh    = 0;
static unsigned int gappov    = 0;
static int swallowfloating    = 0;
static int smartgaps          = 0;
static int showbar            = 1;
static int topbar             = 1;
static char *fonts[]          = { "JetBrainsMono Nerd Font Mono:Bold:size=18" };
static char normbgcolor[]     = "#222222";
static char normbordercolor[] = "#444444";
static char normfgcolor[]     = "#bbbbbb";
static char selfgcolor[]      = "#eeeeee";
static char selbordercolor[]  = "#307a44";
static char selbgcolor[]      = "#307a44";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-T", "spterm", NULL };
static Sp scratchpads[] = {
	{"spterm", spcmd1},
};

/* tagging */
static const char *tags[] = { "󰖟 bsr", "󰆍 trm", " tg", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class       instance   title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ TERMCLASS,   NULL,      NULL,           0,         0,          1,          0,         -1 },
	{ NULL,        NULL,      "Event Tester", 0,         0,          0,          1,         -1 },
	{ TERMCLASS,   "spterm",  NULL,           SPTAG(0),  1,          1,          0,         -1 },
};

/* layout(s) */
static float mfact     = 0.55;
static int nmaster     = 1;
static int resizehints = 0;
static const int lockfullscreen = 1;
#define FORCE_VSPLIT 1
#include "vanitygaps.c"
#include "movestack.c"
static const Layout layouts[] = {
	{ "[tl]",  tile },
	{ "[i3l]",  bstack },
	{ "[sprl]",  spiral },
	{ "[dw]", dwindle },
	{ "[M]",  monocle },
	{ "><>",  NULL },
	{ NULL,   NULL },
};

/* key definitions */
/* ALT = Mod1Mask, как в твоём hyprland */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY, view,       {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY, toggleview, {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY, tag,        {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY, toggletag,  {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j, ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k, ACTION##stack, {.i = INC(-1) } },

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
static const char *termcmd[] = { TERMINAL, NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"

static const Key keys[] = {
	/* modifier          key            function        argument */
	STACKKEYS(MODKEY,                   focus)
	// STACKKEYS(MODKEY|ShiftMask,         push)

	/* теги 1-9 как в hyprland */
	TAGKEYS(XK_1, 0)
	TAGKEYS(XK_2, 1)
	TAGKEYS(XK_3, 2)
	TAGKEYS(XK_4, 3)
	TAGKEYS(XK_5, 4)
	TAGKEYS(XK_6, 5)
	TAGKEYS(XK_7, 6)
	TAGKEYS(XK_8, 7)
	TAGKEYS(XK_9, 8)
	{ MODKEY,            XK_0,          view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,  XK_0,          tag,            {.ui = ~0 } },
	{ MODKEY, XK_i, setlayout, {.v = &layouts[2]} },

	/* основные биндинги как в hyprland */
	{ MODKEY,            XK_Return,     spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,  XK_Return,     togglescratch,  {.ui = 0} },
	{ MODKEY,            XK_c,          killclient,     {0} },          /* ALT+C = killactive */
	{ MODKEY,            XK_p,          spawn,          {.v = (const char*[]){ "dmenu_run", NULL } } }, /* ALT+P = fuzzel замена */
	{ MODKEY,            XK_f,          spawn,          {.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY,            XK_d,          spawn,          {.v = (const char*[]){ "discord", NULL } } },
	{ MODKEY,            XK_t,          spawn,          {.v = (const char*[]){ "Telegram", NULL } } },
	{ MODKEY,            XK_s,          spawn,          {.v = (const char*[]){ "steam", NULL } } },
	{ MODKEY,            XK_n,          spawn,          {.v = (const char*[]){ "dolphin", NULL } } },
	{ MODKEY,            XK_l,          spawn,          {.v = (const char*[]){ "slock", NULL } } }, /* lock */

	/* перемещение между мониторами */
	{ MODKEY,            XK_Left,       focusmon,       {.i = -1 } },
	{ MODKEY,            XK_Right,      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,  XK_Left,       tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,  XK_Right,      tagmon,         {.i = +1 } },

  /* перемещение окон */
  { MODKEY|ShiftMask, XK_j, movestack, {.i = +1 } },
  {MODKEY|ShiftMask, XK_k, movestack, {.i = -1 } },

	/* лейауты */
	/* { MODKEY,            XK_Tab,        view,           {0} },
	 { MODKEY,            XK_space,      zoom,           {0} }, */
	{ MODKEY,            XK_space,      togglefloating, {0} },
	{ MODKEY,            XK_Tab,          togglefullscr,  {0} },

	/* гапы */
	{ MODKEY,            XK_a,          togglegaps,     {0} },
	{ MODKEY|ShiftMask,  XK_a,          defaultgaps,    {0} },
	{ MODKEY,            XK_z,          incrgaps,       {.i = +3 } },
	// { MODKEY,            XK_x,          incrgaps,       {.i = -3 } },

	/* бар */
	{ MODKEY,            XK_b,          togglebar,      {0} },

	/* скриншот как в hyprland (ALT+SHIFT+S) */
	{ MODKEY,        XK_x,          spawn,          SHCMD("maim -s | xclip -selection clipboard -t image/png") },

	/* громкость */
        { 0, XF86XK_AudioMute,         spawn, SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle") },
        { 0, XF86XK_AudioRaiseVolume,  spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +3%") },
        { 0, XF86XK_AudioLowerVolume,  spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -3%") },
};

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
	{ "color0",      STRING,  &normbordercolor },
	{ "color8",      STRING,  &selbordercolor },
	{ "color0",      STRING,  &normbgcolor },
	{ "color4",      STRING,  &normfgcolor },
	{ "color0",      STRING,  &selfgcolor },
	{ "color4",      STRING,  &selbgcolor },
	{ "borderpx",    INTEGER, &borderpx },
	{ "snap",        INTEGER, &snap },
	{ "showbar",     INTEGER, &showbar },
	{ "topbar",      INTEGER, &topbar },
	{ "nmaster",     INTEGER, &nmaster },
	{ "resizehints", INTEGER, &resizehints },
	{ "mfact",       FLOAT,   &mfact },
	{ "gappih",      INTEGER, &gappih },
	{ "gappiv",      INTEGER, &gappiv },
	{ "gappoh",      INTEGER, &gappoh },
	{ "gappov",      INTEGER, &gappov },
	{ "swallowfloating", INTEGER, &swallowfloating },
	{ "smartgaps",   INTEGER, &smartgaps },
};

/* button definitions */
static const Button buttons[] = {
	{ ClkClientWin, MODKEY, Button1, movemouse,   {0} },
	{ ClkClientWin, MODKEY, Button3, resizemouse, {0} },
	{ ClkClientWin, MODKEY, Button4, incrgaps,    {.i = +1} },
	{ ClkClientWin, MODKEY, Button5, incrgaps,    {.i = -1} },
	{ ClkTagBar,    0,      Button1, view,        {0} },
	{ ClkTagBar,    0,      Button3, toggleview,  {0} },
	{ ClkTagBar,    MODKEY, Button1, tag,         {0} },
	{ ClkTagBar,    MODKEY, Button3, toggletag,   {0} },
	{ ClkTagBar,    0,      Button4, shiftview,   {.i = -1} },
	{ ClkTagBar,    0,      Button5, shiftview,   {.i = 1} },
	{ ClkRootWin,   0,      Button2, togglebar,   {0} },
};
