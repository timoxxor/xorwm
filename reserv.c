void
drawbar(Monitor *m)
{
	int x, w, tw = 0, n = 0, scm, etwl = 0, etwr = 0;
	int boxs = drw->fonts->h / 9;
	int boxw = drw->fonts->h / 6 + 2;
	unsigned int i, occ = 0, urg = 0;
	Client *c;

	if (!m->showbar)
		return;
	
	/*if (m == selmon) { 
		drw_setscheme(drw, scheme[SchemeNorm]);
		tw = TEXTW(stext) - lrpad + 2; 
		drw_text(drw, m->ww - tw, 0, tw, bh, 0, stext, 0);
	}*/

	for (c = m->clients; c; c = c->next) {
		if (ISVISIBLE(c))
			n++;
		occ |= c->tags;
		if (c->isurgent)
			urg |= c->tags;
	}
	/*x = 0;
	for (i = 0; i < LENGTH(tags); i++) {
		w = TEXTW(tags[i]);
		drw_setscheme(drw, scheme[m->tagset[m->seltags] & 1 << i ? SchemeSel : SchemeNorm]);
		drw_text(drw, x, 0, w, bh, lrpad / 2, tags[i], urg & 1 << i);
		if (occ & 1 << i)
			drw_rect(drw, x + boxs, boxs, boxw, boxw,
				m == selmon && selmon->sel && selmon->sel->tags & 1 << i,
				urg & 1 << i);
		x += w;
	}*/

	//w = TEXTW(m->ltsymbol);
	drw_setscheme(drw, scheme[SchemeNorm]);
	x = drw_text(drw, x, 0, w, bh, lrpad / 2, m->ltsymbol, 0);

	if ((w = m->ww - tw - x) > bh) {
		if (n > 0) {
			int remainder = w % n;
			int tabw = (1.0 / (double)n) * w + 1;
			for (c = m->clients; c; c = c->next) {
				if (!ISVISIBLE(c))
					continue;
				if (m->sel == c)
					scm = SchemeSel;
				else if (HIDDEN(c))
					scm = SchemeHid;
				else
					scm = SchemeNorm;
				drw_setscheme(drw, scheme[scm]);

				if (remainder >= 0) {
					if (remainder == 0) {
						tabw--;
					}
					remainder--;
				}
				drw_text(drw, x, 0, tabw, bh, lrpad / 2, c->name, 0);
				x += tabw;
			}
		} else {
			drw_setscheme(drw, scheme[SchemeNorm]);
			drw_rect(drw, x, 0, w, bh, 1, 1);
		}
	}
	m->bt = n;
	m->btw = w;
	drw_map(drw, m->barwin, 0, 0, m->ww, bh);

	if (m == selmon) { /* extra status is only drawn on selected monitor */
		drw_setscheme(drw, scheme[SchemeNorm]);
		/* clear default bar draw buffer by drawing a blank rectangle */
		drw_rect(drw, 0, 0, m->ww, bh, 1, 1);
		etwr = TEXTW(estextr) - lrpad + 2; /* 2px right padding */
		drw_text(drw, m->ww - etwr, 0, etwr, bh, 0, estextr, 0);
		etwl = TEXTW(estextl);
		drw_text(drw, 0, 0, etwl, bh, 0, estextl, 0);
		drw_map(drw, m->extrabarwin, 0, 0, m->ww, bh);
	}
}


