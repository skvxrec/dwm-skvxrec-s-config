void
movestack(const Arg *arg) {
	Client *c = NULL, *p = NULL, *pc = NULL, *i;

	if(arg->i > 0) {
		for(c = selmon->sel->next; c && (!ISVISIBLE(c) || c->isfloating); c = c->next);
		if(!c)
			for(c = selmon->clients; c && (!ISVISIBLE(c) || c->isfloating); c = c->next);
	} else {
		for(i = selmon->clients; i != selmon->sel; i = i->next)
			if(ISVISIBLE(i) && !i->isfloating)
				c = i;
		if(!c)
			for(; i; i = i->next)
				if(ISVISIBLE(i) && !i->isfloating)
					c = i;
	}
	for(i = selmon->clients; i && (!p || !pc); i = i->next) {
		if(i->next == selmon->sel) p = i;
		if(i->next == c) pc = i;
	}
	if(c && c != selmon->sel) {
		Client *temp = selmon->sel->next==c?c->next:selmon->sel->next;
		selmon->sel->next = c->next==selmon->sel?c:c->next;
		c->next = temp;
		if(p && p != c) p->next = c;
		if(pc && pc != selmon->sel) pc->next = selmon->sel;
		if(selmon->sel == selmon->clients) selmon->clients = c;
		else if(c == selmon->clients) selmon->clients = selmon->sel;
		arrange(selmon);
	}
}
