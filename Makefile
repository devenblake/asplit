include config.mk

all: asplit

%:
	${CC} -o $* $*.c

clean:
	${RM} asplit

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f asplit ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/asplit
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	cp -f asplit.1 ${DESTDIR}${MANPREFIX}/man1/asplit.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/asplit.1

uninstall:
	${RM} ${DESTDIR}${PREFIX}/bin/asplit
	${RM} ${DESTDIR}${MANPREFIX}/man1/asplit.1

.PHONY: all clean install uninstall
