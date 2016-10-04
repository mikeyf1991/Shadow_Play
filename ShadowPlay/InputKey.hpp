#ifndef INPUT_KEY_HPP
#define INPUT_KEY_HPP

enum InputKey // Class for handling all the invidual keys to press in the game
{
	a,            ///< The A key
	b,            ///< The B key
	c,            ///< The C key
	d,            ///< The D key
	e,            ///< The E key
	f,            ///< The F key
	g,            ///< The G key
	h,            ///< The H key
	i,            ///< The I key
	j,            ///< The J key
	k,            ///< The K key
	l,            ///< The L key
	m,            ///< The M key
	n,            ///< The N key
	o,            ///< The O key
	p,            ///< The P key
	q,            ///< The Q key
	r,            ///< The R key
	s,            ///< The S key
	t,            ///< The T key
	u,            ///< The U key
	v,            ///< The V key
	w,            ///< The W key
	x,            ///< The X key
	y,            ///< The Y key
	z,            ///< The Z key
	num_0,         ///< The 0 key
	num_1,         ///< The 1 key
	num_2,         ///< The 2 key
	num_3,         ///< The 3 key
	num_4,         ///< The 4 key
	num_5,         ///< The 5 key
	num_6,         ///< The 6 key
	num_7,         ///< The 7 key
	num_8,         ///< The 8 key
	num_9,         ///< The 9 key
	escape,       ///< The Escape key
	l_control,     ///< The left Control key
	l_shift,       ///< The left Shift key
	l_alt,         ///< The left Alt key
	l_system,      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
	r_control,     ///< The right Control key
	r_shift,       ///< The right Shift key
	r_alt,         ///< The right Alt key
	r_system,      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
	menu,         ///< The Menu key
	l_bracket,     ///< The [ key
	r_bracket,     ///< The ] key
	semi_colon,    ///< The ; key
	comma,        ///< The , key
	period,       ///< The . key
	quote,        ///< The ' key
	slash,        ///< The / key
	back_slash,    ///< The \ key
	tilde,        ///< The ~ key
	equal,        ///< The = key
	dash,         ///< The - key
	space,        ///< The Space key
	return_key,       ///< The Return key
	back,         ///< The Backspace key
	tab,          ///< The Tabulation key
	page_up,       ///< The Page up key
	page_down,     ///< The Page down key
	end,          ///< The End key
	home,         ///< The Home key
	insert,       ///< The Insert key
	delete_key,       ///< The Delete key
	add,          ///< +
	subtract,     ///< -
	multiply,     ///< *
	divide,       ///< /
	left,         ///< Left arrow
	right,        ///< Right arrow
	up,           ///< Up arrow
	down,         ///< Down arrow
	numpad_0,      ///< The numpad 0 key
	numpad_1,      ///< The numpad 1 key
	numpad_2,      ///< The numpad 2 key
	numpad_3,      ///< The numpad 3 key
	numpad_4,      ///< The numpad 4 key
	numpad_5,      ///< The numpad 5 key
	numpad_6,      ///< The numpad 6 key
	numpad_7,      ///< The numpad 7 key
	numpad_8,      ///< The numpad 8 key
	numpad_9,      ///< The numpad 9 key
	f_1,           ///< The F1 key
	f_2,           ///< The F2 key
	f_3,           ///< The F3 key
	f_4,           ///< The F4 key
	f_5,           ///< The F5 key
	f_6,           ///< The F6 key
	f_7,           ///< The F7 key
	f_8,           ///< The F8 key
	f_9,           ///< The F8 key
	f_10,          ///< The F10 key
	f_11,          ///< The F11 key
	f_12,          ///< The F12 key
	f_13,          ///< The F13 key
	f_14,          ///< The F14 key
	f_15,          ///< The F15 key
	pause,        ///< The Pause key

	key_count      ///< Keep last -- the total number of keyboard keys
};

#endif