/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
static const int respect_monitor_reserved_area = 0;  /* 1 to monitor center while respecting the monitor's reserved area, 0 to monitor center */
static int passthrough                     = 0;  /* enable passthrough by default */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static int enableautoswallow               = 1; /* enables autoswallowing newly spawned clients */
static float swallowborder                 = 0.0f; /* add this multiplied by borderpx to border when a client is swallowed */
static const int smartgaps                 = 1;  /* 1 means no outer gap when there is only one window */
static int gaps                            = 1;  /* 1 means gaps between windows are added */
static const unsigned int gappx            = 8; /* gap pixel between windows */
static const unsigned int borderpx         = 4;  /* border pixel of windows */
static const float rootcolor[]             = COLOR(0x282828ff);
static const int showbar                   = 1; /* 0 means no bar */
static const int topbar                    = 1; /* 0 means bottom bar */
static const char *fonts[]                 = {"JetBrainsMonoNerdFont:size=16","NotoColorEmoji:size=14"};
/* This conforms to the xdg-protocol. Set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.0f, 0.0f, 0.0f, 1.0f}; /* You can also use glsl colors */ /* last value modified if weird behavior then revert to 1.0f */
static uint32_t colors[][3]                = {
	/*               fg          bg          border    */
  [SchemeNorm] = { 0xebdbb2ff, 0x282828ff, 0x928374ff },
  [SchemeSel]  = { 0x282828ff, 0xd65d0eff, 0xd65d0eff },
  [SchemeUrg]  = { 0,          0xfb4934ff, 0xfb4934ff },
};

/* tagging */
static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* logging */
static int log_level = WLR_ERROR;

#define TERMINAL "foot"
#define BROWSER "librewolf"

/* NOTE: ALWAYS keep a rule declared even if you don't use rules (e.g leave at least one example) */
static const Rule rules[] = {
	/* app_id                        title              tags mask     isfloating   isterm   noswallow   monitor      scratchkey */
    { "mpv",                         NULL,              0,            0,            0,          0,          0,       0    },
    { "KeePassXC",                   NULL,              1 << 8,       0,            0,          0,          1,       0    },
    { "org.mozilla.Thunderbird",     NULL,              1 << 2,       0,            0,          0,          1,       0    },
    { "qBittorrent",                 NULL,              1 << 6,       0,            0,          0,          1,       0    },
    { "discord",                     NULL,              1 << 3,       0,            0,          0,          0,       0    },
    { "calibre-gui",                 NULL,              1 << 3,       0,            0,          0,          1,       0    },
	{ NULL,                          "email",           1 << 2,       0,            0,          1,          1,       0    },
	{ NULL,                          "news",            1 << 4,       0,            0,          1,          1,       0    },
    { TERMINAL,                      NULL,              0,            0,            1,          0,         -1,       0    },
    { NULL,                          "floatingterm",    0,            1,            1,          0,         -1,       0    },
    { "Ghostscript",                 NULL,              0,            0,            0,          1,         -1,       0    },
    { NULL,                          "Event Tester",    0,            0,            0,          1,         -1,       0    },
    { "wev",                         NULL,              0,            0,            0,          1,         -1,       0    },
    { "xdg-desktop-portal",          NULL,              0,            1,            0,          0,         -1,       0    },
    { "python3",                     NULL,              0,            1,            0,          0,         -1,       0    },
	{ NULL,                          "spterm",          0,            1,            1,          1,         -1,      't'   },
	{ NULL,                          "spmusic",         0,            1,            1,          1,         -1,      'm'   },

};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors */
/* (x=-1, y=-1) is reserved as an "autoconfigure" monitor position indicator
 * WARNING: negative values other than (-1, -1) cause problems with Xwayland clients
 * https://gitlab.freedesktop.org/xorg/xserver/-/issues/899
*/
/* NOTE: ALWAYS add a fallback rule, even if you are completely sure it won't be used */

static const MonitorRule monrules[] = {
    /* name       mfact nmaster scale layout       rotate/reflect               x       y       resx    resy    rate            mode  adaptive  */
    { "eDP-1",     0.5,  1,      1.25, &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, 0,      0,      0,      0,      60 ,            -1,    0  },
    { "DP-1",      0.5,  1,      1.25, &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, 1920,   0,      2560,   1440,   165.001,         1,    0  },
    { "HDMI-A-1",  0.5,  1,      1.0,  &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, 0,      0,      1920,   1080,   74.973,          1,    0  },
    { NULL,        0.5,  1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,-1,     -1,      0,      0,      0.0f,            0,    1  },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
    .layout = "pl"
};

static const int repeat_rate = 60;
static const int repeat_delay = 300;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]         = { TERMINAL, NULL };
static const char *menucmd[]         = { "bemenu-run", NULL };
static const char *browser[]         = { BROWSER, NULL };
static const char *email[]           = { TERMINAL,"-T","email", "-e", "neomutt", NULL };
static const char *notes[]           = { TERMINAL,"-T","notes","-e","sh","-c","cd ~/dox/notes && $EDITOR", NULL};
static const char *fileManager[]     = { TERMINAL,"-T","files", "-e", "yazi", NULL };
static const char *news[]            = { TERMINAL,"-T","news", "-e", "newsboat", NULL };
static const char *passwords[]       = { "keepassxc", NULL };
static const char *books[]           = { "calibre", NULL };
static const char *lockscreen[]      = { "waylock", "-fail-color", "0xfb4934", "-init-color", "0x282828", "-input-color", "0xd65d0e", "-ignore-empty-password", "-fork-on-lock", NULL };
static const char *communicator[]    = { "discord", "--enable-features=UseOzonePlatform", "--ozone-platform=wayland", NULL};

/* First arg only serves to match against key in rules*/
static const char *spterm[]     = {"t", TERMINAL, "-T", "spterm", NULL};
static const char *spmusic[]    = {"m", TERMINAL, "-T", "spmusic","-e","rmpc", NULL};


static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                 function        argument */
	{ MODKEY,                    XKB_KEY_d,          spawn,          {.v = menucmd} },
	{ MODKEY,                    XKB_KEY_Return,     spawn,          {.v = termcmd} },
	{ MODKEY,                    XKB_KEY_b,          togglebar,      {0} },
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_Return,     togglescratch,  {.v = spterm } },
	{ MODKEY,                    XKB_KEY_m,          togglescratch,  {.v = spmusic } },
	{ MODKEY,                    XKB_KEY_j,          focusstack,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_k,          focusstack,     {.i = -1} },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_J,          relativeswap,   {.i = +1} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_K,          relativeswap,   {.i = -1} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_I,          incnmaster,     {.i = +1} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_D,          incnmaster,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_h,          setmfact,       {.f = -0.05f} },
	{ MODKEY,                    XKB_KEY_l,          setmfact,       {.f = +0.05f} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Return,     zoom,           {0} },
	{ MODKEY,                    XKB_KEY_Tab,        view,           {0} },
	{ MODKEY,                    XKB_KEY_q,          killclient,     {0} },
	{ MODKEY,                    XKB_KEY_g,          togglegaps,     {0} },
    { MODKEY,                    XKB_KEY_w,          spawn,          {.v = browser } },
    { MODKEY,                    XKB_KEY_e,          spawn,          {.v = email } },
    { MODKEY,                    XKB_KEY_n,          spawn,          {.v = notes } },
    { MODKEY,                    XKB_KEY_f,          spawn,          {.v = fileManager } },
    { MODKEY,                    XKB_KEY_p,          spawn,          {.v = passwords } },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_N,          spawn,          {.v = news } },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_B,          spawn,          {.v = books } },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_C,          spawn,          {.v = communicator } },
    { MODKEY,                    XKB_KEY_Escape,     spawn,          {.v = lockscreen } },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Escape,     spawn,          SHCMD("powermenu")},
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_P,          spawn,          SHCMD("colorpicker")},
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_W,          spawn,          SHCMD("wallpaper open")},
    { MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_w,          spawn,          SHCMD("wallpaper random") },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_S,          spawn,          SHCMD("screenshot") },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_M,          spawn,          SHCMD("mpvq play") },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_A,          spawn,          SHCMD("mpvq addclip") },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_asciitilde, spawn,          SHCMD("bemenubookmarks select_browser") },
    { MODKEY,                    XKB_KEY_grave,      spawn,          SHCMD("bemenubookmarks select") },
    { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_b,          spawn,          SHCMD("bemenubookmarks add") },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_U,          spawn,          SHCMD("bemenuunicode") },
    { 0,                         XKB_KEY_Print,      spawn,          SHCMD("screenshot") },
    { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_p,          spawn,          SHCMD("mpc toggle && pkill -RTMIN+3 someblocks") },
    { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_period,     spawn,          SHCMD("mpc next && pkill -RTMIN+3 someblocks") },
    { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_comma,      spawn,          SHCMD("mpc prev && pkill -RTMIN+3 someblocks") },
    { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_equal,      spawn,          SHCMD("mpc volume +5") },
    { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_minus,      spawn,          SHCMD("mpc volume -5") },
    { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_s,          spawn,          SHCMD("mpc pause && mpc seek 0 && pkill -RTMIN+3 someblocks") },
	{ MODKEY,                    XKB_KEY_t,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                    XKB_KEY_v,          setlayout,      {.v = &layouts[1]} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_space,      togglefloating, {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_F,          togglefullscreen, {0} },
	{ MODKEY,                    XKB_KEY_c,          movecenter,     {0} },
    { 0,                         XKB_KEY_XF86AudioMute,          spawn,   SHCMD("wpctl  set-mute   @DEFAULT_AUDIO_SINK@ toggle && pkill -RTMIN+9 someblocks") },
	{ 0,                         XKB_KEY_XF86AudioLowerVolume,   spawn,   SHCMD("wpctl  set-volume @DEFAULT_AUDIO_SINK@ 5%- && pkill -RTMIN+9 someblocks"   ) },
	{ 0,                         XKB_KEY_XF86AudioRaiseVolume,   spawn,   SHCMD("wpctl  set-volume @DEFAULT_AUDIO_SINK@ 5%+ && pkill -RTMIN+9 someblocks"   ) },
    { 0,                         XKB_KEY_XF86AudioPlay,          spawn,   SHCMD("playerctl play-pause") },
    { 0,                         XKB_KEY_XF86AudioNext,          spawn,   SHCMD("playerctl next") },
    { 0,                         XKB_KEY_XF86AudioPrev,          spawn,   SHCMD("playerctl previous") },
	{ MODKEY,                    XKB_KEY_0,          view,           {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright, tag,            {.ui = ~0} },
	{ MODKEY,                    XKB_KEY_comma,      focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    XKB_KEY_period,     focusmon,       {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_less,       tagmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_greater,    tagmon,         {.i = WLR_DIRECTION_RIGHT} },
	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                     0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                         1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                 2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                     3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                    4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                  6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                   7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                  8),
	{ MODKEY,                    XKB_KEY_F11,        togglepassthrough, {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Q,          quit,           {0} },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
	/* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
	 * do not remove them.
	 */
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ ClkLtSymbol, 0,      BTN_LEFT,   setlayout,      {.v = &layouts[0]} },
	{ ClkLtSymbol, 0,      BTN_RIGHT,  setlayout,      {.v = &layouts[1]} },
	{ ClkTitle,    0,      BTN_MIDDLE, zoom,           {0} },
	{ ClkStatus,   0,      BTN_MIDDLE, spawn,          {.v = termcmd} },
	{ ClkClient,   MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ ClkClient,   MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ ClkClient,   MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
	{ ClkTagBar,   0,      BTN_LEFT,   view,           {0} },
	{ ClkTagBar,   0,      BTN_RIGHT,  toggleview,     {0} },
	{ ClkTagBar,   MODKEY, BTN_LEFT,   tag,            {0} },
	{ ClkTagBar,   MODKEY, BTN_RIGHT,  toggletag,      {0} },
};
