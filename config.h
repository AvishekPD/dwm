/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const int gappx		        = 5;	    /* gaps between teh windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int bar_h              = 28;       /* 0 for dwm to auto decide bar height */ 
static const int horizpadbar        = 5;        /* horizontal padding in statusbar */
static const int vertpadbar         = 11;        /* vertical padding in statusbar */
static const unsigned int vertpad   = 5;	    /* vertical padding of the bar */
static const unsigned int sidepad   = 5;	    /* horizontal padding of the bar */
static const Bool viewonmove        = True;     /* move view when change tag */
static const char *fonts[]          ={  
                                        "Jetbrains Mono:pixelsize=12.69:autohint=true", 
					                    "Font Awesome 5 Free:pixelsize=13:autohint=1", 
					                    "Font Awesome 5 Brands:pixelsize=13:autohint=1", 
					                    "Font Awesome 5 Free:pixelsize=13:style=solid:autohint=1"  
                                    };
static const char dmenufont[]       = "JetBrains Mono:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_barbg[]	    = "#111111";
static const char col_barfg[]	    = "#707070";
static const char col_sel[]         = "#202020";
static const char col_border1[]	    = "#717171";
static const char col_border2[]	    = "#111111";
static const char col_cyan[]        = "#005577";
static const char col_trans[]	    = "#0000FF";
static const char *colors[][3]      = {
	/*                  fg         bg         border   */
	[SchemeNorm]        = { col_barfg, col_barbg, col_border2 },
	[SchemeSel]         = { col_barfg, col_barbg, col_border1 },
    [SchemeStatus]      = { col_barfg, col_barbg, NULL },  /*  for border !used but !empty */
    [SchemeTagsNorm]    = { col_barfg, col_barbg, NULL },
    [SchemeTagsSel]     = { col_barfg, col_sel,   NULL },
    [SchemeInfoNorm]    = { col_barfg, col_barbg, NULL },
    [SchemeInfoSel]     = { col_barbg, col_barbg, NULL },
};

/* autostart */
static const char *const autostart[] = {
	NULL //terminates
};

/* tagging */
static const char *tags[] = { "1:work", "2:Culture", "3:Social", "4:Moosic", "5:Egg" };

/* line under active tag */
static const unsigned int ulinepad      = 5; /* horizontal padding between underline and tag */
static const unsigned int ulinestroke   = 2; /* height of the underline */
static const unsigned int ulinevoffset   = 0; /* how far the bottom of bar the ine should apper */
static const int unlineall              = 0; /* 1 to show underline on all tag / 0 for active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
    { "Tilda",    NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "<T>",      tile },    /* first entry is default */
	{ "<>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_barbg , "-nf", col_barfg , "-sb", col_sel , "-sf", col_barfg , NULL };
static const char *termcmd[]  = { "st", NULL };

// Helper for spawning command
#define CALLCMD(cmd) { .v = (const char*[]){"/bin/sh", "-c", cmd ,NULL} }

/* custom commands */
static const char *browser[]    = { "qutebrowser", NULL};
//static const char *ss[]         = { "/usr/bin/maim", "-s", "|", "xclip", "-selection", "c", "-t", "image/png" ,NULL};
static const char *upbright[]   = { "/usr/bin/xbacklight", "-inc", "5", NULL };
static const char *downbright[] = { "/usr/bin/xbacklight", "-dec", "5", NULL };
static const char *volup[]      = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%", NULL };
static const char *voldown[]    = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%", NULL };
static const char *volmute[]    = { "/usr/bin/pactl", "set-sink-mute", "0", "toggle", NULL };
static const char *ytdmenu[]    = { "/usr/bin/ytfzf", "-D", NULL };

/* keybinds */
static Key keys[] = {
	/* modifier                     key                         function        argument */
	{ MODKEY,                       XK_Tab,                     spawn,          {.v = dmenucmd } },
	{ MODKEY,	                    XK_Return,                  spawn,          {.v = termcmd } },
	{ MODKEY, 			            XK_f,	                    spawn,	        {.v = browser } },
	{ 0,			                XK_Print,                   spawn, 	        CALLCMD("maim -s | xclip -selection c -t image/png") },
	{ MODKEY,                       XK_y,                       spawn,          {.v = ytdmenu } },
    { 0,                            XF86XK_AudioRaiseVolume,    spawn,          {.v = volup} },
    { 0,                            XF86XK_AudioLowerVolume,    spawn,          {.v = voldown} },
    { 0,                            XF86XK_AudioMute,           spawn,          {.v = volmute} },
    { 0,                            XF86XK_MonBrightnessUp,     spawn,          {.v = upbright} },
    { 0,                            XF86XK_MonBrightnessDown,   spawn,          {.v = downbright} },
	{ MODKEY,                       XK_b,                       togglebar,      {0} },
	{ MODKEY,                       XK_j,                       focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                       focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                       incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                       incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                       setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                       setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return,                  zoom,           {0} },
	{ MODKEY,                       XK_p,                       view,           {0} },
	{ MODKEY,             		    XK_x,                       killclient,     {0} },
	{ MODKEY,                       XK_space,                   setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                   togglefloating, {0} },
	{ MODKEY,                       XK_0,                       view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                       tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                  tagmon,         {.i = +1 } },
	{ MODKEY, 			            XK_minus,                   setgaps, 	    {.i = -5 } },
	{ MODKEY,			            XK_equal,                   setgaps, 	    {.i = +5 } },
	{ MODKEY|ShiftMask,		        XK_equal,                   setgaps, 	    {.i = 0 } },
	TAGKEYS(                        XK_1,                                       0)
	TAGKEYS(                        XK_2,                                       1)
	TAGKEYS(                        XK_3,                                       2)
	TAGKEYS(                        XK_4,                                       3)
	TAGKEYS(                        XK_5,                                       4)
	{ MODKEY|ShiftMask,             XK_q,                       quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask,	XK_q,	                    quit,	        {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument*/
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} }, 
};

